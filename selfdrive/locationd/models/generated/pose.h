#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1557390242987403893);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4141160926477888419);
void pose_H_mod_fun(double *state, double *out_4604524654630855510);
void pose_f_fun(double *state, double dt, double *out_8144335749808985700);
void pose_F_fun(double *state, double dt, double *out_7938872027079426501);
void pose_h_4(double *state, double *unused, double *out_3382593130953121745);
void pose_H_4(double *state, double *unused, double *out_3406577172747957406);
void pose_h_10(double *state, double *unused, double *out_3810751197064733105);
void pose_H_10(double *state, double *unused, double *out_5824195032039914110);
void pose_h_13(double *state, double *unused, double *out_774085760433495807);
void pose_H_13(double *state, double *unused, double *out_194303347415624605);
void pose_h_14(double *state, double *unused, double *out_6021362742836865981);
void pose_H_14(double *state, double *unused, double *out_556663683591527123);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}