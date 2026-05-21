/*
 * Program: i76shell.dll
 * Function: debug_dump_mpack_database_index
 * Entry: 10007f60
 * Signature: undefined __fastcall debug_dump_mpack_database_index(int param_1)
 */


void __fastcall debug_dump_mpack_database_index(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  fprintf((FILE *)(_iob_exref + 0x20),s_MPack_File___s_Items___d_10043ad8,param_1,
          *(undefined4 *)(param_1 + 0x84));
  iVar1 = *(int *)(param_1 + 0x88);
  iVar3 = 0;
  if (0 < *(int *)(iVar1 + 4)) {
    do {
      puVar2 = (undefined4 *)FUN_10003610(iVar1,iVar3);
      fprintf((FILE *)(_iob_exref + 0x20),s_Offset___d__hex__x___Size___d__h_10043af4,*puVar2,
              *puVar2,puVar2[1],puVar2[1]);
      iVar1 = *(int *)(param_1 + 0x88);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(iVar1 + 4));
  }
  return;
}


