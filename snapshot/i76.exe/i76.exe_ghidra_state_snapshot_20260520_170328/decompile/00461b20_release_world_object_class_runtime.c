/*
 * Program: i76.exe
 * Function: release_world_object_class_runtime
 * Entry: 00461b20
 * Signature: undefined __cdecl release_world_object_class_runtime(int param_1, int param_2)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Dispatches the class-specific
   release callback from the class descriptor table for object class runtime data. */

void __cdecl release_world_object_class_runtime(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
                    /* I76 semantic baseline: release_world_object_class_runtime
                       Dispatches class release callback and releases class runtime. */
  if (param_2 != 0) {
    iVar1 = is_collapsible_special_world_object_class(param_1);
    if ((iVar1 != 0) && (param_1 != 4)) {
      param_1 = 2;
    }
    iVar1 = 0;
    piVar2 = &g_world_object_class_callback_table;
    do {
      if (*piVar2 == param_1) goto LAB_00461b5d;
      piVar2 = piVar2 + 0xd;
      iVar1 = iVar1 + 1;
    } while (piVar2 < s_clasfn_004f7c5c);
    iVar1 = 0;
LAB_00461b5d:
    if ((code *)(&DAT_004f7710)[iVar1 * 0xd] != (code *)0x0) {
      (*(code *)(&DAT_004f7710)[iVar1 * 0xd])(param_2);
    }
  }
  return;
}


