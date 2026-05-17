/*
 * Program: I76EDIT.EXE
 * Function: __alloc_osfhnd
 * Entry: 004280a0
 * Signature: int __cdecl __alloc_osfhnd(void)
 */


/* Library Function - Single Match
    __alloc_osfhnd
   
   Library: Visual Studio 1998 Release */

int __cdecl __alloc_osfhnd(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = -1;
  iVar6 = 0;
  iVar4 = 0;
  piVar3 = &DAT_016423b0;
  do {
    puVar1 = (undefined4 *)*piVar3;
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = _malloc(0x100);
      if (puVar1 != (undefined4 *)0x0) {
        DAT_016424ec = DAT_016424ec + 0x20;
        (&DAT_016423b0)[iVar6] = puVar1;
        if (puVar1 < puVar1 + 0x40) {
          do {
            *(undefined1 *)(puVar1 + 1) = 0;
            puVar2 = puVar1 + 2;
            *puVar1 = 0xffffffff;
            *(undefined1 *)((int)puVar1 + 5) = 10;
            puVar1 = puVar2;
          } while (puVar2 < (undefined4 *)((&DAT_016423b0)[iVar6] + 0x100));
        }
        iVar5 = iVar6 << 5;
      }
      return iVar5;
    }
    puVar2 = puVar1 + 0x40;
    for (; puVar1 < puVar2; puVar1 = puVar1 + 2) {
      if ((*(byte *)(puVar1 + 1) & 1) == 0) {
        *puVar1 = 0xffffffff;
        iVar5 = ((int)puVar1 - *piVar3 >> 3) + iVar4;
        break;
      }
    }
    if (iVar5 != -1) {
      return iVar5;
    }
    iVar4 = iVar4 + 0x20;
    piVar3 = piVar3 + 1;
    iVar6 = iVar6 + 1;
    if ((int *)0x16424af < piVar3) {
      return -1;
    }
  } while( true );
}


