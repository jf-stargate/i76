/*
 * Program: i76.exe
 * Function: ai_vehicle_behavior_context_stub_00420f80
 * Entry: 00420f80
 * Signature: undefined4 __cdecl ai_vehicle_behavior_context_stub_00420f80(int param_1)
 */


/* cgpt readability rename v13 set A: Small AI vehicle behavior helper; body evidence was limited,
   so this is a neighborhood readability label. */

undefined4 __cdecl ai_vehicle_behavior_context_stub_00420f80(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  if (((*(int *)(iVar1 + 0x98) == 0) && (*(int *)(iVar1 + 0x94) == 0)) &&
     (*(int *)(iVar1 + 0xa8) < *(int *)(iVar1 + 0xac))) {
    return 0;
  }
  return 1;
}


