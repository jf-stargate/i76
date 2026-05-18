/*
 * Program: i76.exe
 * Function: mission_scrounge_record_handler
 * Entry: 004b86d0
 * Signature: undefined __cdecl mission_scrounge_record_handler(int param_1)
 */


/* cgpt whole-binary semantic rename v1: near scrounge init and null strings */

void __cdecl mission_scrounge_record_handler(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = is_transform_composed_world_object_class(param_1);
  if (iVar2 != 0) {
    iVar2 = *(int *)(param_1 + 0x70);
    iVar1 = (*(uint *)(param_1 + 0x10) >> 10 & 3) * 0xd;
    world_reader_null_handler(&DAT_00500b78 + iVar1,(char *)(iVar2 + 0x10),0);
    *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)(s_null_00500bb0 + iVar1);
    *(undefined4 *)(iVar2 + 0x1c) = *(undefined4 *)(s_null_00500bb0 + iVar1 + 4);
    *(undefined4 *)(iVar2 + 0x20) = *(undefined4 *)(&DAT_00500bb8 + iVar1);
    *(undefined *)(iVar2 + 0x24) = (&DAT_00500bbc)[iVar1];
  }
  for (iVar2 = *(int *)(param_1 + 100); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x60)) {
    mission_scrounge_record_handler(iVar2);
  }
  return;
}


