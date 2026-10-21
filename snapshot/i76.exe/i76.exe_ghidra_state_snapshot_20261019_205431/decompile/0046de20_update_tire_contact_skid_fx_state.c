/*
 * Program: i76.exe
 * Function: update_tire_contact_skid_fx_state
 * Entry: 0046de20
 * Signature: LPVOID __cdecl update_tire_contact_skid_fx_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Tracks tire contact,
   begins/appends tire skid trails, and occasionally spawns CHUNK3/K3 dust or skid FX from the tire
   contact point. */

LPVOID __cdecl update_tire_contact_skid_fx_state(int param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  LPVOID pvVar3;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
                    /* I76 semantic baseline: update_tire_contact_skid_fx_state
                       Updates tire contact/skid effect state. */
  iVar2 = *(int *)(param_1 + 0x70);
  pvVar3 = (LPVOID)0x0;
  if ((param_2 == 0) || (pvVar3 = *(LPVOID *)(iVar2 + 0x40), pvVar3 != (LPVOID)0x0)) {
    *(undefined4 *)(iVar2 + 0x48) = 0;
  }
  else {
    pfVar1 = (float *)compose_world_object_runtime_transform(&local_24,param_1);
    local_18 = *pfVar1;
    local_8 = pfVar1[1] - *(float *)(iVar2 + 0x1c);
    local_10 = pfVar1[2];
    local_14 = *(float *)(iVar2 + 0x2c);
    if (*(int *)(iVar2 + 0x48) == 0) {
      pvVar3 = (LPVOID)begin_tire_skid_mark_trail(&local_18,param_1);
      *(undefined4 *)(iVar2 + 0x48) = 1;
      return pvVar3;
    }
    append_tire_skid_mark_trail_point(&local_18,param_1);
    iVar2 = get_root_ancestor_world_object(param_1);
    local_24 = -*(float *)(iVar2 + 0x30) * _DAT_004be4cc;
    local_20 = -*(float *)(iVar2 + 0x34) * _DAT_004be4cc;
    local_1c = -*(float *)(iVar2 + 0x38) * _DAT_004be4cc;
    local_8 = local_20 - _DAT_004be4d0;
    local_c = local_24;
    local_4 = local_1c;
    iVar2 = rand();
    pvVar3 = (LPVOID)(iVar2 / 3);
    if (iVar2 % 3 != 0) {
      pvVar3 = destroy_chunk_manager_objects
                         (DAT_004f89d0,DAT_004f89d4,local_18,local_14,local_10,&local_c,1.0);
      return pvVar3;
    }
  }
  return pvVar3;
}


