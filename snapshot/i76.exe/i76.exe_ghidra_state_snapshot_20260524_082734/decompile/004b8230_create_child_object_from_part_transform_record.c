/*
 * Program: i76.exe
 * Function: create_child_object_from_part_transform_record
 * Entry: 004b8230
 * Signature: int __cdecl create_child_object_from_part_transform_record(int param_1, int param_2, char * param_3, int param_4, int param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: copy_odef_transform_and_resolve_object_label
   confidence: high
   module: level_object_dispatch
   Copies ODEF 3x3 basis and position into runtime transform block and prepares/resolves object
   label. Validates ODEF +0x08 basis and +0x2c/+0x30/+0x34 position interpretation.
   note: Rename skipped because existing name appears user-defined. */

int __cdecl
create_child_object_from_part_transform_record
          (int param_1,int param_2,char *param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 extraout_ST0;
  
  iVar1 = create_vehicle_child_object_and_copy_ids(param_1,(undefined4 *)param_3);
  if (iVar1 == 0) {
    return 0;
  }
  pfVar4 = (float *)(iVar1 + 0x18);
  *pfVar4 = *(float *)(param_2 + 8);
  *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(iVar1 + 0x2c) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(iVar1 + 0x34) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(iVar1 + 0x38) = *(undefined4 *)(param_2 + 0x28);
  *(double *)(iVar1 + 0x40) = (double)*(float *)(param_2 + 0x2c);
  *(double *)(iVar1 + 0x48) = (double)*(float *)(param_2 + 0x30);
  *(double *)(iVar1 + 0x50) = (double)*(float *)(param_2 + 0x34);
  if (param_4 != 0) {
    apply_world_object_transform_to_bounds_or_geometry
              (*(double *)(iVar1 + 0x40),*(double *)(iVar1 + 0x50));
    *(double *)(iVar1 + 0x48) = (double)extraout_ST0;
  }
  *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(param_2 + 0x60);
  iVar2 = _strnicmp(param_3,s_null_004c3280,4);
  if ((((iVar2 == 0) && (*pfVar4 == _DAT_004bec98)) && (*(float *)(iVar1 + 0x1c) == _DAT_004bec98))
     && (*(float *)(iVar1 + 0x20) == _DAT_004bec98)) {
    pfVar3 = (float *)&DAT_004faed8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar4 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar4 = pfVar4 + 1;
    }
  }
  if (param_5 != 0) {
    set_world_object_class_and_register_runtime(iVar1,*(int *)(param_2 + 0x5c));
  }
  if (param_4 == 0) {
    pfVar4 = (float *)(iVar1 + 0x84);
    *(undefined4 *)(iVar1 + 0x90) = *(undefined4 *)(param_2 + 0x4c);
    *pfVar4 = *(float *)(param_2 + 0x40);
    *(undefined4 *)(iVar1 + 0x88) = *(undefined4 *)(param_2 + 0x44);
    *(undefined4 *)(iVar1 + 0x8c) = *(undefined4 *)(param_2 + 0x48);
    *(float *)(iVar1 + 0x94) = *pfVar4 - *(float *)(param_2 + 0x50);
    *(float *)(iVar1 + 0xa0) = *pfVar4 + *(float *)(param_2 + 0x50);
    *(float *)(iVar1 + 0x98) = *(float *)(iVar1 + 0x88) - *(float *)(param_2 + 0x54);
    *(float *)(iVar1 + 0xa4) = *(float *)(param_2 + 0x54) + *(float *)(iVar1 + 0x88);
    *(float *)(iVar1 + 0x9c) = *(float *)(iVar1 + 0x8c) - *(float *)(param_2 + 0x58);
    *(float *)(iVar1 + 0xa8) = *(float *)(param_2 + 0x58) + *(float *)(iVar1 + 0x8c);
    switch(*(undefined4 *)(param_2 + 0x5c)) {
    case 2:
    case 3:
    case 4:
    case 0xb:
    case 0xc:
      building_child_piece_context_helper_0046b200(iVar1,*(undefined4 *)(param_2 + 100));
      break;
    case 7:
      world_object_texture_animation_context_helper_0046d6f0
                (iVar1,*(undefined4 *)(param_2 + 0x68),*(undefined4 *)(param_2 + 0x6c),
                 *(undefined4 *)(param_2 + 0x70),*(undefined4 *)(param_2 + 0x74),
                 *(undefined4 *)(param_2 + 100));
      return iVar1;
    case 10:
      loaded_resource_cache_evict_lru_helper_0046f8f0
                (iVar1,*(float *)(param_2 + 0x68),*(float *)(param_2 + 0x6c),
                 *(float *)(param_2 + 0x70));
      loaded_resource_cache_hash_context_helper_0046f960(iVar1,*(undefined4 *)(param_2 + 100));
      return iVar1;
    }
  }
  return iVar1;
}


