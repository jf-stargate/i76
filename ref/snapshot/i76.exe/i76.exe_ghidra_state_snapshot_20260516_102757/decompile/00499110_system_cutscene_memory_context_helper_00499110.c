/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499110
 * Entry: 00499110
 * Signature: undefined4 __cdecl system_cutscene_memory_context_helper_00499110(int * param_1, byte * param_2, int * param_3, int param_4)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499110. Shorten readability
   label for system/cutscene/virtual-memory context. */

undefined4 __cdecl
system_cutscene_memory_context_helper_00499110(int *param_1,byte *param_2,int *param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  
  if (*param_3 < 1) {
    return 0;
  }
  cVar1 = *(char *)*param_1;
  if ((cVar1 == '\n') || (cVar1 == '\r')) {
    *param_1 = (int)((char *)*param_1 + 1);
    iVar3 = *param_3;
    *param_3 = iVar3 + -1;
    if (iVar3 < 1) {
      return 0;
    }
  }
  iVar3 = *param_3;
  while ((((iVar3 != 0 && (param_4 != 0)) && (bVar2 = *(byte *)*param_1, bVar2 != 10)) &&
         (bVar2 != 0xd))) {
    if (((byte)_mbctype_exref[bVar2 + 1] & 4) != 0) {
      *param_2 = bVar2;
      param_2 = param_2 + 1;
      *param_1 = *param_1 + 1;
      iVar3 = *param_3;
      param_4 = param_4 + -1;
      *param_3 = iVar3 + -1;
      if ((iVar3 + -1 == 0) || (param_4 == 0)) break;
    }
    *param_2 = *(byte *)*param_1;
    *param_1 = *param_1 + 1;
    iVar3 = *param_3 + -1;
    param_4 = param_4 + -1;
    *param_3 = iVar3;
    param_2 = param_2 + 1;
  }
  *param_2 = 0;
  iVar3 = *param_3;
  do {
    if (((iVar3 == 0) || (param_4 == 0)) ||
       (iVar3 = _ismbcspace((int)*(char *)*param_1), iVar3 == 0)) {
      return 1;
    }
    if (((byte)_mbctype_exref[*(byte *)*param_1 + 1] & 4) != 0) {
      *param_1 = (int)((byte *)*param_1 + 1);
      iVar3 = *param_3;
      param_4 = param_4 + -1;
      *param_3 = iVar3 + -1;
      if (iVar3 + -1 == 0) {
        return 1;
      }
      if (param_4 == 0) {
        return 1;
      }
    }
    *param_1 = *param_1 + 1;
    iVar3 = *param_3 + -1;
    param_4 = param_4 + -1;
    *param_3 = iVar3;
  } while( true );
}


