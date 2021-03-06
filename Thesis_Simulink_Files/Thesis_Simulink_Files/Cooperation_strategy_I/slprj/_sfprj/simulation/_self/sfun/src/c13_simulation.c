/* Include files */

#include <stddef.h>
#include "blas.h"
#include "simulation_sfun.h"
#include "c13_simulation.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "simulation_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c13_debug_family_names[19] = { "R", "d", "z", "nargin",
  "nargout", "Vc", "P", "psi", "kx", "ky", "kz", "Pd", "dPd", "Vd", "delta",
  "dgam", "Ud", "e", "ddgam" };

/* Function Declarations */
static void initialize_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance);
static void initialize_params_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance);
static void enable_c13_simulation(SFc13_simulationInstanceStruct *chartInstance);
static void disable_c13_simulation(SFc13_simulationInstanceStruct *chartInstance);
static void c13_update_debugger_state_c13_simulation
  (SFc13_simulationInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_simulation
  (SFc13_simulationInstanceStruct *chartInstance);
static void set_sim_state_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_st);
static void finalize_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance);
static void sf_c13_simulation(SFc13_simulationInstanceStruct *chartInstance);
static void c13_chartstep_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance);
static void initSimStructsc13_simulation(SFc13_simulationInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_ddgam, const char_T *c13_identifier);
static real_T c13_b_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_c_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_e, const char_T *c13_identifier, real_T c13_y[2]);
static void c13_d_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, real_T c13_y[2]);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_e_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, real_T c13_y[4]);
static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static void c13_info_helper(const mxArray **c13_info);
static const mxArray *c13_emlrt_marshallOut(char * c13_u);
static const mxArray *c13_b_emlrt_marshallOut(uint32_T c13_u);
static void c13_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance);
static void c13_tanh(SFc13_simulationInstanceStruct *chartInstance, real_T
                     c13_x[2], real_T c13_b_x[2]);
static void c13_b_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance);
static void c13_c_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance);
static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_f_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_g_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_simulation, const char_T
  *c13_identifier);
static uint8_T c13_h_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_tanh(SFc13_simulationInstanceStruct *chartInstance, real_T
  c13_x[2]);
static void init_dsm_address_info(SFc13_simulationInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c13_is_active_c13_simulation = 0U;
}

static void initialize_params_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance)
{
  real_T c13_d0;
  real_T c13_d1;
  real_T c13_d2;
  real_T c13_d3;
  sf_set_error_prefix_string(
    "Error evaluating data 'kx' in the parent workspace.\n");
  sf_mex_import_named("kx", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c13_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c13_kx = c13_d0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'ky' in the parent workspace.\n");
  sf_mex_import_named("ky", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c13_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c13_ky = c13_d1;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'kz' in the parent workspace.\n");
  sf_mex_import_named("kz", sf_mex_get_sfun_param(chartInstance->S, 3, 0),
                      &c13_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c13_kz = c13_d2;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'delta' in the parent workspace.\n");
  sf_mex_import_named("delta", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c13_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c13_delta = c13_d3;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c13_simulation(SFc13_simulationInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c13_simulation(SFc13_simulationInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c13_update_debugger_state_c13_simulation
  (SFc13_simulationInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c13_simulation
  (SFc13_simulationInstanceStruct *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  int32_T c13_i0;
  real_T c13_u[2];
  const mxArray *c13_b_y = NULL;
  real_T c13_hoistedGlobal;
  real_T c13_b_u;
  const mxArray *c13_c_y = NULL;
  int32_T c13_i1;
  real_T c13_c_u[2];
  const mxArray *c13_d_y = NULL;
  uint8_T c13_b_hoistedGlobal;
  uint8_T c13_d_u;
  const mxArray *c13_e_y = NULL;
  real_T *c13_ddgam;
  real_T (*c13_e)[2];
  real_T (*c13_Ud)[2];
  c13_ddgam = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_e = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_Ud = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellarray(4), FALSE);
  for (c13_i0 = 0; c13_i0 < 2; c13_i0++) {
    c13_u[c13_i0] = (*c13_Ud)[c13_i0];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  c13_hoistedGlobal = *c13_ddgam;
  c13_b_u = c13_hoistedGlobal;
  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", &c13_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  for (c13_i1 = 0; c13_i1 < 2; c13_i1++) {
    c13_c_u[c13_i1] = (*c13_e)[c13_i1];
  }

  c13_d_y = NULL;
  sf_mex_assign(&c13_d_y, sf_mex_create("y", c13_c_u, 0, 0U, 1U, 0U, 1, 2),
                FALSE);
  sf_mex_setcell(c13_y, 2, c13_d_y);
  c13_b_hoistedGlobal = chartInstance->c13_is_active_c13_simulation;
  c13_d_u = c13_b_hoistedGlobal;
  c13_e_y = NULL;
  sf_mex_assign(&c13_e_y, sf_mex_create("y", &c13_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 3, c13_e_y);
  sf_mex_assign(&c13_st, c13_y, FALSE);
  return c13_st;
}

static void set_sim_state_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_st)
{
  const mxArray *c13_u;
  real_T c13_dv0[2];
  int32_T c13_i2;
  real_T c13_dv1[2];
  int32_T c13_i3;
  real_T *c13_ddgam;
  real_T (*c13_Ud)[2];
  real_T (*c13_e)[2];
  c13_ddgam = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_e = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_Ud = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = TRUE;
  c13_u = sf_mex_dup(c13_st);
  c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 0)),
    "Ud", c13_dv0);
  for (c13_i2 = 0; c13_i2 < 2; c13_i2++) {
    (*c13_Ud)[c13_i2] = c13_dv0[c13_i2];
  }

  *c13_ddgam = c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c13_u, 1)), "ddgam");
  c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 2)),
    "e", c13_dv1);
  for (c13_i3 = 0; c13_i3 < 2; c13_i3++) {
    (*c13_e)[c13_i3] = c13_dv1[c13_i3];
  }

  chartInstance->c13_is_active_c13_simulation = c13_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 3)),
     "is_active_c13_simulation");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_simulation(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance)
{
}

static void sf_c13_simulation(SFc13_simulationInstanceStruct *chartInstance)
{
  int32_T c13_i4;
  int32_T c13_i5;
  int32_T c13_i6;
  int32_T c13_i7;
  int32_T c13_i8;
  int32_T c13_i9;
  real_T *c13_psi;
  real_T *c13_Vd;
  real_T *c13_dgam;
  real_T *c13_ddgam;
  real_T (*c13_e)[2];
  real_T (*c13_Ud)[2];
  real_T (*c13_dPd)[2];
  real_T (*c13_Pd)[2];
  real_T (*c13_P)[2];
  real_T (*c13_Vc)[2];
  c13_ddgam = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_dgam = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c13_e = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_Ud = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_Vd = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c13_dPd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c13_Pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c13_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c13_P = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c13_Vc = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  for (c13_i4 = 0; c13_i4 < 2; c13_i4++) {
    _SFD_DATA_RANGE_CHECK((*c13_Vc)[c13_i4], 0U);
  }

  for (c13_i5 = 0; c13_i5 < 2; c13_i5++) {
    _SFD_DATA_RANGE_CHECK((*c13_P)[c13_i5], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c13_psi, 2U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c13_kx, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c13_ky, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c13_kz, 5U);
  for (c13_i6 = 0; c13_i6 < 2; c13_i6++) {
    _SFD_DATA_RANGE_CHECK((*c13_Pd)[c13_i6], 6U);
  }

  for (c13_i7 = 0; c13_i7 < 2; c13_i7++) {
    _SFD_DATA_RANGE_CHECK((*c13_dPd)[c13_i7], 7U);
  }

  _SFD_DATA_RANGE_CHECK(*c13_Vd, 8U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c13_delta, 9U);
  for (c13_i8 = 0; c13_i8 < 2; c13_i8++) {
    _SFD_DATA_RANGE_CHECK((*c13_Ud)[c13_i8], 10U);
  }

  for (c13_i9 = 0; c13_i9 < 2; c13_i9++) {
    _SFD_DATA_RANGE_CHECK((*c13_e)[c13_i9], 11U);
  }

  _SFD_DATA_RANGE_CHECK(*c13_dgam, 12U);
  _SFD_DATA_RANGE_CHECK(*c13_ddgam, 13U);
  chartInstance->c13_sfEvent = CALL_EVENT;
  c13_chartstep_c13_simulation(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_simulationMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c13_chartstep_c13_simulation(SFc13_simulationInstanceStruct
  *chartInstance)
{
  real_T c13_hoistedGlobal;
  real_T c13_b_hoistedGlobal;
  real_T c13_c_hoistedGlobal;
  real_T c13_d_hoistedGlobal;
  real_T c13_e_hoistedGlobal;
  real_T c13_f_hoistedGlobal;
  real_T c13_g_hoistedGlobal;
  int32_T c13_i10;
  real_T c13_Vc[2];
  int32_T c13_i11;
  real_T c13_P[2];
  real_T c13_psi;
  real_T c13_b_kx;
  real_T c13_b_ky;
  real_T c13_b_kz;
  int32_T c13_i12;
  real_T c13_Pd[2];
  int32_T c13_i13;
  real_T c13_dPd[2];
  real_T c13_Vd;
  real_T c13_b_delta;
  real_T c13_dgam;
  uint32_T c13_debug_family_var_map[19];
  real_T c13_R[4];
  real_T c13_d[2];
  real_T c13_z;
  real_T c13_nargin = 11.0;
  real_T c13_nargout = 3.0;
  real_T c13_Ud[2];
  real_T c13_e[2];
  real_T c13_ddgam;
  real_T c13_x;
  real_T c13_b_x;
  real_T c13_c_x;
  real_T c13_d_x;
  real_T c13_e_x;
  real_T c13_f_x;
  real_T c13_g_x;
  real_T c13_h_x;
  int32_T c13_i14;
  int32_T c13_i15;
  int32_T c13_i16;
  int32_T c13_i17;
  real_T c13_a[4];
  int32_T c13_i18;
  real_T c13_b[2];
  int32_T c13_i19;
  int32_T c13_i20;
  int32_T c13_i21;
  real_T c13_C[2];
  int32_T c13_i22;
  int32_T c13_i23;
  int32_T c13_i24;
  int32_T c13_i25;
  int32_T c13_i26;
  int32_T c13_i27;
  real_T c13_B;
  real_T c13_y;
  real_T c13_b_y;
  real_T c13_c_y;
  int32_T c13_i28;
  int32_T c13_i29;
  real_T c13_d_y[2];
  int32_T c13_i30;
  int32_T c13_i31;
  int32_T c13_i32;
  int32_T c13_i33;
  int32_T c13_i34;
  int32_T c13_i35;
  int32_T c13_i36;
  int32_T c13_i37;
  int32_T c13_i38;
  int32_T c13_i39;
  real_T c13_b_a;
  int32_T c13_i40;
  int32_T c13_i41;
  int32_T c13_i42;
  int32_T c13_i43;
  int32_T c13_i44;
  int32_T c13_i45;
  int32_T c13_i46;
  real_T c13_e_y[2];
  int32_T c13_i47;
  int32_T c13_i48;
  int32_T c13_i49;
  int32_T c13_i50;
  int32_T c13_i51;
  int32_T c13_i52;
  int32_T c13_i53;
  int32_T c13_i54;
  int32_T c13_i55;
  int32_T c13_i56;
  int32_T c13_i57;
  int32_T c13_i58;
  int32_T c13_i59;
  int32_T c13_i60;
  real_T c13_c_a;
  real_T c13_b_b;
  real_T c13_f_y;
  int32_T c13_i61;
  real_T c13_d_a[2];
  int32_T c13_i62;
  int32_T c13_i63;
  int32_T c13_i64;
  int32_T c13_i65;
  int32_T c13_i66;
  int32_T c13_i67;
  real_T c13_g_y[2];
  int32_T c13_i68;
  int32_T c13_i69;
  real_T c13_h_y;
  int32_T c13_k;
  int32_T c13_b_k;
  int32_T c13_i70;
  int32_T c13_i71;
  real_T *c13_b_psi;
  real_T *c13_b_Vd;
  real_T *c13_b_dgam;
  real_T *c13_b_ddgam;
  real_T (*c13_b_Ud)[2];
  real_T (*c13_b_e)[2];
  real_T (*c13_b_dPd)[2];
  real_T (*c13_b_Pd)[2];
  real_T (*c13_b_P)[2];
  real_T (*c13_b_Vc)[2];
  c13_b_ddgam = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_b_dgam = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c13_b_e = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_b_Ud = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_Vd = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c13_b_dPd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c13_b_Pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c13_b_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c13_b_P = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c13_b_Vc = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  c13_hoistedGlobal = *c13_b_psi;
  c13_b_hoistedGlobal = chartInstance->c13_kx;
  c13_c_hoistedGlobal = chartInstance->c13_ky;
  c13_d_hoistedGlobal = chartInstance->c13_kz;
  c13_e_hoistedGlobal = *c13_b_Vd;
  c13_f_hoistedGlobal = chartInstance->c13_delta;
  c13_g_hoistedGlobal = *c13_b_dgam;
  for (c13_i10 = 0; c13_i10 < 2; c13_i10++) {
    c13_Vc[c13_i10] = (*c13_b_Vc)[c13_i10];
  }

  for (c13_i11 = 0; c13_i11 < 2; c13_i11++) {
    c13_P[c13_i11] = (*c13_b_P)[c13_i11];
  }

  c13_psi = c13_hoistedGlobal;
  c13_b_kx = c13_b_hoistedGlobal;
  c13_b_ky = c13_c_hoistedGlobal;
  c13_b_kz = c13_d_hoistedGlobal;
  for (c13_i12 = 0; c13_i12 < 2; c13_i12++) {
    c13_Pd[c13_i12] = (*c13_b_Pd)[c13_i12];
  }

  for (c13_i13 = 0; c13_i13 < 2; c13_i13++) {
    c13_dPd[c13_i13] = (*c13_b_dPd)[c13_i13];
  }

  c13_Vd = c13_e_hoistedGlobal;
  c13_b_delta = c13_f_hoistedGlobal;
  c13_dgam = c13_g_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 19U, 19U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_R, 0U, c13_c_sf_marshallOut,
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_d, 1U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_z, 2U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 3U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 4U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_Vc, 5U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_P, 6U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_psi, 7U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_b_kx, 8U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_b_ky, 9U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_b_kz, 10U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_Pd, 11U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_dPd, 12U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_Vd, 13U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_b_delta, 14U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_dgam, 15U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_Ud, 16U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_e, 17U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_ddgam, 18U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 4);
  c13_x = c13_psi;
  c13_b_x = c13_x;
  c13_b_x = muDoubleScalarCos(c13_b_x);
  c13_c_x = c13_psi;
  c13_d_x = c13_c_x;
  c13_d_x = muDoubleScalarSin(c13_d_x);
  c13_e_x = c13_psi;
  c13_f_x = c13_e_x;
  c13_f_x = muDoubleScalarSin(c13_f_x);
  c13_g_x = c13_psi;
  c13_h_x = c13_g_x;
  c13_h_x = muDoubleScalarCos(c13_h_x);
  c13_R[0] = c13_b_x;
  c13_R[2] = -c13_d_x;
  c13_R[1] = c13_f_x;
  c13_R[3] = c13_h_x;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 5);
  c13_i14 = 0;
  for (c13_i15 = 0; c13_i15 < 2; c13_i15++) {
    c13_i16 = 0;
    for (c13_i17 = 0; c13_i17 < 2; c13_i17++) {
      c13_a[c13_i17 + c13_i14] = c13_R[c13_i16 + c13_i15];
      c13_i16 += 2;
    }

    c13_i14 += 2;
  }

  for (c13_i18 = 0; c13_i18 < 2; c13_i18++) {
    c13_b[c13_i18] = c13_Pd[c13_i18] - c13_P[c13_i18];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i19 = 0; c13_i19 < 2; c13_i19++) {
    c13_e[c13_i19] = 0.0;
  }

  for (c13_i20 = 0; c13_i20 < 2; c13_i20++) {
    c13_e[c13_i20] = 0.0;
  }

  for (c13_i21 = 0; c13_i21 < 2; c13_i21++) {
    c13_C[c13_i21] = c13_e[c13_i21];
  }

  for (c13_i22 = 0; c13_i22 < 2; c13_i22++) {
    c13_e[c13_i22] = c13_C[c13_i22];
  }

  for (c13_i23 = 0; c13_i23 < 2; c13_i23++) {
    c13_C[c13_i23] = c13_e[c13_i23];
  }

  for (c13_i24 = 0; c13_i24 < 2; c13_i24++) {
    c13_e[c13_i24] = c13_C[c13_i24];
  }

  for (c13_i25 = 0; c13_i25 < 2; c13_i25++) {
    c13_e[c13_i25] = 0.0;
    c13_i26 = 0;
    for (c13_i27 = 0; c13_i27 < 2; c13_i27++) {
      c13_e[c13_i25] += c13_a[c13_i26 + c13_i25] * c13_b[c13_i27];
      c13_i26 += 2;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 6);
  c13_d[0] = c13_b_delta;
  c13_d[1] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 7);
  c13_z = c13_dgam - c13_Vd;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 9);
  c13_B = c13_b_delta;
  c13_y = c13_B;
  c13_b_y = c13_y;
  c13_c_y = 1.0 / c13_b_y;
  c13_a[0] = c13_b_kx;
  c13_a[2] = 0.0;
  c13_a[1] = 0.0;
  c13_a[3] = c13_b_ky;
  for (c13_i28 = 0; c13_i28 < 2; c13_i28++) {
    c13_b[c13_i28] = c13_e[c13_i28] - c13_d[c13_i28];
  }

  c13_b_tanh(chartInstance, c13_b);
  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i29 = 0; c13_i29 < 2; c13_i29++) {
    c13_d_y[c13_i29] = 0.0;
    c13_i30 = 0;
    for (c13_i31 = 0; c13_i31 < 2; c13_i31++) {
      c13_d_y[c13_i29] += c13_a[c13_i30 + c13_i29] * c13_b[c13_i31];
      c13_i30 += 2;
    }
  }

  c13_i32 = 0;
  for (c13_i33 = 0; c13_i33 < 2; c13_i33++) {
    c13_i34 = 0;
    for (c13_i35 = 0; c13_i35 < 2; c13_i35++) {
      c13_a[c13_i35 + c13_i32] = c13_R[c13_i34 + c13_i33];
      c13_i34 += 2;
    }

    c13_i32 += 2;
  }

  for (c13_i36 = 0; c13_i36 < 2; c13_i36++) {
    c13_b[c13_i36] = c13_Vc[c13_i36];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i37 = 0; c13_i37 < 2; c13_i37++) {
    c13_C[c13_i37] = 0.0;
    c13_i38 = 0;
    for (c13_i39 = 0; c13_i39 < 2; c13_i39++) {
      c13_C[c13_i37] += c13_a[c13_i38 + c13_i37] * c13_b[c13_i39];
      c13_i38 += 2;
    }
  }

  c13_b_a = c13_Vd;
  c13_i40 = 0;
  for (c13_i41 = 0; c13_i41 < 2; c13_i41++) {
    c13_i42 = 0;
    for (c13_i43 = 0; c13_i43 < 2; c13_i43++) {
      c13_a[c13_i43 + c13_i40] = c13_R[c13_i42 + c13_i41];
      c13_i42 += 2;
    }

    c13_i40 += 2;
  }

  for (c13_i44 = 0; c13_i44 < 4; c13_i44++) {
    c13_a[c13_i44] *= c13_b_a;
  }

  for (c13_i45 = 0; c13_i45 < 2; c13_i45++) {
    c13_b[c13_i45] = c13_dPd[c13_i45];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i46 = 0; c13_i46 < 2; c13_i46++) {
    c13_e_y[c13_i46] = 0.0;
    c13_i47 = 0;
    for (c13_i48 = 0; c13_i48 < 2; c13_i48++) {
      c13_e_y[c13_i46] += c13_a[c13_i47 + c13_i46] * c13_b[c13_i48];
      c13_i47 += 2;
    }
  }

  c13_i49 = 0;
  for (c13_i50 = 0; c13_i50 < 2; c13_i50++) {
    c13_a[c13_i49] = 1.0 - (real_T)c13_i50;
    c13_i49 += 2;
  }

  c13_a[1] = 0.0;
  c13_a[3] = c13_c_y;
  for (c13_i51 = 0; c13_i51 < 2; c13_i51++) {
    c13_d_y[c13_i51] = (c13_d_y[c13_i51] - c13_C[c13_i51]) + c13_e_y[c13_i51];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i52 = 0; c13_i52 < 2; c13_i52++) {
    c13_Ud[c13_i52] = 0.0;
  }

  for (c13_i53 = 0; c13_i53 < 2; c13_i53++) {
    c13_Ud[c13_i53] = 0.0;
  }

  for (c13_i54 = 0; c13_i54 < 2; c13_i54++) {
    c13_C[c13_i54] = c13_Ud[c13_i54];
  }

  for (c13_i55 = 0; c13_i55 < 2; c13_i55++) {
    c13_Ud[c13_i55] = c13_C[c13_i55];
  }

  for (c13_i56 = 0; c13_i56 < 2; c13_i56++) {
    c13_C[c13_i56] = c13_Ud[c13_i56];
  }

  for (c13_i57 = 0; c13_i57 < 2; c13_i57++) {
    c13_Ud[c13_i57] = c13_C[c13_i57];
  }

  for (c13_i58 = 0; c13_i58 < 2; c13_i58++) {
    c13_Ud[c13_i58] = 0.0;
    c13_i59 = 0;
    for (c13_i60 = 0; c13_i60 < 2; c13_i60++) {
      c13_Ud[c13_i58] += c13_a[c13_i59 + c13_i58] * c13_d_y[c13_i60];
      c13_i59 += 2;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 10);
  c13_c_a = -c13_b_kz;
  c13_b_b = c13_z;
  c13_f_y = c13_c_a * c13_b_b;
  for (c13_i61 = 0; c13_i61 < 2; c13_i61++) {
    c13_d_a[c13_i61] = c13_e[c13_i61] - c13_d[c13_i61];
  }

  c13_i62 = 0;
  for (c13_i63 = 0; c13_i63 < 2; c13_i63++) {
    c13_i64 = 0;
    for (c13_i65 = 0; c13_i65 < 2; c13_i65++) {
      c13_a[c13_i65 + c13_i62] = c13_R[c13_i64 + c13_i63];
      c13_i64 += 2;
    }

    c13_i62 += 2;
  }

  c13_b_eml_scalar_eg(chartInstance);
  c13_b_eml_scalar_eg(chartInstance);
  c13_i66 = 0;
  for (c13_i67 = 0; c13_i67 < 2; c13_i67++) {
    c13_g_y[c13_i67] = 0.0;
    for (c13_i68 = 0; c13_i68 < 2; c13_i68++) {
      c13_g_y[c13_i67] += c13_d_a[c13_i68] * c13_a[c13_i68 + c13_i66];
    }

    c13_i66 += 2;
  }

  for (c13_i69 = 0; c13_i69 < 2; c13_i69++) {
    c13_b[c13_i69] = c13_dPd[c13_i69];
  }

  c13_c_eml_scalar_eg(chartInstance);
  c13_c_eml_scalar_eg(chartInstance);
  c13_h_y = 0.0;
  for (c13_k = 1; c13_k < 3; c13_k++) {
    c13_b_k = c13_k;
    c13_h_y += c13_g_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c13_b_k), 1, 2, 1, 0) - 1] *
      c13_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c13_b_k), 1, 2, 1, 0) - 1];
  }

  c13_ddgam = c13_f_y - c13_h_y;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -10);
  _SFD_SYMBOL_SCOPE_POP();
  for (c13_i70 = 0; c13_i70 < 2; c13_i70++) {
    (*c13_b_Ud)[c13_i70] = c13_Ud[c13_i70];
  }

  for (c13_i71 = 0; c13_i71 < 2; c13_i71++) {
    (*c13_b_e)[c13_i71] = c13_e[c13_i71];
  }

  *c13_b_ddgam = c13_ddgam;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
}

static void initSimStructsc13_simulation(SFc13_simulationInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber)
{
}

static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static real_T c13_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_ddgam, const char_T *c13_identifier)
{
  real_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_ddgam),
    &c13_thisId);
  sf_mex_destroy(&c13_ddgam);
  return c13_y;
}

static real_T c13_b_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d4;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d4, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d4;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_ddgam;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_ddgam = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_ddgam),
    &c13_thisId);
  sf_mex_destroy(&c13_ddgam);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i72;
  real_T c13_b_inData[2];
  int32_T c13_i73;
  real_T c13_u[2];
  const mxArray *c13_y = NULL;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i72 = 0; c13_i72 < 2; c13_i72++) {
    c13_b_inData[c13_i72] = (*(real_T (*)[2])c13_inData)[c13_i72];
  }

  for (c13_i73 = 0; c13_i73 < 2; c13_i73++) {
    c13_u[c13_i73] = c13_b_inData[c13_i73];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_c_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_e, const char_T *c13_identifier, real_T c13_y[2])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_e), &c13_thisId, c13_y);
  sf_mex_destroy(&c13_e);
}

static void c13_d_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, real_T c13_y[2])
{
  real_T c13_dv2[2];
  int32_T c13_i74;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv2, 1, 0, 0U, 1, 0U, 1, 2);
  for (c13_i74 = 0; c13_i74 < 2; c13_i74++) {
    c13_y[c13_i74] = c13_dv2[c13_i74];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_e;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[2];
  int32_T c13_i75;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_e = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_e), &c13_thisId, c13_y);
  sf_mex_destroy(&c13_e);
  for (c13_i75 = 0; c13_i75 < 2; c13_i75++) {
    (*(real_T (*)[2])c13_outData)[c13_i75] = c13_y[c13_i75];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i76;
  int32_T c13_i77;
  int32_T c13_i78;
  real_T c13_b_inData[4];
  int32_T c13_i79;
  int32_T c13_i80;
  int32_T c13_i81;
  real_T c13_u[4];
  const mxArray *c13_y = NULL;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_i76 = 0;
  for (c13_i77 = 0; c13_i77 < 2; c13_i77++) {
    for (c13_i78 = 0; c13_i78 < 2; c13_i78++) {
      c13_b_inData[c13_i78 + c13_i76] = (*(real_T (*)[4])c13_inData)[c13_i78 +
        c13_i76];
    }

    c13_i76 += 2;
  }

  c13_i79 = 0;
  for (c13_i80 = 0; c13_i80 < 2; c13_i80++) {
    for (c13_i81 = 0; c13_i81 < 2; c13_i81++) {
      c13_u[c13_i81 + c13_i79] = c13_b_inData[c13_i81 + c13_i79];
    }

    c13_i79 += 2;
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_e_emlrt_marshallIn(SFc13_simulationInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, real_T c13_y[4])
{
  real_T c13_dv3[4];
  int32_T c13_i82;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv3, 1, 0, 0U, 1, 0U, 2, 2,
                2);
  for (c13_i82 = 0; c13_i82 < 4; c13_i82++) {
    c13_y[c13_i82] = c13_dv3[c13_i82];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_R;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[4];
  int32_T c13_i83;
  int32_T c13_i84;
  int32_T c13_i85;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_R = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_R), &c13_thisId, c13_y);
  sf_mex_destroy(&c13_R);
  c13_i83 = 0;
  for (c13_i84 = 0; c13_i84 < 2; c13_i84++) {
    for (c13_i85 = 0; c13_i85 < 2; c13_i85++) {
      (*(real_T (*)[4])c13_outData)[c13_i85 + c13_i83] = c13_y[c13_i85 + c13_i83];
    }

    c13_i83 += 2;
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

const mxArray *sf_c13_simulation_get_eml_resolved_functions_info(void)
{
  const mxArray *c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  sf_mex_assign(&c13_nameCaptureInfo, sf_mex_createstruct("structure", 2, 38, 1),
                FALSE);
  c13_info_helper(&c13_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c13_nameCaptureInfo);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(const mxArray **c13_info)
{
  const mxArray *c13_rhs0 = NULL;
  const mxArray *c13_lhs0 = NULL;
  const mxArray *c13_rhs1 = NULL;
  const mxArray *c13_lhs1 = NULL;
  const mxArray *c13_rhs2 = NULL;
  const mxArray *c13_lhs2 = NULL;
  const mxArray *c13_rhs3 = NULL;
  const mxArray *c13_lhs3 = NULL;
  const mxArray *c13_rhs4 = NULL;
  const mxArray *c13_lhs4 = NULL;
  const mxArray *c13_rhs5 = NULL;
  const mxArray *c13_lhs5 = NULL;
  const mxArray *c13_rhs6 = NULL;
  const mxArray *c13_lhs6 = NULL;
  const mxArray *c13_rhs7 = NULL;
  const mxArray *c13_lhs7 = NULL;
  const mxArray *c13_rhs8 = NULL;
  const mxArray *c13_lhs8 = NULL;
  const mxArray *c13_rhs9 = NULL;
  const mxArray *c13_lhs9 = NULL;
  const mxArray *c13_rhs10 = NULL;
  const mxArray *c13_lhs10 = NULL;
  const mxArray *c13_rhs11 = NULL;
  const mxArray *c13_lhs11 = NULL;
  const mxArray *c13_rhs12 = NULL;
  const mxArray *c13_lhs12 = NULL;
  const mxArray *c13_rhs13 = NULL;
  const mxArray *c13_lhs13 = NULL;
  const mxArray *c13_rhs14 = NULL;
  const mxArray *c13_lhs14 = NULL;
  const mxArray *c13_rhs15 = NULL;
  const mxArray *c13_lhs15 = NULL;
  const mxArray *c13_rhs16 = NULL;
  const mxArray *c13_lhs16 = NULL;
  const mxArray *c13_rhs17 = NULL;
  const mxArray *c13_lhs17 = NULL;
  const mxArray *c13_rhs18 = NULL;
  const mxArray *c13_lhs18 = NULL;
  const mxArray *c13_rhs19 = NULL;
  const mxArray *c13_lhs19 = NULL;
  const mxArray *c13_rhs20 = NULL;
  const mxArray *c13_lhs20 = NULL;
  const mxArray *c13_rhs21 = NULL;
  const mxArray *c13_lhs21 = NULL;
  const mxArray *c13_rhs22 = NULL;
  const mxArray *c13_lhs22 = NULL;
  const mxArray *c13_rhs23 = NULL;
  const mxArray *c13_lhs23 = NULL;
  const mxArray *c13_rhs24 = NULL;
  const mxArray *c13_lhs24 = NULL;
  const mxArray *c13_rhs25 = NULL;
  const mxArray *c13_lhs25 = NULL;
  const mxArray *c13_rhs26 = NULL;
  const mxArray *c13_lhs26 = NULL;
  const mxArray *c13_rhs27 = NULL;
  const mxArray *c13_lhs27 = NULL;
  const mxArray *c13_rhs28 = NULL;
  const mxArray *c13_lhs28 = NULL;
  const mxArray *c13_rhs29 = NULL;
  const mxArray *c13_lhs29 = NULL;
  const mxArray *c13_rhs30 = NULL;
  const mxArray *c13_lhs30 = NULL;
  const mxArray *c13_rhs31 = NULL;
  const mxArray *c13_lhs31 = NULL;
  const mxArray *c13_rhs32 = NULL;
  const mxArray *c13_lhs32 = NULL;
  const mxArray *c13_rhs33 = NULL;
  const mxArray *c13_lhs33 = NULL;
  const mxArray *c13_rhs34 = NULL;
  const mxArray *c13_lhs34 = NULL;
  const mxArray *c13_rhs35 = NULL;
  const mxArray *c13_lhs35 = NULL;
  const mxArray *c13_rhs36 = NULL;
  const mxArray *c13_lhs36 = NULL;
  const mxArray *c13_rhs37 = NULL;
  const mxArray *c13_lhs37 = NULL;
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("cos"), "name", "name", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1343833972U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c13_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822322U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c13_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("sin"), "name", "name", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1343833986U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c13_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822336U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c13_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("mtimes"), "name", "name", 4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717478U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c13_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c13_rhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c13_rhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c13_rhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717470U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c13_rhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_blas_inline"), "name",
                  "name", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1299080368U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c13_rhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold"),
                  "context", "context", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("mtimes"), "name", "name", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717478U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c13_rhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 11);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c13_rhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c13_rhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"),
                  "context", "context", 13);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_refblas_xgemm"), "name",
                  "name", 13);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1360285950U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c13_rhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 14);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("mrdivide"), "name", "name",
                  14);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1373310108U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1319733566U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c13_rhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 15);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("rdivide"), "name", "name",
                  15);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717480U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c13_rhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 16);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c13_rhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 17);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c13_rhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_div"), "name", "name",
                  18);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717466U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c13_rhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 19);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("tanh"), "name", "name", 19);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tanh.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1343833988U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c13_rhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tanh.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_tanh"), "name",
                  "name", 20);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tanh.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822340U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c13_rhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_xdotu"), "name", "name",
                  21);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717470U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c13_rhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_blas_inline"), "name",
                  "name", 22);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1299080368U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c13_rhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_xdot"), "name", "name",
                  23);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363717468U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c13_rhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m"), "context",
                  "context", 24);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_blas_inline"), "name",
                  "name", 24);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1299080368U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c13_rhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m"),
                  "context", "context", 25);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 25);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c13_rhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_refblas_xdot"), "name",
                  "name", 26);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1299080372U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c13_rhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_refblas_xdotx"), "name",
                  "name", 27);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1360285950U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c13_rhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 28);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 28);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c13_rhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 29);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c13_rhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 30);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 30);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822378U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c13_rhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 31);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c13_rhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 32);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 32);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822380U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c13_rhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 33);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c13_rhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 34);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 34);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286822378U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c13_rhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 35);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 35);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c13_rhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 36);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1346513940U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c13_rhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 37);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("intmax"), "name", "name", 37);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c13_rhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c13_lhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs37), "lhs", "lhs",
                  37);
  sf_mex_destroy(&c13_rhs0);
  sf_mex_destroy(&c13_lhs0);
  sf_mex_destroy(&c13_rhs1);
  sf_mex_destroy(&c13_lhs1);
  sf_mex_destroy(&c13_rhs2);
  sf_mex_destroy(&c13_lhs2);
  sf_mex_destroy(&c13_rhs3);
  sf_mex_destroy(&c13_lhs3);
  sf_mex_destroy(&c13_rhs4);
  sf_mex_destroy(&c13_lhs4);
  sf_mex_destroy(&c13_rhs5);
  sf_mex_destroy(&c13_lhs5);
  sf_mex_destroy(&c13_rhs6);
  sf_mex_destroy(&c13_lhs6);
  sf_mex_destroy(&c13_rhs7);
  sf_mex_destroy(&c13_lhs7);
  sf_mex_destroy(&c13_rhs8);
  sf_mex_destroy(&c13_lhs8);
  sf_mex_destroy(&c13_rhs9);
  sf_mex_destroy(&c13_lhs9);
  sf_mex_destroy(&c13_rhs10);
  sf_mex_destroy(&c13_lhs10);
  sf_mex_destroy(&c13_rhs11);
  sf_mex_destroy(&c13_lhs11);
  sf_mex_destroy(&c13_rhs12);
  sf_mex_destroy(&c13_lhs12);
  sf_mex_destroy(&c13_rhs13);
  sf_mex_destroy(&c13_lhs13);
  sf_mex_destroy(&c13_rhs14);
  sf_mex_destroy(&c13_lhs14);
  sf_mex_destroy(&c13_rhs15);
  sf_mex_destroy(&c13_lhs15);
  sf_mex_destroy(&c13_rhs16);
  sf_mex_destroy(&c13_lhs16);
  sf_mex_destroy(&c13_rhs17);
  sf_mex_destroy(&c13_lhs17);
  sf_mex_destroy(&c13_rhs18);
  sf_mex_destroy(&c13_lhs18);
  sf_mex_destroy(&c13_rhs19);
  sf_mex_destroy(&c13_lhs19);
  sf_mex_destroy(&c13_rhs20);
  sf_mex_destroy(&c13_lhs20);
  sf_mex_destroy(&c13_rhs21);
  sf_mex_destroy(&c13_lhs21);
  sf_mex_destroy(&c13_rhs22);
  sf_mex_destroy(&c13_lhs22);
  sf_mex_destroy(&c13_rhs23);
  sf_mex_destroy(&c13_lhs23);
  sf_mex_destroy(&c13_rhs24);
  sf_mex_destroy(&c13_lhs24);
  sf_mex_destroy(&c13_rhs25);
  sf_mex_destroy(&c13_lhs25);
  sf_mex_destroy(&c13_rhs26);
  sf_mex_destroy(&c13_lhs26);
  sf_mex_destroy(&c13_rhs27);
  sf_mex_destroy(&c13_lhs27);
  sf_mex_destroy(&c13_rhs28);
  sf_mex_destroy(&c13_lhs28);
  sf_mex_destroy(&c13_rhs29);
  sf_mex_destroy(&c13_lhs29);
  sf_mex_destroy(&c13_rhs30);
  sf_mex_destroy(&c13_lhs30);
  sf_mex_destroy(&c13_rhs31);
  sf_mex_destroy(&c13_lhs31);
  sf_mex_destroy(&c13_rhs32);
  sf_mex_destroy(&c13_lhs32);
  sf_mex_destroy(&c13_rhs33);
  sf_mex_destroy(&c13_lhs33);
  sf_mex_destroy(&c13_rhs34);
  sf_mex_destroy(&c13_lhs34);
  sf_mex_destroy(&c13_rhs35);
  sf_mex_destroy(&c13_lhs35);
  sf_mex_destroy(&c13_rhs36);
  sf_mex_destroy(&c13_lhs36);
  sf_mex_destroy(&c13_rhs37);
  sf_mex_destroy(&c13_lhs37);
}

static const mxArray *c13_emlrt_marshallOut(char * c13_u)
{
  const mxArray *c13_y = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c13_u)), FALSE);
  return c13_y;
}

static const mxArray *c13_b_emlrt_marshallOut(uint32_T c13_u)
{
  const mxArray *c13_y = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c13_y;
}

static void c13_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance)
{
}

static void c13_tanh(SFc13_simulationInstanceStruct *chartInstance, real_T
                     c13_x[2], real_T c13_b_x[2])
{
  int32_T c13_i86;
  for (c13_i86 = 0; c13_i86 < 2; c13_i86++) {
    c13_b_x[c13_i86] = c13_x[c13_i86];
  }

  c13_b_tanh(chartInstance, c13_b_x);
}

static void c13_b_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance)
{
}

static void c13_c_eml_scalar_eg(SFc13_simulationInstanceStruct *chartInstance)
{
}

static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static int32_T c13_f_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i87;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i87, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i87;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_g_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_simulation, const char_T
  *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_simulation), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_simulation);
  return c13_y;
}

static uint8_T c13_h_emlrt_marshallIn(SFc13_simulationInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_tanh(SFc13_simulationInstanceStruct *chartInstance, real_T
  c13_x[2])
{
  int32_T c13_k;
  real_T c13_b_k;
  real_T c13_b_x;
  real_T c13_c_x;
  for (c13_k = 0; c13_k < 2; c13_k++) {
    c13_b_k = 1.0 + (real_T)c13_k;
    c13_b_x = c13_x[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c13_b_k), 1, 2, 1, 0) - 1];
    c13_c_x = c13_b_x;
    c13_c_x = muDoubleScalarTanh(c13_c_x);
    c13_x[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c13_b_k), 1, 2, 1, 0) - 1] = c13_c_x;
  }
}

static void init_dsm_address_info(SFc13_simulationInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c13_simulation_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1361279294U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2228128789U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3442779983U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(728325978U);
}

mxArray *sf_c13_simulation_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("y8e0cPHhL8wowOVjmeuxWB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c13_simulation_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c13_simulation_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c13_simulation(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[18],T\"Ud\",},{M[1],M[21],T\"ddgam\",},{M[1],M[19],T\"e\",},{M[8],M[0],T\"is_active_c13_simulation\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_simulation_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_simulationInstanceStruct *chartInstance;
    chartInstance = (SFc13_simulationInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _simulationMachineNumber_,
           13,
           1,
           1,
           14,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_simulationMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_simulationMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _simulationMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Vc");
          _SFD_SET_DATA_PROPS(1,1,1,0,"P");
          _SFD_SET_DATA_PROPS(2,1,1,0,"psi");
          _SFD_SET_DATA_PROPS(3,10,0,0,"kx");
          _SFD_SET_DATA_PROPS(4,10,0,0,"ky");
          _SFD_SET_DATA_PROPS(5,10,0,0,"kz");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Pd");
          _SFD_SET_DATA_PROPS(7,1,1,0,"dPd");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Vd");
          _SFD_SET_DATA_PROPS(9,10,0,0,"delta");
          _SFD_SET_DATA_PROPS(10,2,0,1,"Ud");
          _SFD_SET_DATA_PROPS(11,2,0,1,"e");
          _SFD_SET_DATA_PROPS(12,1,1,0,"dgam");
          _SFD_SET_DATA_PROPS(13,2,0,1,"ddgam");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,266);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)
            c13_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)
            c13_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);

        {
          real_T *c13_psi;
          real_T *c13_Vd;
          real_T *c13_dgam;
          real_T *c13_ddgam;
          real_T (*c13_Vc)[2];
          real_T (*c13_P)[2];
          real_T (*c13_Pd)[2];
          real_T (*c13_dPd)[2];
          real_T (*c13_Ud)[2];
          real_T (*c13_e)[2];
          c13_ddgam = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c13_dgam = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c13_e = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
          c13_Ud = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c13_Vd = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c13_dPd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
          c13_Pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
          c13_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c13_P = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c13_Vc = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c13_Vc);
          _SFD_SET_DATA_VALUE_PTR(1U, *c13_P);
          _SFD_SET_DATA_VALUE_PTR(2U, c13_psi);
          _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c13_kx);
          _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c13_ky);
          _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c13_kz);
          _SFD_SET_DATA_VALUE_PTR(6U, *c13_Pd);
          _SFD_SET_DATA_VALUE_PTR(7U, *c13_dPd);
          _SFD_SET_DATA_VALUE_PTR(8U, c13_Vd);
          _SFD_SET_DATA_VALUE_PTR(9U, &chartInstance->c13_delta);
          _SFD_SET_DATA_VALUE_PTR(10U, *c13_Ud);
          _SFD_SET_DATA_VALUE_PTR(11U, *c13_e);
          _SFD_SET_DATA_VALUE_PTR(12U, c13_dgam);
          _SFD_SET_DATA_VALUE_PTR(13U, c13_ddgam);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _simulationMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "QTzmt1qx9WtHjQwVoCpiiG";
}

static void sf_opaque_initialize_c13_simulation(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_simulationInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c13_simulation((SFc13_simulationInstanceStruct*)
    chartInstanceVar);
  initialize_c13_simulation((SFc13_simulationInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c13_simulation(void *chartInstanceVar)
{
  enable_c13_simulation((SFc13_simulationInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c13_simulation(void *chartInstanceVar)
{
  disable_c13_simulation((SFc13_simulationInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c13_simulation(void *chartInstanceVar)
{
  sf_c13_simulation((SFc13_simulationInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_simulation(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_simulation
    ((SFc13_simulationInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_simulation();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c13_simulation(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_simulation();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_simulation((SFc13_simulationInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_simulation(SimStruct* S)
{
  return sf_internal_get_sim_state_c13_simulation(S);
}

static void sf_opaque_set_sim_state_c13_simulation(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c13_simulation(S, st);
}

static void sf_opaque_terminate_c13_simulation(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_simulationInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_simulation_optimization_info();
    }

    finalize_c13_simulation((SFc13_simulationInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_simulation((SFc13_simulationInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_simulation(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c13_simulation((SFc13_simulationInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_simulation(SimStruct *S)
{
  /* Actual parameters from chart:
     delta kx ky kz
   */
  const char_T *rtParamNames[] = { "delta", "kx", "ky", "kz" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for delta*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for kx*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for ky*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for kz*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_simulation_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,13,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,13);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3961098328U));
  ssSetChecksum1(S,(2373532266U));
  ssSetChecksum2(S,(79633212U));
  ssSetChecksum3(S,(3271377554U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_simulation(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_simulation(SimStruct *S)
{
  SFc13_simulationInstanceStruct *chartInstance;
  chartInstance = (SFc13_simulationInstanceStruct *)utMalloc(sizeof
    (SFc13_simulationInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_simulationInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c13_simulation;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c13_simulation;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c13_simulation;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c13_simulation;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c13_simulation;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c13_simulation;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c13_simulation;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c13_simulation;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_simulation;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_simulation;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c13_simulation;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c13_simulation_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_simulation(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_simulation(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_simulation(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_simulation_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
