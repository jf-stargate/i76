/*
 * Program: i76.exe
 * Function: world_object_placement_transform_helper_00469f50
 * Entry: 00469f50
 * Signature: undefined __stdcall world_object_placement_transform_helper_00469f50(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object placement transform
   helper based on adjacent named subsystem context. */

void world_object_placement_transform_helper_00469f50(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x30);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 300;
    puVar1[1] = 300;
    puVar1[2] = 1;
    puVar1[3] = 0x3ccccccd;
    puVar1[4] = 0;
    puVar1[5] = 0x48927c00;
    puVar1[6] = 0x3f800000;
    puVar1[7] = 0x44834000;
    puVar1[8] = 0x45dac000;
    puVar1[9] = 0;
    puVar1[10] = 0xffffffff;
  }
  return;
}


