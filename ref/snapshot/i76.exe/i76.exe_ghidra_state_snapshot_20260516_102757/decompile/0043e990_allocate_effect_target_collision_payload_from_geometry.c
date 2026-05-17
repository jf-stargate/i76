/*
 * Program: i76.exe
 * Function: allocate_effect_target_collision_payload_from_geometry
 * Entry: 0043e990
 * Signature: undefined4 * __cdecl allocate_effect_target_collision_payload_from_geometry(undefined4 * param_1, float * param_2)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Allocates and fills an effect-target
   collision payload from geometry/section records and transformed vertex data. */

undefined4 * __cdecl
allocate_effect_target_collision_payload_from_geometry(undefined4 *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  int *piVar16;
  int iVar17;
  
  iVar13 = param_1[0x17];
  puVar15 = HeapAlloc(DAT_00608be8,0,(*(int *)(iVar13 + 4) + 1) * 0xc);
  if (puVar15 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *puVar15 = *(undefined4 *)(iVar13 + 4);
  puVar15[2] = 0;
  puVar15[1] = puVar15 + 3;
  transform_vec3_array_by_matrix
            ((float *)(puVar15 + 3),*(float **)(iVar13 + 0xc),*(int *)(iVar13 + 4),param_2);
  for (iVar13 = *(int *)(iVar13 + 0x14); iVar13 != 0; iVar13 = *(int *)(iVar13 + 0x30)) {
    iVar14 = *(int *)(iVar13 + 4);
    if ((2 < iVar14) &&
       (piVar16 = HeapAlloc(DAT_00608be8,0,iVar14 * 4 + 0x1c), piVar16 != (int *)0x0)) {
      iVar17 = 0;
      *piVar16 = iVar14;
      piVar16[5] = (int)(piVar16 + 7);
      if (0 < iVar14) {
        param_1 = (undefined4 *)(iVar13 + 0x40);
        do {
          iVar17 = iVar17 + 1;
          *(undefined4 *)(piVar16[5] + -4 + iVar17 * 4) = *param_1;
          param_1 = param_1 + 4;
        } while (iVar17 < iVar14);
      }
      fVar1 = param_2[4];
      fVar2 = param_2[7];
      fVar3 = param_2[8];
      fVar4 = param_2[5];
      fVar5 = *(float *)(iVar13 + 0x10);
      fVar6 = param_2[1];
      fVar7 = *(float *)(iVar13 + 0x14);
      fVar8 = *(float *)(iVar13 + 0x14);
      fVar9 = param_2[2];
      fVar10 = *(float *)(iVar13 + 0xc);
      fVar11 = *(float *)(iVar13 + 0x10);
      fVar12 = *(float *)(iVar13 + 0xc);
      piVar16[1] = (int)-(*param_2 * *(float *)(iVar13 + 0xc) +
                         param_2[6] * *(float *)(iVar13 + 0x14) +
                         param_2[3] * *(float *)(iVar13 + 0x10));
      piVar16[2] = (int)-(fVar6 * fVar10 + fVar2 * fVar7 + fVar1 * fVar5);
      piVar16[3] = (int)-(fVar9 * fVar12 + fVar4 * fVar11 + fVar3 * fVar8);
      iVar14 = *(int *)piVar16[5];
      iVar17 = puVar15[1];
      piVar16[4] = (int)-(*(float *)(iVar17 + iVar14 * 0xc) * (float)piVar16[1] +
                         (float)piVar16[3] * *(float *)(iVar17 + 8 + iVar14 * 0xc) +
                         (float)piVar16[2] * *(float *)(iVar17 + 4 + iVar14 * 0xc));
      piVar16[6] = puVar15[2];
      puVar15[2] = piVar16;
    }
  }
  return puVar15;
}


