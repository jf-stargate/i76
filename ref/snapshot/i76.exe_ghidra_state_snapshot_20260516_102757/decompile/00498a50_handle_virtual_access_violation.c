/*
 * Program: i76.exe
 * Function: handle_virtual_access_violation
 * Entry: 00498a50
 * Signature: undefined4 __cdecl handle_virtual_access_violation(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence Virtual Access Violation Error Cr2 */

undefined4 __cdecl handle_virtual_access_violation(int *param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  _MEMORY_BASIC_INFORMATION local_1c;
  
  if (*(int *)*param_1 == -0x3ffffffb) {
    uVar1 = ((int *)*param_1)[6];
    piVar3 = DAT_005a6170;
    if (DAT_005a6170 != (int *)0x0) {
      while ((uVar2 = *piVar3 + piVar3[2], uVar1 < (uint)piVar3[2] || (uVar2 <= uVar1))) {
        piVar3 = (int *)piVar3[3];
        if (piVar3 == (int *)0x0) {
          return 0;
        }
      }
      VirtualQuery((LPCVOID)piVar3[2],&local_1c,0x1c);
      if ((LPVOID)(uVar2 - piVar3[1]) <= (LPVOID)((int)local_1c.BaseAddress + local_1c.RegionSize))
      {
        report_chunk_parse_error();
        return 0;
      }
      VirtualAlloc((LPVOID)((int)local_1c.BaseAddress + local_1c.RegionSize),piVar3[1],0x1000,4);
      return 0xffffffff;
    }
  }
  return 0;
}


