/*
 * Program: i76.exe
 * Function: vehicle_specials_log_tag
 * Entry: 00467280
 * Signature: undefined __cdecl vehicle_specials_log_tag(int param_1, int param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence: v-spcl */

void __cdecl vehicle_specials_log_tag(int param_1,int param_2,int param_3)

{
  int *piVar1;
  LPVOID pvVar2;
  
  if ((param_2 != 0) && (param_3 < 3)) {
    piVar1 = (int *)(*(int *)(param_1 + 0x70) + 0x3ec + param_3 * 4);
    pvVar2 = allocate_world_object_node(0);
    *piVar1 = (int)pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      set_world_object_class_and_register_runtime((int)pvVar2,0x18);
      vehicle_specials_display_render_context_helper_00467760(*piVar1,param_2);
    }
  }
  return;
}


