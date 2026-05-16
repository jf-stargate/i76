/*
 * Program: i76.exe
 * Function: geometry_math_context_helper_00479c90
 * Entry: 00479c90
 * Signature: size_t * __cdecl geometry_math_context_helper_00479c90(char * param_1)
 */


/* cgpt readability rename set D v16: Readability pass set D: geometry math context helper based on
   adjacent named subsystem context. */

size_t * __cdecl geometry_math_context_helper_00479c90(char *param_1)

{
  undefined1 uVar1;
  FILE *_File;
  size_t *psVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  size_t _Size;
  uint uVar6;
  code *pcVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  size_t *local_8d0;
  uint local_8cc;
  char local_8b4;
  char local_8b3;
  char local_8b1;
  short local_8b0;
  short local_8ae;
  short local_8ac;
  short local_8aa;
  short local_872;
  int local_834 [13];
  undefined4 local_800 [512];
  
  _File = fopen(param_1,&DAT_004c2098);
  if (_File == (FILE *)0x0) {
    return (size_t *)0x0;
  }
  fread(&local_8b4,0x80,1,_File);
  if (((local_8b4 != '\n') && (local_8b3 != '\x05')) && (local_8b1 != '\b')) {
    fclose(_File);
    return (size_t *)0x0;
  }
  _Size = ((int)local_8ac - (int)local_8b0) + 1;
  uVar8 = ((int)local_8aa - (int)local_8ae) + 1;
  psVar2 = (size_t *)xalloc_global_heap(uVar8 * _Size + 8);
  *psVar2 = _Size;
  psVar2[1] = (uVar8 ^ psVar2[1]) & 0x1fffffff ^ psVar2[1];
  if (0 < (int)uVar8) {
    local_8d0 = psVar2 + 2;
    pcVar7 = fgetc_exref;
    local_8cc = uVar8;
    do {
      iVar3 = (int)local_872;
      iVar9 = 0;
      if (0 < iVar3) {
        do {
          iVar4 = (*pcVar7)(_File);
          if (iVar4 < 0xc1) {
            *(char *)((int)local_800 + iVar9) = (char)iVar4;
            iVar9 = iVar9 + 1;
          }
          else {
            uVar6 = iVar4 - 0xc0;
            uVar1 = (*pcVar7)(_File);
            puVar10 = (undefined4 *)((int)local_800 + iVar9);
            for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar10 = CONCAT22(CONCAT11(uVar1,uVar1),CONCAT11(uVar1,uVar1));
              puVar10 = puVar10 + 1;
            }
            iVar9 = iVar9 + uVar6;
            for (uVar6 = uVar6 & 3; pcVar7 = fgetc_exref, uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined1 *)puVar10 = uVar1;
              puVar10 = (undefined4 *)((int)puVar10 + 1);
            }
          }
        } while (iVar9 < iVar3);
      }
      memmove(local_8d0,local_800,_Size);
      local_8d0 = (size_t *)((int)local_8d0 + _Size);
      local_8cc = local_8cc - 1;
    } while (local_8cc != 0);
  }
  construct_bitmap_surface_context(local_834,_Size,uVar8,(int)(psVar2 + 2),0);
  fclose(_File);
  return psVar2;
}


