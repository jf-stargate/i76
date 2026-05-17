/*
 * Program: i76.exe
 * Function: virtual_alloc_reserved_commit_region
 * Entry: 00498940
 * Signature: LPVOID __cdecl virtual_alloc_reserved_commit_region(uint param_1, SIZE_T param_2)
 */


/* cgpt rename v2: Reserves a VirtualAlloc region, commits the aligned initial size, and tracks it
   in a global allocation list. */

LPVOID __cdecl virtual_alloc_reserved_commit_region(uint param_1,SIZE_T param_2)

{
  LPVOID lpAddress;
  LPVOID pvVar1;
  SIZE_T *pSVar2;
  SIZE_T dwSize;
  SIZE_T dwSize_00;
  _SYSTEM_INFO local_24;
  
  GetSystemInfo(&local_24);
  dwSize_00 = (-local_24.dwPageSize & param_1) + local_24.dwPageSize;
  if ((int)param_2 < (int)dwSize_00) {
    param_2 = dwSize_00;
  }
  dwSize = (param_2 - 1 & 0xffff0000) + 0x10000;
  lpAddress = VirtualAlloc((LPVOID)0x0,dwSize,0x102000,4);
  if (lpAddress == (LPVOID)0x0) {
    return (LPVOID)0x0;
  }
  pvVar1 = VirtualAlloc(lpAddress,dwSize_00,0x1000,4);
  if (pvVar1 != (LPVOID)0x0) {
    pSVar2 = (SIZE_T *)xalloc_global_heap(0x10);
    if (pSVar2 != (SIZE_T *)0x0) {
      *pSVar2 = dwSize;
      pSVar2[2] = (SIZE_T)lpAddress;
      pSVar2[1] = local_24.dwPageSize;
      pSVar2[3] = (SIZE_T)DAT_005a6170;
      DAT_005a6170 = pSVar2;
      return lpAddress;
    }
  }
  VirtualFree(lpAddress,0,0x8000);
  return (LPVOID)0x0;
}


