/*
 * Program: i76.exe
 * Function: load_mission_objective_text_file
 * Entry: 0045dea0
 * Signature: undefined4 __stdcall load_mission_objective_text_file(void)
 */


/* WARNING: Removing unreachable block (ram,0x0045e0b0) */
/* cgpt whole-binary semantic rename v1: string evidence objective text file / Notepad unavailable
    */

undefined4 load_mission_objective_text_file(void)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined4 *local_110;
  int local_10c;
  uint *local_108;
  int local_104;
  byte local_100 [8];
  byte local_f8;
  byte local_f7 [247];
  
  puVar8 = &DAT_006093c0;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  DAT_00609438 = 0xffffffff;
  local_110 = &DAT_00609420;
  bVar2 = false;
  DAT_006093c4 = 0;
  DAT_006093c0 = 0;
  if ((char)DAT_006094f0 == '\0') {
    iVar5 = 0;
  }
  else {
    local_108 = open_resource_file_into_memory((char *)&DAT_006094f0);
    if (local_108 != (uint *)0x0) {
      local_104 = get_loaded_resource_file_size((char *)&DAT_006094f0);
      puVar8 = &DAT_006093c8;
      piVar9 = &DAT_006093c0;
      iVar3 = system_cutscene_memory_context_helper_00499110
                        ((int *)&local_108,local_100,&local_104,0x100);
      iVar5 = 6;
      do {
        if ((iVar3 == 0) || (local_10c = iVar5 + -1, iVar5 == 0)) {
          release_resource_file_reference((char *)&DAT_006094f0);
          return 1;
        }
        pbVar10 = local_100;
        if (bVar2) {
LAB_0045dfe6:
          uVar6 = 0xffffffff;
          pbVar4 = pbVar10;
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            bVar1 = *pbVar4;
            pbVar4 = pbVar4 + 1;
          } while (bVar1 != 0);
          pbVar4 = (byte *)xalloc_global_heap(~uVar6);
          *puVar8 = pbVar4;
          if (pbVar4 == (byte *)0x0) {
            iVar5 = 0;
            goto LAB_0045e07b;
          }
          uVar6 = 0xffffffff;
          puVar8 = puVar8 + 1;
          do {
            pbVar11 = pbVar10;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pbVar11 = pbVar10 + 1;
            bVar1 = *pbVar10;
            pbVar10 = pbVar11;
          } while (bVar1 != 0);
          uVar6 = ~uVar6;
          pbVar10 = pbVar11 + -uVar6;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pbVar4 = *(undefined4 *)pbVar10;
            pbVar10 = pbVar10 + 4;
            pbVar4 = pbVar4 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pbVar4 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            pbVar4 = pbVar4 + 1;
          }
          *piVar9 = *piVar9 + 1;
          if (!bVar2) {
            local_110 = local_110 + 1;
          }
        }
        else {
          iVar5 = _mbsnbicmp(local_100,(uchar *)s__hidden__004f7324,8);
          if (iVar5 == 0) {
            pbVar10 = &local_f8;
            *local_110 = 1;
            iVar5 = _ismbcspace((int)(char)local_f8);
            while (iVar5 != 0) {
              pbVar4 = pbVar10 + 1;
              pbVar10 = pbVar10 + 1;
              iVar5 = _ismbcspace((int)(char)*pbVar4);
            }
            goto LAB_0045dfe6;
          }
          iVar5 = _mbsnbicmp(local_100,(uchar *)s__failure__004f72e4,9);
          if (iVar5 != 0) goto LAB_0045dfe6;
          puVar8 = &DAT_006093e0;
          bVar2 = true;
          local_10c = 0x10;
          piVar9 = &DAT_006093c4;
        }
        iVar3 = system_cutscene_memory_context_helper_00499110
                          ((int *)&local_108,local_100,&local_104,0x100);
        iVar5 = local_10c;
      } while( true );
    }
    report_error();
    iVar5 = -1;
  }
LAB_0045e07b:
  if (iVar5 == 0) {
    report_error();
    return 0;
  }
  DAT_006093c0 = 0xffffffff;
  return 0;
}


