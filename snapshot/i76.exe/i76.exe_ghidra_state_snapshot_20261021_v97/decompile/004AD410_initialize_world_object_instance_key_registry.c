/* Decompiled retail i76.exe, Ghidra v97; 004ad410 initialize_world_object_instance_key_registry */

/* cgpt readability rename set E v17: Readability pass set E: world instance id registration context
   helper based on adjacent named subsystem context. */

bool __cdecl initialize_world_object_instance_key_registry(undefined4 *param_1)

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


