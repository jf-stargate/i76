/*
 * Program: I76EDIT.EXE
 * Function: __output
 * Entry: 00424440
 * Signature: int __cdecl __output(FILE * param_1, byte * param_2, undefined4 * param_3)
 */


/* Library Function - Single Match
    __output
   
   Library: Visual Studio 1998 Release */

int __cdecl __output(FILE *param_1,byte *param_2,undefined4 *param_3)

{
  char cVar1;
  byte *pbVar2;
  wchar_t wVar3;
  uint uVar4;
  undefined1 *puVar5;
  short *psVar6;
  int *piVar7;
  undefined4 uVar8;
  int iVar9;
  byte bVar10;
  undefined1 *puVar11;
  wchar_t *pwVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  char *pcVar15;
  undefined8 uVar16;
  char local_246;
  char local_245;
  char local_244 [4];
  wchar_t *local_240;
  undefined8 local_23c;
  int local_234;
  undefined8 local_230;
  int local_228;
  int local_224;
  int local_220;
  int local_21c;
  uint local_218;
  int local_214;
  int local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined1 uStack_1;
  
  local_234 = 0;
  bVar10 = *param_2;
  local_21c = 0;
  pbVar2 = param_2;
  puVar5 = local_200;
  puVar14 = local_200;
  puVar11 = local_200;
  do {
    if ((bVar10 == 0) || (param_2 = pbVar2 + 1, local_234 < 0)) {
      return local_234;
    }
    if (((char)bVar10 < ' ') || ('x' < (char)bVar10)) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(byte *)((int)&PTR_LAB_00432268 + (int)(char)bVar10) & 0xf;
    }
    local_21c = (int)((char)(&DAT_00432288)[uVar4 * 8 + local_21c] >> 4);
    switch(local_21c) {
    case 0:
switchD_004244c5_caseD_0:
      local_220 = 0;
      if ((PTR_DAT_00438840[(uint)bVar10 * 2 + 1] & 0x80) != 0) {
        write_char((int)(char)bVar10,param_1,&local_234);
        bVar10 = *param_2;
        param_2 = pbVar2 + 2;
      }
      write_char((int)(char)bVar10,param_1,&local_234);
      break;
    case 1:
      local_20c = 0;
      puVar14 = (undefined1 *)0x0;
      puVar5 = (undefined1 *)0xffffffff;
      local_210 = 0;
      local_228 = 0;
      local_224 = 0;
      local_220 = 0;
      break;
    case 2:
      switch(bVar10) {
      case 0x20:
        puVar14 = (undefined1 *)((uint)puVar14 | 2);
        break;
      case 0x23:
        puVar14 = (undefined1 *)((uint)puVar14 | 0x80);
        break;
      case 0x2b:
        puVar14 = (undefined1 *)((uint)puVar14 | 1);
        break;
      case 0x2d:
        puVar14 = (undefined1 *)((uint)puVar14 | 4);
        break;
      case 0x30:
        puVar14 = (undefined1 *)((uint)puVar14 | 8);
      }
      break;
    case 3:
      if (bVar10 == 0x2a) {
        local_228 = get_int_arg((int *)&param_3);
        if (local_228 < 0) {
          local_228 = -local_228;
          puVar14 = (undefined1 *)((uint)puVar14 | 4);
        }
      }
      else {
        local_228 = (char)bVar10 + -0x30 + local_228 * 10;
      }
      break;
    case 4:
      puVar5 = (undefined1 *)0x0;
      break;
    case 5:
      if (bVar10 == 0x2a) {
        puVar5 = (undefined1 *)get_int_arg((int *)&param_3);
        if ((int)puVar5 < 0) {
          puVar5 = (undefined1 *)0xffffffff;
        }
      }
      else {
        puVar5 = (undefined1 *)((char)bVar10 + -0x30 + (int)puVar5 * 10);
      }
      break;
    case 6:
      switch(bVar10) {
      case 0x49:
        if ((*param_2 != 0x36) || (pbVar2[2] != 0x34)) {
          local_21c = 0;
          goto switchD_004244c5_caseD_0;
        }
        param_2 = pbVar2 + 3;
        puVar14 = (undefined1 *)((uint)puVar14 | 0x8000);
        break;
      case 0x68:
        puVar14 = (undefined1 *)((uint)puVar14 | 0x20);
        break;
      case 0x6c:
        puVar14 = (undefined1 *)((uint)puVar14 | 0x10);
        break;
      case 0x77:
        puVar14 = (undefined1 *)((uint)puVar14 | 0x800);
      }
      break;
    case 7:
      pwVar12 = local_240;
      puVar13 = puVar5;
      switch(bVar10) {
      case 0x43:
        if (((uint)puVar14 & 0x830) == 0) {
          puVar14 = (undefined1 *)((uint)puVar14 | 0x800);
        }
      case 99:
        if (((uint)puVar14 & 0x810) == 0) {
          puVar11 = (undefined1 *)0x1;
          uVar8 = get_int_arg((int *)&param_3);
          local_200 = (undefined1 *)CONCAT31(local_200._1_3_,(char)uVar8);
        }
        else {
          wVar3 = get_short_arg(&param_3);
          puVar11 = (undefined1 *)_wctomb((char *)&local_200,wVar3);
          if ((int)puVar11 < 0) {
            local_210 = 1;
          }
        }
        pwVar12 = (wchar_t *)&local_200;
        break;
      case 0x45:
      case 0x47:
        local_20c = 1;
        bVar10 = bVar10 + 0x20;
      case 0x65:
      case 0x66:
      case 0x67:
        puVar13 = (undefined1 *)((uint)puVar14 | 0x40);
        local_240 = (wchar_t *)&local_200;
        if ((int)puVar5 < 0) {
          puVar5 = (undefined1 *)0x6;
        }
        else if ((puVar5 == (undefined1 *)0x0) && (bVar10 == 0x67)) {
          puVar5 = (undefined1 *)0x1;
        }
        local_208 = *param_3;
        local_204 = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR_FUN_00438680)(&local_208,&local_200,(int)(char)bVar10,puVar5,local_20c);
        if ((((uint)puVar14 & 0x80) != 0) && (puVar5 == (undefined1 *)0x0)) {
          (*(code *)PTR_FUN_0043868c)(&local_200);
        }
        if ((bVar10 == 0x67) && (((uint)puVar14 & 0x80) == 0)) {
          (*(code *)PTR_FUN_00438684)(&local_200);
        }
        if ((char)local_200 == '-') {
          puVar13 = (undefined1 *)((uint)puVar14 | 0x140);
          local_240 = (wchar_t *)((int)&local_200 + 1);
        }
        uVar4 = 0xffffffff;
        pwVar12 = local_240;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          wVar3 = *pwVar12;
          pwVar12 = (wchar_t *)((int)pwVar12 + 1);
        } while ((char)wVar3 != '\0');
        puVar11 = (undefined1 *)(~uVar4 - 1);
        puVar14 = puVar13;
        pwVar12 = local_240;
        break;
      case 0x53:
        if (((uint)puVar14 & 0x830) == 0) {
          puVar14 = (undefined1 *)((uint)puVar14 | 0x800);
        }
      case 0x73:
        puVar11 = (undefined1 *)0x7fffffff;
        if (puVar5 != (undefined1 *)0xffffffff) {
          puVar11 = puVar5;
        }
        local_240 = (wchar_t *)get_int_arg((int *)&param_3);
        if (((uint)puVar14 & 0x810) == 0) {
          pwVar12 = local_240;
          if (local_240 == (wchar_t *)0x0) {
            local_240 = (wchar_t *)PTR_DAT_00437e48;
            pwVar12 = (wchar_t *)PTR_DAT_00437e48;
          }
          for (; (puVar11 != (undefined1 *)0x0 && (puVar11 = puVar11 + -1, (char)*pwVar12 != '\0'));
              pwVar12 = (wchar_t *)((int)pwVar12 + 1)) {
          }
          puVar11 = (undefined1 *)((int)pwVar12 - (int)local_240);
          pwVar12 = local_240;
        }
        else {
          if (local_240 == (wchar_t *)0x0) {
            local_240 = (wchar_t *)PTR_DAT_00437e4c;
          }
          local_220 = 1;
          for (pwVar12 = local_240;
              (puVar11 != (undefined1 *)0x0 && (puVar11 = puVar11 + -1, *pwVar12 != L'\0'));
              pwVar12 = pwVar12 + 1) {
          }
          puVar11 = (undefined1 *)((int)pwVar12 - (int)local_240 >> 1);
          pwVar12 = local_240;
        }
        break;
      case 0x5a:
        psVar6 = (short *)get_int_arg((int *)&param_3);
        if ((psVar6 == (short *)0x0) ||
           (pwVar12 = *(wchar_t **)(psVar6 + 2), pwVar12 == (wchar_t *)0x0)) {
          uVar4 = 0xffffffff;
          local_240 = (wchar_t *)PTR_DAT_00437e48;
          pcVar15 = PTR_DAT_00437e48;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar15;
            pcVar15 = pcVar15 + 1;
          } while (cVar1 != '\0');
          puVar11 = (undefined1 *)(~uVar4 - 1);
          pwVar12 = local_240;
        }
        else if (((uint)puVar14 & 0x800) == 0) {
          local_220 = 0;
          puVar11 = (undefined1 *)(int)*psVar6;
        }
        else {
          local_220 = 1;
          puVar11 = (undefined1 *)((uint)(int)*psVar6 >> 1);
        }
        break;
      case 100:
      case 0x69:
        local_218 = 10;
        puVar14 = (undefined1 *)((uint)puVar14 | 0x40);
        goto LAB_004248a7;
      case 0x6e:
        piVar7 = (int *)get_int_arg((int *)&param_3);
        if (((uint)puVar14 & 0x20) == 0) {
          *piVar7 = local_234;
        }
        else {
          *(short *)piVar7 = (short)local_234;
        }
        local_210 = 1;
        pwVar12 = local_240;
        break;
      case 0x6f:
        local_218 = 8;
        if (((uint)puVar14 & 0x80) != 0) {
          puVar14 = (undefined1 *)((uint)puVar14 | 0x200);
        }
        goto LAB_004248a7;
      case 0x70:
        puVar5 = (undefined1 *)0x8;
      case 0x58:
        local_214 = 7;
        goto LAB_00424880;
      case 0x75:
        local_218 = 10;
        goto LAB_004248a7;
      case 0x78:
        local_214 = 0x27;
LAB_00424880:
        local_218 = 0x10;
        puVar13 = puVar5;
        if (((uint)puVar14 & 0x80) != 0) {
          local_246 = '0';
          local_224 = 2;
          local_245 = (char)local_214 + 'Q';
        }
LAB_004248a7:
        if (((uint)puVar14 & 0x8000) == 0) {
          if (((uint)puVar14 & 0x20) == 0) {
            if (((uint)puVar14 & 0x40) == 0) {
              uVar4 = get_int_arg((int *)&param_3);
              goto LAB_00424946;
            }
            iVar9 = get_int_arg((int *)&param_3);
            local_23c = (ulonglong)iVar9;
          }
          else if (((uint)puVar14 & 0x40) == 0) {
            uVar4 = get_int_arg((int *)&param_3);
            uVar4 = uVar4 & 0xffff;
LAB_00424946:
            local_23c = (ulonglong)uVar4;
          }
          else {
            uVar8 = get_int_arg((int *)&param_3);
            local_23c = (ulonglong)(int)(short)uVar8;
          }
        }
        else {
          local_23c = get_int64_arg((int *)&param_3);
        }
        if (((((uint)puVar14 & 0x40) == 0) || (0 < local_23c._4_4_)) || (-1 < (longlong)local_23c))
        {
          local_230 = local_23c;
        }
        else {
          puVar14 = (undefined1 *)((uint)puVar14 | 0x100);
          local_230 = CONCAT44(-(local_23c._4_4_ + (uint)((uint)local_23c != 0)),-(uint)local_23c);
        }
        if (((uint)puVar14 & 0x8000) == 0) {
          local_230 = local_230 & 0xffffffff;
        }
        if ((int)puVar13 < 0) {
          puVar13 = (undefined1 *)0x1;
        }
        else {
          puVar14 = (undefined1 *)((uint)puVar14 & 0xfffffff7);
        }
        pwVar12 = (wchar_t *)register0x00000010;
        if ((local_230._4_4_ == 0) && ((uint)local_230 == 0)) {
          local_224 = 0;
        }
        while( true ) {
          local_240 = (wchar_t *)((int)pwVar12 + -1);
          puVar5 = puVar13 + -1;
          if ((((int)puVar13 < 1) && (local_230._4_4_ == 0)) && ((uint)local_230 == 0)) break;
          uVar4 = (int)local_218 >> 0x1f;
          local_23c = (ulonglong)(int)local_218;
          uVar16 = __aullrem((uint)local_230,local_230._4_4_,local_218,uVar4);
          iVar9 = (int)uVar16 + 0x30;
          local_230 = __aulldiv((uint)local_230,local_230._4_4_,(uint)local_23c,uVar4);
          if (0x39 < iVar9) {
            iVar9 = iVar9 + local_214;
          }
          *(char *)local_240 = (char)iVar9;
          puVar13 = puVar5;
          pwVar12 = local_240;
        }
        puVar11 = &uStack_1 + -(int)local_240;
        if ((((uint)puVar14 & 0x200) != 0) &&
           (((char)*pwVar12 != '0' || (puVar11 == (undefined1 *)0x0)))) {
          puVar11 = &stack0x00000000 + -(int)local_240;
          *(char *)local_240 = '0';
          pwVar12 = local_240;
        }
      }
      local_240 = pwVar12;
      if (local_210 == 0) {
        if (((uint)puVar14 & 0x40) != 0) {
          if (((uint)puVar14 & 0x100) == 0) {
            if (((uint)puVar14 & 1) == 0) {
              if (((uint)puVar14 & 2) == 0) goto LAB_00424bb9;
              local_246 = ' ';
            }
            else {
              local_246 = '+';
            }
          }
          else {
            local_246 = '-';
          }
          local_224 = 1;
        }
LAB_00424bb9:
        iVar9 = (local_228 - (int)puVar11) - local_224;
        local_230 = CONCAT44(local_230._4_4_,iVar9);
        if (((uint)puVar14 & 0xc) == 0) {
          write_multi_char(0x20,iVar9,param_1,&local_234);
        }
        write_string(&local_246,local_224,param_1,&local_234);
        if ((((uint)puVar14 & 8) != 0) && (((uint)puVar14 & 4) == 0)) {
          write_multi_char(0x30,(uint)local_230,param_1,&local_234);
        }
        if ((local_220 == 0) || ((int)puVar11 < 1)) {
          write_string((char *)local_240,(int)puVar11,param_1,&local_234);
        }
        else {
          local_23c = CONCAT44(local_23c._4_4_,puVar11 + -1);
          pwVar12 = local_240;
          do {
            wVar3 = *pwVar12;
            pwVar12 = pwVar12 + 1;
            iVar9 = _wctomb(local_244,wVar3);
            if (iVar9 < 1) break;
            write_string(local_244,iVar9,param_1,&local_234);
            iVar9 = (uint)local_23c;
            local_23c = CONCAT44(local_23c._4_4_,(uint)local_23c + -1);
          } while (iVar9 != 0);
        }
        if (((uint)puVar14 & 4) != 0) {
          write_multi_char(0x20,(uint)local_230,param_1,&local_234);
        }
      }
    }
    bVar10 = *param_2;
    pbVar2 = param_2;
  } while( true );
}


