/*
 * Program: i76.exe
 * Function: ordnance_runtime_context_helper_004a11e0
 * Entry: 004a11e0
 * Signature: undefined4 __cdecl ordnance_runtime_context_helper_004a11e0(int param_1, char * param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: ordnance runtime context helper based
   on adjacent named subsystem context. */

undefined4 __cdecl ordnance_runtime_context_helper_004a11e0(int param_1,char *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  LPVOID pvVar4;
  int iVar5;
  
  uVar3 = (param_1 * 0x6cd + 0xaabU) % 0x71;
  if (uVar3 < 0x71) {
    for (piVar2 = (int *)(&DAT_005a8118)[uVar3]; piVar2 != (int *)0x0; piVar2 = (int *)piVar2[0x11b]
        ) {
      if (*piVar2 == param_1) goto LAB_004a1225;
    }
  }
  piVar2 = (int *)0x0;
LAB_004a1225:
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  if (uVar3 < 0x71) {
    piVar2 = (int *)(&DAT_005a8118)[uVar3];
    if (*piVar2 == param_1) {
      (&DAT_005a8118)[uVar3] = piVar2[0x11b];
    }
    else {
      piVar1 = piVar2;
      for (piVar2 = (int *)piVar2[0x11b]; piVar2 != (int *)0x0; piVar2 = (int *)piVar2[0x11b]) {
        if (*piVar2 == param_1) {
          piVar1[0x11b] = piVar2[0x11b];
          break;
        }
        piVar1 = piVar2;
      }
    }
    pvVar4 = HeapReAlloc(DAT_005aaac0,0,piVar2,0x540);
    *(undefined4 *)((int)pvVar4 + 0x46c) = (&DAT_005a8118)[uVar3];
    (&DAT_005a8118)[uVar3] = pvVar4;
  }
  else {
    pvVar4 = (LPVOID)0x0;
  }
  iVar5 = 0;
  *(int *)((int)pvVar4 + 0x468) = (int)pvVar4 + 0x470;
  do {
    strncpy((char *)(*(int *)((int)pvVar4 + 0x468) + iVar5),param_2,0x10);
    iVar5 = iVar5 + 0x10;
    param_2 = param_2 + 0xd;
  } while (iVar5 < 0xd0);
  return 1;
}


