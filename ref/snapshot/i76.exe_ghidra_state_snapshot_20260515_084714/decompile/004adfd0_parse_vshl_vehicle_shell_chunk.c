/*
 * Program: i76.exe
 * Function: parse_vshl_vehicle_shell_chunk
 * Entry: 004adfd0
 * Signature: undefined4 __cdecl parse_vshl_vehicle_shell_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium] VSHL callback in the
   runtime vehicle descriptor table. */

undefined4 __cdecl parse_vshl_vehicle_shell_chunk(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(*(int *)(param_2 + 4) + 0x10a);
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  return 1;
}


