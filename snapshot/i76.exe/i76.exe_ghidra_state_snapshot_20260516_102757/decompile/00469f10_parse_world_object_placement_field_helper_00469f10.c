/*
 * Program: i76.exe
 * Function: parse_world_object_placement_field_helper_00469f10
 * Entry: 00469f10
 * Signature: undefined4 __cdecl parse_world_object_placement_field_helper_00469f10(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: parse world object placement field
   helper based on adjacent named subsystem context. */

undefined4 __cdecl parse_world_object_placement_field_helper_00469f10(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (DAT_0058d900 < 1) {
    return 0xffffffff;
  }
  piVar2 = &DAT_00588e00;
  do {
    if (*piVar2 == param_1) {
      return *(undefined4 *)(&DAT_00588e04 + iVar1 * 0x60);
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0x18;
  } while (iVar1 < DAT_0058d900);
  return 0xffffffff;
}


