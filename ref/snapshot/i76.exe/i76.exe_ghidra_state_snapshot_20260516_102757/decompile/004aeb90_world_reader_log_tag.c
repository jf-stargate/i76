/*
 * Program: i76.exe
 * Function: world_reader_log_tag
 * Entry: 004aeb90
 * Signature: undefined4 __cdecl world_reader_log_tag(int param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence wrldr */

undefined4 __cdecl world_reader_log_tag(int param_1,int *param_2)

{
  char cVar1;
  bool bVar2;
  undefined3 extraout_var;
  float *pfVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  char *pcVar10;
  int **ppiVar11;
  float *pfVar12;
  char *pcVar13;
  char local_5ac [4];
  int local_5a8 [2];
  float local_5a0;
  undefined4 local_59c;
  undefined4 local_598;
  undefined4 local_594;
  undefined4 local_590;
  undefined4 local_58c;
  undefined4 local_588;
  undefined4 local_584;
  undefined4 local_580;
  double local_578;
  double local_570;
  double local_568;
  undefined4 local_560;
  undefined4 local_55c;
  undefined4 local_558;
  int *local_550 [2];
  char local_548 [8];
  int local_540;
  char local_53c [16];
  undefined4 local_52c;
  int local_528;
  undefined4 local_510;
  undefined4 local_50c;
  float local_508;
  undefined4 local_4f6;
  undefined4 local_4f2;
  undefined4 local_4ee;
  undefined4 local_4ea;
  undefined4 local_4e6;
  undefined4 local_4e2;
  undefined4 local_4de;
  undefined4 local_4da;
  byte local_4d6 [13];
  char local_4c9 [13];
  int local_4bc;
  char local_4b8 [16];
  char local_4a8 [16];
  int local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined4 local_48c;
  undefined4 local_488;
  byte local_484 [13];
  byte local_477 [13];
  char local_46a [13];
  byte local_45d [13];
  char local_450 [13];
  byte local_443 [13];
  char local_436 [13];
  byte local_429 [13];
  char local_41c [16];
  LPVOID local_40c;
  undefined4 local_408;
  int local_404;
  int local_3c0 [4];
  undefined4 local_3b0;
  undefined1 local_3a8 [8];
  undefined4 local_3a0;
  char local_398 [8];
  char local_390 [16];
  char local_380 [8];
  char local_378 [16];
  char local_368 [8];
  char local_360 [16];
  char local_350 [8];
  char local_348 [16];
  char local_338 [16];
  char local_328 [80];
  undefined4 local_2d8;
  int local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  char local_2a8 [8];
  char local_2a0 [16];
  uint local_290;
  undefined4 local_28c;
  int local_288;
  int local_284;
  LPVOID local_280;
  int local_27c;
  undefined4 local_278;
  char local_270 [21];
  char local_25b [27];
  float local_240 [16];
  char local_200 [256];
  char local_100 [256];
  
  ppiVar11 = local_550;
  for (iVar4 = 100; iVar4 != 0; iVar4 = iVar4 + -1) {
    *ppiVar11 = (int *)0x0;
    ppiVar11 = ppiVar11 + 1;
  }
  pcVar10 = local_328;
  for (iVar4 = 0x3a; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  piVar9 = local_3c0;
  for (iVar4 = 0x22; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar9 = 0;
    piVar9 = piVar9 + 1;
  }
  piVar9 = local_5a8;
  for (iVar4 = 0x16; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar9 = 0;
    piVar9 = piVar9 + 1;
  }
  iVar4 = param_2[1];
  local_550[0] = param_2;
  local_540 = *(int *)(param_1 + 8);
  _splitpath((char *)(param_1 + 0xc),local_5ac,local_100,local_338,local_200);
  strncpy(local_548,local_338,8);
  bVar2 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)(param_1 + 0xc),&DAT_004ff270,6,(byte *)local_550);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    iVar8 = *(int *)(iVar4 + 0xa5c);
    iVar5 = 0;
    iVar4 = iVar4 + 0x378;
    if (0 < iVar8) {
      do {
        if (*(int *)(iVar4 + 0xb0) == local_540) goto LAB_004aec73;
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0xfc;
      } while (iVar5 < iVar8);
    }
    iVar4 = 0;
LAB_004aec73:
    if ((iVar4 == 0) || (local_404 == 0)) {
      unlink_and_release_world_object_node_refcounted(local_40c,s_wrldr_004ffd3c);
    }
    else {
      local_55c = 3;
      if (local_528 < 100) {
        local_55c = *(undefined4 *)(iVar4 + 0xb8);
      }
      local_560 = *(undefined4 *)(iVar4 + 0xb4);
      local_558 = *(undefined4 *)(iVar4 + 0xb0);
      local_5a8[0] = *param_2;
      local_5a0 = *(float *)(iVar4 + 0xbc);
      local_59c = *(undefined4 *)(iVar4 + 0xc0);
      local_598 = *(undefined4 *)(iVar4 + 0xc4);
      local_594 = *(undefined4 *)(iVar4 + 200);
      local_590 = *(undefined4 *)(iVar4 + 0xcc);
      local_58c = *(undefined4 *)(iVar4 + 0xd0);
      local_588 = *(undefined4 *)(iVar4 + 0xd4);
      local_584 = *(undefined4 *)(iVar4 + 0xd8);
      local_580 = *(undefined4 *)(iVar4 + 0xdc);
      local_578 = (double)*(float *)(iVar4 + 0xe0);
      local_570 = (double)*(float *)(iVar4 + 0xe4);
      local_568 = (double)*(float *)(iVar4 + 0xe8);
      register_hardpoint_carrier(local_5a8);
      pfVar3 = compose_matrix_or_transform_a(local_240,(float *)((int)local_40c + 0x18),&local_5a0);
      pfVar12 = (float *)((int)local_40c + 0x18);
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar12 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar12 = pfVar12 + 1;
      }
      local_2d0 = local_510;
      local_2cc = local_50c;
      local_2c4 = local_4f2;
      local_2c0 = local_4ee;
      local_2bc = local_4de;
      local_278 = local_4de;
      local_2b4 = local_4e6;
      local_2b0 = local_4e2;
      uVar6 = 0xffffffff;
      local_2d8 = local_52c;
      local_2d4 = local_528;
      pcVar10 = local_4a8;
      do {
        pcVar13 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar13;
      } while (cVar1 != '\0');
      local_2c8 = local_4f6;
      local_2b8 = local_4ea;
      uVar6 = ~uVar6;
      local_2ac = local_4da;
      pcVar10 = pcVar13 + -uVar6;
      pcVar13 = local_25b;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar10 = local_4b8;
      do {
        pcVar13 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar10 = pcVar13 + -uVar6;
      pcVar13 = local_270;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar13 = pcVar13 + 1;
      }
      local_280 = local_40c;
      local_288 = local_540;
      local_27c = *param_2;
      uVar6 = 0xffffffff;
      pcVar10 = local_53c;
      do {
        pcVar13 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      local_284 = local_404;
      pcVar10 = pcVar13 + -uVar6;
      pcVar13 = local_328;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar13 = pcVar13 + 1;
      }
      local_290 = (uint)(local_4bc == 1);
      local_28c = local_488;
      iVar4 = _strnicmp(local_4c9,s_null_004c3280,4);
      if (iVar4 == 0) {
        local_4c9[0] = '\0';
      }
      uVar6 = 0xffffffff;
      pcVar10 = local_4c9;
      do {
        pcVar13 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar13;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar10 = pcVar13 + -uVar6;
      pcVar13 = local_2a0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar13 = pcVar13 + 1;
      }
      iVar4 = world_reader_null_handler(local_4d6,local_2a8,local_284);
      if (iVar4 != 0) {
        mount_weapon_on_hardpoint(local_328);
        local_3c0[1] = local_408;
        local_3c0[3] = local_490;
        local_3c0[0] = local_498;
        local_3c0[2] = local_494;
        local_3a0 = local_488;
        local_3b0 = local_48c;
        iVar4 = _strnicmp(local_46a,s_null_004c3280,4);
        if (iVar4 == 0) {
          local_46a[0] = '\0';
        }
        uVar6 = 0xffffffff;
        pcVar10 = local_46a;
        do {
          pcVar13 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar13 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar13;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        pcVar10 = pcVar13 + -uVar6;
        pcVar13 = local_390;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar13 = pcVar13 + 1;
        }
        iVar4 = _strnicmp(local_450,s_null_004c3280,4);
        if (iVar4 == 0) {
          local_450[0] = '\0';
        }
        uVar6 = 0xffffffff;
        pcVar10 = local_450;
        do {
          pcVar13 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar13 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar13;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        pcVar10 = pcVar13 + -uVar6;
        pcVar13 = local_378;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar13 = pcVar13 + 1;
        }
        iVar4 = _strnicmp(local_436,s_null_004c3280,4);
        if (iVar4 == 0) {
          local_436[0] = '\0';
        }
        uVar6 = 0xffffffff;
        pcVar10 = local_436;
        do {
          pcVar13 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar13 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar13;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        pcVar10 = pcVar13 + -uVar6;
        pcVar13 = local_360;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar13 = pcVar13 + 1;
        }
        iVar4 = _strnicmp(local_41c,s_null_004c3280,4);
        if (iVar4 == 0) {
          local_41c[0] = '\0';
        }
        uVar6 = 0xffffffff;
        pcVar10 = local_41c;
        do {
          pcVar13 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar13 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar13;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        pcVar10 = pcVar13 + -uVar6;
        pcVar13 = local_348;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar13 = pcVar13 + 1;
        }
        iVar4 = world_reader_null_handler(local_477,local_398,0);
        if ((((iVar4 != 0) && (iVar4 = world_reader_null_handler(local_45d,local_380,0), iVar4 != 0)
             ) && (iVar4 = world_reader_null_handler(local_443,local_368,0), iVar4 != 0)) &&
           ((iVar4 = world_reader_null_handler(local_429,local_350,0), iVar4 != 0 &&
            (iVar4 = world_reader_record_handler(local_484,local_3a8,0), iVar4 != 0)))) {
          initialize_ordnance_instance(local_3c0);
          *(float *)(*(int *)(*param_2 + 0x70) + 0xa4) =
               local_508 + *(float *)(*(int *)(*param_2 + 0x70) + 0xa4);
          iVar4 = get_vehicle_runtime_context(*param_2);
          iVar8 = 10;
          piVar9 = (int *)(iVar4 + 0x3d0);
          do {
            if (*piVar9 == 0) {
              *(LPVOID *)(iVar4 + 0x3a8 + iVar8 * 4) = local_40c;
              return 1;
            }
            iVar8 = iVar8 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar8 < 0x11);
          return 1;
        }
      }
    }
  }
  return 0;
}


