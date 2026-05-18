/*
 * Program: i76.exe
 * Function: parse_analog_control_binding
 * Entry: 0044c8a0
 * Signature: int __cdecl parse_analog_control_binding(undefined4 * param_1, char * param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Too many analog controls */

int __cdecl parse_analog_control_binding(undefined4 *param_1,char *param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  iVar6 = g_input_axis_binding_count;
  iVar4 = 0;
  if (0 < g_input_axis_binding_count) {
    piVar3 = &DAT_0053684c;
    do {
      if (((int *)*piVar3 != (int *)0x0) && (*(int *)*piVar3 == param_1[1])) {
        if (param_2 == (char *)0x0) {
          return iVar4;
        }
        if (piVar3[-3] == 0) {
          iVar6 = 0;
          if (g_input_device_context_count < 1) goto LAB_0044ca06;
          pcVar5 = (char *)&DAT_0053da68;
          goto LAB_0044c9ea;
        }
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 0x20;
    } while (iVar4 < g_input_axis_binding_count);
  }
  g_input_axis_binding_count = g_input_axis_binding_count + 1;
  if (100 < g_input_axis_binding_count) {
    report_chunk_parse_error();
    return -1;
  }
  if (param_2 == (char *)0x0) {
LAB_0044c963:
    iVar4 = -1;
  }
  else {
    iVar4 = 0;
    if (0 < g_input_device_context_count) {
      pcVar5 = (char *)&DAT_0053da68;
      do {
        iVar1 = _stricmp(pcVar5,param_2);
        if (iVar1 == 0) {
          if ((&DAT_0053da50)[iVar4] == 0) goto LAB_0044c963;
          goto LAB_0044c966;
        }
        iVar4 = iVar4 + 1;
        pcVar5 = pcVar5 + 0x28;
      } while (iVar4 < g_input_device_context_count);
    }
    iVar4 = validate_input_device(param_2);
  }
LAB_0044c966:
  (&DAT_00536838)[iVar6 * 0x20] = iVar4;
  (&DAT_0053683c)[iVar6 * 0x20] = param_3;
  puVar2 = register_runtime_axis_input_binding_descriptor(param_1);
  (&DAT_0053684c)[iVar6 * 0x20] = puVar2;
  if (iVar4 < 0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2 = &DAT_005365c8 + param_3 + iVar4 * 0x14;
  }
  (&DAT_00536840)[iVar6 * 0x20] = puVar2;
  iVar4 = strncmp((char *)*param_1,s_menu__004f4a58,5);
  *(uint *)(&DAT_005368b4 + iVar6 * 0x80) = (uint)(iVar4 == 0);
  return iVar6;
  while( true ) {
    iVar6 = iVar6 + 1;
    pcVar5 = pcVar5 + 0x28;
    if (g_input_device_context_count <= iVar6) break;
LAB_0044c9ea:
    iVar1 = _stricmp(pcVar5,param_2);
    if (iVar1 == 0) {
      if ((&DAT_0053da50)[iVar6] == 0) {
        iVar6 = -1;
      }
      goto LAB_0044ca13;
    }
  }
LAB_0044ca06:
  iVar6 = validate_input_device(param_2);
LAB_0044ca13:
  (&DAT_00536840)[iVar4 * 0x20] = &DAT_005365c8 + param_3 + iVar6 * 0x14;
  (&DAT_00536838)[iVar4 * 0x20] = iVar6;
  (&DAT_0053683c)[iVar4 * 0x20] = param_3;
  return iVar4;
}


