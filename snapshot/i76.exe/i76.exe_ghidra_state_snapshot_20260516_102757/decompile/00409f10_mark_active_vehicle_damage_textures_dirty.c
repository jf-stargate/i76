/*
 * Program: i76.exe
 * Function: mark_active_vehicle_damage_textures_dirty
 * Entry: 00409f10
 * Signature: undefined __stdcall mark_active_vehicle_damage_textures_dirty(void)
 */


/* cgpt rename v2: Walks active vehicle tables and marks each vehicle damage texture/state block
   dirty. */

void mark_active_vehicle_damage_textures_dirty(void)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_00507da0;
  piVar3 = &DAT_0051f5d0;
  do {
    iVar2 = *piVar3;
    puVar1 = puVar4;
    if (0 < iVar2) {
      do {
        iVar2 = iVar2 + -1;
        *(undefined4 *)(*(int *)(*(int *)(*(int *)*puVar1 + 0x70) + 0x108) + 0xa714) = 1;
        puVar1 = puVar1 + 1;
      } while (iVar2 != 0);
    }
    piVar3 = piVar3 + 1;
    puVar4 = puVar4 + 0x40;
  } while ((int)piVar3 < 0x51f5f0);
  return;
}


