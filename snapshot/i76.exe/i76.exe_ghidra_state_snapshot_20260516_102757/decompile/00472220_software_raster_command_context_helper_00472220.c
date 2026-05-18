/*
 * Program: i76.exe
 * Function: software_raster_command_context_helper_00472220
 * Entry: 00472220
 * Signature: undefined __cdecl software_raster_command_context_helper_00472220(float * param_1, int param_2, float param_3, undefined4 param_4, float param_5, float param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: software raster command context helper
   based on adjacent named subsystem context. */

void __cdecl
software_raster_command_context_helper_00472220
          (float *param_1,int param_2,float param_3,undefined4 param_4,float param_5,float param_6)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  undefined8 uVar4;
  float local_218 [10];
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  float local_1d8 [4];
  float local_1c8;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  undefined4 local_1a8;
  int local_19c;
  
  pfVar2 = local_1d8;
  for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = 0.0;
    pfVar2 = pfVar2 + 1;
  }
  local_19c = param_2;
  if (param_3 < _DAT_004be5a8) {
    param_3 = _DAT_004be5a8;
  }
  if (_DAT_004be5ac < param_3) {
    param_3 = _DAT_004be5ac;
  }
  if (param_5 < _DAT_004be5b0) {
    param_5 = 100.0;
  }
  if (_DAT_004be5b4 < param_5) {
    param_5 = 100000.0;
  }
  uVar4 = mission_flow_map_context_helper_0049d400(param_3 * _DAT_004be5b8);
  local_1c8 = param_5;
  local_1d8[0] = (float)((*(int *)(param_2 + 0x24) - *(int *)(param_2 + 0x1c)) + 1) * _DAT_004be5b8;
  local_1a8 = param_4;
  local_1d8[1] = (float)((*(int *)(param_2 + 0x28) - *(int *)(param_2 + 0x20)) + 1) * _DAT_004be5b8;
  local_1ac = (float)uVar4 / (float)((ulonglong)uVar4 >> 0x20);
  local_1bc = (float)*(int *)(param_2 + 0x1c);
  local_1b8 = (float)*(int *)(param_2 + 0x20);
  local_1b4 = (float)*(int *)(param_2 + 0x24);
  local_1b0 = (float)*(int *)(param_2 + 0x28);
  software_raster_command_context_helper_00472400(local_1d8,param_6);
  pfVar2 = (float *)&DAT_004faed8;
  pfVar3 = local_218;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  local_1f0 = 0;
  local_1ec = 0;
  local_1e8 = 0;
  local_1e4 = 0x3ff00000;
  local_1e0 = 0;
  local_1dc = 0;
  software_raster_queue_context_helper_00472990((int)local_1d8,local_218);
  pfVar2 = local_1d8;
  for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


