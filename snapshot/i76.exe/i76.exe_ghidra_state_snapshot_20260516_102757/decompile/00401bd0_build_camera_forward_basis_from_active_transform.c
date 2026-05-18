/*
 * Program: i76.exe
 * Function: build_camera_forward_basis_from_active_transform
 * Entry: 00401bd0
 * Signature: undefined __cdecl build_camera_forward_basis_from_active_transform(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Builds normalized camera/forward basis vectors into globals
   from an active transform row. */

void __cdecl build_camera_forward_basis_from_active_transform(float param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar4 = -*(float *)((int)param_1 + 0x48);
  fVar2 = -*(float *)((int)param_1 + 0x60);
  fVar3 = fVar4 * fVar4 + fVar2 * fVar2;
  if (_DAT_004bc44c <= fVar3) {
    dVar1 = (double)fVar3;
    fVar6 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar5 = fVar6 * (float10)fVar2;
    param_1 = (float)(fVar6 * (float10)fVar4);
  }
  else {
    fVar5 = (float10)_DAT_004bc454;
    param_1 = 0.0;
  }
  DAT_005dd380 = (float)fVar5;
  DAT_005dd384 = 0;
  _DAT_005dd388 = -param_1;
  _DAT_005dd38c = 0;
  _DAT_005dd390 = 0x3f800000;
  _DAT_005dd3a0 = (float)fVar5;
  _DAT_005dd394 = 0;
  _DAT_005dd398 = param_1;
  _DAT_005dd39c = 0;
  return;
}


