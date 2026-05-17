/*
 * Program: i76.exe
 * Function: runtime_library_memory_copy_helper_004bb010
 * Entry: 004bb010
 * Signature: undefined __cdecl runtime_library_memory_copy_helper_004bb010(undefined4 * param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: runtime library memory copy helper
   based on adjacent named subsystem context. */

void __cdecl runtime_library_memory_copy_helper_004bb010(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  double in_stack_00000030;
  double in_stack_00000038;
  double in_stack_00000040;
  undefined4 local_24 [6];
  float local_c;
  float local_8;
  float local_4;
  
  local_c = (float)in_stack_00000030;
  local_8 = (float)in_stack_00000038;
  local_4 = (float)in_stack_00000040;
  puVar2 = local_24;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


