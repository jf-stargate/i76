/*
 * Program: I76EDIT.EXE
 * Function: i76edit_load_road_records
 * Entry: 004012a8
 * Signature: undefined __cdecl i76edit_load_road_records(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
 */


/* WARNING: Removing unreachable block (ram,0x00415b7f) */
/* WARNING: Removing unreachable block (ram,0x00415bbf) */
/* WARNING: Removing unreachable block (ram,0x00415bdd) */
/* WARNING: Removing unreachable block (ram,0x00415be4) */
/* WARNING: Removing unreachable block (ram,0x00415bf6) */
/* WARNING: Removing unreachable block (ram,0x00415bfd) */
/* WARNING: Removing unreachable block (ram,0x00415c07) */
/* WARNING: Removing unreachable block (ram,0x00415c13) */
/* WARNING: Removing unreachable block (ram,0x00415c0b) */
/* WARNING: Removing unreachable block (ram,0x00415c19) */
/* WARNING: Removing unreachable block (ram,0x00415c27) */
/* WARNING: Removing unreachable block (ram,0x00415b2f) */
/* WARNING: Removing unreachable block (ram,0x00415b33) */
/* WARNING: Removing unreachable block (ram,0x00415b4c) */
/* WARNING: Removing unreachable block (ram,0x00415b4e) */

void __cdecl
i76edit_load_road_records
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int in_stack_00004058;
  
  FUN_004237d0();
  thunk_FUN_00415aa0();
  thunk_FUN_00415430();
  puVar2 = (undefined4 *)&stack0x00000054;
  for (iVar1 = 0x1000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  __read(in_stack_00004058,&stack0x00000000,4);
  DAT_0043c544 = 0;
  return;
}


