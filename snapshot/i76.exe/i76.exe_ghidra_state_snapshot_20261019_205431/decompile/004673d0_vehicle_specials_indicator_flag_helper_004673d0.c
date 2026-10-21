/*
 * Program: i76.exe
 * Function: vehicle_specials_indicator_flag_helper_004673d0
 * Entry: 004673d0
 * Signature: undefined __cdecl vehicle_specials_indicator_flag_helper_004673d0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials indicator flag helper
   based on adjacent named subsystem context. */

void __cdecl vehicle_specials_indicator_flag_helper_004673d0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if ((*(byte *)(iVar1 + 0x454) & 1) != 0) {
    dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
    *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) & 0xfffffffe;
  }
  return;
}


