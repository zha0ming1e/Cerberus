//
// Created by shuoy on 8/10/21.
//

#include "A1Kinematics.h"

Eigen::Vector3d A1Kinematics::fk(Eigen::Vector3d q, Eigen::VectorXd rho_opt, Eigen::VectorXd rho_fix) {
    Eigen::Vector3d out;
    autoFunc_fk_pf_pos(q.data(), rho_opt.data(), rho_fix.data(), out.data());
    return out;
}

Eigen::Matrix3d A1Kinematics::jac(Eigen::Vector3d q, Eigen::VectorXd rho_opt, Eigen::VectorXd rho_fix) {
    Eigen::Matrix3d mtx;
    autoFunc_d_fk_dt(q.data(), rho_opt.data(), rho_fix.data(), mtx.data());
    return mtx;
}

Eigen::Matrix<double, 3, RHO_OPT_SIZE> A1Kinematics::dfk_drho(Eigen::Vector3d q, Eigen::VectorXd rho_opt, Eigen::VectorXd rho_fix) {
    Eigen::Matrix<double, 3, RHO_OPT_SIZE> mtx;
    autoFunc_d_fk_drho(q.data(), rho_opt.data(), rho_fix.data(), mtx.data());
    return mtx;
}

Eigen::Matrix<double, 9, 3> A1Kinematics::dJ_dq(Eigen::Vector3d q, Eigen::VectorXd rho_opt, Eigen::VectorXd rho_fix) {
    Eigen::Matrix<double, 9, 3> mtx;
    autoFunc_dJ_dt(q.data(), rho_opt.data(), rho_fix.data(), mtx.data());
    return mtx;
}

Eigen::Matrix<double, 9, RHO_OPT_SIZE> A1Kinematics::dJ_drho(Eigen::Vector3d q, Eigen::VectorXd rho_opt, Eigen::VectorXd rho_fix) {
    Eigen::Matrix<double, 9, RHO_OPT_SIZE> mtx;
    autoFunc_dJ_drho(q.data(), rho_opt.data(), rho_fix.data(), mtx.data());
    return mtx;
}


// functions generated by matlab
void A1Kinematics::autoFunc_fk_pf_pos(const double in1[3], const double in2[RHO_OPT_SIZE], const double
in3[RHO_FIX_SIZE], double p_bf[3])
{
    double cz = in2[0];
    double p_bf_tmp;
    double t10;
    double t12;
    double t5;
    double t6;
    double t7;
    double t8;
    double t9;
    //     This function was generated by the Symbolic Math Toolbox version 8.7.
    //     12-Jan-2022 10:52:25
    t5 = std::cos(in1[0]);
    t6 = std::cos(in1[1]);
    t7 = std::cos(in1[2]);
    t8 = std::sin(in1[0]);
    t9 = std::sin(in1[1]);
    t10 = std::sin(in1[2]);
    t12 = std::sin(in1[1] + in1[2]);
    p_bf[0] = ((in3[0] - cz * t12) - in3[4] * t12) - in3[3] * t9;
    p_bf[1] =
            (((((in3[1] + in3[2] * t5) + in3[3] * t6 * t8) + cz * t6 * t7 * t8) -
              cz * t8 * t9 * t10) +
             in3[4] * t6 * t7 * t8) -
            in3[4] * t8 * t9 * t10;
    t12 = cz * t5;
    p_bf_tmp = in3[4] * t5;
    p_bf[2] =
            ((((in3[2] * t8 - in3[3] * t5 * t6) - t12 * t6 * t7) + t12 * t9 * t10) -
             p_bf_tmp * t6 * t7) +
            p_bf_tmp * t9 * t10;
}

void A1Kinematics::autoFunc_d_fk_dt(const double in1[3], const double in2[RHO_OPT_SIZE], const double
in3[RHO_FIX_SIZE], double jacobian[9])
{
    double cz = in2[0];
    double b_jacobian_tmp;
    double jacobian_tmp;
    double t10;
    double t11;
    double t12;
    double t13;
    double t18;
    double t5;
    double t6;
    double t7;
    double t8;
    double t9;
    //     This function was generated by the Symbolic Math Toolbox version 8.7.
    //     12-Jan-2022 10:52:25
    t5 = std::cos(in1[0]);
    t6 = std::cos(in1[1]);
    t7 = std::cos(in1[2]);
    t8 = std::sin(in1[0]);
    t9 = std::sin(in1[1]);
    t10 = std::sin(in1[2]);
    t11 = cz + in3[4];
    t12 = in1[1] + in1[2];
    t13 = std::cos(t12);
    t12 = std::sin(t12);
    t18 = (in3[3] * t9 + cz * t12) + in3[4] * t12;
    jacobian[0] = 0.0;
    jacobian_tmp = cz * t5;
    b_jacobian_tmp = in3[4] * t5;
    jacobian[1] = ((((-in3[2] * t8 + in3[3] * t5 * t6) + jacobian_tmp * t6 * t7) -
                    jacobian_tmp * t9 * t10) +
                   b_jacobian_tmp * t6 * t7) -
                  b_jacobian_tmp * t9 * t10;
    jacobian_tmp = in3[3] * t6;
    jacobian[2] = ((((in3[2] * t5 + jacobian_tmp * t8) + cz * t6 * t7 * t8) -
                    cz * t8 * t9 * t10) +
                   in3[4] * t6 * t7 * t8) -
                  in3[4] * t8 * t9 * t10;
    jacobian[3] = (-cz * t13 - in3[4] * t13) - jacobian_tmp;
    jacobian[4] = -t8 * t18;
    jacobian[5] = t5 * t18;
    jacobian[6] = -t11 * t13;
    jacobian[7] = -t8 * t11 * t12;
    jacobian[8] = t5 * t11 * t12;
}

void A1Kinematics::autoFunc_d_fk_drho(const double in1[3], const double in2[RHO_OPT_SIZE], const double
in3[RHO_FIX_SIZE], double d_fk_drho[D_FK_DRHO_SIZE])
{
    double t5;
    double t6;
    //     This function was generated by the Symbolic Math Toolbox version 8.7.
    //     12-Jan-2022 10:52:25
    t5 = in1[1] + in1[2];
    t6 = std::cos(t5);
    d_fk_drho[0] = -std::sin(t5);
    d_fk_drho[1] = t6 * std::sin(in1[0]);
    d_fk_drho[2] = -t6 * std::cos(in1[0]);
}

void A1Kinematics::autoFunc_dJ_dt(const double in1[3], const double in2[RHO_OPT_SIZE], const double in3[RHO_FIX_SIZE],
                    double dJ_dq[27])
{
    double cz = in2[0];
    double b_dJ_dq_tmp;
    double dJ_dq_tmp;
    double t10;
    double t11;
    double t12;
    double t13;
    double t14;
    double t21;
    double t22;
    double t26;
    double t29;
    double t33;
    double t34;
    double t5;
    double t6;
    double t7;
    double t8;
    double t9;
    //     This function was generated by the Symbolic Math Toolbox version 8.7.
    //     12-Jan-2022 10:52:25
    t5 = std::cos(in1[0]);
    t6 = std::cos(in1[1]);
    t7 = std::cos(in1[2]);
    t8 = std::sin(in1[0]);
    t9 = std::sin(in1[1]);
    t10 = std::sin(in1[2]);
    t11 = cz + in3[4];
    t12 = in1[1] + in1[2];
    t13 = in3[3] * t6;
    t14 = std::cos(t12);
    t12 = std::sin(t12);
    t21 = t11 * t12;
    t22 = t5 * t11 * t14;
    t26 = -(t8 * t11 * t14);
    t29 = (in3[3] * t9 + cz * t12) + in3[4] * t12;
    t12 = (t13 + cz * t14) + in3[4] * t14;
    t11 = -(t5 * t21);
    t14 = -(t8 * t21);
    t33 = -(t5 * t29);
    t34 = -(t8 * t29);
    dJ_dq[0] = 0.0;
    dJ_dq[1] =
            ((((-in3[2] * t5 - t8 * t13) - cz * t6 * t7 * t8) + cz * t8 * t9 * t10) -
             in3[4] * t6 * t7 * t8) +
            in3[4] * t8 * t9 * t10;
    dJ_dq_tmp = cz * t5;
    b_dJ_dq_tmp = in3[4] * t5;
    dJ_dq[2] = ((((-in3[2] * t8 + t5 * t13) + dJ_dq_tmp * t6 * t7) -
                 dJ_dq_tmp * t9 * t10) +
                b_dJ_dq_tmp * t6 * t7) -
               b_dJ_dq_tmp * t9 * t10;
    dJ_dq[3] = 0.0;
    dJ_dq[4] = t33;
    dJ_dq[5] = t34;
    dJ_dq[6] = 0.0;
    dJ_dq[7] = t11;
    dJ_dq[8] = t14;
    dJ_dq[9] = 0.0;
    dJ_dq[10] = t33;
    dJ_dq[11] = t34;
    dJ_dq[12] = t29;
    dJ_dq[13] = -t8 * t12;
    dJ_dq[14] = t5 * t12;
    dJ_dq[15] = t21;
    dJ_dq[16] = t26;
    dJ_dq[17] = t22;
    dJ_dq[18] = 0.0;
    dJ_dq[19] = t11;
    dJ_dq[20] = t14;
    dJ_dq[21] = t21;
    dJ_dq[22] = t26;
    dJ_dq[23] = t22;
    dJ_dq[24] = t21;
    dJ_dq[25] = t26;
    dJ_dq[26] = t22;
}

void A1Kinematics::autoFunc_dJ_drho(const double in1[3], const double in2[RHO_OPT_SIZE], const double in3[RHO_FIX_SIZE],
                      double dJ_drho[D_J_DRHO_SIZE])
{
    double cz = in2[0];
    double t10;
    double t5;
    double t6;
    double t7;
    double t8;
    //     This function was generated by the Symbolic Math Toolbox version 8.7.
    //     12-Jan-2022 10:52:25
    t5 = std::cos(in1[0]);
    t6 = std::sin(in1[0]);
    t7 = in1[1] + in1[2];
    t8 = std::cos(t7);
    t7 = std::sin(t7);
    t10 = t6 * t7;
    t7 *= t5;
    dJ_drho[0] = 0.0;
    dJ_drho[1] = t5 * t8;
    dJ_drho[2] = t6 * t8;
    dJ_drho[3] = -t8;
    dJ_drho[4] = -t10;
    dJ_drho[5] = t7;
    dJ_drho[6] = -t8;
    dJ_drho[7] = -t10;
    dJ_drho[8] = t7;

}