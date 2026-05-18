/*
 * Program: I76EDIT.EXE
 * Function: i76edit_alloc_first_unused_base_terrain_row
 * Entry: 004125a0
 * Signature: int __stdcall i76edit_alloc_first_unused_base_terrain_row(void)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Scans the base terrain plane at 009bc820 in 0x8004-byte
   row slots and marks the first empty row as used. */

int i76edit_alloc_first_unused_base_terrain_row(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_009bc820;
  do {
    if (*piVar2 == 0) {
      (&DAT_009bc820)[iVar1 * 0x2001] = 1;
      return iVar1;
    }
    piVar2 = piVar2 + 0x2001;
    iVar1 = iVar1 + 1;
  } while (piVar2 < &DAT_00c3c960);
  return -1;
}


