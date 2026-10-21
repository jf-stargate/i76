/*
 * Program: i76.exe
 * Function: compare_resource_record_16byte_key
 * Entry: 00470ca0
 * Signature: int __cdecl compare_resource_record_16byte_key(int * param_1, int param_2)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Comparator for bsearch/qsort over
   registered or indexed records keyed by the first 16 bytes. */

int __cdecl compare_resource_record_16byte_key(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = param_2 - (int)param_1;
  do {
    iVar1 = *param_1 - *(int *)((int)param_1 + iVar3);
    if (iVar1 != 0) {
      return iVar1;
    }
    param_1 = param_1 + 1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return 0;
}


