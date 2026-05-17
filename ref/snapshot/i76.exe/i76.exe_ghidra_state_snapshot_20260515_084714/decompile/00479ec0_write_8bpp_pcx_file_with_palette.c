/*
 * Program: i76.exe
 * Function: write_8bpp_pcx_file_with_palette
 * Entry: 00479ec0
 * Signature: undefined4 __cdecl write_8bpp_pcx_file_with_palette(char * param_1, int * param_2, void * param_3)
 */


/* cgpt rename v2: Writes an 8bpp PCX-style file: 0x80 header, RLE scanlines, palette marker, and
   256 RGB triplets. */

undefined4 __cdecl write_8bpp_pcx_file_with_palette(char *param_1,int *param_2,void *param_3)

{
  byte bVar1;
  FILE *_File;
  uint uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  undefined4 *puVar6;
  int local_390;
  int local_38c;
  int local_388;
  undefined1 local_380;
  undefined1 local_37f;
  undefined1 local_37e;
  undefined1 local_37d;
  undefined2 local_37c;
  undefined2 local_37a;
  short local_378;
  short local_376;
  undefined2 local_374;
  undefined2 local_372;
  undefined1 local_370;
  undefined4 local_36f;
  undefined1 local_340;
  undefined1 local_33f;
  short local_33e;
  undefined2 local_33c;
  undefined1 local_33a;
  undefined4 local_339 [14];
  undefined1 local_300 [768];
  
  local_380 = 10;
  local_37f = 5;
  local_37e = 1;
  local_37d = 8;
  local_37c = 0;
  local_37a = 0;
  local_374 = 0x140;
  local_372 = 200;
  local_370 = 0;
  puVar6 = &local_36f;
  for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  *(undefined2 *)puVar6 = 0;
  *(undefined1 *)((int)puVar6 + 2) = 0;
  local_340 = 0;
  local_33f = 1;
  local_33c = 1;
  local_33a = 0;
  iVar3 = param_2[1];
  puVar6 = local_339;
  for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  *(undefined1 *)puVar6 = 0;
  iVar4 = param_2[5];
  local_33e = (short)*param_2;
  local_378 = local_33e + -1;
  local_376 = (short)((iVar3 << 3) >> 3) + -1;
  _File = fopen(param_1,s_wb_004edf28);
  if (_File != (FILE *)0x0) {
    fwrite(&local_380,1,0x80,_File);
    local_390 = 0;
    local_38c = 0;
    if (-1 < param_2[1] << 3) {
      do {
        bVar5 = *(byte *)(iVar4 + local_390);
        iVar3 = iVar4 + local_390;
        uVar2 = 1;
        if (1 < *param_2) {
          local_388 = *param_2 + -1;
          do {
            bVar1 = *(byte *)(iVar3 + 1);
            iVar3 = iVar3 + 1;
            if (bVar1 == bVar5) {
              uVar2 = uVar2 + 1;
              if (uVar2 == 0x3f) {
                fputc(0xff,_File);
                fputc((int)(char)bVar5,_File);
                uVar2 = 0;
              }
            }
            else {
              if (uVar2 != 0) {
                if ((uVar2 != 1) || ((bVar5 & 0xc0) == 0xc0)) {
                  fputc(uVar2 | 0xc0,_File);
                }
                fputc((int)(char)bVar5,_File);
              }
              uVar2 = 1;
              bVar5 = bVar1;
            }
            local_388 = local_388 + -1;
          } while (local_388 != 0);
        }
        if (uVar2 != 0) {
          if ((uVar2 != 1) || ((bVar5 & 0xc0) == 0xc0)) {
            fputc(uVar2 | 0xc0,_File);
          }
          fputc((int)(char)bVar5,_File);
        }
        local_38c = local_38c + 1;
        local_390 = local_390 + *param_2;
      } while (local_38c <= (param_2[1] << 3) >> 3);
    }
    memmove(local_300,param_3,0x300);
    fputc(0xc,_File);
    fwrite(local_300,3,0x100,_File);
    fclose(_File);
    return 1;
  }
  return 0;
}


