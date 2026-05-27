/*
 * Program: i76.exe
 * Function: register_runtime_axis_input_binding_descriptor
 * Entry: 0044c4a0
 * Signature: undefined4 * __cdecl register_runtime_axis_input_binding_descriptor(undefined4 * param_1)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium-high] Parses axis binding
   descriptors such as throttle_up/throttle_down and stores them in the runtime input binding table.
    */

undefined4 * __cdecl register_runtime_axis_input_binding_descriptor(undefined4 *param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  uint uVar9;
  undefined **ppuVar10;
  char *pcVar11;
  char *pcVar12;
  char local_28 [40];
  
  iVar5 = g_runtime_axis_input_binding_count;
  iVar3 = 0;
  if (0 < g_runtime_axis_input_binding_count) {
    piVar7 = &g_runtime_axis_input_binding_table;
    do {
      if (*piVar7 == param_1[1]) {
        return &g_runtime_axis_input_binding_table + iVar3 * 0xd;
      }
      iVar3 = iVar3 + 1;
      piVar7 = piVar7 + 0xd;
    } while (iVar3 < g_runtime_axis_input_binding_count);
  }
  g_runtime_axis_input_binding_count = g_runtime_axis_input_binding_count + 1;
  if (100 < g_runtime_axis_input_binding_count) {
    report_error();
    return (undefined4 *)0x0;
  }
  pcVar4 = strstr((char *)*param_1,&DAT_004f4a30);
  if (pcVar4 == (char *)0x0) {
    (&DAT_00539a3c)[iVar5 * 0xd] = &DAT_00539a50 + iVar5 * 0x34;
  }
  else {
    (&DAT_00539a3c)[iVar5 * 0xd] = &DAT_00539a54 + iVar5 * 0x34;
  }
  iVar3 = iVar5 * 0x34;
  puVar1 = &g_runtime_axis_input_binding_table + iVar5 * 0xd;
  *puVar1 = param_1[1];
  *(undefined4 *)(&DAT_00539a40 + iVar3) = param_1[5] - param_1[4];
  *(undefined4 *)(&DAT_00539a44 + iVar3) = param_1[4] << 0x10;
  (&DAT_00539a4c)[iVar3] = *(undefined1 *)(param_1 + 7);
  iVar5 = param_1[3];
  *(int *)(&DAT_00539a48 + iVar3) = iVar5 * 0x10000;
  uVar8 = 0xffffffff;
  iVar5 = (iVar5 * 0x10000 - *(int *)(&DAT_00539a44 + iVar3)) * 2;
  *(int *)(&DAT_00539a48 + iVar3) = iVar5;
  *(int *)(&DAT_00539a48 + iVar3) = iVar5 / *(int *)(&DAT_00539a40 + iVar3) + -0x10000;
  *(undefined4 *)(&DAT_00539a58 + iVar3) = param_1[6];
  *(undefined4 *)(&DAT_00539a54 + iVar3) = *(undefined4 *)(&DAT_00539a48 + iVar3);
  pcVar4 = (char *)*param_1;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = local_28;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  pcVar4 = strstr(local_28,&DAT_004f4a30);
  if (pcVar4 != (char *)0x0) {
    *pcVar4 = '\0';
  }
  uVar8 = 0xffffffff;
  pcVar4 = s__plus_004f4a28;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar5 = -1;
  pcVar4 = local_28;
  do {
    pcVar11 = pcVar4;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar5 = 0;
  ppuVar10 = &PTR_s_input_axis_throttle_004f2860;
  do {
    iVar6 = _stricmp(*ppuVar10,local_28);
    if (iVar6 == 0) {
      ppuVar10 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
      goto LAB_0044c650;
    }
    ppuVar10 = ppuVar10 + 8;
    iVar5 = iVar5 + 1;
  } while (ppuVar10 < &PTR_s_COCKPIT_VIEW_004f3320);
  ppuVar10 = (undefined **)0x0;
LAB_0044c650:
  if (ppuVar10 == (undefined **)0x0) {
    *(undefined4 *)(&DAT_00539a5c + iVar3) = 0;
  }
  else {
    *(undefined **)(&DAT_00539a5c + iVar3) = ppuVar10[1];
  }
  uVar8 = 0xffffffff;
  pcVar4 = (char *)*param_1;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = local_28;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  pcVar4 = strstr(local_28,&DAT_004f4a30);
  if (pcVar4 != (char *)0x0) {
    *pcVar4 = '\0';
  }
  uVar8 = 0xffffffff;
  pcVar4 = s__minus_004f4a20;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar5 = -1;
  pcVar4 = local_28;
  do {
    pcVar11 = pcVar4;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar5 = 0;
  ppuVar10 = &PTR_s_input_axis_throttle_004f2860;
  do {
    iVar6 = _stricmp(*ppuVar10,local_28);
    if (iVar6 == 0) {
      ppuVar10 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
      goto LAB_0044c70b;
    }
    ppuVar10 = ppuVar10 + 8;
    iVar5 = iVar5 + 1;
  } while (ppuVar10 < &PTR_s_COCKPIT_VIEW_004f3320);
  ppuVar10 = (undefined **)0x0;
LAB_0044c70b:
  if (ppuVar10 == (undefined **)0x0) {
    *(undefined4 *)(&DAT_00539a60 + iVar3) = 0;
  }
  else {
    *(undefined **)(&DAT_00539a60 + iVar3) = ppuVar10[1];
  }
  uVar8 = 0xffffffff;
  pcVar4 = (char *)*param_1;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = local_28;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  uVar8 = 0xffffffff;
  pcVar4 = s__set_004f4a18;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar5 = -1;
  pcVar4 = local_28;
  do {
    pcVar11 = pcVar4;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar5 = 0;
  ppuVar10 = &PTR_s_input_axis_throttle_004f2860;
  do {
    iVar6 = _stricmp(*ppuVar10,local_28);
    if (iVar6 == 0) {
      ppuVar10 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
      goto LAB_0044c7ac;
    }
    ppuVar10 = ppuVar10 + 8;
    iVar5 = iVar5 + 1;
  } while (ppuVar10 < &PTR_s_COCKPIT_VIEW_004f3320);
  ppuVar10 = (undefined **)0x0;
LAB_0044c7ac:
  if (ppuVar10 == (undefined **)0x0) {
    *(undefined4 *)(&DAT_00539a68 + iVar3) = 0;
  }
  else {
    *(undefined **)(&DAT_00539a68 + iVar3) = ppuVar10[1];
  }
  uVar8 = 0xffffffff;
  pcVar4 = (char *)*param_1;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = local_28;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  uVar8 = 0xffffffff;
  pcVar4 = s__reset_004f4a10;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar5 = -1;
  pcVar4 = local_28;
  do {
    pcVar11 = pcVar4;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar5 = 0;
  ppuVar10 = &PTR_s_input_axis_throttle_004f2860;
  do {
    iVar6 = _stricmp(*ppuVar10,local_28);
    if (iVar6 == 0) {
      ppuVar10 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
      goto LAB_0044c84d;
    }
    ppuVar10 = ppuVar10 + 8;
    iVar5 = iVar5 + 1;
  } while (ppuVar10 < &PTR_s_COCKPIT_VIEW_004f3320);
  ppuVar10 = (undefined **)0x0;
LAB_0044c84d:
  if (ppuVar10 != (undefined **)0x0) {
    *(undefined **)(&DAT_00539a64 + iVar3) = ppuVar10[1];
    return puVar1;
  }
  *(undefined4 *)(&DAT_00539a64 + iVar3) = 0;
  return puVar1;
}


