/*
 * Program: i76.exe
 * Function: parse_tagged_chunk_descriptor_table
 * Entry: 004b3db0
 * Signature: int * __cdecl parse_tagged_chunk_descriptor_table(int * param_1, byte * param_2, int param_3, byte * param_4, byte * param_5, int param_6, int * param_7)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Generic tagged chunk
   descriptor-table parser used by VDF/VCF/VTF/WDF/SOBJ/BWD2 style resources.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=parse_tagged_chunk_descriptor_table :: Generic
   BWD2-style descriptor-table parser. Entry descriptors appear to be 0x10 bytes: tag, arg/extension
   pointer, callback, flags.
   
   I76 rename v43: parse_tagged_chunk_descriptor_table
   Core BWD2 descriptor-table dispatcher used by mission/resource sections. */

int * __cdecl
parse_tagged_chunk_descriptor_table
          (int *param_1,byte *param_2,int param_3,byte *param_4,byte *param_5,int param_6,
          int *param_7)

{
  byte bVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  int *_Source;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_8 [8];
  
  local_10 = 1;
  local_20 = 1;
  local_8[0] = '\0';
  local_8[1] = 0;
  local_8[2] = 0;
  local_8[3] = 0;
  local_8[4] = 0;
  local_c = param_3;
  local_14 = 0;
  local_1c = 0;
  bVar3 = false;
  local_24 = 0;
  _Source = param_1;
  pbVar8 = param_2;
LAB_004b3dfa:
  iVar4 = 0;
  if (local_20 == 0) {
    if (((param_7 != (int *)0x0) && (param_7 <= _Source)) ||
       ((_Source = (int *)((int)_Source + _Source[1]), param_1 = _Source, param_7 != (int *)0x0 &&
        (param_7 <= _Source)))) goto LAB_004b4152;
  }
  else {
    local_20 = 0;
  }
  pbVar5 = (byte *)0x0;
  if (param_6 == 0) {
    bVar9 = param_3 == 0;
    pbVar8 = param_2;
    if (0 < param_3) {
      do {
        if (*_Source == *(int *)pbVar8) break;
        iVar4 = iVar4 + 1;
        pbVar8 = pbVar8 + 0x10;
      } while (iVar4 < param_3);
      bVar9 = iVar4 == param_3;
    }
    if (bVar9) {
      strncpy(local_8,(char *)_Source,4);
      local_8[4] = 0;
      report_error();
    }
    if (*_Source == 0x54495845) goto LAB_004b4152;
  }
  else {
    if (*_Source == *(int *)pbVar8) {
      *(uint *)(pbVar8 + 0xc) = *(uint *)(pbVar8 + 0xc) | 0x80;
      goto LAB_004b3f34;
    }
    if ((bVar3) || (local_14 == 0)) {
      param_3 = param_3 + -1;
      if (param_3 == 0) goto LAB_004b4152;
      bVar3 = false;
      local_24 = 0;
      pbVar8 = pbVar8 + 0x10;
      if (*_Source != 0x54495845) {
        local_20 = 1;
      }
      goto LAB_004b3dfa;
    }
    if ((pbVar8[0xc] & 4) != 0) {
      report_error();
      goto LAB_004b3f34;
    }
    pbVar6 = &DAT_00500680;
    pbVar7 = pbVar8;
    do {
      bVar1 = *pbVar7;
      bVar9 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004b3ee9:
        iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
        goto LAB_004b3eee;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar7[1];
      bVar9 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004b3ee9;
      pbVar7 = pbVar7 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004b3eee:
    if (iVar4 != 0) {
      if ((pbVar8[0xc] & 8) != 0) {
        report_error();
      }
      if ((*(uint *)(pbVar8 + 0xc) & 0x10) != 0) {
        return _Source;
      }
      if ((*(uint *)(pbVar8 + 0xc) & 0x20) != 0) {
        return (int *)0x0;
      }
LAB_004b4152:
      iVar4 = 0;
      if (0 < local_c) {
        do {
          if (((*(uint *)(param_2 + 0xc) & 0x40) != 0) && ((*(uint *)(param_2 + 0xc) & 0x80) == 0))
          {
            strncpy(local_8,(char *)param_2,4);
            local_8[4] = 0;
            report_error();
            local_10 = 0;
            break;
          }
          iVar4 = iVar4 + 1;
          param_2 = param_2 + 0x10;
        } while (iVar4 < local_c);
      }
      if (local_10 != 0) {
        if ((param_7 == (int *)0x0) || (_Source < param_7)) {
          _Source = (int *)((int)_Source + _Source[1]);
        }
        return _Source;
      }
      return (int *)0x0;
    }
  }
LAB_004b3f34:
  uVar2 = *(uint *)(pbVar8 + 0xc);
  if ((uVar2 & 0x100) == 0) {
    if ((uVar2 & 0x200) == 0) {
      if ((bVar3) && (local_24 != 0)) {
        report_error();
      }
      else if ((uVar2 & 0x400) != 0) {
        bVar3 = true;
      }
    }
    else {
      if (!bVar3) {
        bVar3 = true;
        local_14 = 1;
        if (local_1c == 0) {
          local_24 = 0;
          local_18 = 1;
          goto LAB_004b3fd0;
        }
        local_1c = 0;
      }
      local_18 = local_18 + 1;
    }
  }
  else {
    if (bVar3) {
      report_error();
    }
    pbVar5 = (byte *)&local_24;
    local_18 = 0;
    local_1c = 1;
  }
LAB_004b3fd0:
  pbVar7 = pbVar5;
  if (((*(uint *)(pbVar8 + 0xc) & 0x800) != 0) && (pbVar7 = param_4, pbVar5 != (byte *)0x0)) {
    report_error();
  }
  pbVar5 = pbVar7;
  if (((*(uint *)(pbVar8 + 0xc) & 0x1000) != 0) && (pbVar5 = pbVar8, pbVar7 != (byte *)0x0)) {
    report_error();
  }
  pbVar7 = pbVar5;
  if (((*(uint *)(pbVar8 + 0xc) & 0x2000) != 0) && (pbVar7 = param_5, pbVar5 != (byte *)0x0)) {
    report_error();
  }
  if ((*(code **)(pbVar8 + 8) != (code *)0x0) &&
     (iVar4 = (**(code **)(pbVar8 + 8))
                        (_Source + (*(uint *)(param_2 + 0xc) >> 1 & 1) * 2,pbVar7,param_7),
     iVar4 == 0)) {
    if ((param_6 == 0) || (*_Source != 0x54495845)) {
      if ((*(uint *)(pbVar8 + 0xc) & 4) == 0) {
        pbVar7 = &DAT_00500680;
        pbVar5 = pbVar8;
        do {
          bVar1 = *pbVar5;
          bVar9 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_004b40a6:
            iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_004b40ab;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar5[1];
          bVar9 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_004b40a6;
          pbVar5 = pbVar5 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_004b40ab:
        if (iVar4 != 0) {
          if ((*(uint *)(pbVar8 + 0xc) & 8) != 0) {
            report_error();
          }
          uVar2 = *(uint *)(pbVar8 + 0xc);
          if ((uVar2 & 0x10) != 0) {
            return param_1;
          }
          if ((uVar2 & 0x20) != 0) {
            return (int *)0x0;
          }
          _Source = param_1;
          if ((uVar2 & 0x200) == 0) goto LAB_004b3dfa;
        }
      }
      else {
        report_error();
      }
    }
    bVar3 = false;
    local_24 = 0;
    _Source = param_1;
  }
  if ((!bVar3) && (param_6 != 0)) {
    param_3 = param_3 + -1;
    if (param_3 == 0) goto LAB_004b4152;
    pbVar8 = pbVar8 + 0x10;
  }
  goto LAB_004b3dfa;
}


