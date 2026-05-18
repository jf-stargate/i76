/*
 * Program: i76.exe
 * Function: load_vehicle_weapon_wdf_and_attach_mount_pair
 * Entry: 004ae5e0
 * Signature: undefined4 __cdecl load_vehicle_weapon_wdf_and_attach_mount_pair(byte * param_1, int * param_2, int param_3)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] Loads a WDF weapon/mount resource and
   attaches the paired weapon objects to the vehicle runtime. */

undefined4 __cdecl
load_vehicle_weapon_wdf_and_attach_mount_pair(byte *param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  undefined3 extraout_var;
  int iVar5;
  int **ppiVar6;
  char local_254 [4];
  char local_250 [16];
  int *local_240 [2];
  char local_238 [8];
  int local_230;
  int local_22c;
  char local_200 [256];
  char local_100 [256];
  
  iVar2 = param_2[1];
  iVar3 = *(int *)(*param_2 + 0x70);
  iVar1 = param_3 + 1;
  ppiVar6 = local_240;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *ppiVar6 = (int *)0x0;
    ppiVar6 = ppiVar6 + 1;
  }
  local_240[0] = param_2;
  _splitpath((char *)param_1,local_254,local_100,local_250,local_200);
  strncpy(local_238,local_250,8);
  bVar4 = parse_bwd2_resource_with_descriptor_table(param_1,&DAT_004ff210,3,(byte *)local_240);
  if (CONCAT31(extraout_var,bVar4) != 0) {
    if (local_230 != 0) {
      iVar5 = iVar2 + 0x16c + param_3 * 0x38;
      *(undefined4 *)(local_230 + 0x18) = *(undefined4 *)(iVar2 + 0x16c + param_3 * 0x38);
      *(undefined4 *)(local_230 + 0x1c) = *(undefined4 *)(iVar5 + 4);
      *(undefined4 *)(local_230 + 0x20) = *(undefined4 *)(iVar5 + 8);
      *(undefined4 *)(local_230 + 0x24) = *(undefined4 *)(iVar5 + 0xc);
      *(undefined4 *)(local_230 + 0x28) = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(local_230 + 0x2c) = *(undefined4 *)(iVar5 + 0x14);
      *(undefined4 *)(local_230 + 0x30) = *(undefined4 *)(iVar5 + 0x18);
      *(undefined4 *)(local_230 + 0x34) = *(undefined4 *)(iVar5 + 0x1c);
      *(undefined4 *)(local_230 + 0x38) = *(undefined4 *)(iVar5 + 0x20);
      *(double *)(local_230 + 0x40) = (double)*(float *)(iVar5 + 0x24);
      *(double *)(local_230 + 0x48) = (double)*(float *)(iVar5 + 0x28);
      *(double *)(local_230 + 0x50) = (double)*(float *)(iVar5 + 0x2c);
    }
    if (local_22c != 0) {
      iVar5 = iVar2 + 0x16c + iVar1 * 0x38;
      *(undefined4 *)(local_22c + 0x18) = *(undefined4 *)(iVar2 + 0x16c + iVar1 * 0x38);
      *(undefined4 *)(local_22c + 0x1c) = *(undefined4 *)(iVar5 + 4);
      *(undefined4 *)(local_22c + 0x20) = *(undefined4 *)(iVar5 + 8);
      *(undefined4 *)(local_22c + 0x24) = *(undefined4 *)(iVar5 + 0xc);
      *(undefined4 *)(local_22c + 0x28) = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(local_22c + 0x2c) = *(undefined4 *)(iVar5 + 0x14);
      *(undefined4 *)(local_22c + 0x30) = *(undefined4 *)(iVar5 + 0x18);
      *(undefined4 *)(local_22c + 0x34) = *(undefined4 *)(iVar5 + 0x1c);
      *(undefined4 *)(local_22c + 0x38) = *(undefined4 *)(iVar5 + 0x20);
      *(double *)(local_22c + 0x40) = (double)*(float *)(iVar5 + 0x24);
      *(double *)(local_22c + 0x48) = (double)*(float *)(iVar5 + 0x28);
      *(double *)(local_22c + 0x50) = (double)*(float *)(iVar5 + 0x2c);
    }
    if (iVar3 != 0) {
      *(int *)(iVar3 + 0x3a8 + param_3 * 4) = local_230;
      *(int *)(iVar3 + 0x3a8 + iVar1 * 4) = local_22c;
    }
    return 1;
  }
  return 0;
}


