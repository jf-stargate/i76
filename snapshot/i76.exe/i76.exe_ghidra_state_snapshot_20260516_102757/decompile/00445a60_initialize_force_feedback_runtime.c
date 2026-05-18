/*
 * Program: i76.exe
 * Function: initialize_force_feedback_runtime
 * Entry: 00445a60
 * Signature: undefined __stdcall initialize_force_feedback_runtime(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Initializes force-feedback/runtime parameter globals, resolves optional APIs, and
   creates the runtime parameter heap. */

void initialize_force_feedback_runtime(void)

{
  bool bVar1;
  undefined3 extraout_var;
  char local_50 [80];
  
  _DAT_0052bbd4 = 1;
  _s_l_004f2328 = 0x16c;
  g_runtime_parameter_heap_ready = 0;
  _DAT_004f2490 = DAT_005dcf7c;
  _DAT_004f248c = &DAT_005dcf3c;
  g_damage_runtime_param_front_angle = 0;
  g_damage_runtime_param_up_angle = 0;
  g_damage_runtime_param_side_angle = 0;
  g_damage_runtime_param_impulse_angle = 0;
  _DAT_004f232c = 0;
  _DAT_004f2330 = 0;
  _DAT_004f2470 = 0;
  _DAT_004f2474 = 0;
  _DAT_004f2488 = 0;
  bVar1 = resolve_optional_win32_apis();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    g_runtime_parameter_heap_ready = 1;
    sprintf(local_50,s_Forcefeed_004f2318);
    g_runtime_parameter_heap = HeapCreate(0,0,0);
    DAT_004f2314 = 0xffffffff;
  }
  return;
}


