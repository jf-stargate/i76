/*
 * Program: i76.exe
 * Function: ai_vehicle_behavior_context_stub_00420e70
 * Entry: 00420e70
 * Signature: undefined4 __cdecl ai_vehicle_behavior_context_stub_00420e70(int param_1)
 */


/* cgpt readability rename v13 set A: Small AI vehicle behavior helper; body evidence was limited,
   so this is a neighborhood readability label. */

undefined4 __cdecl ai_vehicle_behavior_context_stub_00420e70(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  if ((*(int *)(iVar1 + 0x9c) == 0) && (*(int *)(iVar1 + 0x88) == *(int *)(iVar1 + 0x8c))) {
    return 0;
  }
  return 1;
}


