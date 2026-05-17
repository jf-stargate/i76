/*
 * Program: i76.exe
 * Function: vehicle_component_config_context_helper_004ae2e0
 * Entry: 004ae2e0
 * Signature: undefined __cdecl vehicle_component_config_context_helper_004ae2e0(int param_1, int param_2)
 */


/* cgpt label refinement v20: was vehicle_config_component_context_helper_004ae2e0. Normalize
   component/config label ordering. */

void __cdecl vehicle_component_config_context_helper_004ae2e0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x70);
  switch(*(undefined4 *)(param_1 + 0x6c)) {
  case 0x26:
    *(int *)(iVar1 + 0x440) = param_1;
    return;
  case 0x41:
    *(int *)(iVar1 + 0x408) = param_1;
    return;
  case 0x42:
    *(int *)(iVar1 + 0x40c) = param_1;
    return;
  case 0x43:
    *(int *)(iVar1 + 0x410) = param_1;
    return;
  case 0x44:
    *(int *)(iVar1 + 0x414) = param_1;
    return;
  case 0x45:
    *(int *)(iVar1 + 0x418) = param_1;
    return;
  case 0x46:
    *(int *)(iVar1 + 0x41c) = param_1;
    return;
  case 0x47:
    *(int *)(iVar1 + 0x3a0) = param_1;
    return;
  case 0x48:
    *(int *)(iVar1 + 0x3a4) = param_1;
  }
  return;
}


