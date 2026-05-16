/*
 * Program: i76.exe
 * Function: definition_record_parser_context_helper_00448bf0
 * Entry: 00448bf0
 * Signature: undefined __cdecl definition_record_parser_context_helper_00448bf0(undefined4 param_1, char * param_2, char * param_3, char * param_4, int * param_5)
 */


/* cgpt label refinement v18: was definition_record_parser_definition_parser_helper_00448bf0. Remove
   duplicated parser wording. */

void __cdecl
definition_record_parser_context_helper_00448bf0
          (undefined4 param_1,char *param_2,char *param_3,char *param_4,int *param_5)

{
  undefined4 *puVar1;
  int *piVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined1 *puVar10;
  undefined4 *local_a0;
  byte *local_9c;
  char local_98 [8];
  undefined1 auStack_90 [8];
  char local_88 [16];
  char local_78 [16];
  int local_68 [13];
  int local_34 [13];
  
  strncpy(local_78,param_4,0x10);
  _strlwr(local_78);
  strncpy(local_88,param_3,0x10);
  _strlwr(local_88);
  strncpy(local_98,param_2,0x10);
  _strlwr(local_98);
  for (puVar1 = DAT_00531d0c; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    iVar8 = 0;
    if (0 < (int)puVar1[5]) {
      piVar9 = puVar1 + 6;
      puVar10 = auStack_90 + -(int)puVar1;
      do {
        iVar7 = 0;
        piVar4 = piVar9;
        do {
          iVar5 = *piVar4 - *(int *)((int)piVar4 + (int)puVar10);
          if (iVar5 != 0) goto LAB_00448c92;
          piVar4 = piVar4 + 1;
          iVar7 = iVar7 + 1;
        } while (iVar7 < 4);
        iVar5 = 0;
LAB_00448c92:
        if (iVar5 == 0) {
          local_a0 = puVar1 + iVar8 * 8 + 6;
          local_9c = (byte *)puVar1;
          goto LAB_00448cb7;
        }
        iVar8 = iVar8 + 1;
        puVar10 = puVar10 + -0x20;
        piVar9 = piVar9 + 8;
      } while (iVar8 < (int)puVar1[5]);
    }
  }
  local_a0 = (undefined4 *)0x0;
LAB_00448cb7:
  piVar9 = DAT_00531d08;
  if (DAT_00531d08 != (int *)0x0) {
    do {
      iVar8 = _stricmp((char *)(piVar9 + 1),local_98);
      if (iVar8 == 0) break;
      piVar9 = (int *)*piVar9;
    } while (piVar9 != (int *)0x0);
    if ((piVar9 != (int *)0x0) && (iVar8 = 0, 0 < piVar9[5])) {
      piVar4 = piVar9 + 6;
      iVar7 = (int)&local_a0 - (int)piVar9;
      do {
        iVar5 = 0;
        piVar2 = piVar4;
        do {
          iVar6 = *piVar2 - *(int *)((int)piVar2 + iVar7);
          if (iVar6 != 0) goto LAB_00448d0e;
          piVar2 = piVar2 + 1;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 4);
        iVar6 = 0;
LAB_00448d0e:
        if (iVar6 == 0) {
          piVar9 = piVar9 + iVar8 * 8 + 6;
          goto LAB_00448d2d;
        }
        iVar8 = iVar8 + 1;
        iVar7 = iVar7 + -0x20;
        piVar4 = piVar4 + 8;
      } while (iVar8 < piVar9[5]);
    }
  }
  piVar9 = (int *)0x0;
LAB_00448d2d:
  if ((piVar9 != (int *)0x0) && (local_a0 != (undefined4 *)0x0)) {
    local_9c = (byte *)((int)local_9c + 4);
    puVar3 = load_texture_resource_resolving_vqm_cbk_to_cache(local_9c);
    if ((puVar3 != (uint *)0x0) && (param_5[5] != 0)) {
      piVar4 = (int *)construct_bitmap_surface_context
                                (local_34,*puVar3,(int)(puVar3[1] << 3) >> 3,(int)(puVar3 + 2),0);
      puVar1 = local_a0;
      piVar2 = local_68;
      for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
        *piVar2 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar2 = piVar2 + 1;
      }
      iVar8 = ((int)(puVar3[1] << 3) >> 3) - local_a0[5];
      set_bitmap_surface_clip_rect
                (local_68,local_a0[4],iVar8,local_a0[6] + -1 + local_a0[4],(iVar8 - local_a0[7]) + 1
                );
      blit_bitmap_surface_context_clipped_with_palette_blend
                (param_5,local_68,piVar9[4],
                 (uint *)((((param_5[1] << 3) >> 3) - piVar9[5]) - puVar1[7]),(uint *)0x1);
      release_vqm_texture_cache_reference_by_name((char *)local_9c);
    }
  }
  return;
}


