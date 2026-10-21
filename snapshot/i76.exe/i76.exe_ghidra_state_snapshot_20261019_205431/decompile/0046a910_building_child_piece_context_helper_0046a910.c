/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046a910
 * Entry: 0046a910
 * Signature: undefined4 __cdecl building_child_piece_context_helper_0046a910(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046a910. Remove
   duplicated building wording. */

undefined4 __cdecl building_child_piece_context_helper_0046a910(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iVar6 = 0;
  piVar5 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar6 & 0x1f)) != 0) {
      iVar2 = *piVar5;
      iVar4 = iVar2;
      if ((*(ushort *)(param_2 + 4) & 8) != 0) {
        iVar4 = ftol();
      }
      if (*piVar1 < iVar4) {
        *(int *)(param_2 + 8 + iVar6 * 4) = iVar4 - *piVar1;
        *piVar1 = 0;
        piVar1[3] = 0x40a00000;
        piVar1[5] = 0x3f000000;
        return 1;
      }
      *piVar1 = *piVar1 - iVar2;
      *piVar5 = 0;
    }
    iVar6 = iVar6 + 1;
    piVar5 = piVar5 + 1;
    if (3 < iVar6) {
      fVar3 = _DAT_004be310 -
              (_DAT_004be310 - (float)piVar1[4]) * ((float)*piVar1 / (float)piVar1[1]);
      piVar1[5] = (int)(((float)piVar1[6] - _DAT_004be314) * ((float)*piVar1 / (float)piVar1[1]) -
                       _DAT_004be30c);
      piVar1[3] = (int)fVar3;
      return 0;
    }
  } while( true );
}


