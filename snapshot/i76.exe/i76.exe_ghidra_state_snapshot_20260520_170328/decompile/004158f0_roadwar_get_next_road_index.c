/*
 * Program: i76.exe
 * Function: roadwar_get_next_road_index
 * Entry: 004158f0
 * Signature: undefined4 __cdecl roadwar_get_next_road_index(int * param_1, int param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: roadwar get_next_index infinite loop */

undefined4 __cdecl roadwar_get_next_road_index(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  
  iVar8 = 0;
  iVar1 = *(int *)(*param_1 + 0x28) + 0xc + *param_3 * 0x18;
  fVar2 = *(float *)(*(int *)(*param_1 + 0x28) + 0xc + *param_3 * 0x18);
  fVar3 = *(float *)(iVar1 + 4);
  fVar4 = *(float *)(iVar1 + 8);
  do {
    if (param_2 == -1) {
      if (*param_3 == 0) {
        iVar1 = *(int *)(*param_1 + 8);
        if ((iVar1 == 0) || (*(int *)(iVar1 + 0xc) != 0)) {
          return 0;
        }
        *param_1 = iVar1;
        *param_3 = *(int *)(iVar1 + 0x14) + -1;
      }
      else {
        *param_3 = *param_3 + -1;
      }
    }
    else {
      iVar1 = *param_1;
      if (*param_3 == *(int *)(iVar1 + 0x14) + -1) {
        if (*(int *)(iVar1 + 0xc) != 0) {
          return 0;
        }
        *param_1 = *(int *)(iVar1 + 4);
        *param_3 = 0;
      }
      else {
        *param_3 = *param_3 + 1;
      }
    }
    iVar1 = *(int *)(*param_1 + 0x28) + 0xc + *param_3 * 0x18;
    fVar5 = *(float *)(*(int *)(*param_1 + 0x28) + 0xc + *param_3 * 0x18) - fVar2;
    fVar7 = *(float *)(iVar1 + 4) - fVar3;
    fVar6 = *(float *)(iVar1 + 8) - fVar4;
    if ((float)_DAT_004bc820 < fVar6 * fVar6 + fVar7 * fVar7 + fVar5 * fVar5) {
      return 1;
    }
    iVar8 = iVar8 + 1;
    if (10 < iVar8) {
      report_error();
    }
  } while( true );
}


