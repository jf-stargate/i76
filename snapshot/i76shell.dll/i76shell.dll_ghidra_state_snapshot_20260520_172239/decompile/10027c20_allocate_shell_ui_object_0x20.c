/*
 * Program: i76shell.dll
 * Function: allocate_shell_ui_object_0x20
 * Entry: 10027c20
 * Signature: undefined __stdcall allocate_shell_ui_object_0x20(void)
 */


void allocate_shell_ui_object_0x20(void)

{
  LPVOID pvVar1;
  
  pvVar1 = HeapAlloc(DAT_10051c50,1,0x20);
  if (pvVar1 != (LPVOID)0x0) {
    *(undefined4 *)((int)pvVar1 + 0x1c) = 0;
    *(undefined4 *)((int)pvVar1 + 0x14) = 0;
    *(undefined4 *)((int)pvVar1 + 0x18) = 0;
  }
  return;
}


