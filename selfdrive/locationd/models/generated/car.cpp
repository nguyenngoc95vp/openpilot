#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4017716193843905404) {
   out_4017716193843905404[0] = delta_x[0] + nom_x[0];
   out_4017716193843905404[1] = delta_x[1] + nom_x[1];
   out_4017716193843905404[2] = delta_x[2] + nom_x[2];
   out_4017716193843905404[3] = delta_x[3] + nom_x[3];
   out_4017716193843905404[4] = delta_x[4] + nom_x[4];
   out_4017716193843905404[5] = delta_x[5] + nom_x[5];
   out_4017716193843905404[6] = delta_x[6] + nom_x[6];
   out_4017716193843905404[7] = delta_x[7] + nom_x[7];
   out_4017716193843905404[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5882689715107181908) {
   out_5882689715107181908[0] = -nom_x[0] + true_x[0];
   out_5882689715107181908[1] = -nom_x[1] + true_x[1];
   out_5882689715107181908[2] = -nom_x[2] + true_x[2];
   out_5882689715107181908[3] = -nom_x[3] + true_x[3];
   out_5882689715107181908[4] = -nom_x[4] + true_x[4];
   out_5882689715107181908[5] = -nom_x[5] + true_x[5];
   out_5882689715107181908[6] = -nom_x[6] + true_x[6];
   out_5882689715107181908[7] = -nom_x[7] + true_x[7];
   out_5882689715107181908[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2846716468053487474) {
   out_2846716468053487474[0] = 1.0;
   out_2846716468053487474[1] = 0.0;
   out_2846716468053487474[2] = 0.0;
   out_2846716468053487474[3] = 0.0;
   out_2846716468053487474[4] = 0.0;
   out_2846716468053487474[5] = 0.0;
   out_2846716468053487474[6] = 0.0;
   out_2846716468053487474[7] = 0.0;
   out_2846716468053487474[8] = 0.0;
   out_2846716468053487474[9] = 0.0;
   out_2846716468053487474[10] = 1.0;
   out_2846716468053487474[11] = 0.0;
   out_2846716468053487474[12] = 0.0;
   out_2846716468053487474[13] = 0.0;
   out_2846716468053487474[14] = 0.0;
   out_2846716468053487474[15] = 0.0;
   out_2846716468053487474[16] = 0.0;
   out_2846716468053487474[17] = 0.0;
   out_2846716468053487474[18] = 0.0;
   out_2846716468053487474[19] = 0.0;
   out_2846716468053487474[20] = 1.0;
   out_2846716468053487474[21] = 0.0;
   out_2846716468053487474[22] = 0.0;
   out_2846716468053487474[23] = 0.0;
   out_2846716468053487474[24] = 0.0;
   out_2846716468053487474[25] = 0.0;
   out_2846716468053487474[26] = 0.0;
   out_2846716468053487474[27] = 0.0;
   out_2846716468053487474[28] = 0.0;
   out_2846716468053487474[29] = 0.0;
   out_2846716468053487474[30] = 1.0;
   out_2846716468053487474[31] = 0.0;
   out_2846716468053487474[32] = 0.0;
   out_2846716468053487474[33] = 0.0;
   out_2846716468053487474[34] = 0.0;
   out_2846716468053487474[35] = 0.0;
   out_2846716468053487474[36] = 0.0;
   out_2846716468053487474[37] = 0.0;
   out_2846716468053487474[38] = 0.0;
   out_2846716468053487474[39] = 0.0;
   out_2846716468053487474[40] = 1.0;
   out_2846716468053487474[41] = 0.0;
   out_2846716468053487474[42] = 0.0;
   out_2846716468053487474[43] = 0.0;
   out_2846716468053487474[44] = 0.0;
   out_2846716468053487474[45] = 0.0;
   out_2846716468053487474[46] = 0.0;
   out_2846716468053487474[47] = 0.0;
   out_2846716468053487474[48] = 0.0;
   out_2846716468053487474[49] = 0.0;
   out_2846716468053487474[50] = 1.0;
   out_2846716468053487474[51] = 0.0;
   out_2846716468053487474[52] = 0.0;
   out_2846716468053487474[53] = 0.0;
   out_2846716468053487474[54] = 0.0;
   out_2846716468053487474[55] = 0.0;
   out_2846716468053487474[56] = 0.0;
   out_2846716468053487474[57] = 0.0;
   out_2846716468053487474[58] = 0.0;
   out_2846716468053487474[59] = 0.0;
   out_2846716468053487474[60] = 1.0;
   out_2846716468053487474[61] = 0.0;
   out_2846716468053487474[62] = 0.0;
   out_2846716468053487474[63] = 0.0;
   out_2846716468053487474[64] = 0.0;
   out_2846716468053487474[65] = 0.0;
   out_2846716468053487474[66] = 0.0;
   out_2846716468053487474[67] = 0.0;
   out_2846716468053487474[68] = 0.0;
   out_2846716468053487474[69] = 0.0;
   out_2846716468053487474[70] = 1.0;
   out_2846716468053487474[71] = 0.0;
   out_2846716468053487474[72] = 0.0;
   out_2846716468053487474[73] = 0.0;
   out_2846716468053487474[74] = 0.0;
   out_2846716468053487474[75] = 0.0;
   out_2846716468053487474[76] = 0.0;
   out_2846716468053487474[77] = 0.0;
   out_2846716468053487474[78] = 0.0;
   out_2846716468053487474[79] = 0.0;
   out_2846716468053487474[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8601976082523866967) {
   out_8601976082523866967[0] = state[0];
   out_8601976082523866967[1] = state[1];
   out_8601976082523866967[2] = state[2];
   out_8601976082523866967[3] = state[3];
   out_8601976082523866967[4] = state[4];
   out_8601976082523866967[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8601976082523866967[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8601976082523866967[7] = state[7];
   out_8601976082523866967[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3649835622450013063) {
   out_3649835622450013063[0] = 1;
   out_3649835622450013063[1] = 0;
   out_3649835622450013063[2] = 0;
   out_3649835622450013063[3] = 0;
   out_3649835622450013063[4] = 0;
   out_3649835622450013063[5] = 0;
   out_3649835622450013063[6] = 0;
   out_3649835622450013063[7] = 0;
   out_3649835622450013063[8] = 0;
   out_3649835622450013063[9] = 0;
   out_3649835622450013063[10] = 1;
   out_3649835622450013063[11] = 0;
   out_3649835622450013063[12] = 0;
   out_3649835622450013063[13] = 0;
   out_3649835622450013063[14] = 0;
   out_3649835622450013063[15] = 0;
   out_3649835622450013063[16] = 0;
   out_3649835622450013063[17] = 0;
   out_3649835622450013063[18] = 0;
   out_3649835622450013063[19] = 0;
   out_3649835622450013063[20] = 1;
   out_3649835622450013063[21] = 0;
   out_3649835622450013063[22] = 0;
   out_3649835622450013063[23] = 0;
   out_3649835622450013063[24] = 0;
   out_3649835622450013063[25] = 0;
   out_3649835622450013063[26] = 0;
   out_3649835622450013063[27] = 0;
   out_3649835622450013063[28] = 0;
   out_3649835622450013063[29] = 0;
   out_3649835622450013063[30] = 1;
   out_3649835622450013063[31] = 0;
   out_3649835622450013063[32] = 0;
   out_3649835622450013063[33] = 0;
   out_3649835622450013063[34] = 0;
   out_3649835622450013063[35] = 0;
   out_3649835622450013063[36] = 0;
   out_3649835622450013063[37] = 0;
   out_3649835622450013063[38] = 0;
   out_3649835622450013063[39] = 0;
   out_3649835622450013063[40] = 1;
   out_3649835622450013063[41] = 0;
   out_3649835622450013063[42] = 0;
   out_3649835622450013063[43] = 0;
   out_3649835622450013063[44] = 0;
   out_3649835622450013063[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3649835622450013063[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3649835622450013063[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3649835622450013063[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3649835622450013063[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3649835622450013063[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3649835622450013063[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3649835622450013063[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3649835622450013063[53] = -9.8100000000000005*dt;
   out_3649835622450013063[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3649835622450013063[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3649835622450013063[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3649835622450013063[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3649835622450013063[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3649835622450013063[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3649835622450013063[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3649835622450013063[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3649835622450013063[62] = 0;
   out_3649835622450013063[63] = 0;
   out_3649835622450013063[64] = 0;
   out_3649835622450013063[65] = 0;
   out_3649835622450013063[66] = 0;
   out_3649835622450013063[67] = 0;
   out_3649835622450013063[68] = 0;
   out_3649835622450013063[69] = 0;
   out_3649835622450013063[70] = 1;
   out_3649835622450013063[71] = 0;
   out_3649835622450013063[72] = 0;
   out_3649835622450013063[73] = 0;
   out_3649835622450013063[74] = 0;
   out_3649835622450013063[75] = 0;
   out_3649835622450013063[76] = 0;
   out_3649835622450013063[77] = 0;
   out_3649835622450013063[78] = 0;
   out_3649835622450013063[79] = 0;
   out_3649835622450013063[80] = 1;
}
void h_25(double *state, double *unused, double *out_326503409893567898) {
   out_326503409893567898[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2056975357131177366) {
   out_2056975357131177366[0] = 0;
   out_2056975357131177366[1] = 0;
   out_2056975357131177366[2] = 0;
   out_2056975357131177366[3] = 0;
   out_2056975357131177366[4] = 0;
   out_2056975357131177366[5] = 0;
   out_2056975357131177366[6] = 1;
   out_2056975357131177366[7] = 0;
   out_2056975357131177366[8] = 0;
}
void h_24(double *state, double *unused, double *out_446324488512940374) {
   out_446324488512940374[0] = state[4];
   out_446324488512940374[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4234189780738327339) {
   out_4234189780738327339[0] = 0;
   out_4234189780738327339[1] = 0;
   out_4234189780738327339[2] = 0;
   out_4234189780738327339[3] = 0;
   out_4234189780738327339[4] = 1;
   out_4234189780738327339[5] = 0;
   out_4234189780738327339[6] = 0;
   out_4234189780738327339[7] = 0;
   out_4234189780738327339[8] = 0;
   out_4234189780738327339[9] = 0;
   out_4234189780738327339[10] = 0;
   out_4234189780738327339[11] = 0;
   out_4234189780738327339[12] = 0;
   out_4234189780738327339[13] = 0;
   out_4234189780738327339[14] = 1;
   out_4234189780738327339[15] = 0;
   out_4234189780738327339[16] = 0;
   out_4234189780738327339[17] = 0;
}
void h_30(double *state, double *unused, double *out_8982523379132132536) {
   out_8982523379132132536[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4575308315638425993) {
   out_4575308315638425993[0] = 0;
   out_4575308315638425993[1] = 0;
   out_4575308315638425993[2] = 0;
   out_4575308315638425993[3] = 0;
   out_4575308315638425993[4] = 1;
   out_4575308315638425993[5] = 0;
   out_4575308315638425993[6] = 0;
   out_4575308315638425993[7] = 0;
   out_4575308315638425993[8] = 0;
}
void h_26(double *state, double *unused, double *out_6427434643133086395) {
   out_6427434643133086395[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5361501326891977967) {
   out_5361501326891977967[0] = 0;
   out_5361501326891977967[1] = 0;
   out_5361501326891977967[2] = 0;
   out_5361501326891977967[3] = 0;
   out_5361501326891977967[4] = 0;
   out_5361501326891977967[5] = 0;
   out_5361501326891977967[6] = 0;
   out_5361501326891977967[7] = 1;
   out_5361501326891977967[8] = 0;
}
void h_27(double *state, double *unused, double *out_4675169857767277747) {
   out_4675169857767277747[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2400545003838001082) {
   out_2400545003838001082[0] = 0;
   out_2400545003838001082[1] = 0;
   out_2400545003838001082[2] = 0;
   out_2400545003838001082[3] = 1;
   out_2400545003838001082[4] = 0;
   out_2400545003838001082[5] = 0;
   out_2400545003838001082[6] = 0;
   out_2400545003838001082[7] = 0;
   out_2400545003838001082[8] = 0;
}
void h_29(double *state, double *unused, double *out_4462547426916573435) {
   out_4462547426916573435[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5085539659952818177) {
   out_5085539659952818177[0] = 0;
   out_5085539659952818177[1] = 1;
   out_5085539659952818177[2] = 0;
   out_5085539659952818177[3] = 0;
   out_5085539659952818177[4] = 0;
   out_5085539659952818177[5] = 0;
   out_5085539659952818177[6] = 0;
   out_5085539659952818177[7] = 0;
   out_5085539659952818177[8] = 0;
}
void h_28(double *state, double *unused, double *out_7807086048787755258) {
   out_7807086048787755258[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3140642883287603) {
   out_3140642883287603[0] = 1;
   out_3140642883287603[1] = 0;
   out_3140642883287603[2] = 0;
   out_3140642883287603[3] = 0;
   out_3140642883287603[4] = 0;
   out_3140642883287603[5] = 0;
   out_3140642883287603[6] = 0;
   out_3140642883287603[7] = 0;
   out_3140642883287603[8] = 0;
}
void h_31(double *state, double *unused, double *out_5199554026657455215) {
   out_5199554026657455215[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4735293224658626491) {
   out_4735293224658626491[0] = 0;
   out_4735293224658626491[1] = 0;
   out_4735293224658626491[2] = 0;
   out_4735293224658626491[3] = 0;
   out_4735293224658626491[4] = 0;
   out_4735293224658626491[5] = 0;
   out_4735293224658626491[6] = 0;
   out_4735293224658626491[7] = 0;
   out_4735293224658626491[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4017716193843905404) {
  err_fun(nom_x, delta_x, out_4017716193843905404);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5882689715107181908) {
  inv_err_fun(nom_x, true_x, out_5882689715107181908);
}
void car_H_mod_fun(double *state, double *out_2846716468053487474) {
  H_mod_fun(state, out_2846716468053487474);
}
void car_f_fun(double *state, double dt, double *out_8601976082523866967) {
  f_fun(state,  dt, out_8601976082523866967);
}
void car_F_fun(double *state, double dt, double *out_3649835622450013063) {
  F_fun(state,  dt, out_3649835622450013063);
}
void car_h_25(double *state, double *unused, double *out_326503409893567898) {
  h_25(state, unused, out_326503409893567898);
}
void car_H_25(double *state, double *unused, double *out_2056975357131177366) {
  H_25(state, unused, out_2056975357131177366);
}
void car_h_24(double *state, double *unused, double *out_446324488512940374) {
  h_24(state, unused, out_446324488512940374);
}
void car_H_24(double *state, double *unused, double *out_4234189780738327339) {
  H_24(state, unused, out_4234189780738327339);
}
void car_h_30(double *state, double *unused, double *out_8982523379132132536) {
  h_30(state, unused, out_8982523379132132536);
}
void car_H_30(double *state, double *unused, double *out_4575308315638425993) {
  H_30(state, unused, out_4575308315638425993);
}
void car_h_26(double *state, double *unused, double *out_6427434643133086395) {
  h_26(state, unused, out_6427434643133086395);
}
void car_H_26(double *state, double *unused, double *out_5361501326891977967) {
  H_26(state, unused, out_5361501326891977967);
}
void car_h_27(double *state, double *unused, double *out_4675169857767277747) {
  h_27(state, unused, out_4675169857767277747);
}
void car_H_27(double *state, double *unused, double *out_2400545003838001082) {
  H_27(state, unused, out_2400545003838001082);
}
void car_h_29(double *state, double *unused, double *out_4462547426916573435) {
  h_29(state, unused, out_4462547426916573435);
}
void car_H_29(double *state, double *unused, double *out_5085539659952818177) {
  H_29(state, unused, out_5085539659952818177);
}
void car_h_28(double *state, double *unused, double *out_7807086048787755258) {
  h_28(state, unused, out_7807086048787755258);
}
void car_H_28(double *state, double *unused, double *out_3140642883287603) {
  H_28(state, unused, out_3140642883287603);
}
void car_h_31(double *state, double *unused, double *out_5199554026657455215) {
  h_31(state, unused, out_5199554026657455215);
}
void car_H_31(double *state, double *unused, double *out_4735293224658626491) {
  H_31(state, unused, out_4735293224658626491);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
