/*
 * Program: i76shell.dll
 * Function: update_victory_record_for_selected_map
 * Entry: 1002d340
 * Signature: undefined __stdcall update_victory_record_for_selected_map(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_victory_record_for_selected_map(void)

{
  FILE *pFVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (DAT_100d4478 == (LPVOID)0x0) {
    DAT_100d4478 = HeapAlloc(DAT_10051c50,1,DAT_1004b2f4 * 8);
    pFVar1 = fopen(s_victory_rec_1004c318,s_r_1004c314);
    if (pFVar1 == (FILE *)0x0) {
      pFVar1 = fopen(s_victory_rec_1004c328,s_wb_1004c324);
      iVar2 = 0;
      if (0 < DAT_1004b2f4) {
        do {
          iVar2 = iVar2 + 1;
          *(undefined4 *)((int)DAT_100d4478 + iVar2 * 8 + -8) = 0xffffffff;
          *(undefined4 *)((int)DAT_100d4478 + iVar2 * 8 + -4) = 0xffffffff;
        } while (iVar2 < DAT_1004b2f4);
      }
      *(undefined4 *)((int)DAT_100d4478 + DAT_100d4474 * 8) = *(undefined4 *)(DAT_100c5ad8 + 0x38);
      uVar3 = ftol();
      *(undefined4 *)((int)DAT_100d4478 + DAT_100d4474 * 8 + 4) = uVar3;
      fwrite(DAT_100d4478,8,DAT_1004b2f4,pFVar1);
      fclose(pFVar1);
      _DAT_100f1d64 = 0xffffffff;
      return;
    }
    fread(DAT_100d4478,8,DAT_1004b2f4,pFVar1);
    fclose(pFVar1);
    if (*DAT_100d2164 == 1) {
      iVar2 = *(int *)((int)DAT_100d4478 + DAT_100d4474 * 8 + 4);
      if ((iVar2 != -1) && (iVar4 = ftol(), iVar2 <= iVar4)) {
        return;
      }
      fopen(s_victory_rec_1004c338,s_wb_1004c334);
      *(undefined4 *)((int)DAT_100d4478 + DAT_100d4474 * 8) = *(undefined4 *)(DAT_100c5ad8 + 0x38);
      uVar3 = ftol();
      *(undefined4 *)((int)DAT_100d4478 + DAT_100d4474 * 8 + 4) = uVar3;
      fwrite(DAT_100d4478,8,DAT_1004b2f4,pFVar1);
      fclose(pFVar1);
    }
  }
  return;
}


