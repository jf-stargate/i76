/*
 * Program: i76.exe
 * Function: copy_wdf_component_definition_to_shell_descriptor
 * Entry: 004b7190
 * Signature: undefined __cdecl copy_wdf_component_definition_to_shell_descriptor(undefined4 * param_1, byte * param_2, undefined4 param_3)
 */


/* [cgpt i76.exe callback subsystem rename v3; confidence=high] ShellMain callback slot +0x18.
   Parses a component definition buffer and copies core numeric fields plus component block entries
   into the shell-facing descriptor structure. */

void __cdecl
copy_wdf_component_definition_to_shell_descriptor
          (undefined4 *param_1,byte *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_c0 [3];
  undefined4 local_b3;
  undefined4 local_af;
  undefined4 local_ab;
  undefined4 local_a7;
  undefined4 local_a3;
  undefined4 local_9f;
  undefined4 local_9b;
  undefined4 local_97;
  undefined4 local_83;
  undefined4 local_7f;
  undefined4 local_7b;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58 [20];
  undefined4 local_8;
  int local_4;
  
  puVar1 = local_c0;
  for (iVar2 = 0x30; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  local_8 = param_3;
  parse_vcst_vehicle_state_resource(param_2,(int)local_c0);
  param_1[2] = local_7b;
  param_1[5] = local_6c;
  *param_1 = local_83;
  param_1[1] = local_7f;
  param_1[8] = local_60;
  param_1[3] = local_74;
  param_1[4] = local_70;
  param_1[6] = local_68;
  param_1[7] = local_64;
  if (0 < local_4) {
    puVar1 = param_1 + 0x27;
    puVar3 = local_58;
    do {
      puVar1[-0x1e] = puVar3[-1];
      *puVar1 = *puVar3;
      puVar1 = puVar1 + 1;
      local_4 = local_4 + -1;
      puVar3 = puVar3 + 3;
    } while (local_4 != 0);
  }
  *(undefined1 *)(param_1 + 0x45) = local_77;
  *(undefined1 *)((int)param_1 + 0x115) = local_76;
  *(undefined1 *)((int)param_1 + 0x116) = local_75;
  param_1[0x46] = local_b3;
  param_1[0x47] = local_af;
  param_1[0x48] = local_ab;
  param_1[0x49] = local_a7;
  param_1[0x4a] = local_a3;
  param_1[0x4b] = local_9f;
  param_1[0x4c] = local_9b;
  param_1[0x4d] = local_97;
  return;
}


