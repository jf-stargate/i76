/*
 * Program: i76.exe
 * Function: parse_scene_object_descriptor_resource
 * Entry: 004b7ea0
 * Signature: undefined4 __cdecl parse_scene_object_descriptor_resource(undefined4 param_1, byte * param_2, byte * param_3)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium] Parses a scene object
   descriptor resource through the SOBJ-like descriptor table and adjusts transform-composed child
   texture/slot metadata. */

undefined4 __cdecl
parse_scene_object_descriptor_resource(undefined4 param_1,byte *param_2,byte *param_3)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  
  bVar3 = parse_bwd2_resource_with_descriptor_table(param_3,&DAT_00500b18,6,param_2);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return 0;
  }
  iVar1 = *(int *)param_2;
  iVar4 = *(int *)(iVar1 + 0x6c);
  if (((((iVar4 == 2) || (iVar4 == 3)) || (iVar4 == 0xc)) || (iVar4 == 0xb)) &&
     (*(int *)(iVar1 + 0x70) != 0)) {
    for (iVar1 = *(int *)(iVar1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      iVar4 = is_transform_composed_world_object_class(iVar1);
      if (iVar4 != 0) {
        iVar4 = *(int *)(iVar1 + 0x70);
        iVar2 = (*(uint *)(iVar1 + 0x10) >> 10 & 3) * 0xd;
        world_reader_null_handler(&DAT_00500b78 + iVar2,(char *)(iVar4 + 0x10),0);
        *(undefined4 *)(iVar4 + 0x18) = *(undefined4 *)(s_null_00500bb0 + iVar2);
        *(undefined4 *)(iVar4 + 0x1c) = *(undefined4 *)(s_null_00500bb0 + iVar2 + 4);
        *(undefined4 *)(iVar4 + 0x20) = *(undefined4 *)(&DAT_00500bb8 + iVar2);
        *(undefined *)(iVar4 + 0x24) = (&DAT_00500bbc)[iVar2];
      }
      for (iVar4 = *(int *)(iVar1 + 100); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x60)) {
        mission_scrounge_record_handler(iVar4);
      }
    }
  }
  return 1;
}


