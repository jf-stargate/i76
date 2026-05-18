/*
 * Program: i76.exe
 * Function: set_vehicle_current_damage_or_effect_object
 * Entry: 004674c0
 * Signature: undefined __cdecl set_vehicle_current_damage_or_effect_object(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Stores/updates a vehicle
   runtime effect/damage object pointer and releases/rebinds related light/object state. */

void __cdecl set_vehicle_current_damage_or_effect_object(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if (param_2 != 0) {
    *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) ^ 0x40;
  }
  uVar5 = *(uint *)(iVar1 + 0x454) >> 6 & 1;
  if (*(int *)(iVar1 + 0x158) == 0) {
    fVar3 = (float)*(int *)(iVar1 + 0x178) * _DAT_004be1d4;
  }
  else {
    fVar3 = (float)*(int *)(iVar1 + 0x178) / (float)*(int *)(iVar1 + 0x158);
  }
  if (*(int *)(iVar1 + 0x168) == 0) {
    fVar4 = (float)*(int *)(iVar1 + 0x18c) * _DAT_004be1d4;
  }
  else {
    fVar4 = (float)*(int *)(iVar1 + 0x18c) / (float)*(int *)(iVar1 + 0x168);
  }
  if (fVar3 <= fVar4) {
    fVar4 = fVar3;
  }
  if (fVar4 < _DAT_004be1dc) {
    uVar5 = 0;
  }
  if (param_2 != 0) {
    palette_dib_surface_lock_context_helper_00477e80(param_1,(uint)(uVar5 != 0));
  }
  iVar2 = *(int *)(iVar1 + 0x440);
  if (iVar2 != 0) {
    *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) & 0xfffffffe;
    *(uint *)(*(int *)(iVar1 + 0x440) + 0x10) =
         *(uint *)(*(int *)(iVar1 + 0x440) + 0x10) | (uint)(uVar5 == 0);
  }
  if (uVar5 == 0) {
    get_world_object_class_id(*(int *)(iVar1 + 0x3a0),1);
  }
  else {
    world_object_geometry_context_helper_00458860(*(int *)(iVar1 + 0x3a0),1);
  }
  uVar5 = *(uint *)(iVar1 + 0x454) >> 6 & 1;
  if (*(float *)(iVar1 + 0xe4) < _DAT_004be23c) {
    uVar5 = 2;
  }
  if (*(int *)(iVar1 + 0x164) == 0) {
    fVar3 = (float)*(int *)(iVar1 + 0x184) * _DAT_004be1d4;
  }
  else {
    fVar3 = (float)*(int *)(iVar1 + 0x184) / (float)*(int *)(iVar1 + 0x164);
  }
  if (*(int *)(iVar1 + 0x174) == 0) {
    fVar4 = (float)*(int *)(iVar1 + 0x198) * _DAT_004be1d4;
  }
  else {
    fVar4 = (float)*(int *)(iVar1 + 0x198) / (float)*(int *)(iVar1 + 0x174);
  }
  if (fVar3 <= fVar4) {
    fVar4 = fVar3;
  }
  if (fVar4 < _DAT_004be1dc) {
    uVar5 = 0;
  }
  iVar2 = *(int *)(iVar1 + 0x3a4);
  if (iVar2 != 0) {
    *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) & 0xfffffffe;
    *(uint *)(*(int *)(iVar1 + 0x3a4) + 0x10) =
         *(uint *)(*(int *)(iVar1 + 0x3a4) + 0x10) | (uint)(uVar5 != 2);
  }
  return;
}


