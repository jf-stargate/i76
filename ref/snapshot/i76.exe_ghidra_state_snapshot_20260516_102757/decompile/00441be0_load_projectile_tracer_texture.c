/*
 * Program: i76.exe
 * Function: load_projectile_tracer_texture
 * Entry: 00441be0
 * Signature: undefined __cdecl load_projectile_tracer_texture(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references mcannon.map and Tracer map missing */

void __cdecl load_projectile_tracer_texture(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  undefined4 *puVar8;
  
  DAT_0052ba48 = (undefined4 *)0x0;
  pcVar7 = s_mcannon_map_004f1c40;
  do {
    if (pcVar7 != &DAT_004f1c58) {
      puVar3 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)pcVar7);
      *(uint **)(pcVar7 + 0x10) = puVar3;
      if (puVar3 == (uint *)0x0) {
        report_chunk_parse_error();
        pcVar7[0x14] = 0xe3;
        pcVar7[0x15] = 0;
        pcVar7[0x16] = 0;
        pcVar7[0x17] = 0;
      }
      else {
        pcVar7[0x14] = 0x54;
        pcVar7[0x15] = 0;
        pcVar7[0x16] = 0;
        pcVar7[0x17] = 0;
      }
    }
    pcVar7 = pcVar7 + 0x18;
  } while ((int)pcVar7 < 0x4f1c70);
  if (0 < param_1) {
    do {
      puVar4 = (undefined4 *)xalloc_global_heap(100);
      puVar8 = puVar4;
      for (iVar6 = 0x19; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      *puVar4 = DAT_0052ba48;
      param_1 = param_1 + -1;
      DAT_0052ba48 = puVar4;
    } while (param_1 != 0);
  }
  puVar4 = (undefined4 *)*DAT_0052ba48;
  puVar8 = DAT_0052ba48;
  while (puVar2 = puVar4, puVar2 != (undefined4 *)0x0) {
    puVar8 = puVar2;
    puVar4 = (undefined4 *)*puVar2;
  }
  *puVar8 = DAT_0052ba48;
  iVar6 = 0;
  piVar5 = &DAT_0052ba38;
  do {
    iVar6 = iVar6 + 1;
    *piVar5 = iVar6;
    piVar5 = piVar5 + 1;
  } while ((int)piVar5 < 0x52ba40);
  (&DAT_0052ba34)[iVar6] = 0;
  iVar6 = 0;
  piVar5 = &DAT_0052ba40;
  do {
    iVar1 = iVar6 + -1;
    iVar6 = iVar6 + 1;
    *piVar5 = iVar1;
    piVar5 = piVar5 + 1;
  } while ((int)piVar5 < 0x52ba48);
  DAT_0052ba40 = 1;
  return;
}


