/*
 * Program: i76.exe
 * Function: shell_cb_2c_audio_helper
 * Entry: 00421d50
 * Signature: bool __cdecl shell_cb_2c_audio_helper(int param_1, int param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=high] ShellMain callback slot +0x2c. Finds or
   creates an audio object keyed by caller ID, converts integer coordinates to floats, and
   inserts/updates it in the audio object system. */

bool __cdecl shell_cb_2c_audio_helper(int param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 local_2c [5];
  float local_18;
  float local_14;
  float local_10;
  
  if (DAT_00524564 == (undefined4 *)0x0) {
    return false;
  }
  puVar4 = local_2c;
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  local_14 = (float)param_2;
  local_10 = (float)param_3;
  for (piVar3 = (int *)DAT_00524564[7]; piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
    if ((piVar3[0x15] != 0) && (piVar3[0x13] == param_1)) goto LAB_00421dc9;
  }
  for (piVar3 = (int *)DAT_00524564[8]; piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
    if ((piVar3[0x15] != 0) && (piVar3[0x13] == param_1)) goto LAB_00421dc9;
  }
  piVar3 = (int *)0x0;
LAB_00421dc9:
  local_18 = (float)param_4;
  piVar1 = (int *)allocate_audio_object_record_for_world_object((char *)0x0,0,local_2c,(char *)0x0);
  if (piVar1 != (int *)0x0) {
    piVar1[0x13] = param_1;
    piVar1[0x1e] = piVar1[0x1e] | 0x200;
  }
  if (piVar3 == (int *)0x0) {
    sprintf((char *)(piVar1 + 1),s__d_s_004ed7f0,DAT_00524568,s__sse_004ed7f8);
    DAT_00524568 = DAT_00524568 + 1;
    if (100 < DAT_00524568) {
      DAT_00524568 = 0;
    }
  }
  else {
    if (piVar1 == (int *)0x0) {
      return false;
    }
    iVar2 = 0xb;
    piVar5 = piVar1;
    while( true ) {
      piVar5 = piVar5 + 1;
      piVar3 = piVar3 + 1;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      *piVar5 = *piVar3;
    }
  }
  iVar2 = attach_audio_object_resource_and_buffers(DAT_00524564,piVar1,(int *)0x0);
  if (iVar2 == 0) {
    piVar1 = (int *)0x0;
  }
  return piVar1 != (int *)0x0;
}


