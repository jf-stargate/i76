/*
 * Program: i76.exe
 * Function: vehicle_geometry_part_set_context_helper_004b7f70
 * Entry: 004b7f70
 * Signature: undefined4 __cdecl vehicle_geometry_part_set_context_helper_004b7f70(int param_1, int * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle geometry part set context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl vehicle_geometry_part_set_context_helper_004b7f70(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = (int *)(param_1 + 0x1c);
  piVar3 = param_2 + 0xf;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar3 = piVar3 + 1;
  }
  param_2[0x14] = 1;
  iVar1 = *(int *)(*param_2 + 0x6c);
  if (((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 0xc)) || (iVar1 == 0xb)) &&
     (iVar1 = *(int *)(*param_2 + 0x70), iVar1 != 0)) {
    world_reader_null_handler((byte *)(param_1 + 0x34),(char *)(iVar1 + 0x10),0);
    *(undefined4 *)(iVar1 + 0x18) = *(undefined4 *)(param_1 + 0x41);
    *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(param_1 + 0x45);
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_1 + 0x49);
    *(undefined1 *)(iVar1 + 0x24) = *(undefined1 *)(param_1 + 0x4d);
  }
  return 1;
}


