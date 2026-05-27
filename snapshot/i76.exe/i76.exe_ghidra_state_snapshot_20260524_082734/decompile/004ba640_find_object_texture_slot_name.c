/*
 * Program: i76.exe
 * Function: find_object_texture_slot_name
 * Entry: 004ba640
 * Signature: int __cdecl find_object_texture_slot_name(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Looks up texture slot names and
   normalizes .map/.tmt suffix behavior for object/geometry texture bindings. */

int __cdecl find_object_texture_slot_name(int param_1,int param_2)

{
  char *_Str1;
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x5c);
  for (; (iVar2 == 0 && (param_2 < 6)); param_2 = param_2 + 1) {
    ensure_world_object_geometry_variant_binding(param_1,param_2);
    iVar2 = *(int *)(param_1 + 0x5c);
  }
  if ((*(int *)(param_1 + 0x5c) == 0) ||
     (iVar2 = *(int *)(*(int *)(param_1 + 0x5c) + 0x14), iVar2 == 0)) {
    return 0;
  }
  do {
    if (*(char *)(iVar2 + 0x20) != '\0') {
      _Str1 = strchr((char *)(iVar2 + 0x20),0x2e);
      if (_Str1 == (char *)0x0) {
        iVar1 = 0;
      }
      else {
        iVar1 = _stricmp(_Str1,(char *)&DAT_004f25e8);
      }
      if (iVar1 != 0) {
        return iVar2 + 0x20;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x30);
    if (iVar2 == 0) {
      return 0;
    }
  } while( true );
}


