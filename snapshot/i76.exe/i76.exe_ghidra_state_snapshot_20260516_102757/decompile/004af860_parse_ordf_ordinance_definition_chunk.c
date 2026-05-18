/*
 * Program: i76.exe
 * Function: parse_ordf_ordinance_definition_chunk
 * Entry: 004af860
 * Signature: undefined4 __cdecl parse_ordf_ordinance_definition_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] ORDF callback for
   ordinance/projectile definition records. */

undefined4 __cdecl parse_ordf_ordinance_definition_chunk(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(param_2 + 0xb8);
  for (iVar1 = 0x22; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  return 1;
}


