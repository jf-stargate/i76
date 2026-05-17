/*
 * Program: i76.exe
 * Function: release_audio_object_resource_and_buffers
 * Entry: 00425ef0
 * Signature: undefined __cdecl release_audio_object_resource_and_buffers(undefined4 * param_1)
 */


/* cgpt rename v2: Releases audio object resources, DirectSound buffers/interfaces, and loaded
   resource references. */

void __cdecl release_audio_object_resource_and_buffers(undefined4 *param_1)

{
  char cVar1;
  int *piVar2;
  bool bVar3;
  undefined3 extraout_var;
  LPVOID pvVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  char local_214 [4];
  char local_210 [16];
  char local_200 [256];
  char local_100 [256];
  
  if (param_1 != (undefined4 *)0x0) {
    stop_audio_object_buffer_if_playing((uint)param_1);
    unlink_audio_object_from_active_or_pending_list(param_1);
    if (param_1[0x15] != 0) {
      piVar2 = (int *)param_1[0x16];
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 8))(piVar2);
      }
      (**(code **)(*(int *)param_1[0x15] + 8))((int *)param_1[0x15]);
      param_1[0x15] = 0;
      param_1[0x16] = 0;
      DAT_005fcbf4 = DAT_005fcbf4 - param_1[0x1c];
    }
    if (param_1[0x13] != 0) {
      if ((param_1[0x1e] & 0x200) == 0) {
        _splitpath((char *)(param_1 + 1),local_214,local_100,local_210,local_200);
        uVar5 = 0xffffffff;
        pcVar8 = &DAT_004ed898;
        do {
          pcVar10 = pcVar8;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar10 = pcVar8 + 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar10;
        } while (cVar1 != '\0');
        uVar5 = ~uVar5;
        iVar6 = -1;
        pcVar8 = local_210;
        do {
          pcVar9 = pcVar8;
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          pcVar9 = pcVar8 + 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar9;
        } while (cVar1 != '\0');
        pcVar8 = pcVar10 + -uVar5;
        pcVar10 = pcVar9 + -1;
        for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
          pcVar8 = pcVar8 + 4;
          pcVar10 = pcVar10 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar10 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          pcVar10 = pcVar10 + 1;
        }
        bVar3 = resource_exists_in_cache_or_search_paths(local_210);
        if (CONCAT31(extraout_var,bVar3) == 0) {
          uVar5 = 0xffffffff;
          pcVar8 = (char *)(param_1 + 1);
          do {
            pcVar10 = pcVar8;
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            pcVar10 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar10;
          } while (bVar3 != (bool)cVar1);
          uVar5 = ~uVar5;
          pcVar8 = pcVar10 + -uVar5;
          pcVar10 = local_210;
          for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            pcVar10 = pcVar10 + 4;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pcVar10 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            pcVar10 = pcVar10 + 1;
          }
        }
        release_resource_file_reference(local_210);
      }
      param_1[0x13] = 0;
      param_1[0x14] = 0;
    }
    if ((LPVOID)param_1[0x17] != (LPVOID)0x0) {
      pvVar4 = release_world_object_tree_reference((LPVOID)param_1[0x17],&PTR_DAT_004ed7ec);
      param_1[0x17] = pvVar4;
      if (pvVar4 != (LPVOID)0x0) {
        finalize_released_world_object_after_damage(pvVar4,&PTR_DAT_004ed7ec);
      }
    }
    HeapFree(DAT_005fcc00,0,param_1);
  }
  return;
}


