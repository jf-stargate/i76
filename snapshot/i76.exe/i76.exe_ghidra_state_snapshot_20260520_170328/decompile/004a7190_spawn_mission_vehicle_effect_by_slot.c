/*
 * Program: i76.exe
 * Function: spawn_mission_vehicle_effect_by_slot
 * Entry: 004a7190
 * Signature: undefined __cdecl spawn_mission_vehicle_effect_by_slot(int param_1, float * param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=medium] Uses mission runtime table indexed
   by vehicle mission id; selects one of several per-slot resource pairs and spawns/attaches runtime
   effect/object. */

void __cdecl
spawn_mission_vehicle_effect_by_slot(int param_1,float *param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  
  iVar2 = 0;
  piVar1 = *(int **)(param_1 + 0x70);
  piVar4 = &g_mission_runtime_vehicle_table;
  do {
    if (*piVar4 == *piVar1) goto LAB_004a71b7;
    piVar4 = piVar4 + 0x34;
    iVar2 = iVar2 + 1;
  } while ((int)piVar4 < 0x6562c0);
  iVar2 = -1;
LAB_004a71b7:
  if (param_4 == -1) {
    if (piVar1 == (int *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = piVar1[3];
    }
    puVar3 = spawn_cached_explosion_runtime_object
                       ((&DAT_006552f0)[iVar2 * 0x34],(&DAT_006552f4)[iVar2 * 0x34],iVar5,*param_2,
                        param_2[1],param_2[2],0);
    if (puVar3 != (uint *)0x0) {
      attach_named_sound_to_runtime_object
                (&DAT_006552f8 + iVar2 * 0xd0,(int)puVar3,(undefined4 *)0x0);
    }
  }
  else {
    switch(param_4) {
    case 1:
    case 4:
    case 8:
    case 9:
      if (piVar1 == (int *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = piVar1[3];
      }
      puVar3 = spawn_cached_explosion_runtime_object
                         ((&DAT_00655308)[iVar2 * 0x34],(&DAT_0065530c)[iVar2 * 0x34],iVar5,*param_2
                          ,param_2[1],param_2[2],param_3);
      if (puVar3 != (uint *)0x0) {
        attach_named_sound_to_runtime_object
                  (&DAT_00655310 + iVar2 * 0xd0,(int)puVar3,(undefined4 *)0x0);
        return;
      }
      break;
    case 2:
    case 0xc:
      if (piVar1 == (int *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = piVar1[3];
      }
      puVar3 = spawn_cached_explosion_runtime_object
                         ((&DAT_00655320)[iVar2 * 0x34],(&DAT_00655324)[iVar2 * 0x34],iVar5,*param_2
                          ,param_2[1],param_2[2],param_3);
      if (puVar3 != (uint *)0x0) {
        attach_named_sound_to_runtime_object
                  (&DAT_00655328 + iVar2 * 0xd0,(int)puVar3,(undefined4 *)0x0);
        return;
      }
      break;
    case 3:
    case 0xb:
      if (piVar1 == (int *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = piVar1[3];
      }
      puVar3 = spawn_cached_explosion_runtime_object
                         ((&DAT_00655338)[iVar2 * 0x34],(&DAT_0065533c)[iVar2 * 0x34],iVar5,*param_2
                          ,param_2[1],param_2[2],param_3);
      if (puVar3 != (uint *)0x0) {
        attach_named_sound_to_runtime_object
                  (&DAT_00655340 + iVar2 * 0xd0,(int)puVar3,(undefined4 *)0x0);
        return;
      }
    }
  }
  return;
}


