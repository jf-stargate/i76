/*
 * Program: i76.exe
 * Function: reset_pending_mission_vehicle_effect_spawn_heap
 * Entry: 004a9020
 * Signature: undefined __stdcall reset_pending_mission_vehicle_effect_spawn_heap(void)
 */


/* cgpt rename v2: Clears the pending mission vehicle/effect spawn list, recreates its heap, and
   reseeds randomness. */

void reset_pending_mission_vehicle_effect_spawn_heap(void)

{
  LPVOID pvVar1;
  time_t tVar2;
  
  while (g_pending_mission_vehicle_effect_spawn_list != (LPVOID)0x0) {
    pvVar1 = *(LPVOID *)((int)g_pending_mission_vehicle_effect_spawn_list + 0x120);
    HeapFree(DAT_005da7b0,0,g_pending_mission_vehicle_effect_spawn_list);
    g_pending_mission_vehicle_effect_spawn_list = pvVar1;
  }
  if (DAT_005da7b0 != (HANDLE)0x0) {
    HeapDestroy(DAT_005da7b0);
  }
  DAT_005da7b0 = HeapCreate(0,0,0);
  g_pending_mission_vehicle_effect_spawn_list = (LPVOID)0x0;
  tVar2 = time((time_t *)0x0);
  srand((uint)tVar2);
  return;
}


