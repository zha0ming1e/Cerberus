//
// Created by shuoy on 7/19/21.
//

#ifndef VILENS_ESTIMATOR_H
#define VILENS_ESTIMATOR_H
#pragma once
#include <thread>
#include <mutex>
#include <std_msgs/Header.h>
#include <std_msgs/Float32.h>
#include <ceres/ceres.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <opencv2/core/eigen.hpp>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

#include "../utils/parameters.h"
#include "../featureTracker/feature_manager.h"
#include "../featureTracker/feature_tracker.h"
#include "../factor/imu_factor.h"
#include "../factor/pose_local_parameterization.h"
#include "../factor/marginalization_factor.h"
#include "../factor/projectionTwoFrameOneCamFactor.h"
#include "../factor/projectionTwoFrameTwoCamFactor.h"
#include "../factor/projectionOneFrameTwoCamFactor.h"

#include "../initial/solve_5pts.h"
#include "../initial/initial_sfm.h"
#include "../initial/initial_alignment.h"
#include "../initial/initial_ex_rotation.h"

class Estimator {
public:
    Estimator();
    ~Estimator();
    void setParameter();

    // interface
    void inputImage(double t, const cv::Mat &_img, const cv::Mat &_img1 = cv::Mat());
    void inputIMU(double t, const Vector3d &linearAcceleration, const Vector3d &angularVelocity);
    void inputLeg(double t, const VectorXd &jointAngles, const VectorXd &footForces);
    void inputFeature(double t, const map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> &featureFrame);

    void processMeasurements();
    void initFirstPose(Eigen::Vector3d p, Eigen::Matrix3d r);
    void processIMU(double t, double dt, const Vector3d &linear_acceleration, const Vector3d &angular_velocity);
    // // most important function, trigger optimization
    void processImage(const map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> &image, const double header);


    // internal
    void clearState();
    bool IMUAvailable(double t);
    bool getIMUInterval(double t0, double t1, vector<pair<double, Eigen::Vector3d>> &accVector,
                        vector<pair<double, Eigen::Vector3d>> &gyrVector);
    void initFirstIMUPose(vector<pair<double, Eigen::Vector3d>> &accVector);
    void fastPredictIMU(double t, Eigen::Vector3d linear_acceleration, Eigen::Vector3d angular_velocity);
    void updateLatestStates();  // readout latest states
    // // most important internal functions
    void optimization();
    void slideWindow();
    void slideWindowNew();
    void slideWindowOld();
    // // convert between ceres optimization variables and system states
    void vector2double();
    void double2vector();


    enum SolverFlag
    {
        INITIAL,
        NON_LINEAR
    };

    enum MarginalizationFlag
    {
        MARGIN_OLD = 0,
        MARGIN_SECOND_NEW = 1
    };

    std::mutex mProcess;
    std::mutex mBuf;
    std::mutex mPropagate;
    queue<pair<double, Eigen::Vector3d>> accBuf;
    queue<pair<double, Eigen::Vector3d>> gyrBuf;

    std::vector<queue<pair<double, Eigen::Vector3d>>> legAngBufList;
    std::vector<queue<pair<double, Eigen::Vector3d>>> footForceBufList;

    queue<pair<double, map<int, vector<pair<int, Eigen::Matrix<double, 7, 1> > > > > > featureBuf;
    double prevTime, curTime;
    bool openExEstimation;

    std::thread trackThread;
    std::thread processThread;

    FeatureTracker featureTracker;

    SolverFlag solver_flag;
    MarginalizationFlag  marginalization_flag;
    Vector3d g;


    // the actual solved results, Ps Vs Rs are the pose of the imu link 
    Matrix3d ric[2];
    Vector3d tic[2];
    Vector3d        Ps[(WINDOW_SIZE + 1)];
    Vector3d        Vs[(WINDOW_SIZE + 1)];
    Matrix3d        Rs[(WINDOW_SIZE + 1)];
    Vector3d        Bas[(WINDOW_SIZE + 1)];
    Vector3d        Bgs[(WINDOW_SIZE + 1)];
    double td;

    Matrix3d back_R0, last_R, last_R0;
    Vector3d back_P0, last_P, last_P0;
    double Headers[(WINDOW_SIZE + 1)];

    IntegrationBase *pre_integrations[(WINDOW_SIZE + 1)];
    Vector3d acc_0, gyr_0;

    vector<double> dt_buf[(WINDOW_SIZE + 1)];
    vector<Vector3d> linear_acceleration_buf[(WINDOW_SIZE + 1)];
    vector<Vector3d> angular_velocity_buf[(WINDOW_SIZE + 1)];

    int frame_count;
    int sum_of_outlier, sum_of_back, sum_of_front, sum_of_invalid;
    int inputImageCnt;

    FeatureManager f_manager;
//    MotionEstimator m_estimator;
    InitialEXRotation initial_ex_rotation;

    bool first_imu;
    bool is_valid, is_key;
    bool failure_occur;

    vector<Vector3d> point_cloud;
    vector<Vector3d> margin_cloud;
    vector<Vector3d> key_poses;
    double initial_timestamp;


    // variable of optimization
    double para_Pose[WINDOW_SIZE + 1][SIZE_POSE];
    double para_SpeedBias[WINDOW_SIZE + 1][SIZE_SPEEDBIAS];
    double para_Feature[NUM_OF_F][SIZE_FEATURE];
    double para_Ex_Pose[2][SIZE_POSE];
    double para_Retrive_Pose[SIZE_POSE];
    double para_Td[1][1];
    double para_Tr[1][1];

    int loop_window_index;

    MarginalizationInfo *last_marginalization_info;
    vector<double *> last_marginalization_parameter_blocks;

    map<double, ImageFrame> all_image_frame;
    IntegrationBase *tmp_pre_integration;

    Eigen::Vector3d initP;
    Eigen::Matrix3d initR;

    double latest_time;  // used in fastPredictIMU to get dt from last function call
    // used in fastPredictIMU and updateLatestStates
    Eigen::Vector3d latest_P, latest_V, latest_Ba, latest_Bg, latest_acc_0, latest_gyr_0;
    Eigen::Quaterniond latest_Q;

    bool initFirstPoseFlag;
    bool initThreadFlag;
};


#endif //VILENS_ESTIMATOR_H
