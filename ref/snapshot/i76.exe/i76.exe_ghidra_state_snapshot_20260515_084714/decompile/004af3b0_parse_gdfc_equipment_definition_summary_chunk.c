/*
 * Program: i76.exe
 * Function: parse_gdfc_equipment_definition_summary_chunk
 * Entry: 004af3b0
 * Signature: undefined4 __cdecl parse_gdfc_equipment_definition_summary_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium] Alternate GDFC
   callback used by a compact/summary equipment descriptor table. */

undefined4 __cdecl parse_gdfc_equipment_definition_summary_chunk(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(param_2 + 0x14);
  for (iVar1 = 0x29; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 1;
}


