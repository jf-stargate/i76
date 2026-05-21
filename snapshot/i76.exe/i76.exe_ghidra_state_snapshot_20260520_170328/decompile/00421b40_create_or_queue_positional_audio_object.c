/*
 * Program: i76.exe
 * Function: create_or_queue_positional_audio_object
 * Entry: 00421b40
 * Signature: int * __cdecl create_or_queue_positional_audio_object(char * param_1, int param_2, undefined4 * param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Creates or queues a named audio object with optional world-object distance
   gating. */

int * __cdecl
create_or_queue_positional_audio_object(char *param_1,int param_2,undefined4 *param_3,int *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  float *pfVar6;
  int *piVar7;
  double local_34;
  double local_28;
  float local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  bVar4 = false;
  if ((((DAT_00524564 == (undefined4 *)0x0) || (param_1 == (char *)0x0)) || (*param_1 == '\0')) ||
     (((((byte)g_runtime_display_input_mode & 0x3e) != 0 &&
       (iVar5 = is_damage_side_effects_suppressed(), iVar5 == 0)) &&
      ((param_3 == (undefined4 *)0x0 || ((*(byte *)(param_3 + 4) & 0x10) == 0)))))) {
    return (int *)0x0;
  }
  if (((param_2 != 0) && (param_4 != (int *)0x0)) &&
     ((param_4[3] != 1 &&
      (((DAT_004c2908 != (int *)0x0 ||
        (DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry(),
        DAT_004c2908 != (int *)0x0)) && (iVar5 = *DAT_004c2908, iVar5 != 0)))))) {
    pfVar6 = (float *)compose_world_object_runtime_transform((float *)&local_34,param_2);
    local_20 = pfVar6[2];
    fVar1 = *pfVar6 - (float)*(double *)(iVar5 + 0x40);
    fVar3 = pfVar6[1] - (float)*(double *)(iVar5 + 0x48);
    fVar2 = local_20 - (float)*(double *)(iVar5 + 0x50);
    local_34 = (double)fVar1;
    local_28 = (double)fVar3;
    if ((float)_DAT_004bccf0 <= fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1) {
      return (int *)0x0;
    }
  }
  if (DAT_00524564 != (undefined4 *)0x0) {
    for (piVar7 = (int *)DAT_00524564[7]; piVar7 != (int *)0x0; piVar7 = (int *)*piVar7) {
      if ((piVar7[0x17] == param_2) && (iVar5 = _stricmp((char *)(piVar7 + 1),param_1), iVar5 == 0))
      goto LAB_00421c81;
    }
  }
  piVar7 = (int *)0x0;
LAB_00421c81:
  if ((piVar7 != (int *)0x0) && (piVar7[0xf] == 2)) {
    *(char *)(piVar7 + 0x1d) = (char)piVar7[0x1d] + '\x01';
    return piVar7;
  }
  if (((param_2 != 0) && (iVar5 = get_root_ancestor_world_object(param_2), iVar5 != 0)) &&
     ((*(byte *)(iVar5 + 0x10) & 0x10) != 0)) {
    if (param_4 == (int *)0x0) {
      param_4 = &local_1c;
      local_1c = 0x30534147;
      local_14 = 0xffffffff;
      local_10 = 0xffffffff;
      local_c = 0xffffffff;
      local_8 = 0xffffffff;
      local_4 = 0xffffffff;
      local_18 = 0x14;
    }
    else {
      param_4[1] = param_4[1] + 0x14;
    }
  }
  piVar7 = (int *)allocate_audio_object_record_for_world_object(param_1,param_2,param_3,(char *)0x0)
  ;
  if ((piVar7 != (int *)0x0) &&
     (iVar5 = attach_audio_object_resource_and_buffers(DAT_00524564,piVar7,param_4), iVar5 != 0)) {
    bVar4 = true;
  }
  if (!bVar4) {
    piVar7 = (int *)0x0;
  }
  return piVar7;
}


