/*
 * Program: i76.exe
 * Function: world_instance_id_registration_context_helper_004ad410
 * Entry: 004ad410
 * Signature: bool __cdecl world_instance_id_registration_context_helper_004ad410(undefined4 * param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: world instance id registration context
   helper based on adjacent named subsystem context. */

bool __cdecl world_instance_id_registration_context_helper_004ad410(undefined4 *param_1)

{
  HANDLE hHeap;
  LPVOID pvVar1;
  
  hHeap = HeapCreate(0,0,0);
  *param_1 = hHeap;
  pvVar1 = HeapAlloc(hHeap,8,0x8000);
  param_1[1] = pvVar1;
  param_1[3] = 0x800;
  param_1[2] = 0;
  return pvVar1 != (LPVOID)0x0;
}


