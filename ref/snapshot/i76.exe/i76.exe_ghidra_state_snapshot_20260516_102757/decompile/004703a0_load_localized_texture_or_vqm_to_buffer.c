/*
 * Program: i76.exe
 * Function: load_localized_texture_or_vqm_to_buffer
 * Entry: 004703a0
 * Signature: undefined __cdecl load_localized_texture_or_vqm_to_buffer(char * param_1, int param_2, size_t param_3, uint * param_4, uint * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe image payload renames v28; confidence=medium] Localized/resource-variant texture
   loader that ultimately routes texture image data through direct/VQM image loading into a caller
   buffer. */

void __cdecl
load_localized_texture_or_vqm_to_buffer
          (char *param_1,int param_2,size_t param_3,uint *param_4,uint *param_5)

{
  char cVar1;
  undefined1 uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  
  uVar2 = (&DAT_004f8aaf)[_g_display_mode_variant_index & 0xff];
  if (param_1 == (char *)0x0) {
    pcVar3 = (char *)0x0;
    goto LAB_0047045f;
  }
  if (param_2 == 0) {
    strncpy((char *)&g_localized_texture_variant_name_scratch,param_1,param_3);
    uVar4 = 0xffffffff;
    *(undefined1 *)((int)&g_localized_texture_variant_name_scratch + param_3) = uVar2;
    pcVar3 = param_1 + param_3;
    do {
      pcVar6 = pcVar3;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar6 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar6;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar3 = pcVar6 + -uVar4;
    pcVar6 = (char *)((int)&g_localized_texture_variant_name_scratch + param_3 + 1);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar6 = pcVar6 + 4;
    }
LAB_00470455:
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar6 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  else {
    if (param_2 != 1) {
      uVar4 = 0xffffffff;
      pcVar3 = param_1;
      do {
        pcVar6 = pcVar3;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar6 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar6;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar3 = pcVar6 + -uVar4;
      pcVar6 = (char *)&g_localized_texture_variant_name_scratch;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar6 = pcVar6 + 4;
      }
      goto LAB_00470455;
    }
    uVar4 = 0xffffffff;
    pcVar3 = param_1;
    do {
      pcVar6 = pcVar3;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar6 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar6;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar3 = pcVar6 + -uVar4;
    pcVar6 = (char *)&g_localized_texture_variant_name_scratch;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar6 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar6 = pcVar6 + 1;
    }
    *(undefined1 *)((int)&g_localized_texture_variant_name_scratch + param_3) = uVar2;
  }
  pcVar3 = (char *)&g_localized_texture_variant_name_scratch;
LAB_0047045f:
  if (pcVar3 == (char *)0x0) {
    load_texture_resource_resolving_vqm_cbk_to_buffer(param_1,param_4,param_5);
    return;
  }
  load_texture_resource_resolving_vqm_cbk_to_buffer(pcVar3,param_4,param_5);
  return;
}


