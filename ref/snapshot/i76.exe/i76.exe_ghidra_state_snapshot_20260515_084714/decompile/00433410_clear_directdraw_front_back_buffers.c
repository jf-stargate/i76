/*
 * Program: i76.exe
 * Function: clear_directdraw_front_back_buffers
 * Entry: 00433410
 * Signature: undefined4 __stdcall clear_directdraw_front_back_buffers(void)
 */


/* cgpt whole-binary semantic rename v1: locks/describes and clears front/back buffers */

undefined4 clear_directdraw_front_back_buffers(void)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int local_d0 [25];
  undefined4 auStack_6c [27];
  
  if (DAT_006080c0 != (int *)0x0) {
    piVar2 = local_d0;
    for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar2 = 0;
      piVar2 = piVar2 + 1;
    }
    local_d0[0] = 0x6c;
    DAT_005fdc0c = (**(code **)(*DAT_006080c0 + 0x58))(DAT_006080c0,local_d0);
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_Failure_getting_the_surface_desc_004f12cc);
      return 0;
    }
    puVar3 = auStack_6c;
    for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    auStack_6c[0] = 100;
    SetRect((LPRECT)&stack0xffffff18,0,0,local_d0[1],local_d0[0]);
    DAT_005fdc0c = (**(code **)(*DAT_006080c0 + 0x14))
                             (DAT_006080c0,&stack0xffffff18,0,0,0x1000400,auStack_6c);
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_Clearing_the_front_buffer_failed_004f12a4);
      return 0;
    }
  }
  if (DAT_006080c4 != (int *)0x0) {
    piVar2 = local_d0;
    for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar2 = 0;
      piVar2 = piVar2 + 1;
    }
    local_d0[0] = 0x6c;
    DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x58))(DAT_006080c4,local_d0);
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_Failure_while_getting_the_surfac_004f124c);
      return 0;
    }
    puVar3 = auStack_6c;
    for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    auStack_6c[0] = 100;
    SetRect((LPRECT)&stack0xffffff18,0,0,local_d0[1],local_d0[0]);
    DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x14))
                             (DAT_006080c4,&stack0xffffff18,0,0,0x1000400,auStack_6c);
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_Clearing_the_front_buffer_failed_004f12a4);
      return 0;
    }
  }
  return 1;
}


