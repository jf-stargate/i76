/*
 * Program: i76.exe
 * Function: parse_gpof_equipment_position_offset_chunk
 * Entry: 004af3d0
 * Signature: undefined4 __cdecl parse_gpof_equipment_position_offset_chunk(int param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] GPOF callback for
   equipment/gadget position or offset records. */

undefined4 __cdecl parse_gpof_equipment_position_offset_chunk(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  
  iVar2 = 0;
  iVar3 = *(int *)(*param_2 + 4) + 0x378;
  iVar1 = *(int *)(*(int *)(*param_2 + 4) + 0xa5c);
  if (0 < iVar1) {
    do {
      if (*(int *)(iVar3 + 0xb0) == param_2[4]) goto LAB_004af40a;
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0xfc;
    } while (iVar2 < iVar1);
  }
  iVar3 = 0;
LAB_004af40a:
  if (iVar3 != 0) {
    if (param_2[10] < 100) {
      uVar4 = *(undefined4 *)(iVar3 + 0xb8);
    }
    else {
      uVar4 = 3;
    }
    switch(uVar4) {
    case 1:
      param_2[0x54] = *(int *)(param_1 + 8);
      param_2[0x55] = *(int *)(param_1 + 0xc);
      param_2[0x56] = *(int *)(param_1 + 0x10);
      param_2[0x57] = *(int *)(param_1 + 0x14);
      param_2[0x58] = *(int *)(param_1 + 0x18);
      param_2[0x59] = *(int *)(param_1 + 0x1c);
      param_2[0x5a] = *(int *)(param_1 + 0x20);
      param_2[0x5b] = *(int *)(param_1 + 0x24);
      param_2[0x5c] = *(int *)(param_1 + 0x28);
      *(double *)(param_2 + 0x5e) = (double)*(float *)(param_1 + 0x2c);
      *(double *)(param_2 + 0x60) = (double)*(float *)(param_1 + 0x30);
      *(double *)(param_2 + 0x62) = (double)*(float *)(param_1 + 0x34);
      return 1;
    case 2:
      param_2[0x54] = *(int *)(param_1 + 0x38);
      param_2[0x55] = *(int *)(param_1 + 0x3c);
      param_2[0x56] = *(int *)(param_1 + 0x40);
      param_2[0x57] = *(int *)(param_1 + 0x44);
      param_2[0x58] = *(int *)(param_1 + 0x48);
      param_2[0x59] = *(int *)(param_1 + 0x4c);
      param_2[0x5a] = *(int *)(param_1 + 0x50);
      param_2[0x5b] = *(int *)(param_1 + 0x54);
      param_2[0x5c] = *(int *)(param_1 + 0x58);
      *(double *)(param_2 + 0x5e) = (double)*(float *)(param_1 + 0x5c);
      *(double *)(param_2 + 0x60) = (double)*(float *)(param_1 + 0x60);
      *(double *)(param_2 + 0x62) = (double)*(float *)(param_1 + 100);
      return 1;
    case 3:
      param_2[0x54] = *(int *)(param_1 + 0x68);
      param_2[0x55] = *(int *)(param_1 + 0x6c);
      param_2[0x56] = *(int *)(param_1 + 0x70);
      param_2[0x57] = *(int *)(param_1 + 0x74);
      param_2[0x58] = *(int *)(param_1 + 0x78);
      param_2[0x59] = *(int *)(param_1 + 0x7c);
      param_2[0x5a] = *(int *)(param_1 + 0x80);
      param_2[0x5b] = *(int *)(param_1 + 0x84);
      param_2[0x5c] = *(int *)(param_1 + 0x88);
      *(double *)(param_2 + 0x5e) = (double)*(float *)(param_1 + 0x8c);
      *(double *)(param_2 + 0x60) = (double)*(float *)(param_1 + 0x90);
      *(double *)(param_2 + 0x62) = (double)*(float *)(param_1 + 0x94);
      return 1;
    case 4:
      piVar5 = &DAT_004faed8;
      piVar6 = param_2 + 0x54;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar6 = *piVar5;
        piVar5 = piVar5 + 1;
        piVar6 = piVar6 + 1;
      }
      return 1;
    case 5:
      param_2[0x54] = *(int *)(param_1 + 0x98);
      param_2[0x55] = *(int *)(param_1 + 0x9c);
      param_2[0x56] = *(int *)(param_1 + 0xa0);
      param_2[0x57] = *(int *)(param_1 + 0xa4);
      param_2[0x58] = *(int *)(param_1 + 0xa8);
      param_2[0x59] = *(int *)(param_1 + 0xac);
      param_2[0x5a] = *(int *)(param_1 + 0xb0);
      param_2[0x5b] = *(int *)(param_1 + 0xb4);
      param_2[0x5c] = *(int *)(param_1 + 0xb8);
      *(double *)(param_2 + 0x5e) = (double)*(float *)(param_1 + 0xbc);
      *(double *)(param_2 + 0x60) = (double)*(float *)(param_1 + 0xc0);
      *(double *)(param_2 + 0x62) = (double)*(float *)(param_1 + 0xc4);
      return 1;
    }
  }
  return 0;
}


