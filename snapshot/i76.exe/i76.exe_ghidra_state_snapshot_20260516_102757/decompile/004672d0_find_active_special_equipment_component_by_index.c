/*
 * Program: i76.exe
 * Function: find_active_special_equipment_component_by_index
 * Entry: 004672d0
 * Signature: int __cdecl find_active_special_equipment_component_by_index(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Scans special-equipment
   component slots and returns active component matching requested equipment index. */

int __cdecl find_active_special_equipment_component_by_index(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x3ec);
  iVar2 = get_special_equipment_runtime_index(iVar1);
  if (iVar2 == param_2) {
    iVar2 = is_special_equipment_component_active(iVar1);
    if (iVar2 != 0) {
      return iVar1;
    }
  }
  iVar1 = *(int *)(param_1 + 0x3f0);
  iVar2 = get_special_equipment_runtime_index(iVar1);
  if (iVar2 == param_2) {
    iVar2 = is_special_equipment_component_active(iVar1);
    if (iVar2 != 0) {
      return iVar1;
    }
  }
  iVar1 = *(int *)(param_1 + 0x3f4);
  iVar2 = get_special_equipment_runtime_index(iVar1);
  if (iVar2 == param_2) {
    iVar2 = is_special_equipment_component_active(iVar1);
    if (iVar2 != 0) {
      return iVar1;
    }
  }
  return 0;
}


