/*
 * Program: i76.exe
 * Function: initialize_flamer_effect_state
 * Entry: 00443c90
 * Signature: undefined __cdecl initialize_flamer_effect_state(int param_1, int param_2, int param_3, int param_4, int param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: flamer */

void __cdecl
initialize_flamer_effect_state(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  LPVOID pvVar3;
  int *piVar4;
  
  if (DAT_0052bb90 != (int *)0x0) {
    piVar4 = (int *)0x0;
    piVar1 = DAT_0052bb90;
    do {
      if (piVar1[1] == param_1) {
        piVar4 = piVar1;
      }
      piVar1 = (int *)*piVar1;
    } while (piVar1 != DAT_0052bb90);
    if (piVar4 == (int *)0x0) {
      if (param_2 < 3) {
        DAT_0052bb90[6] = 0;
        DAT_0052bb90[7] = 0;
        DAT_0052bb90[1] = param_1;
        iVar2 = get_root_ancestor_world_object(param_1);
        DAT_0052bb90[2] = iVar2;
        increment_refcount_recursive_for_object_tree(DAT_0052bb90[1],s_flamer_004f22e0);
        increment_refcount_recursive_for_object_tree(DAT_0052bb90[2],s_flamer_004f22e0);
        create_lobj_light_runtime_entry(param_1,1,5.0,0.0,(float *)0x0,(undefined4 *)0x0);
        pvVar3 = allocate_world_object_node(0);
        DAT_0052bb90[3] = (int)pvVar3;
        piVar1 = (int *)(param_1 + 0x18);
        piVar4 = (int *)(DAT_0052bb90[3] + 0x18);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar4 = *piVar1;
          piVar1 = piVar1 + 1;
          piVar4 = piVar4 + 1;
        }
        create_lobj_light_runtime_entry(DAT_0052bb90[3],0,2.0,0.0,(float *)0x0,(undefined4 *)0x0);
        DAT_0052bb90[9] = param_2;
        DAT_0052bb90[10] = 0;
        DAT_0052bb90[0xb] = 0;
        DAT_0052bb90[0xc] = 0;
        DAT_0052bb90[0xd] = 0;
        DAT_0052bb90[5] = 1;
        piVar1 = (int *)(param_1 + 0x18);
        piVar4 = DAT_0052bb90 + 0x12;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar4 = *piVar1;
          piVar1 = piVar1 + 1;
          piVar4 = piVar4 + 1;
        }
        DAT_0052bb90[4] = 1;
        DAT_0052bb90[0x10] = param_3;
        DAT_0052bb90[0xe] = param_4;
        DAT_0052bb90[0xf] = param_5;
        DAT_0052bb90[0x22] = 0;
        piVar4 = DAT_0052bb90;
        DAT_0052bb90 = (int *)*DAT_0052bb90;
      }
      else {
        piVar4 = (int *)0x0;
      }
      if (piVar4 == (int *)0x0) {
        return;
      }
    }
    if ((piVar4[5] < 0x13) && ((&DAT_0052bb40)[piVar4[7]] != piVar4[6])) {
      piVar4[7] = (&DAT_0052bb40)[piVar4[7]];
      piVar4[5] = piVar4[5] + 1;
      if (piVar4[3] == 0) {
        pvVar3 = allocate_world_object_node(0);
        piVar4[3] = (int)pvVar3;
      }
      else {
        release_world_object_light_runtime(piVar4[3]);
      }
      create_lobj_light_runtime_entry
                (piVar4[3],0,(float)piVar4[5] - _DAT_004bd310,0.0,(float *)0x0,(undefined4 *)0x0);
    }
    piVar4[4] = 1;
  }
  return;
}


