/*
 * Program: i76.exe
 * Function: dib_surface_palette_context_helper_004764c0
 * Entry: 004764c0
 * Signature: undefined4 * __stdcall dib_surface_palette_context_helper_004764c0(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: dib surface palette context helper
   based on adjacent named subsystem context. */

undefined4 * dib_surface_palette_context_helper_004764c0(void)

{
  int iVar1;
  int iVar2;
  FILE *_File;
  undefined4 *puVar3;
  int iVar4;
  size_t _ElementSize;
  int *piVar5;
  int *piVar6;
  size_t _Size;
  undefined4 *puVar7;
  int iVar8;
  FILE *pFStack00000004;
  uint uStack00000008;
  size_t in_stack_00000010;
  size_t in_stack_00000014;
  int in_stack_0000001c;
  undefined4 *in_stack_00086c60;
  
  zfsf_error_context_helper_004ba0a0();
  _Size = 0;
  uStack00000008 = (uint)((in_stack_00086c60[1] & 0x100) != 0);
  _File = fopen((char *)*in_stack_00086c60,&DAT_004c2098);
  if (_File == (FILE *)0x0) {
    return (undefined4 *)0x0;
  }
  pFStack00000004 = _File;
  fread(&stack0x0000000c,4,4,_File);
  fread(&stack0x0000001c,in_stack_00000010,4,_File);
  iVar8 = 0;
  if (0 < (int)in_stack_00000010) {
    do {
      fread(&stack0x00009c5c + _Size,1,4,_File);
      _ElementSize = *(size_t *)(&stack0x00009c5c + _Size);
      if (_ElementSize != 0) {
        if (uStack00000008 != 0) {
          _ElementSize = (8 < (int)_ElementSize) + 1;
        }
        fread(&stack0x00009c60 + _Size,_ElementSize,in_stack_00000014,pFStack00000004);
      }
      iVar8 = iVar8 + 1;
      _Size = _Size + 4 + in_stack_00000014 * _ElementSize;
      _File = pFStack00000004;
    } while (iVar8 < (int)in_stack_00000010);
  }
  puVar3 = (undefined4 *)xalloc_global_heap(_Size + 0x20c + in_stack_00000010 * 4);
  if (puVar3 == (undefined4 *)0x0) {
    fclose(_File);
    return (undefined4 *)0x0;
  }
  puVar3[1] = in_stack_00000010;
  puVar3[2] = in_stack_00000014;
  iVar8 = 0;
  if (0 < (int)in_stack_00000010) {
    piVar5 = &stack0x0000001c;
    piVar6 = puVar3 + 0x83;
    do {
      iVar8 = iVar8 + 1;
      *piVar6 = (int)puVar3 + *piVar5 + ((in_stack_00000010 * 4 + 0x20c) - in_stack_0000001c);
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar8 < (int)in_stack_00000010);
  }
  memmove(puVar3 + in_stack_00000010 + 0x83,&stack0x00009c5c,_Size);
  memmove(puVar3 + 3,&g_palette_blend_table_b,0x100);
  puVar7 = puVar3 + 0x43;
  for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar7 = 0xf0f0f0f;
    puVar7 = puVar7 + 1;
  }
  if ((uStack00000008 == 0) && (iVar8 = 0, 0 < (int)in_stack_00000010)) {
    piVar5 = puVar3 + 0x83;
    do {
      piVar6 = (int *)*piVar5;
      iVar4 = 0;
      iVar1 = *piVar6;
      iVar2 = puVar3[2];
      if (0 < iVar1 * iVar2) {
        do {
          *(bool *)((int)piVar6 + iVar4 + 4) = *(char *)((int)piVar6 + iVar4 + 4) != -1;
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar1 * iVar2);
      }
      iVar8 = iVar8 + 1;
      piVar5 = piVar5 + 1;
      _File = pFStack00000004;
    } while (iVar8 < (int)in_stack_00000010);
  }
  fclose(_File);
  *puVar3 = in_stack_00086c60[1];
  return puVar3;
}


