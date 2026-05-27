/*
 * Program: i76.exe
 * Function: software_raster_queue_context_helper_00472c10
 * Entry: 00472c10
 * Signature: int __cdecl software_raster_queue_context_helper_00472c10(int param_1, float * param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: software raster queue context helper
   based on adjacent named subsystem context. */

int __cdecl software_raster_queue_context_helper_00472c10(int param_1,float *param_2,float param_3)

{
  float fVar1;
  uint uVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  
  fVar1 = *(float *)(param_1 + 0xf8) * param_2[2] + *(float *)(param_1 + 0xfc);
  uVar2 = (uint)(fVar1 - param_3) >> 0x1f | (uint)(fVar1 + param_3) >> 0x1e & 2;
  if (uVar2 == 3) {
    return 1;
  }
  fVar1 = *(float *)(param_1 + 0xe8) * param_2[2] + *(float *)(param_1 + 0xec);
  uVar5 = (uint)(fVar1 - param_3) >> 0x1f | (uint)(fVar1 + param_3) >> 0x1e & 2;
  if (uVar5 == 3) {
    return 1;
  }
  uVar2 = uVar2 | uVar5;
  iVar4 = 0;
  pfVar3 = (float *)(param_1 + 0xa8);
  do {
    fVar1 = pfVar3[-1] * param_2[1] + param_2[2] * *pfVar3 + pfVar3[-2] * *param_2;
    uVar5 = (uint)(fVar1 - param_3 * _DAT_004be5f0) >> 0x1f |
            (uint)(fVar1 + param_3 * _DAT_004be5f0) >> 0x1e & 2;
    if (uVar5 == 3) {
      return 1;
    }
    uVar2 = uVar2 | uVar5;
    iVar4 = iVar4 + 1;
    pfVar3 = pfVar3 + 4;
  } while (iVar4 < 4);
  return -uVar2;
}


