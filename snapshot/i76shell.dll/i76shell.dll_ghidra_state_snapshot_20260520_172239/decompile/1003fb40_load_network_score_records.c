/*
 * Program: i76shell.dll
 * Function: load_network_score_records
 * Entry: 1003fb40
 * Signature: undefined __stdcall load_network_score_records(void)
 */


void load_network_score_records(void)

{
  char cVar1;
  int iVar2;
  FILE *_File;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  char *_Dest;
  int *piVar7;
  undefined *_DstBuf;
  char *pcVar8;
  char *pcVar9;
  int *piVar10;
  uint local_68;
  int local_64;
  uint local_60;
  int local_5c;
  int *local_58;
  FILE *local_54;
  char local_50 [80];
  
  local_64 = -1;
  DAT_100f5cb8 = create_pointer_list_with_capacity(0x20);
  _File = fopen(s_NSCR_DAT_1004efc0,&DAT_1004efbc);
  uVar4 = 0;
  if (_File != (FILE *)0x0) {
    local_54 = _File;
    fread(&local_68,4,1,_File);
    fread(&local_5c,4,1,_File);
    if (local_5c == 0) {
      if (local_68 != 0) {
        _DstBuf = &DAT_100f5778;
        do {
          fread(_DstBuf,0x54,1,_File);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5cb8,(int)_DstBuf,(undefined *)0x0)
          ;
          uVar4 = uVar4 + 1;
          _DstBuf = _DstBuf + 0x54;
        } while (uVar4 < local_68);
      }
    }
    else {
      local_60 = 0;
      if (local_68 != 0) {
        piVar5 = (int *)&DAT_100f5a0c;
        _Dest = &DAT_100f5778;
        do {
          fread(_Dest,0x54,1,_File);
          iVar2 = *(int *)(_Dest + 0x40);
          piVar6 = piVar5;
          if (iVar2 != local_64) {
            piVar6 = piVar5 + 0x15;
            local_58 = piVar5 + 3;
            local_64 = iVar2;
            insert_pointer_list_item_sorted_or_append
                      ((int)DAT_100f5cb8,(int)local_58,(undefined *)0x0);
            uVar4 = 0xffffffff;
            pcVar8 = (&PTR_s_Grey_Hounds_1004b920)[iVar2];
            do {
              pcVar9 = pcVar8;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar9 = pcVar8 + 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar9;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            piVar7 = (int *)(pcVar9 + -uVar4);
            piVar10 = local_58;
            for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
              *piVar10 = *piVar7;
              piVar7 = piVar7 + 1;
              piVar10 = piVar10 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(char *)piVar10 = (char)*piVar7;
              piVar7 = (int *)((int)piVar7 + 1);
              piVar10 = (int *)((int)piVar10 + 1);
            }
            *piVar6 = 0;
            piVar5[0x16] = 0;
            piVar5[0x17] = 0;
            _File = local_54;
          }
          sprintf(local_50,&DAT_1004efcc,_Dest);
          strncpy(_Dest,local_50,0x20);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5cb8,(int)_Dest,(undefined *)0x0);
          *piVar6 = *piVar6 + *(int *)(_Dest + 0x48);
          piVar6[1] = piVar6[1] + *(int *)(_Dest + 0x4c);
          piVar6[2] = piVar6[2] + *(int *)(_Dest + 0x50);
          local_60 = local_60 + 1;
          piVar5 = piVar6;
          _Dest = _Dest + 0x54;
          if (local_68 <= local_60) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
}


