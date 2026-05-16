/*
 * Program: i76.exe
 * Function: evaluate_audio_object_priority_distance_state
 * Entry: 00422750
 * Signature: char __cdecl evaluate_audio_object_priority_distance_state(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Evaluates an audio object for priority, distance,
   duplicate-name limits, and active/pending list promotion decisions. */

char __cdecl evaluate_audio_object_priority_distance_state(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  int *piVar7;
  float *pfVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  double local_18;
  double local_c;
  float local_4;
  
  bVar6 = false;
  if ((((param_1[5] & 2U) != 0) && (*(int *)(DAT_00524564 + 0x14) == 0)) ||
     (((param_1[5] & 4U) != 0 && (*(int *)(DAT_00524564 + 0x18) == 0)))) {
    return '\x05';
  }
  iVar11 = param_1[0x17];
  if ((iVar11 != 0) &&
     (((DAT_004c2908 != (int *)0x0 ||
       (DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry(),
       DAT_004c2908 != (int *)0x0)) && (iVar9 = *DAT_004c2908, iVar9 != 0)))) {
    pfVar8 = (float *)compose_world_object_runtime_transform((float *)&local_18,iVar11);
    local_4 = pfVar8[2];
    fVar3 = *pfVar8 - (float)*(double *)(iVar9 + 0x40);
    fVar5 = pfVar8[1] - (float)*(double *)(iVar9 + 0x48);
    fVar4 = local_4 - (float)*(double *)(iVar9 + 0x50);
    local_18 = (double)fVar3;
    local_c = (double)fVar5;
    if ((float)_DAT_004bccf0 <= fVar4 * fVar4 + fVar5 * fVar5 + fVar3 * fVar3) {
      return '\x03';
    }
  }
  iVar11 = 0;
  piVar2 = param_1 + 1;
  if ((DAT_00524564 == 0) || ((char)*piVar2 == '\0')) {
    iVar11 = 0;
  }
  else {
    for (puVar1 = *(undefined4 **)(DAT_00524564 + 0x1c); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      iVar9 = _stricmp((char *)(puVar1 + 1),(char *)piVar2);
      if (iVar9 == 0) {
        iVar11 = iVar11 + 1;
      }
    }
  }
  if (iVar11 < param_1[0xe]) {
    if (*(int *)(DAT_00524564 + 0xc) < *(int *)(DAT_00524564 + 0x10)) {
      return '\x01';
    }
    piVar12 = *(int **)(DAT_00524564 + 0x1c);
    piVar2 = param_1;
    while (piVar7 = piVar12, piVar7 != (int *)0x0) {
      if ((!bVar6) && (piVar7[0xd] < param_1[0xd])) {
        bVar6 = true;
      }
      piVar2 = piVar7;
      piVar12 = (int *)*piVar7;
    }
    if (!bVar6) {
      return '\x04';
    }
    piVar12 = (int *)piVar2[0x15];
    if ((piVar12 != (int *)0x0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar12 + 0x24))(piVar12,&param_1);
      param_1 = (int *)((uint)param_1 & 1);
      if (param_1 != (int *)0x0) {
        (**(code **)(*(int *)piVar2[0x15] + 0x48))((int *)piVar2[0x15]);
        piVar2[0x1e] = piVar2[0x1e] & 0xfffffffb;
        piVar2[0x18] = piVar2[0x18] + -1;
      }
    }
    set_audio_object_playback_flags_and_queue(piVar2,0x20);
    return '\x01';
  }
  piVar12 = *(int **)(DAT_00524564 + 0x1c);
  if (piVar12 != (int *)0x0) {
    while ((iVar11 = _stricmp((char *)piVar2,(char *)(piVar12 + 1)), iVar11 != 0 ||
           (param_1[0xd] <= piVar12[0xd]))) {
      piVar12 = (int *)*piVar12;
      if (piVar12 == (int *)0x0) {
        return '\x02';
      }
    }
    if (piVar12 != (int *)0x0) {
      piVar2 = (int *)piVar12[0x15];
      uVar10 = 0;
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x24))(piVar2,&param_1);
        uVar10 = (uint)param_1 & 1;
      }
      if (uVar10 != 0) {
        (**(code **)(*(int *)piVar12[0x15] + 0x48))((int *)piVar12[0x15]);
        piVar12[0x1e] = piVar12[0x1e] & 0xfffffffb;
        piVar12[0x18] = piVar12[0x18] + -1;
      }
    }
    iVar11 = set_audio_object_playback_flags_and_queue(piVar12,0x100);
    if (iVar11 == 0) {
      piVar12 = (int *)0x0;
    }
  }
  return (-(piVar12 != (int *)0x0) & 4U) + 2;
}


