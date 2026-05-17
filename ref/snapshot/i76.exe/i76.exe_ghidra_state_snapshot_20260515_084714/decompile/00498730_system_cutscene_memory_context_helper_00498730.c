/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00498730
 * Entry: 00498730
 * Signature: undefined __cdecl system_cutscene_memory_context_helper_00498730(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00498730. Shorten readability
   label for system/cutscene/virtual-memory context. */

void __cdecl system_cutscene_memory_context_helper_00498730(int param_1)

{
  float fVar1;
  int *piVar2;
  float fVar3;
  bool bVar4;
  undefined3 extraout_var;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  float10 fVar9;
  uint *puVar10;
  
  fVar9 = get_runtime_frame_delta_seconds();
  fVar1 = (float)fVar9;
  bVar4 = get_global_heap_handle();
  if (CONCAT31(extraout_var,bVar4) == 0) {
    piVar2 = *(int **)(param_1 + 0x3c);
    if (DAT_005a615c == 0) {
      uVar5 = rand();
      uVar6 = rand();
      fVar3 = (float)(uVar5 & 0xf);
      if (((_DAT_004be91c <= fVar1) && (fVar1 <= _DAT_004be924)) &&
         ((float)_DAT_004be928 <= ABS(fVar3 - _DAT_005a6168))) {
        fVar3 = (fVar3 - _DAT_005a6168) * fVar1 + _DAT_005a6168;
      }
      _DAT_005a6168 = fVar3;
      fVar3 = (float)(uVar6 & 0xf);
      if (((_DAT_004be91c <= fVar1) && (fVar1 <= _DAT_004be924)) &&
         ((float)_DAT_004be928 <= ABS(fVar3 - _DAT_005a616c))) {
        fVar3 = (fVar3 - _DAT_005a616c) * fVar1 + _DAT_005a616c;
      }
    }
    else {
      if (_DAT_005a6160 - _DAT_004be918 <= _DAT_005a6164) {
        _DAT_005a6160 = 0.0;
      }
      fVar1 = fVar1 + fVar1;
      fVar3 = _DAT_005a6160;
      if (((_DAT_004be91c <= fVar1) && (fVar3 = _DAT_005a6160, fVar1 <= _DAT_004be924)) &&
         (fVar3 = _DAT_005a6160, (float)_DAT_004be928 <= ABS(_DAT_005a6160 - _DAT_005a6164))) {
        fVar3 = (_DAT_005a6160 - _DAT_005a6164) * fVar1 + _DAT_005a6164;
      }
      _DAT_005a6164 = fVar3;
      fVar3 = _DAT_005a616c;
      if ((_DAT_005a6164 < _DAT_004be918) && (_DAT_005a6160 == _DAT_004be91c)) {
        DAT_005a615c = 0;
        DAT_005a6158 = 0;
      }
    }
    _DAT_005a616c = fVar3;
    puVar10 = (uint *)0x2;
    puVar7 = (uint *)ftol();
    iVar8 = ftol();
    blit_bitmap_surface_context_clipped_with_palette_blend(piVar2,piVar2,iVar8,puVar7,puVar10);
  }
  return;
}


