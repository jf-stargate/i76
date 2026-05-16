/*
 * Program: i76.exe
 * Function: find_audio_object_by_name_with_loaded_buffer
 * Entry: 00422230
 * Signature: int * __cdecl find_audio_object_by_name_with_loaded_buffer(char * param_1)
 */


/* cgpt readability rename v13 set A: Searches active and pending audio object lists by name and
   loaded-buffer state. */

int * __cdecl find_audio_object_by_name_with_loaded_buffer(char *param_1)

{
  int iVar1;
  int *piVar2;
  
  if (DAT_00524564 != 0) {
    for (piVar2 = *(int **)(DAT_00524564 + 0x1c); piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
      if ((piVar2[0x15] != 0) && (piVar2[0x19] == 0)) {
        if (param_1 == (char *)0x0) {
          return piVar2;
        }
        iVar1 = _stricmp((char *)(piVar2 + 1),param_1);
        if (iVar1 == 0) {
          return piVar2;
        }
      }
    }
    piVar2 = *(int **)(DAT_00524564 + 0x20);
    if (piVar2 != (int *)0x0) {
      while (((piVar2[0x15] == 0 || (piVar2[0x19] != 0)) ||
             ((param_1 != (char *)0x0 &&
              (iVar1 = _stricmp((char *)(piVar2 + 1),param_1), iVar1 != 0))))) {
        piVar2 = (int *)*piVar2;
        if (piVar2 == (int *)0x0) {
          return (int *)0x0;
        }
      }
      return piVar2;
    }
  }
  return (int *)0x0;
}


