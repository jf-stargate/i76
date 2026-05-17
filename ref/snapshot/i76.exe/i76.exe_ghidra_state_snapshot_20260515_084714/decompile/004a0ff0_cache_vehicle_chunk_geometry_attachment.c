/*
 * Program: i76.exe
 * Function: cache_vehicle_chunk_geometry_attachment
 * Entry: 004a0ff0
 * Signature: undefined4 __cdecl cache_vehicle_chunk_geometry_attachment(int param_1, int param_2, int param_3, float * param_4, int * param_5, int * param_6)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=medium-high] Caches or links geometry
   attachment data for vehicle/object chunk geometry. */

undefined4 __cdecl
cache_vehicle_chunk_geometry_attachment
          (int param_1,int param_2,int param_3,float *param_4,int *param_5,int *param_6)

{
  ushort uVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  float *pfVar7;
  int *piVar8;
  float local_80 [16];
  float local_40 [16];
  
  uVar5 = (param_1 * 0x6cd + 0xaabU) % 0x71;
  if (uVar5 < 0x71) {
    for (piVar6 = (int *)(&DAT_005a8118)[uVar5]; piVar6 != (int *)0x0; piVar6 = (int *)piVar6[0x11b]
        ) {
      if (*piVar6 == param_1) goto LAB_004a103d;
    }
  }
  piVar6 = (int *)0x0;
LAB_004a103d:
  if (piVar6 == (int *)0x0) {
    piVar6 = HeapAlloc(DAT_005aaac0,0,0x470);
    *(undefined2 *)(piVar6 + 1) = 0;
    piVar6[0x11a] = 0;
    *piVar6 = param_1;
    piVar8 = piVar6 + 2;
    for (iVar4 = 0x118; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar8 = 0;
      piVar8 = piVar8 + 1;
    }
    if (uVar5 < 0x71) {
      piVar6[0x11b] = (&DAT_005a8118)[uVar5];
      (&DAT_005a8118)[uVar5] = piVar6;
    }
    else {
      piVar6 = (int *)0x0;
    }
    if (piVar6 == (int *)0x0) {
      return 0;
    }
  }
  if (*(ushort *)(piVar6 + 1) < 10) {
    iVar4 = get_root_ancestor_world_object(param_1);
    iVar2 = is_transform_composed_world_object_class(iVar4);
    if ((iVar2 == 0) && (*(int *)(iVar4 + 0x6c) != 8)) {
      uVar1 = *(ushort *)(piVar6 + 1);
    }
    else {
      pfVar3 = (float *)compute_transform_relative_to_ancestor(local_40,iVar4,0);
      pfVar7 = local_80;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar7 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar7 = pfVar7 + 1;
      }
      param_4 = compose_matrix_or_transform_a(local_40,param_4,local_80);
      uVar1 = *(ushort *)(piVar6 + 1);
    }
    pfVar3 = (float *)(piVar6 + (uint)uVar1 * 0x1c + 4);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar3 = *param_4;
      param_4 = param_4 + 1;
      pfVar3 = pfVar3 + 1;
    }
    uVar1 = *(ushort *)(piVar6 + 1);
    piVar6[(uint)uVar1 * 0x1c + 2] = param_2;
    piVar6[(uint)uVar1 * 0x1c + 3] = param_3;
    piVar8 = piVar6 + (uint)*(ushort *)(piVar6 + 1) * 0x1c + 0x14;
    *piVar8 = *param_5;
    piVar8[1] = param_5[1];
    piVar8[2] = param_5[2];
    piVar8[3] = param_5[3];
    piVar8 = piVar6 + (uint)*(ushort *)(piVar6 + 1) * 0x1c + 0x18;
    for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar8 = *param_6;
      param_6 = param_6 + 1;
      piVar8 = piVar8 + 1;
    }
    *(short *)(piVar6 + 1) = (short)piVar6[1] + 1;
    return 1;
  }
  return 0;
}


