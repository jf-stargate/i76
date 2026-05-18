/*
 * Program: i76.exe
 * Function: create_lobj_light_runtime_entry
 * Entry: 00477c20
 * Signature: undefined __cdecl create_lobj_light_runtime_entry(int param_1, int param_2, float param_3, float param_4, float * param_5, undefined4 * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Creates runtime LOBJ light entry,
   clamps range/cone values, computes attenuation, stores color fields, and handles spotlight
   direction. */

void __cdecl
create_lobj_light_runtime_entry
          (int param_1,int param_2,float param_3,float param_4,float *param_5,undefined4 *param_6)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float10 fVar7;
  double dVar8;
  undefined4 *local_4;
  
  iVar2 = g_runtime_light_entry_count;
  if ((*(int *)(&DAT_004fa0b0 + DAT_0058db00 * 0x14) != 1) && (g_runtime_light_entry_count < 0x200))
  {
    iVar3 = 0;
    if (0 < g_runtime_light_entry_count) {
      piVar4 = &g_runtime_light_entries;
      do {
        if (*piVar4 == param_1) {
          return;
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 0x1b;
      } while (iVar3 < g_runtime_light_entry_count);
    }
    g_runtime_light_entry_count = g_runtime_light_entry_count + 1;
    if (param_6 == (undefined4 *)0x0) {
      local_4 = param_6;
      uVar5 = 0;
      uVar6 = 0;
    }
    else {
      local_4 = (undefined4 *)param_6[2];
      uVar5 = *param_6;
      uVar6 = param_6[1];
    }
    if (param_3 < _DAT_004be614) {
      param_3 = 20.0;
    }
    fVar7 = (float10)param_4;
    if (fVar7 < (float10)_DAT_004be618) {
      fVar7 = (float10)_DAT_004be618;
    }
    if ((float10)_DAT_004be61c < fVar7) {
      fVar7 = (float10)_DAT_004be61c;
    }
    fVar7 = (float10)fcos(fVar7);
    dVar8 = floor((double)((float10)_DAT_004be630 /
                          ((float10)0.6931471805599453 *
                          (fVar7 - (float10)_DAT_004be620) * (float10)_DAT_004be628)));
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 0x800;
    iVar3 = iVar2 * 0x6c;
    (&g_runtime_light_entries)[iVar2 * 0x1b] = param_1;
    if (param_2 == 0) {
      *(undefined4 *)(&DAT_0058db88 + iVar3) = 0;
    }
    else if (param_2 == 1) {
      *(undefined4 *)(&DAT_0058db88 + iVar3) = 1;
    }
    fVar1 = _DAT_004be638 / (param_3 * param_3);
    *(uint *)(&DAT_0058db88 + iVar3) = *(uint *)(&DAT_0058db88 + iVar3) | 8;
    (&DAT_0058db94)[iVar2 * 0x1b] = param_3;
    *(float *)(&DAT_0058db90 + iVar3) = fVar1;
    *(float *)(&DAT_0058db8c + iVar3) = (float)dVar8;
    *(undefined4 *)(&DAT_0058dba4 + iVar3) = uVar5;
    *(undefined4 *)(&DAT_0058dba8 + iVar3) = uVar6;
    *(undefined4 **)(&DAT_0058dbac + iVar3) = local_4;
    if (param_2 == 1) {
      if (param_5 != (float *)0x0) {
        (&DAT_0058db98)[iVar2 * 0x1b] = -*param_5;
        (&DAT_0058db9c)[iVar2 * 0x1b] = -param_5[1];
        (&DAT_0058dba0)[iVar2 * 0x1b] = -param_5[2];
        return;
      }
      (&DAT_0058db98)[iVar2 * 0x1b] = -*(float *)(param_1 + 0x30);
      (&DAT_0058db9c)[iVar2 * 0x1b] = -*(float *)(param_1 + 0x34);
      (&DAT_0058dba0)[iVar2 * 0x1b] = -*(float *)(param_1 + 0x38);
      return;
    }
    (&DAT_0058db98)[iVar2 * 0x1b] = 0;
    (&DAT_0058db9c)[iVar2 * 0x1b] = 0;
    (&DAT_0058dba0)[iVar2 * 0x1b] = 0;
  }
  return;
}


