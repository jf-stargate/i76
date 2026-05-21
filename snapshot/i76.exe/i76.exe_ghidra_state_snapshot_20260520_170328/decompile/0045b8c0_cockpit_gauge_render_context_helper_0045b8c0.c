/*
 * Program: i76.exe
 * Function: cockpit_gauge_render_context_helper_0045b8c0
 * Entry: 0045b8c0
 * Signature: undefined __cdecl cockpit_gauge_render_context_helper_0045b8c0(float * param_1, uint * param_2, int param_3, int param_4, int param_5, int param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: cockpit gauge render context helper
   based on prior focused closure context. */

void __cdecl
cockpit_gauge_render_context_helper_0045b8c0
          (float *param_1,uint *param_2,int param_3,int param_4,int param_5,int param_6)

{
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_48 = (float)(param_5 + param_3);
  local_2c = (float)(param_6 + param_4);
  local_60 = (float)param_3;
  local_5c = (float)param_4;
  local_58 = _DAT_004bdfd8;
  local_40 = _DAT_004bdfd8;
  local_54 = DAT_004fa8e8;
  local_50 = DAT_004fa8ec;
  local_4c = DAT_004fa8f0;
  local_28 = _DAT_004bdfd8;
  local_3c = DAT_004fa8f4;
  local_10 = _DAT_004bdfd8;
  local_38 = DAT_004fa8f8;
  local_20 = DAT_004fa904;
  local_34 = DAT_004fa8fc;
  local_24 = DAT_004fa900;
  local_1c = DAT_004fa908;
  local_c = DAT_004fa90c;
  local_8 = DAT_004fa910;
  local_4 = DAT_004fa914;
  local_44 = local_5c;
  local_30 = local_48;
  local_18 = local_60;
  local_14 = local_2c;
  if (*(int *)((int)param_1[0xf] + 8) == 1) {
    log_cache_memory_status(param_1,&local_60,(float *)0x4,param_2,(float *)0x8);
    return;
  }
  submit_lit_textured_polygon_to_renderer(param_1,&local_60,4,param_2,8);
  return;
}


