/*
 * Program: i76.exe
 * Function: ordnance_collision_context_helper_004a0cc0
 * Entry: 004a0cc0
 * Signature: undefined __cdecl ordnance_collision_context_helper_004a0cc0(int param_1, float param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: ordnance collision context helper
   based on adjacent named subsystem context. */

void __cdecl ordnance_collision_context_helper_004a0cc0(int param_1,float param_2)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  
  fVar2 = *(float *)(param_1 + 0x30);
  fVar3 = *(float *)(param_1 + 0x34);
  fVar4 = *(float *)(param_1 + 0x38);
  dVar1 = (double)(fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2);
  fVar6 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  fVar5 = (float)fVar6;
  *(double *)(param_1 + 0x40) =
       (double)((float)*(double *)(param_1 + 0x40) + fVar2 * fVar5 * param_2);
  *(double *)(param_1 + 0x48) =
       (double)((float)*(double *)(param_1 + 0x48) + fVar3 * fVar5 * param_2);
  *(double *)(param_1 + 0x50) =
       (double)((float)*(double *)(param_1 + 0x50) + fVar4 * fVar5 * param_2);
  return;
}


