/*
 * Program: i76.exe
 * Function: clear_mission_parse_object_callback_state
 * Entry: 004b84b0
 * Signature: undefined __cdecl clear_mission_parse_object_callback_state(int * param_1)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=MEDIUM_HIGH] Mission parser object
   reset callback that releases geometry cache state stored at object +0x5c. */

void __cdecl clear_mission_parse_object_callback_state(int *param_1)

{
  int iVar1;
  
  if (((param_1 != (int *)0x0) && (*param_1 != 0)) &&
     (iVar1 = *(int *)(*param_1 + 0x5c), iVar1 != 0)) {
    release_geometry_cache_reference(iVar1);
    *(undefined4 *)(*param_1 + 0x5c) = 0;
  }
  return;
}


