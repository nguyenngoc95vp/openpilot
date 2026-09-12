#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_4017716193843905404);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5882689715107181908);
void car_H_mod_fun(double *state, double *out_2846716468053487474);
void car_f_fun(double *state, double dt, double *out_8601976082523866967);
void car_F_fun(double *state, double dt, double *out_3649835622450013063);
void car_h_25(double *state, double *unused, double *out_326503409893567898);
void car_H_25(double *state, double *unused, double *out_2056975357131177366);
void car_h_24(double *state, double *unused, double *out_446324488512940374);
void car_H_24(double *state, double *unused, double *out_4234189780738327339);
void car_h_30(double *state, double *unused, double *out_8982523379132132536);
void car_H_30(double *state, double *unused, double *out_4575308315638425993);
void car_h_26(double *state, double *unused, double *out_6427434643133086395);
void car_H_26(double *state, double *unused, double *out_5361501326891977967);
void car_h_27(double *state, double *unused, double *out_4675169857767277747);
void car_H_27(double *state, double *unused, double *out_2400545003838001082);
void car_h_29(double *state, double *unused, double *out_4462547426916573435);
void car_H_29(double *state, double *unused, double *out_5085539659952818177);
void car_h_28(double *state, double *unused, double *out_7807086048787755258);
void car_H_28(double *state, double *unused, double *out_3140642883287603);
void car_h_31(double *state, double *unused, double *out_5199554026657455215);
void car_H_31(double *state, double *unused, double *out_4735293224658626491);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}