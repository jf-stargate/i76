/*
 * Program: i76.exe
 * Function: find_audio_object_by_name_and_attached_world_object
 * Entry: 004222c0
 * Signature: int * __cdecl find_audio_object_by_name_and_attached_world_object(char * param_1, int param_2)
 */


/* cgpt readability rename v13 set A: Searches active and pending audio object lists by name and
   attached world-object pointer. */

int * __cdecl find_audio_object_by_name_and_attached_world_object(char *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (DAT_00524564 != 0) {
    for (piVar2 = *(int **)(DAT_00524564 + 0x1c); piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
      if (piVar2[0x17] == param_2) {
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
      while ((piVar2[0x17] != param_2 ||
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


