/*
 * Program: i76.exe
 * Function: mark_special_equipment_runtime_activated
 * Entry: 004677e0
 * Signature: undefined __cdecl mark_special_equipment_runtime_activated(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=medium-high] Marks
   special-equipment component runtime activation/state fields. */

void __cdecl mark_special_equipment_runtime_activated(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x70);
    if ((0 < *(int *)(iVar1 + 4)) && (*(int *)(iVar1 + 0x10) == 0)) {
      *(undefined4 *)(iVar1 + 0x10) = 1;
      fVar2 = get_runtime_time_seconds();
      *(float *)(iVar1 + 0x14) = (float)fVar2;
      return;
    }
    *(undefined4 *)(iVar1 + 0x10) = 0;
  }
  return;
}


