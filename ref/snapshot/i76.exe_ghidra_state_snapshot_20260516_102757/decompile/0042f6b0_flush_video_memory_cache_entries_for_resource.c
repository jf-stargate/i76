/*
 * Program: i76.exe
 * Function: flush_video_memory_cache_entries_for_resource
 * Entry: 0042f6b0
 * Signature: int __cdecl flush_video_memory_cache_entries_for_resource(uint * param_1, uint param_2)
 */


/* cgpt rename v2: String-anchored video-memory cache flush path for overfull resource/video-memory
   item lists. */

int __cdecl flush_video_memory_cache_entries_for_resource(uint *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  DWORD DVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  uint **ppuVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int *piVar12;
  bool bVar13;
  char *_Format;
  int local_40;
  int local_38 [4];
  int local_28;
  uint *local_1c [7];
  
  iVar1 = get_current_texture_cache_generation();
  iVar6 = 0;
  local_40 = 0;
  iVar5 = DAT_0052b910;
  if (0 < DAT_0052b910) {
    do {
      iVar2 = iVar5 + iVar6 >> 1;
      if ((uint *)(&DAT_005280f0)[iVar2 * 7] < param_1) {
        iVar6 = iVar2 + 1;
        iVar2 = iVar5;
      }
      iVar5 = iVar2;
      local_40 = iVar6;
    } while (iVar6 < iVar2);
  }
  piVar12 = &DAT_005280f0 + local_40 * 7;
  if ((uint *)(&DAT_005280f0)[local_40 * 7] == param_1) {
    if ((&DAT_005280f8)[local_40 * 7] == 0) {
      if ((int)(&DAT_005280fc)[local_40 * 7] < -1) {
        create_or_restore_video_memory_texture_surface(piVar12);
      }
    }
    else if ((((DAT_0052b90c < iVar1) && (DAT_005280e8 < iVar1)) &&
             (DVar3 = GetTickCount(), (int)(DAT_005280e4 + 0xa6) <= (int)DVar3)) &&
            ((param_1 != DAT_005280ec ||
             (((int)(DAT_005280e4 + 0x14d) <= (int)DVar3 && (DAT_0052b90c + 1 < iVar1)))))) {
      create_or_restore_video_memory_texture_surface(piVar12);
      (&DAT_005280f8)[local_40 * 7] = 0;
      DAT_0052b90c = iVar1;
      (&DAT_005280fc)[local_40 * 7] = iVar1;
      DAT_005280e4 = DVar3;
      DAT_005280ec = param_1;
      return (&DAT_00528100)[local_40 * 7];
    }
    (&DAT_005280fc)[local_40 * 7] = iVar1;
    return (&DAT_00528100)[local_40 * 7];
  }
  if (DAT_0052b910 < 0x200) {
    initialize_video_memory_texture_cache_record(local_38,param_1,param_2);
    if (DAT_0052b914 < 700000) {
      param_2 = DAT_0052b914 >> 0xf;
      if ((int)param_2 < 1) {
        param_2 = 1;
      }
      iVar6 = iVar1 - param_2;
      iVar5 = -1;
      iVar2 = 0;
      if (0 < DAT_0052b910) {
        piVar7 = &DAT_00528100;
        do {
          if ((piVar7[-3] == local_38[1]) && (*piVar7 != 0)) {
            iVar4 = piVar7[-1];
            if (iVar4 == -1) {
              iVar4 = iVar1 + -5;
            }
            if ((iVar4 < iVar6) &&
               (iVar6 = iVar4, iVar5 = iVar2, iVar4 < (int)(iVar1 + param_2 * -0x10))) break;
          }
          iVar2 = iVar2 + 1;
          piVar7 = piVar7 + 7;
        } while (iVar2 < DAT_0052b910);
      }
      if (-1 < iVar5) {
        iVar6 = 0;
        iVar2 = DAT_0052b910;
        if (0 < DAT_0052b910) {
          do {
            iVar4 = iVar2 + iVar6 >> 1;
            if ((uint *)(&DAT_005280f0)[iVar4 * 7] < param_1) {
              iVar6 = iVar4 + 1;
              iVar4 = iVar2;
            }
            iVar2 = iVar4;
          } while (iVar6 < iVar4);
        }
        puVar10 = &DAT_005280f0 + iVar5 * 7;
        puVar8 = puVar10;
        ppuVar9 = local_1c;
        for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
          *ppuVar9 = (uint *)*puVar8;
          puVar8 = puVar8 + 1;
          ppuVar9 = ppuVar9 + 1;
        }
        local_1c[0] = param_1;
        if (iVar5 < iVar6) {
          iVar6 = iVar6 + -1;
          if (iVar5 < iVar6) {
            iVar5 = iVar6 - iVar5;
            do {
              iVar5 = iVar5 + -1;
              puVar8 = puVar10 + 7;
              puVar11 = puVar10;
              for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
                *puVar11 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar11 = puVar11 + 1;
              }
              puVar10 = puVar10 + 7;
            } while (iVar5 != 0);
          }
        }
        else if (iVar6 < iVar5) {
          iVar5 = iVar5 - iVar6;
          do {
            iVar5 = iVar5 + -1;
            puVar8 = puVar10 + -7;
            puVar11 = puVar10;
            for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar10 = puVar10 + -7;
          } while (iVar5 != 0);
        }
        ppuVar9 = local_1c;
        piVar12 = &DAT_005280f0 + iVar6 * 7;
        for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar12 = (int)*ppuVar9;
          ppuVar9 = ppuVar9 + 1;
          piVar12 = piVar12 + 1;
        }
        (&DAT_005280fc)[iVar6 * 7] = iVar1;
        create_or_restore_video_memory_texture_surface(&DAT_005280f0 + iVar6 * 7);
        return (&DAT_00528100)[iVar6 * 7];
      }
    }
    create_or_restore_video_memory_texture_surface(local_38);
    if (local_28 != 0) {
      if (local_40 < DAT_0052b910) {
        local_40 = DAT_0052b910 - local_40;
        puVar10 = &DAT_005280f0 + DAT_0052b910 * 7;
        do {
          local_40 = local_40 + -1;
          puVar8 = puVar10 + -7;
          puVar11 = puVar10;
          for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar11 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar11 = puVar11 + 1;
          }
          puVar10 = puVar10 + -7;
        } while (local_40 != 0);
      }
      DAT_0052b910 = DAT_0052b910 + 1;
      (&DAT_005280f0)[DAT_0052b910 * 7] = 0;
      piVar7 = local_38;
      for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
        *piVar12 = *piVar7;
        piVar7 = piVar7 + 1;
        piVar12 = piVar12 + 1;
      }
      return local_28;
    }
    if (local_40 < DAT_0052b910) {
      local_40 = DAT_0052b910 - local_40;
      puVar10 = &DAT_005280f0 + DAT_0052b910 * 7;
      do {
        local_40 = local_40 + -1;
        puVar8 = puVar10 + -7;
        puVar11 = puVar10;
        for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar11 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar11 = puVar11 + 1;
        }
        puVar10 = puVar10 + -7;
      } while (local_40 != 0);
    }
    DAT_0052b910 = DAT_0052b910 + 1;
    (&DAT_005280f0)[DAT_0052b910 * 7] = 0;
    iVar6 = g_resource_debug_log_file;
    bVar13 = g_resource_debug_log_file == 0;
    piVar7 = local_38;
    for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar12 = *piVar7;
      piVar7 = piVar7 + 1;
      piVar12 = piVar12 + 1;
    }
    if (bVar13) {
      DAT_005280d0 = 1;
      return 0;
    }
    if (iVar6 != DAT_005a7c90) {
      DAT_005280d0 = 1;
      return 0;
    }
    if (DAT_005280d0 != 0) {
      DAT_005280d0 = 1;
      return 0;
    }
    iVar6 = find_vqm_texture_cache_record_by_bitmap_id((int)param_1);
    _Format = s_Flushing_video_mem_for__s_004edfac;
  }
  else {
    if (g_resource_debug_log_file == 0) {
      DAT_005280d0 = 1;
      return 0;
    }
    if (g_resource_debug_log_file != DAT_005a7c90) {
      DAT_005280d0 = 1;
      return 0;
    }
    if (DAT_005280d0 != 0) {
      DAT_005280d0 = 1;
      return 0;
    }
    iVar6 = find_vqm_texture_cache_record_by_bitmap_id((int)param_1);
    _Format = s_Flushing_video_mem_for__s__too_m_004edfc8;
  }
  fprintf((FILE *)DAT_005a7c90,_Format,iVar6);
  DAT_005280d0 = 1;
  return 0;
}


