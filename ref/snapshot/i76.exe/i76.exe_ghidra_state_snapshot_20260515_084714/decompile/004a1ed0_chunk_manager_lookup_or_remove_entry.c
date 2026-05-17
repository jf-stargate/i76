/*
 * Program: i76.exe
 * Function: chunk_manager_lookup_or_remove_entry
 * Entry: 004a1ed0
 * Signature: undefined __cdecl chunk_manager_lookup_or_remove_entry(float * param_1, float param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence chnkmgr */

void __cdecl chunk_manager_lookup_or_remove_entry(float *param_1,float param_2)

{
  LPVOID pvVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  LPVOID pvVar6;
  int iStack_18;
  
  pvVar1 = *(LPVOID *)(DAT_005aaac4 + 100);
  while (pvVar6 = pvVar1, pvVar6 != (LPVOID)0x0) {
    fVar2 = *param_1 - (float)*(double *)((int)pvVar6 + 0x40);
    pvVar1 = *(LPVOID *)((int)pvVar6 + 0x60);
    fVar5 = param_1[1] - (float)*(double *)((int)pvVar6 + 0x48);
    fVar4 = param_1[2] - (float)*(double *)((int)pvVar6 + 0x50);
    fVar3 = param_2 + *(float *)((int)pvVar6 + 0x90);
    if (((uint)((longlong)(double)((fVar4 * fVar4 + fVar5 * fVar5 + fVar2 * fVar2) - fVar3 * fVar3)
               >> 0x3f) & 1) != 0) {
      draw_classifier_display(pvVar6);
      unlink_and_release_world_object_node_refcounted(pvVar6,s_chnkmgr_004fe71c);
    }
  }
  return;
}


