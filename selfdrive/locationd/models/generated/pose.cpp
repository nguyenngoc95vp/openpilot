#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1557390242987403893) {
   out_1557390242987403893[0] = delta_x[0] + nom_x[0];
   out_1557390242987403893[1] = delta_x[1] + nom_x[1];
   out_1557390242987403893[2] = delta_x[2] + nom_x[2];
   out_1557390242987403893[3] = delta_x[3] + nom_x[3];
   out_1557390242987403893[4] = delta_x[4] + nom_x[4];
   out_1557390242987403893[5] = delta_x[5] + nom_x[5];
   out_1557390242987403893[6] = delta_x[6] + nom_x[6];
   out_1557390242987403893[7] = delta_x[7] + nom_x[7];
   out_1557390242987403893[8] = delta_x[8] + nom_x[8];
   out_1557390242987403893[9] = delta_x[9] + nom_x[9];
   out_1557390242987403893[10] = delta_x[10] + nom_x[10];
   out_1557390242987403893[11] = delta_x[11] + nom_x[11];
   out_1557390242987403893[12] = delta_x[12] + nom_x[12];
   out_1557390242987403893[13] = delta_x[13] + nom_x[13];
   out_1557390242987403893[14] = delta_x[14] + nom_x[14];
   out_1557390242987403893[15] = delta_x[15] + nom_x[15];
   out_1557390242987403893[16] = delta_x[16] + nom_x[16];
   out_1557390242987403893[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4141160926477888419) {
   out_4141160926477888419[0] = -nom_x[0] + true_x[0];
   out_4141160926477888419[1] = -nom_x[1] + true_x[1];
   out_4141160926477888419[2] = -nom_x[2] + true_x[2];
   out_4141160926477888419[3] = -nom_x[3] + true_x[3];
   out_4141160926477888419[4] = -nom_x[4] + true_x[4];
   out_4141160926477888419[5] = -nom_x[5] + true_x[5];
   out_4141160926477888419[6] = -nom_x[6] + true_x[6];
   out_4141160926477888419[7] = -nom_x[7] + true_x[7];
   out_4141160926477888419[8] = -nom_x[8] + true_x[8];
   out_4141160926477888419[9] = -nom_x[9] + true_x[9];
   out_4141160926477888419[10] = -nom_x[10] + true_x[10];
   out_4141160926477888419[11] = -nom_x[11] + true_x[11];
   out_4141160926477888419[12] = -nom_x[12] + true_x[12];
   out_4141160926477888419[13] = -nom_x[13] + true_x[13];
   out_4141160926477888419[14] = -nom_x[14] + true_x[14];
   out_4141160926477888419[15] = -nom_x[15] + true_x[15];
   out_4141160926477888419[16] = -nom_x[16] + true_x[16];
   out_4141160926477888419[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4604524654630855510) {
   out_4604524654630855510[0] = 1.0;
   out_4604524654630855510[1] = 0.0;
   out_4604524654630855510[2] = 0.0;
   out_4604524654630855510[3] = 0.0;
   out_4604524654630855510[4] = 0.0;
   out_4604524654630855510[5] = 0.0;
   out_4604524654630855510[6] = 0.0;
   out_4604524654630855510[7] = 0.0;
   out_4604524654630855510[8] = 0.0;
   out_4604524654630855510[9] = 0.0;
   out_4604524654630855510[10] = 0.0;
   out_4604524654630855510[11] = 0.0;
   out_4604524654630855510[12] = 0.0;
   out_4604524654630855510[13] = 0.0;
   out_4604524654630855510[14] = 0.0;
   out_4604524654630855510[15] = 0.0;
   out_4604524654630855510[16] = 0.0;
   out_4604524654630855510[17] = 0.0;
   out_4604524654630855510[18] = 0.0;
   out_4604524654630855510[19] = 1.0;
   out_4604524654630855510[20] = 0.0;
   out_4604524654630855510[21] = 0.0;
   out_4604524654630855510[22] = 0.0;
   out_4604524654630855510[23] = 0.0;
   out_4604524654630855510[24] = 0.0;
   out_4604524654630855510[25] = 0.0;
   out_4604524654630855510[26] = 0.0;
   out_4604524654630855510[27] = 0.0;
   out_4604524654630855510[28] = 0.0;
   out_4604524654630855510[29] = 0.0;
   out_4604524654630855510[30] = 0.0;
   out_4604524654630855510[31] = 0.0;
   out_4604524654630855510[32] = 0.0;
   out_4604524654630855510[33] = 0.0;
   out_4604524654630855510[34] = 0.0;
   out_4604524654630855510[35] = 0.0;
   out_4604524654630855510[36] = 0.0;
   out_4604524654630855510[37] = 0.0;
   out_4604524654630855510[38] = 1.0;
   out_4604524654630855510[39] = 0.0;
   out_4604524654630855510[40] = 0.0;
   out_4604524654630855510[41] = 0.0;
   out_4604524654630855510[42] = 0.0;
   out_4604524654630855510[43] = 0.0;
   out_4604524654630855510[44] = 0.0;
   out_4604524654630855510[45] = 0.0;
   out_4604524654630855510[46] = 0.0;
   out_4604524654630855510[47] = 0.0;
   out_4604524654630855510[48] = 0.0;
   out_4604524654630855510[49] = 0.0;
   out_4604524654630855510[50] = 0.0;
   out_4604524654630855510[51] = 0.0;
   out_4604524654630855510[52] = 0.0;
   out_4604524654630855510[53] = 0.0;
   out_4604524654630855510[54] = 0.0;
   out_4604524654630855510[55] = 0.0;
   out_4604524654630855510[56] = 0.0;
   out_4604524654630855510[57] = 1.0;
   out_4604524654630855510[58] = 0.0;
   out_4604524654630855510[59] = 0.0;
   out_4604524654630855510[60] = 0.0;
   out_4604524654630855510[61] = 0.0;
   out_4604524654630855510[62] = 0.0;
   out_4604524654630855510[63] = 0.0;
   out_4604524654630855510[64] = 0.0;
   out_4604524654630855510[65] = 0.0;
   out_4604524654630855510[66] = 0.0;
   out_4604524654630855510[67] = 0.0;
   out_4604524654630855510[68] = 0.0;
   out_4604524654630855510[69] = 0.0;
   out_4604524654630855510[70] = 0.0;
   out_4604524654630855510[71] = 0.0;
   out_4604524654630855510[72] = 0.0;
   out_4604524654630855510[73] = 0.0;
   out_4604524654630855510[74] = 0.0;
   out_4604524654630855510[75] = 0.0;
   out_4604524654630855510[76] = 1.0;
   out_4604524654630855510[77] = 0.0;
   out_4604524654630855510[78] = 0.0;
   out_4604524654630855510[79] = 0.0;
   out_4604524654630855510[80] = 0.0;
   out_4604524654630855510[81] = 0.0;
   out_4604524654630855510[82] = 0.0;
   out_4604524654630855510[83] = 0.0;
   out_4604524654630855510[84] = 0.0;
   out_4604524654630855510[85] = 0.0;
   out_4604524654630855510[86] = 0.0;
   out_4604524654630855510[87] = 0.0;
   out_4604524654630855510[88] = 0.0;
   out_4604524654630855510[89] = 0.0;
   out_4604524654630855510[90] = 0.0;
   out_4604524654630855510[91] = 0.0;
   out_4604524654630855510[92] = 0.0;
   out_4604524654630855510[93] = 0.0;
   out_4604524654630855510[94] = 0.0;
   out_4604524654630855510[95] = 1.0;
   out_4604524654630855510[96] = 0.0;
   out_4604524654630855510[97] = 0.0;
   out_4604524654630855510[98] = 0.0;
   out_4604524654630855510[99] = 0.0;
   out_4604524654630855510[100] = 0.0;
   out_4604524654630855510[101] = 0.0;
   out_4604524654630855510[102] = 0.0;
   out_4604524654630855510[103] = 0.0;
   out_4604524654630855510[104] = 0.0;
   out_4604524654630855510[105] = 0.0;
   out_4604524654630855510[106] = 0.0;
   out_4604524654630855510[107] = 0.0;
   out_4604524654630855510[108] = 0.0;
   out_4604524654630855510[109] = 0.0;
   out_4604524654630855510[110] = 0.0;
   out_4604524654630855510[111] = 0.0;
   out_4604524654630855510[112] = 0.0;
   out_4604524654630855510[113] = 0.0;
   out_4604524654630855510[114] = 1.0;
   out_4604524654630855510[115] = 0.0;
   out_4604524654630855510[116] = 0.0;
   out_4604524654630855510[117] = 0.0;
   out_4604524654630855510[118] = 0.0;
   out_4604524654630855510[119] = 0.0;
   out_4604524654630855510[120] = 0.0;
   out_4604524654630855510[121] = 0.0;
   out_4604524654630855510[122] = 0.0;
   out_4604524654630855510[123] = 0.0;
   out_4604524654630855510[124] = 0.0;
   out_4604524654630855510[125] = 0.0;
   out_4604524654630855510[126] = 0.0;
   out_4604524654630855510[127] = 0.0;
   out_4604524654630855510[128] = 0.0;
   out_4604524654630855510[129] = 0.0;
   out_4604524654630855510[130] = 0.0;
   out_4604524654630855510[131] = 0.0;
   out_4604524654630855510[132] = 0.0;
   out_4604524654630855510[133] = 1.0;
   out_4604524654630855510[134] = 0.0;
   out_4604524654630855510[135] = 0.0;
   out_4604524654630855510[136] = 0.0;
   out_4604524654630855510[137] = 0.0;
   out_4604524654630855510[138] = 0.0;
   out_4604524654630855510[139] = 0.0;
   out_4604524654630855510[140] = 0.0;
   out_4604524654630855510[141] = 0.0;
   out_4604524654630855510[142] = 0.0;
   out_4604524654630855510[143] = 0.0;
   out_4604524654630855510[144] = 0.0;
   out_4604524654630855510[145] = 0.0;
   out_4604524654630855510[146] = 0.0;
   out_4604524654630855510[147] = 0.0;
   out_4604524654630855510[148] = 0.0;
   out_4604524654630855510[149] = 0.0;
   out_4604524654630855510[150] = 0.0;
   out_4604524654630855510[151] = 0.0;
   out_4604524654630855510[152] = 1.0;
   out_4604524654630855510[153] = 0.0;
   out_4604524654630855510[154] = 0.0;
   out_4604524654630855510[155] = 0.0;
   out_4604524654630855510[156] = 0.0;
   out_4604524654630855510[157] = 0.0;
   out_4604524654630855510[158] = 0.0;
   out_4604524654630855510[159] = 0.0;
   out_4604524654630855510[160] = 0.0;
   out_4604524654630855510[161] = 0.0;
   out_4604524654630855510[162] = 0.0;
   out_4604524654630855510[163] = 0.0;
   out_4604524654630855510[164] = 0.0;
   out_4604524654630855510[165] = 0.0;
   out_4604524654630855510[166] = 0.0;
   out_4604524654630855510[167] = 0.0;
   out_4604524654630855510[168] = 0.0;
   out_4604524654630855510[169] = 0.0;
   out_4604524654630855510[170] = 0.0;
   out_4604524654630855510[171] = 1.0;
   out_4604524654630855510[172] = 0.0;
   out_4604524654630855510[173] = 0.0;
   out_4604524654630855510[174] = 0.0;
   out_4604524654630855510[175] = 0.0;
   out_4604524654630855510[176] = 0.0;
   out_4604524654630855510[177] = 0.0;
   out_4604524654630855510[178] = 0.0;
   out_4604524654630855510[179] = 0.0;
   out_4604524654630855510[180] = 0.0;
   out_4604524654630855510[181] = 0.0;
   out_4604524654630855510[182] = 0.0;
   out_4604524654630855510[183] = 0.0;
   out_4604524654630855510[184] = 0.0;
   out_4604524654630855510[185] = 0.0;
   out_4604524654630855510[186] = 0.0;
   out_4604524654630855510[187] = 0.0;
   out_4604524654630855510[188] = 0.0;
   out_4604524654630855510[189] = 0.0;
   out_4604524654630855510[190] = 1.0;
   out_4604524654630855510[191] = 0.0;
   out_4604524654630855510[192] = 0.0;
   out_4604524654630855510[193] = 0.0;
   out_4604524654630855510[194] = 0.0;
   out_4604524654630855510[195] = 0.0;
   out_4604524654630855510[196] = 0.0;
   out_4604524654630855510[197] = 0.0;
   out_4604524654630855510[198] = 0.0;
   out_4604524654630855510[199] = 0.0;
   out_4604524654630855510[200] = 0.0;
   out_4604524654630855510[201] = 0.0;
   out_4604524654630855510[202] = 0.0;
   out_4604524654630855510[203] = 0.0;
   out_4604524654630855510[204] = 0.0;
   out_4604524654630855510[205] = 0.0;
   out_4604524654630855510[206] = 0.0;
   out_4604524654630855510[207] = 0.0;
   out_4604524654630855510[208] = 0.0;
   out_4604524654630855510[209] = 1.0;
   out_4604524654630855510[210] = 0.0;
   out_4604524654630855510[211] = 0.0;
   out_4604524654630855510[212] = 0.0;
   out_4604524654630855510[213] = 0.0;
   out_4604524654630855510[214] = 0.0;
   out_4604524654630855510[215] = 0.0;
   out_4604524654630855510[216] = 0.0;
   out_4604524654630855510[217] = 0.0;
   out_4604524654630855510[218] = 0.0;
   out_4604524654630855510[219] = 0.0;
   out_4604524654630855510[220] = 0.0;
   out_4604524654630855510[221] = 0.0;
   out_4604524654630855510[222] = 0.0;
   out_4604524654630855510[223] = 0.0;
   out_4604524654630855510[224] = 0.0;
   out_4604524654630855510[225] = 0.0;
   out_4604524654630855510[226] = 0.0;
   out_4604524654630855510[227] = 0.0;
   out_4604524654630855510[228] = 1.0;
   out_4604524654630855510[229] = 0.0;
   out_4604524654630855510[230] = 0.0;
   out_4604524654630855510[231] = 0.0;
   out_4604524654630855510[232] = 0.0;
   out_4604524654630855510[233] = 0.0;
   out_4604524654630855510[234] = 0.0;
   out_4604524654630855510[235] = 0.0;
   out_4604524654630855510[236] = 0.0;
   out_4604524654630855510[237] = 0.0;
   out_4604524654630855510[238] = 0.0;
   out_4604524654630855510[239] = 0.0;
   out_4604524654630855510[240] = 0.0;
   out_4604524654630855510[241] = 0.0;
   out_4604524654630855510[242] = 0.0;
   out_4604524654630855510[243] = 0.0;
   out_4604524654630855510[244] = 0.0;
   out_4604524654630855510[245] = 0.0;
   out_4604524654630855510[246] = 0.0;
   out_4604524654630855510[247] = 1.0;
   out_4604524654630855510[248] = 0.0;
   out_4604524654630855510[249] = 0.0;
   out_4604524654630855510[250] = 0.0;
   out_4604524654630855510[251] = 0.0;
   out_4604524654630855510[252] = 0.0;
   out_4604524654630855510[253] = 0.0;
   out_4604524654630855510[254] = 0.0;
   out_4604524654630855510[255] = 0.0;
   out_4604524654630855510[256] = 0.0;
   out_4604524654630855510[257] = 0.0;
   out_4604524654630855510[258] = 0.0;
   out_4604524654630855510[259] = 0.0;
   out_4604524654630855510[260] = 0.0;
   out_4604524654630855510[261] = 0.0;
   out_4604524654630855510[262] = 0.0;
   out_4604524654630855510[263] = 0.0;
   out_4604524654630855510[264] = 0.0;
   out_4604524654630855510[265] = 0.0;
   out_4604524654630855510[266] = 1.0;
   out_4604524654630855510[267] = 0.0;
   out_4604524654630855510[268] = 0.0;
   out_4604524654630855510[269] = 0.0;
   out_4604524654630855510[270] = 0.0;
   out_4604524654630855510[271] = 0.0;
   out_4604524654630855510[272] = 0.0;
   out_4604524654630855510[273] = 0.0;
   out_4604524654630855510[274] = 0.0;
   out_4604524654630855510[275] = 0.0;
   out_4604524654630855510[276] = 0.0;
   out_4604524654630855510[277] = 0.0;
   out_4604524654630855510[278] = 0.0;
   out_4604524654630855510[279] = 0.0;
   out_4604524654630855510[280] = 0.0;
   out_4604524654630855510[281] = 0.0;
   out_4604524654630855510[282] = 0.0;
   out_4604524654630855510[283] = 0.0;
   out_4604524654630855510[284] = 0.0;
   out_4604524654630855510[285] = 1.0;
   out_4604524654630855510[286] = 0.0;
   out_4604524654630855510[287] = 0.0;
   out_4604524654630855510[288] = 0.0;
   out_4604524654630855510[289] = 0.0;
   out_4604524654630855510[290] = 0.0;
   out_4604524654630855510[291] = 0.0;
   out_4604524654630855510[292] = 0.0;
   out_4604524654630855510[293] = 0.0;
   out_4604524654630855510[294] = 0.0;
   out_4604524654630855510[295] = 0.0;
   out_4604524654630855510[296] = 0.0;
   out_4604524654630855510[297] = 0.0;
   out_4604524654630855510[298] = 0.0;
   out_4604524654630855510[299] = 0.0;
   out_4604524654630855510[300] = 0.0;
   out_4604524654630855510[301] = 0.0;
   out_4604524654630855510[302] = 0.0;
   out_4604524654630855510[303] = 0.0;
   out_4604524654630855510[304] = 1.0;
   out_4604524654630855510[305] = 0.0;
   out_4604524654630855510[306] = 0.0;
   out_4604524654630855510[307] = 0.0;
   out_4604524654630855510[308] = 0.0;
   out_4604524654630855510[309] = 0.0;
   out_4604524654630855510[310] = 0.0;
   out_4604524654630855510[311] = 0.0;
   out_4604524654630855510[312] = 0.0;
   out_4604524654630855510[313] = 0.0;
   out_4604524654630855510[314] = 0.0;
   out_4604524654630855510[315] = 0.0;
   out_4604524654630855510[316] = 0.0;
   out_4604524654630855510[317] = 0.0;
   out_4604524654630855510[318] = 0.0;
   out_4604524654630855510[319] = 0.0;
   out_4604524654630855510[320] = 0.0;
   out_4604524654630855510[321] = 0.0;
   out_4604524654630855510[322] = 0.0;
   out_4604524654630855510[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8144335749808985700) {
   out_8144335749808985700[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8144335749808985700[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8144335749808985700[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8144335749808985700[3] = dt*state[12] + state[3];
   out_8144335749808985700[4] = dt*state[13] + state[4];
   out_8144335749808985700[5] = dt*state[14] + state[5];
   out_8144335749808985700[6] = state[6];
   out_8144335749808985700[7] = state[7];
   out_8144335749808985700[8] = state[8];
   out_8144335749808985700[9] = state[9];
   out_8144335749808985700[10] = state[10];
   out_8144335749808985700[11] = state[11];
   out_8144335749808985700[12] = state[12];
   out_8144335749808985700[13] = state[13];
   out_8144335749808985700[14] = state[14];
   out_8144335749808985700[15] = state[15];
   out_8144335749808985700[16] = state[16];
   out_8144335749808985700[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7938872027079426501) {
   out_7938872027079426501[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7938872027079426501[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7938872027079426501[2] = 0;
   out_7938872027079426501[3] = 0;
   out_7938872027079426501[4] = 0;
   out_7938872027079426501[5] = 0;
   out_7938872027079426501[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7938872027079426501[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7938872027079426501[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7938872027079426501[9] = 0;
   out_7938872027079426501[10] = 0;
   out_7938872027079426501[11] = 0;
   out_7938872027079426501[12] = 0;
   out_7938872027079426501[13] = 0;
   out_7938872027079426501[14] = 0;
   out_7938872027079426501[15] = 0;
   out_7938872027079426501[16] = 0;
   out_7938872027079426501[17] = 0;
   out_7938872027079426501[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7938872027079426501[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7938872027079426501[20] = 0;
   out_7938872027079426501[21] = 0;
   out_7938872027079426501[22] = 0;
   out_7938872027079426501[23] = 0;
   out_7938872027079426501[24] = 0;
   out_7938872027079426501[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7938872027079426501[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7938872027079426501[27] = 0;
   out_7938872027079426501[28] = 0;
   out_7938872027079426501[29] = 0;
   out_7938872027079426501[30] = 0;
   out_7938872027079426501[31] = 0;
   out_7938872027079426501[32] = 0;
   out_7938872027079426501[33] = 0;
   out_7938872027079426501[34] = 0;
   out_7938872027079426501[35] = 0;
   out_7938872027079426501[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7938872027079426501[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7938872027079426501[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7938872027079426501[39] = 0;
   out_7938872027079426501[40] = 0;
   out_7938872027079426501[41] = 0;
   out_7938872027079426501[42] = 0;
   out_7938872027079426501[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7938872027079426501[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7938872027079426501[45] = 0;
   out_7938872027079426501[46] = 0;
   out_7938872027079426501[47] = 0;
   out_7938872027079426501[48] = 0;
   out_7938872027079426501[49] = 0;
   out_7938872027079426501[50] = 0;
   out_7938872027079426501[51] = 0;
   out_7938872027079426501[52] = 0;
   out_7938872027079426501[53] = 0;
   out_7938872027079426501[54] = 0;
   out_7938872027079426501[55] = 0;
   out_7938872027079426501[56] = 0;
   out_7938872027079426501[57] = 1;
   out_7938872027079426501[58] = 0;
   out_7938872027079426501[59] = 0;
   out_7938872027079426501[60] = 0;
   out_7938872027079426501[61] = 0;
   out_7938872027079426501[62] = 0;
   out_7938872027079426501[63] = 0;
   out_7938872027079426501[64] = 0;
   out_7938872027079426501[65] = 0;
   out_7938872027079426501[66] = dt;
   out_7938872027079426501[67] = 0;
   out_7938872027079426501[68] = 0;
   out_7938872027079426501[69] = 0;
   out_7938872027079426501[70] = 0;
   out_7938872027079426501[71] = 0;
   out_7938872027079426501[72] = 0;
   out_7938872027079426501[73] = 0;
   out_7938872027079426501[74] = 0;
   out_7938872027079426501[75] = 0;
   out_7938872027079426501[76] = 1;
   out_7938872027079426501[77] = 0;
   out_7938872027079426501[78] = 0;
   out_7938872027079426501[79] = 0;
   out_7938872027079426501[80] = 0;
   out_7938872027079426501[81] = 0;
   out_7938872027079426501[82] = 0;
   out_7938872027079426501[83] = 0;
   out_7938872027079426501[84] = 0;
   out_7938872027079426501[85] = dt;
   out_7938872027079426501[86] = 0;
   out_7938872027079426501[87] = 0;
   out_7938872027079426501[88] = 0;
   out_7938872027079426501[89] = 0;
   out_7938872027079426501[90] = 0;
   out_7938872027079426501[91] = 0;
   out_7938872027079426501[92] = 0;
   out_7938872027079426501[93] = 0;
   out_7938872027079426501[94] = 0;
   out_7938872027079426501[95] = 1;
   out_7938872027079426501[96] = 0;
   out_7938872027079426501[97] = 0;
   out_7938872027079426501[98] = 0;
   out_7938872027079426501[99] = 0;
   out_7938872027079426501[100] = 0;
   out_7938872027079426501[101] = 0;
   out_7938872027079426501[102] = 0;
   out_7938872027079426501[103] = 0;
   out_7938872027079426501[104] = dt;
   out_7938872027079426501[105] = 0;
   out_7938872027079426501[106] = 0;
   out_7938872027079426501[107] = 0;
   out_7938872027079426501[108] = 0;
   out_7938872027079426501[109] = 0;
   out_7938872027079426501[110] = 0;
   out_7938872027079426501[111] = 0;
   out_7938872027079426501[112] = 0;
   out_7938872027079426501[113] = 0;
   out_7938872027079426501[114] = 1;
   out_7938872027079426501[115] = 0;
   out_7938872027079426501[116] = 0;
   out_7938872027079426501[117] = 0;
   out_7938872027079426501[118] = 0;
   out_7938872027079426501[119] = 0;
   out_7938872027079426501[120] = 0;
   out_7938872027079426501[121] = 0;
   out_7938872027079426501[122] = 0;
   out_7938872027079426501[123] = 0;
   out_7938872027079426501[124] = 0;
   out_7938872027079426501[125] = 0;
   out_7938872027079426501[126] = 0;
   out_7938872027079426501[127] = 0;
   out_7938872027079426501[128] = 0;
   out_7938872027079426501[129] = 0;
   out_7938872027079426501[130] = 0;
   out_7938872027079426501[131] = 0;
   out_7938872027079426501[132] = 0;
   out_7938872027079426501[133] = 1;
   out_7938872027079426501[134] = 0;
   out_7938872027079426501[135] = 0;
   out_7938872027079426501[136] = 0;
   out_7938872027079426501[137] = 0;
   out_7938872027079426501[138] = 0;
   out_7938872027079426501[139] = 0;
   out_7938872027079426501[140] = 0;
   out_7938872027079426501[141] = 0;
   out_7938872027079426501[142] = 0;
   out_7938872027079426501[143] = 0;
   out_7938872027079426501[144] = 0;
   out_7938872027079426501[145] = 0;
   out_7938872027079426501[146] = 0;
   out_7938872027079426501[147] = 0;
   out_7938872027079426501[148] = 0;
   out_7938872027079426501[149] = 0;
   out_7938872027079426501[150] = 0;
   out_7938872027079426501[151] = 0;
   out_7938872027079426501[152] = 1;
   out_7938872027079426501[153] = 0;
   out_7938872027079426501[154] = 0;
   out_7938872027079426501[155] = 0;
   out_7938872027079426501[156] = 0;
   out_7938872027079426501[157] = 0;
   out_7938872027079426501[158] = 0;
   out_7938872027079426501[159] = 0;
   out_7938872027079426501[160] = 0;
   out_7938872027079426501[161] = 0;
   out_7938872027079426501[162] = 0;
   out_7938872027079426501[163] = 0;
   out_7938872027079426501[164] = 0;
   out_7938872027079426501[165] = 0;
   out_7938872027079426501[166] = 0;
   out_7938872027079426501[167] = 0;
   out_7938872027079426501[168] = 0;
   out_7938872027079426501[169] = 0;
   out_7938872027079426501[170] = 0;
   out_7938872027079426501[171] = 1;
   out_7938872027079426501[172] = 0;
   out_7938872027079426501[173] = 0;
   out_7938872027079426501[174] = 0;
   out_7938872027079426501[175] = 0;
   out_7938872027079426501[176] = 0;
   out_7938872027079426501[177] = 0;
   out_7938872027079426501[178] = 0;
   out_7938872027079426501[179] = 0;
   out_7938872027079426501[180] = 0;
   out_7938872027079426501[181] = 0;
   out_7938872027079426501[182] = 0;
   out_7938872027079426501[183] = 0;
   out_7938872027079426501[184] = 0;
   out_7938872027079426501[185] = 0;
   out_7938872027079426501[186] = 0;
   out_7938872027079426501[187] = 0;
   out_7938872027079426501[188] = 0;
   out_7938872027079426501[189] = 0;
   out_7938872027079426501[190] = 1;
   out_7938872027079426501[191] = 0;
   out_7938872027079426501[192] = 0;
   out_7938872027079426501[193] = 0;
   out_7938872027079426501[194] = 0;
   out_7938872027079426501[195] = 0;
   out_7938872027079426501[196] = 0;
   out_7938872027079426501[197] = 0;
   out_7938872027079426501[198] = 0;
   out_7938872027079426501[199] = 0;
   out_7938872027079426501[200] = 0;
   out_7938872027079426501[201] = 0;
   out_7938872027079426501[202] = 0;
   out_7938872027079426501[203] = 0;
   out_7938872027079426501[204] = 0;
   out_7938872027079426501[205] = 0;
   out_7938872027079426501[206] = 0;
   out_7938872027079426501[207] = 0;
   out_7938872027079426501[208] = 0;
   out_7938872027079426501[209] = 1;
   out_7938872027079426501[210] = 0;
   out_7938872027079426501[211] = 0;
   out_7938872027079426501[212] = 0;
   out_7938872027079426501[213] = 0;
   out_7938872027079426501[214] = 0;
   out_7938872027079426501[215] = 0;
   out_7938872027079426501[216] = 0;
   out_7938872027079426501[217] = 0;
   out_7938872027079426501[218] = 0;
   out_7938872027079426501[219] = 0;
   out_7938872027079426501[220] = 0;
   out_7938872027079426501[221] = 0;
   out_7938872027079426501[222] = 0;
   out_7938872027079426501[223] = 0;
   out_7938872027079426501[224] = 0;
   out_7938872027079426501[225] = 0;
   out_7938872027079426501[226] = 0;
   out_7938872027079426501[227] = 0;
   out_7938872027079426501[228] = 1;
   out_7938872027079426501[229] = 0;
   out_7938872027079426501[230] = 0;
   out_7938872027079426501[231] = 0;
   out_7938872027079426501[232] = 0;
   out_7938872027079426501[233] = 0;
   out_7938872027079426501[234] = 0;
   out_7938872027079426501[235] = 0;
   out_7938872027079426501[236] = 0;
   out_7938872027079426501[237] = 0;
   out_7938872027079426501[238] = 0;
   out_7938872027079426501[239] = 0;
   out_7938872027079426501[240] = 0;
   out_7938872027079426501[241] = 0;
   out_7938872027079426501[242] = 0;
   out_7938872027079426501[243] = 0;
   out_7938872027079426501[244] = 0;
   out_7938872027079426501[245] = 0;
   out_7938872027079426501[246] = 0;
   out_7938872027079426501[247] = 1;
   out_7938872027079426501[248] = 0;
   out_7938872027079426501[249] = 0;
   out_7938872027079426501[250] = 0;
   out_7938872027079426501[251] = 0;
   out_7938872027079426501[252] = 0;
   out_7938872027079426501[253] = 0;
   out_7938872027079426501[254] = 0;
   out_7938872027079426501[255] = 0;
   out_7938872027079426501[256] = 0;
   out_7938872027079426501[257] = 0;
   out_7938872027079426501[258] = 0;
   out_7938872027079426501[259] = 0;
   out_7938872027079426501[260] = 0;
   out_7938872027079426501[261] = 0;
   out_7938872027079426501[262] = 0;
   out_7938872027079426501[263] = 0;
   out_7938872027079426501[264] = 0;
   out_7938872027079426501[265] = 0;
   out_7938872027079426501[266] = 1;
   out_7938872027079426501[267] = 0;
   out_7938872027079426501[268] = 0;
   out_7938872027079426501[269] = 0;
   out_7938872027079426501[270] = 0;
   out_7938872027079426501[271] = 0;
   out_7938872027079426501[272] = 0;
   out_7938872027079426501[273] = 0;
   out_7938872027079426501[274] = 0;
   out_7938872027079426501[275] = 0;
   out_7938872027079426501[276] = 0;
   out_7938872027079426501[277] = 0;
   out_7938872027079426501[278] = 0;
   out_7938872027079426501[279] = 0;
   out_7938872027079426501[280] = 0;
   out_7938872027079426501[281] = 0;
   out_7938872027079426501[282] = 0;
   out_7938872027079426501[283] = 0;
   out_7938872027079426501[284] = 0;
   out_7938872027079426501[285] = 1;
   out_7938872027079426501[286] = 0;
   out_7938872027079426501[287] = 0;
   out_7938872027079426501[288] = 0;
   out_7938872027079426501[289] = 0;
   out_7938872027079426501[290] = 0;
   out_7938872027079426501[291] = 0;
   out_7938872027079426501[292] = 0;
   out_7938872027079426501[293] = 0;
   out_7938872027079426501[294] = 0;
   out_7938872027079426501[295] = 0;
   out_7938872027079426501[296] = 0;
   out_7938872027079426501[297] = 0;
   out_7938872027079426501[298] = 0;
   out_7938872027079426501[299] = 0;
   out_7938872027079426501[300] = 0;
   out_7938872027079426501[301] = 0;
   out_7938872027079426501[302] = 0;
   out_7938872027079426501[303] = 0;
   out_7938872027079426501[304] = 1;
   out_7938872027079426501[305] = 0;
   out_7938872027079426501[306] = 0;
   out_7938872027079426501[307] = 0;
   out_7938872027079426501[308] = 0;
   out_7938872027079426501[309] = 0;
   out_7938872027079426501[310] = 0;
   out_7938872027079426501[311] = 0;
   out_7938872027079426501[312] = 0;
   out_7938872027079426501[313] = 0;
   out_7938872027079426501[314] = 0;
   out_7938872027079426501[315] = 0;
   out_7938872027079426501[316] = 0;
   out_7938872027079426501[317] = 0;
   out_7938872027079426501[318] = 0;
   out_7938872027079426501[319] = 0;
   out_7938872027079426501[320] = 0;
   out_7938872027079426501[321] = 0;
   out_7938872027079426501[322] = 0;
   out_7938872027079426501[323] = 1;
}
void h_4(double *state, double *unused, double *out_3382593130953121745) {
   out_3382593130953121745[0] = state[6] + state[9];
   out_3382593130953121745[1] = state[7] + state[10];
   out_3382593130953121745[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3406577172747957406) {
   out_3406577172747957406[0] = 0;
   out_3406577172747957406[1] = 0;
   out_3406577172747957406[2] = 0;
   out_3406577172747957406[3] = 0;
   out_3406577172747957406[4] = 0;
   out_3406577172747957406[5] = 0;
   out_3406577172747957406[6] = 1;
   out_3406577172747957406[7] = 0;
   out_3406577172747957406[8] = 0;
   out_3406577172747957406[9] = 1;
   out_3406577172747957406[10] = 0;
   out_3406577172747957406[11] = 0;
   out_3406577172747957406[12] = 0;
   out_3406577172747957406[13] = 0;
   out_3406577172747957406[14] = 0;
   out_3406577172747957406[15] = 0;
   out_3406577172747957406[16] = 0;
   out_3406577172747957406[17] = 0;
   out_3406577172747957406[18] = 0;
   out_3406577172747957406[19] = 0;
   out_3406577172747957406[20] = 0;
   out_3406577172747957406[21] = 0;
   out_3406577172747957406[22] = 0;
   out_3406577172747957406[23] = 0;
   out_3406577172747957406[24] = 0;
   out_3406577172747957406[25] = 1;
   out_3406577172747957406[26] = 0;
   out_3406577172747957406[27] = 0;
   out_3406577172747957406[28] = 1;
   out_3406577172747957406[29] = 0;
   out_3406577172747957406[30] = 0;
   out_3406577172747957406[31] = 0;
   out_3406577172747957406[32] = 0;
   out_3406577172747957406[33] = 0;
   out_3406577172747957406[34] = 0;
   out_3406577172747957406[35] = 0;
   out_3406577172747957406[36] = 0;
   out_3406577172747957406[37] = 0;
   out_3406577172747957406[38] = 0;
   out_3406577172747957406[39] = 0;
   out_3406577172747957406[40] = 0;
   out_3406577172747957406[41] = 0;
   out_3406577172747957406[42] = 0;
   out_3406577172747957406[43] = 0;
   out_3406577172747957406[44] = 1;
   out_3406577172747957406[45] = 0;
   out_3406577172747957406[46] = 0;
   out_3406577172747957406[47] = 1;
   out_3406577172747957406[48] = 0;
   out_3406577172747957406[49] = 0;
   out_3406577172747957406[50] = 0;
   out_3406577172747957406[51] = 0;
   out_3406577172747957406[52] = 0;
   out_3406577172747957406[53] = 0;
}
void h_10(double *state, double *unused, double *out_3810751197064733105) {
   out_3810751197064733105[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3810751197064733105[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3810751197064733105[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5824195032039914110) {
   out_5824195032039914110[0] = 0;
   out_5824195032039914110[1] = 9.8100000000000005*cos(state[1]);
   out_5824195032039914110[2] = 0;
   out_5824195032039914110[3] = 0;
   out_5824195032039914110[4] = -state[8];
   out_5824195032039914110[5] = state[7];
   out_5824195032039914110[6] = 0;
   out_5824195032039914110[7] = state[5];
   out_5824195032039914110[8] = -state[4];
   out_5824195032039914110[9] = 0;
   out_5824195032039914110[10] = 0;
   out_5824195032039914110[11] = 0;
   out_5824195032039914110[12] = 1;
   out_5824195032039914110[13] = 0;
   out_5824195032039914110[14] = 0;
   out_5824195032039914110[15] = 1;
   out_5824195032039914110[16] = 0;
   out_5824195032039914110[17] = 0;
   out_5824195032039914110[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5824195032039914110[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5824195032039914110[20] = 0;
   out_5824195032039914110[21] = state[8];
   out_5824195032039914110[22] = 0;
   out_5824195032039914110[23] = -state[6];
   out_5824195032039914110[24] = -state[5];
   out_5824195032039914110[25] = 0;
   out_5824195032039914110[26] = state[3];
   out_5824195032039914110[27] = 0;
   out_5824195032039914110[28] = 0;
   out_5824195032039914110[29] = 0;
   out_5824195032039914110[30] = 0;
   out_5824195032039914110[31] = 1;
   out_5824195032039914110[32] = 0;
   out_5824195032039914110[33] = 0;
   out_5824195032039914110[34] = 1;
   out_5824195032039914110[35] = 0;
   out_5824195032039914110[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5824195032039914110[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5824195032039914110[38] = 0;
   out_5824195032039914110[39] = -state[7];
   out_5824195032039914110[40] = state[6];
   out_5824195032039914110[41] = 0;
   out_5824195032039914110[42] = state[4];
   out_5824195032039914110[43] = -state[3];
   out_5824195032039914110[44] = 0;
   out_5824195032039914110[45] = 0;
   out_5824195032039914110[46] = 0;
   out_5824195032039914110[47] = 0;
   out_5824195032039914110[48] = 0;
   out_5824195032039914110[49] = 0;
   out_5824195032039914110[50] = 1;
   out_5824195032039914110[51] = 0;
   out_5824195032039914110[52] = 0;
   out_5824195032039914110[53] = 1;
}
void h_13(double *state, double *unused, double *out_774085760433495807) {
   out_774085760433495807[0] = state[3];
   out_774085760433495807[1] = state[4];
   out_774085760433495807[2] = state[5];
}
void H_13(double *state, double *unused, double *out_194303347415624605) {
   out_194303347415624605[0] = 0;
   out_194303347415624605[1] = 0;
   out_194303347415624605[2] = 0;
   out_194303347415624605[3] = 1;
   out_194303347415624605[4] = 0;
   out_194303347415624605[5] = 0;
   out_194303347415624605[6] = 0;
   out_194303347415624605[7] = 0;
   out_194303347415624605[8] = 0;
   out_194303347415624605[9] = 0;
   out_194303347415624605[10] = 0;
   out_194303347415624605[11] = 0;
   out_194303347415624605[12] = 0;
   out_194303347415624605[13] = 0;
   out_194303347415624605[14] = 0;
   out_194303347415624605[15] = 0;
   out_194303347415624605[16] = 0;
   out_194303347415624605[17] = 0;
   out_194303347415624605[18] = 0;
   out_194303347415624605[19] = 0;
   out_194303347415624605[20] = 0;
   out_194303347415624605[21] = 0;
   out_194303347415624605[22] = 1;
   out_194303347415624605[23] = 0;
   out_194303347415624605[24] = 0;
   out_194303347415624605[25] = 0;
   out_194303347415624605[26] = 0;
   out_194303347415624605[27] = 0;
   out_194303347415624605[28] = 0;
   out_194303347415624605[29] = 0;
   out_194303347415624605[30] = 0;
   out_194303347415624605[31] = 0;
   out_194303347415624605[32] = 0;
   out_194303347415624605[33] = 0;
   out_194303347415624605[34] = 0;
   out_194303347415624605[35] = 0;
   out_194303347415624605[36] = 0;
   out_194303347415624605[37] = 0;
   out_194303347415624605[38] = 0;
   out_194303347415624605[39] = 0;
   out_194303347415624605[40] = 0;
   out_194303347415624605[41] = 1;
   out_194303347415624605[42] = 0;
   out_194303347415624605[43] = 0;
   out_194303347415624605[44] = 0;
   out_194303347415624605[45] = 0;
   out_194303347415624605[46] = 0;
   out_194303347415624605[47] = 0;
   out_194303347415624605[48] = 0;
   out_194303347415624605[49] = 0;
   out_194303347415624605[50] = 0;
   out_194303347415624605[51] = 0;
   out_194303347415624605[52] = 0;
   out_194303347415624605[53] = 0;
}
void h_14(double *state, double *unused, double *out_6021362742836865981) {
   out_6021362742836865981[0] = state[6];
   out_6021362742836865981[1] = state[7];
   out_6021362742836865981[2] = state[8];
}
void H_14(double *state, double *unused, double *out_556663683591527123) {
   out_556663683591527123[0] = 0;
   out_556663683591527123[1] = 0;
   out_556663683591527123[2] = 0;
   out_556663683591527123[3] = 0;
   out_556663683591527123[4] = 0;
   out_556663683591527123[5] = 0;
   out_556663683591527123[6] = 1;
   out_556663683591527123[7] = 0;
   out_556663683591527123[8] = 0;
   out_556663683591527123[9] = 0;
   out_556663683591527123[10] = 0;
   out_556663683591527123[11] = 0;
   out_556663683591527123[12] = 0;
   out_556663683591527123[13] = 0;
   out_556663683591527123[14] = 0;
   out_556663683591527123[15] = 0;
   out_556663683591527123[16] = 0;
   out_556663683591527123[17] = 0;
   out_556663683591527123[18] = 0;
   out_556663683591527123[19] = 0;
   out_556663683591527123[20] = 0;
   out_556663683591527123[21] = 0;
   out_556663683591527123[22] = 0;
   out_556663683591527123[23] = 0;
   out_556663683591527123[24] = 0;
   out_556663683591527123[25] = 1;
   out_556663683591527123[26] = 0;
   out_556663683591527123[27] = 0;
   out_556663683591527123[28] = 0;
   out_556663683591527123[29] = 0;
   out_556663683591527123[30] = 0;
   out_556663683591527123[31] = 0;
   out_556663683591527123[32] = 0;
   out_556663683591527123[33] = 0;
   out_556663683591527123[34] = 0;
   out_556663683591527123[35] = 0;
   out_556663683591527123[36] = 0;
   out_556663683591527123[37] = 0;
   out_556663683591527123[38] = 0;
   out_556663683591527123[39] = 0;
   out_556663683591527123[40] = 0;
   out_556663683591527123[41] = 0;
   out_556663683591527123[42] = 0;
   out_556663683591527123[43] = 0;
   out_556663683591527123[44] = 1;
   out_556663683591527123[45] = 0;
   out_556663683591527123[46] = 0;
   out_556663683591527123[47] = 0;
   out_556663683591527123[48] = 0;
   out_556663683591527123[49] = 0;
   out_556663683591527123[50] = 0;
   out_556663683591527123[51] = 0;
   out_556663683591527123[52] = 0;
   out_556663683591527123[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_1557390242987403893) {
  err_fun(nom_x, delta_x, out_1557390242987403893);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4141160926477888419) {
  inv_err_fun(nom_x, true_x, out_4141160926477888419);
}
void pose_H_mod_fun(double *state, double *out_4604524654630855510) {
  H_mod_fun(state, out_4604524654630855510);
}
void pose_f_fun(double *state, double dt, double *out_8144335749808985700) {
  f_fun(state,  dt, out_8144335749808985700);
}
void pose_F_fun(double *state, double dt, double *out_7938872027079426501) {
  F_fun(state,  dt, out_7938872027079426501);
}
void pose_h_4(double *state, double *unused, double *out_3382593130953121745) {
  h_4(state, unused, out_3382593130953121745);
}
void pose_H_4(double *state, double *unused, double *out_3406577172747957406) {
  H_4(state, unused, out_3406577172747957406);
}
void pose_h_10(double *state, double *unused, double *out_3810751197064733105) {
  h_10(state, unused, out_3810751197064733105);
}
void pose_H_10(double *state, double *unused, double *out_5824195032039914110) {
  H_10(state, unused, out_5824195032039914110);
}
void pose_h_13(double *state, double *unused, double *out_774085760433495807) {
  h_13(state, unused, out_774085760433495807);
}
void pose_H_13(double *state, double *unused, double *out_194303347415624605) {
  H_13(state, unused, out_194303347415624605);
}
void pose_h_14(double *state, double *unused, double *out_6021362742836865981) {
  h_14(state, unused, out_6021362742836865981);
}
void pose_H_14(double *state, double *unused, double *out_556663683591527123) {
  H_14(state, unused, out_556663683591527123);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
