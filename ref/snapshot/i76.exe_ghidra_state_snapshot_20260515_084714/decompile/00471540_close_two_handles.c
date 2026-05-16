/*
 * Program: i76.exe
 * Function: close_two_handles
 * Entry: 00471540
 * Signature: undefined __cdecl close_two_handles(undefined4 * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00471540
   suggested_name: close_two_handles
   basis: Small helper closing two Win32 handles. */

void __cdecl close_two_handles(undefined4 *param_1)

{
  if ((LPCVOID)param_1[2] != (LPCVOID)0x0) {
    UnmapViewOfFile((LPCVOID)param_1[2]);
  }
  if ((HANDLE)param_1[1] != (HANDLE)0x0) {
    CloseHandle((HANDLE)param_1[1]);
  }
  if ((HANDLE)*param_1 != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)*param_1);
  }
  return;
}


