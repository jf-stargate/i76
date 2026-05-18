/*
 * Program: i76.exe
 * Function: vehicle_damage_texture_context_helper_00465fe0
 * Entry: 00465fe0
 * Signature: int __cdecl vehicle_damage_texture_context_helper_00465fe0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle damage texture context helper
   based on adjacent named subsystem context. */

int __cdecl vehicle_damage_texture_context_helper_00465fe0(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 8);
  do {
    if (((uint)*(ushort *)(param_1 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
      iVar1 = iVar1 + *piVar3;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 4);
  return iVar1;
}


