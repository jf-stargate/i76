/*
 * Program: I76EDIT.EXE
 * Function: i76edit_load_object_records
 * Entry: 004014bf
 * Signature: undefined __cdecl i76edit_load_object_records(int param_1, int param_2)
 */


void __cdecl i76edit_load_object_records(int param_1,int param_2)

{
  char cVar1;
  undefined4 *_DstBuf;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *_DstBuf_00;
  char *pcVar6;
  undefined4 *puVar7;
  char *pcVar8;
  char *pcVar9;
  int iStack_14;
  uint uStack_10;
  uint uStack_c;
  uint uStack_8;
  uint uStack_4;
  
  _DstBuf_00 = (undefined4 *)0x0;
  __read(param_1,&uStack_4,4);
  uStack_c = 0;
  if (uStack_4 != 0) {
    do {
      __read(param_1,&iStack_14,4);
      __read(param_1,&uStack_8,4);
      uStack_10 = 0;
      if (uStack_8 != 0) {
        do {
          _DstBuf = _malloc(0x78);
          puVar7 = _DstBuf;
          for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar7 = 0;
            puVar7 = puVar7 + 1;
          }
          if (param_2 < 2) {
            if (param_2 == 1) {
              _DstBuf_00 = _malloc(0x70);
              __read(param_1,_DstBuf_00,0x70);
              *_DstBuf = *_DstBuf_00;
              _DstBuf[1] = _DstBuf_00[1];
              _DstBuf[2] = _DstBuf_00[2];
              _DstBuf[3] = _DstBuf_00[3];
              _DstBuf[4] = _DstBuf_00[4];
              _DstBuf[5] = _DstBuf_00[5];
              _DstBuf[6] = _DstBuf_00[6];
              _DstBuf[7] = _DstBuf_00[7];
              uVar4 = 0xffffffff;
              pcVar6 = (char *)((int)_DstBuf_00 + 0x29);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = (char *)((int)_DstBuf + 0x29);
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar4 = 0xffffffff;
              pcVar6 = (char *)(_DstBuf_00 + 8);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = (char *)(_DstBuf + 8);
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar2 = _DstBuf_00[0x17];
              _DstBuf[0x16] = _DstBuf_00[0x16];
              _DstBuf[0x17] = uVar2;
              uVar4 = 0xffffffff;
              _DstBuf[0x18] = _DstBuf_00[0x18];
              pcVar6 = (char *)(_DstBuf_00 + 0x19);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = (char *)(_DstBuf + 0x19);
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar4 = 0xffffffff;
              pcVar6 = (char *)(_DstBuf_00 + 0x19);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar8 = pcVar8 + -uVar4;
              pcVar9 = (char *)((int)_DstBuf + 0x6d);
            }
            else {
              _DstBuf_00 = _malloc(0x68);
              __read(param_1,_DstBuf_00,0x68);
              *_DstBuf = *_DstBuf_00;
              _DstBuf[1] = _DstBuf_00[1];
              _DstBuf[2] = _DstBuf_00[2];
              _DstBuf[3] = _DstBuf_00[3];
              _DstBuf[4] = _DstBuf_00[4];
              _DstBuf[5] = _DstBuf_00[5];
              _DstBuf[6] = _DstBuf_00[6];
              _DstBuf[7] = _DstBuf_00[7];
              uVar4 = 0xffffffff;
              pcVar6 = (char *)((int)_DstBuf_00 + 0x29);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = (char *)((int)_DstBuf + 0x29);
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar4 = 0xffffffff;
              pcVar6 = (char *)(_DstBuf_00 + 8);
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = (char *)(_DstBuf + 8);
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar2 = _DstBuf_00[0x17];
              _DstBuf[0x16] = _DstBuf_00[0x16];
              _DstBuf[0x17] = uVar2;
              uVar4 = 0xffffffff;
              _DstBuf[0x18] = _DstBuf_00[0x18];
              pcVar6 = (char *)&DAT_00434764;
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              iVar3 = -1;
              pcVar6 = (char *)(_DstBuf + 0x19);
              do {
                pcVar9 = pcVar6;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar9 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar9;
              } while (cVar1 != '\0');
              pcVar6 = pcVar8 + -uVar4;
              pcVar8 = pcVar9 + -1;
              for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
                pcVar6 = pcVar6 + 4;
                pcVar8 = pcVar8 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar8 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar8 = pcVar8 + 1;
              }
              uVar4 = 0xffffffff;
              pcVar6 = (char *)&DAT_00434764;
              do {
                pcVar8 = pcVar6;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar8 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar8;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              pcVar8 = pcVar8 + -uVar4;
              iVar3 = -1;
              pcVar6 = (char *)((int)_DstBuf + 0x6d);
              do {
                pcVar9 = pcVar6;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar9 = pcVar6 + 1;
                cVar1 = *pcVar6;
                pcVar6 = pcVar9;
              } while (cVar1 != '\0');
              pcVar9 = pcVar9 + -1;
            }
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar9 = pcVar9 + 4;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar9 = *pcVar8;
              pcVar8 = pcVar8 + 1;
              pcVar9 = pcVar9 + 1;
            }
          }
          else {
            __read(param_1,_DstBuf,0x78);
          }
          puVar7 = &DAT_00439be8 + iStack_14;
          uVar2 = i76edit_alloc_linked_list_node3
                            ((&DAT_00439be8)[iStack_14],(undefined4 *)0x0,(int)_DstBuf);
          *puVar7 = uVar2;
          _DstBuf[0x18] = _DstBuf[0x18] & 0xfffffffe;
          if (_DstBuf_00 != (undefined4 *)0x0) {
            _free(_DstBuf_00);
            _DstBuf_00 = (undefined4 *)0x0;
          }
          uStack_10 = uStack_10 + 1;
        } while (uStack_10 < uStack_8);
      }
      uStack_c = uStack_c + 1;
    } while (uStack_c < uStack_4);
  }
  return;
}


