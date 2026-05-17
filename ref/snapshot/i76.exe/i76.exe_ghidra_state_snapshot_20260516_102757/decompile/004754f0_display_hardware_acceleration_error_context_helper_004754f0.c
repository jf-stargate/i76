/*
 * Program: i76.exe
 * Function: display_hardware_acceleration_error_context_helper_004754f0
 * Entry: 004754f0
 * Signature: undefined __stdcall display_hardware_acceleration_error_context_helper_004754f0(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: display hardware acceleration error
   context helper based on adjacent named subsystem context. */

void display_hardware_acceleration_error_context_helper_004754f0(void)

{
  int iVar1;
  int **ppiVar2;
  int *piStack_78;
  int *piStack_74;
  
  if (DAT_0058dadc == 0) {
    if (DAT_0058daec != (int *)0x0) {
      piStack_74 = DAT_0058daec;
      piStack_78 = (int *)0x47550c;
      iVar1 = (**(code **)(*DAT_0058daec + 0x60))();
      if (iVar1 != 0) {
        piStack_74 = DAT_0058daec;
        piStack_78 = (int *)0x47551b;
        (**(code **)(*DAT_0058daec + 0x6c))();
      }
    }
    if (DAT_0058dae0 != (int *)0x0) {
      piStack_74 = DAT_0058dae0;
      piStack_78 = (int *)0x47552e;
      iVar1 = (**(code **)(*DAT_0058dae0 + 0x60))();
      if (iVar1 != 0) {
        piStack_78 = DAT_0058dae0;
        (**(code **)(*DAT_0058dae0 + 0x6c))();
        return;
      }
    }
  }
  else {
    piStack_74 = (int *)0x0;
    piStack_78 = DAT_0058daec;
    (**(code **)(*DAT_0058daec + 0x80))();
    if (DAT_0058daec != (int *)0x0) {
      iVar1 = (**(code **)(*DAT_0058daec + 0x60))(DAT_0058daec);
      if (iVar1 != 0) {
        (**(code **)(*DAT_0058daec + 0x6c))(DAT_0058daec);
      }
    }
    if (DAT_0058dae0 != (int *)0x0) {
      iVar1 = (**(code **)(*DAT_0058dae0 + 0x60))(DAT_0058dae0);
      if (iVar1 != 0) {
        (**(code **)(*DAT_0058dae0 + 0x6c))(DAT_0058dae0);
      }
    }
    ppiVar2 = &piStack_78;
    for (iVar1 = 0x1b; ppiVar2 = ppiVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
      *ppiVar2 = (int *)0x0;
    }
    piStack_74 = (int *)0x6c;
    (**(code **)(*DAT_0058daec + 100))(DAT_0058daec,0,&piStack_74,1,0);
  }
  return;
}


