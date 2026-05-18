/*
 * Program: i76.exe
 * Function: path_nodes_share_same_position
 * Entry: 00415a30
 * Signature: undefined4 __cdecl path_nodes_share_same_position(int * param_1, int param_2, int * param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Compares two path node records and returns true if they
   reference the same path object and nearly identical vertex position. */

undefined4 __cdecl path_nodes_share_same_position(int *param_1,int param_2,int *param_3,int param_4)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if ((param_1 == param_3) && (param_2 == param_4)) {
    return 1;
  }
  if (*param_1 == *param_3) {
    pfVar1 = (float *)(param_3[10] + 0xc + param_4 * 0x18);
    iVar2 = param_1[10] + 0xc + param_2 * 0x18;
    fVar3 = *(float *)(param_1[10] + 0xc + param_2 * 0x18) - *pfVar1;
    fVar5 = *(float *)(iVar2 + 4) - pfVar1[1];
    fVar4 = *(float *)(iVar2 + 8) - pfVar1[2];
    if (fVar4 * fVar4 + fVar5 * fVar5 + fVar3 * fVar3 < (float)_DAT_004bc820) {
      return 1;
    }
  }
  return 0;
}


