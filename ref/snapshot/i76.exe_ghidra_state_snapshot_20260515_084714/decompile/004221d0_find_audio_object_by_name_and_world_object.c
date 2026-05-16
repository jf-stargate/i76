/*
 * Program: i76.exe
 * Function: find_audio_object_by_name_and_world_object
 * Entry: 004221d0
 * Signature: int * __cdecl find_audio_object_by_name_and_world_object(char * param_1, int param_2)
 */


/* cgpt rename v3: Searches the active audio object list by attached world object and optional
   case-insensitive sound name. */

int * __cdecl find_audio_object_by_name_and_world_object(char *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if ((DAT_00524564 != 0) && (piVar2 = *(int **)(DAT_00524564 + 0x1c), piVar2 != (int *)0x0)) {
    while ((piVar2[0x17] != param_2 ||
           ((param_1 != (char *)0x0 && (iVar1 = _stricmp((char *)(piVar2 + 1),param_1), iVar1 != 0))
           ))) {
      piVar2 = (int *)*piVar2;
      if (piVar2 == (int *)0x0) {
        return (int *)0x0;
      }
    }
    return piVar2;
  }
  return (int *)0x0;
}


