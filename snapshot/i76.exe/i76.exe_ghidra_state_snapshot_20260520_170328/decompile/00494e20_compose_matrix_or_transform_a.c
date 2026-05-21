/*
 * Program: i76.exe
 * Function: compose_matrix_or_transform_a
 * Entry: 00494e20
 * Signature: float * __cdecl compose_matrix_or_transform_a(float * param_1, float * param_2, float * param_3)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Matrix/affine transform multiply
   helper used by world-object transform composition.
   
   I76 rename v43: compose_transform_matrix_or_basis
   Composes runtime transform matrix/basis. */

float * __cdecl compose_matrix_or_transform_a(float *param_1,float *param_2,float *param_3)

{
  double *pdVar1;
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
  float fVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  float *pfVar22;
  float *pfVar23;
  char cVar24;
  float *pfVar25;
  
  cVar24 = '\x03';
  pfVar22 = param_1;
  do {
    pfVar25 = param_2;
    pfVar23 = pfVar22;
    fVar2 = param_3[1];
    fVar3 = *pfVar25;
    fVar4 = param_3[2];
    fVar5 = *pfVar25;
    fVar6 = param_3[4];
    fVar7 = pfVar25[1];
    fVar8 = param_3[5];
    fVar9 = pfVar25[1];
    fVar10 = param_3[7];
    fVar11 = pfVar25[2];
    fVar12 = param_3[8];
    fVar13 = pfVar25[2];
    *pfVar23 = param_3[6] * pfVar25[2] + param_3[3] * pfVar25[1] + *param_3 * *pfVar25;
    pfVar23[1] = fVar10 * fVar11 + fVar6 * fVar7 + fVar2 * fVar3;
    pfVar23[2] = fVar12 * fVar13 + fVar8 * fVar9 + fVar4 * fVar5;
    cVar24 = cVar24 + -1;
    pfVar22 = pfVar23 + 3;
    param_2 = pfVar25 + 3;
  } while (cVar24 != '\0');
  pdVar1 = (double *)(pfVar25 + 4);
  fVar2 = param_3[1];
  dVar14 = *pdVar1;
  fVar3 = param_3[2];
  dVar15 = *pdVar1;
  fVar4 = param_3[4];
  dVar16 = *(double *)(pfVar25 + 6);
  fVar5 = param_3[5];
  dVar17 = *(double *)(pfVar25 + 6);
  fVar6 = param_3[7];
  dVar18 = *(double *)(pfVar25 + 8);
  fVar7 = param_3[8];
  dVar19 = *(double *)(pfVar25 + 8);
  dVar20 = *(double *)(param_3 + 0xc);
  dVar21 = *(double *)(param_3 + 0xe);
  *(double *)(pfVar23 + 4) =
       (double)(param_3[6] * (float)*(double *)(pfVar25 + 8) +
                param_3[3] * (float)*(double *)(pfVar25 + 6) + *param_3 * (float)*pdVar1 +
               (float)*(double *)(param_3 + 10));
  *(double *)(pfVar23 + 8) =
       (double)(fVar7 * (float)dVar19 + fVar5 * (float)dVar17 + fVar3 * (float)dVar15 +
               (float)dVar21);
  *(double *)(pfVar23 + 6) =
       (double)(fVar6 * (float)dVar18 + fVar4 * (float)dVar16 + fVar2 * (float)dVar14 +
               (float)dVar20);
  return param_1;
}


