/*
 * Program: i76.exe
 * Function: parse_vcfc_vdf_vtf_wdf_resource_refs
 * Entry: 004ad950
 * Signature: undefined4 __cdecl parse_vcfc_vdf_vtf_wdf_resource_refs(int param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] VCFC-adjacent resolver: parses VDF at
   +0x18, VTFC at +0x25, WDF weapon slots at +0x3e/+0x4b/+0x58, and component CDF selections at
   +0x32/+0x36/+0x3a.
   
   I76 rename v43: parse_vcfc_vdf_vtf_wdf_resource_refs
   VCFC helper parsing VDF/VTF/WDF resource refs. */

undefined4 __cdecl parse_vcfc_vdf_vtf_wdf_resource_refs(int param_1,byte *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar5;
  undefined3 extraout_var_01;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  int local_b0 [15];
  undefined4 local_74;
  int local_70;
  undefined4 local_3c;
  int local_38;
  
  bVar4 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)(param_1 + 0x18),&vdfc_reference_descriptor_table,0xc,param_2);
  if (CONCAT31(extraout_var,bVar4) == 0) {
    return 0;
  }
  bVar4 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)(param_1 + 0x25),&vtfc_descriptor_table,2,param_2);
  if (CONCAT31(extraout_var_00,bVar4) == 0) {
    return 0;
  }
  iVar5 = load_vehicle_weapon_wdf_and_attach_mount_pair((byte *)(param_1 + 0x3e),(int *)param_2,0);
  if (iVar5 == 0) {
    return 0;
  }
  iVar5 = load_vehicle_weapon_wdf_and_attach_mount_pair((byte *)(param_1 + 0x4b),(int *)param_2,2);
  if (iVar5 == 0) {
    return 0;
  }
  iVar5 = load_vehicle_weapon_wdf_and_attach_mount_pair((byte *)(param_1 + 0x58),(int *)param_2,4);
  if (iVar5 == 0) {
    return 0;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x36);
  uVar2 = *(undefined4 *)(param_1 + 0x3a);
  uVar3 = *(undefined4 *)(param_1 + 0x32);
  piVar8 = local_b0;
  for (iVar5 = 0x2c; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  local_b0[0] = *(int *)(*(int *)param_2 + 0x70);
  local_b0[1] = uVar3;
  local_74 = uVar2;
  local_3c = uVar1;
  bVar4 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)s_compnent_cdf_004ffcd0,&DAT_004ff380,0xd,(byte *)local_b0);
  if (CONCAT31(extraout_var_01,bVar4) != 0) {
    if (local_b0[2] == 0) {
      report_error();
    }
    if (local_70 == 0) {
      report_error();
    }
    if (local_38 == 0) {
      report_error();
    }
    puVar7 = (undefined4 *)(param_1 + 0x65);
    iVar5 = *(int *)(*(int *)param_2 + 0x70);
    *(undefined4 *)(iVar5 + 0x138) = *puVar7;
    *(undefined4 *)(iVar5 + 0x13c) = *(undefined4 *)(param_1 + 0x69);
    *(undefined4 *)(iVar5 + 0x140) = *(undefined4 *)(param_1 + 0x6d);
    *(undefined4 *)(iVar5 + 0x144) = *(undefined4 *)(param_1 + 0x71);
    *(undefined4 *)(iVar5 + 0x158) = *puVar7;
    *(undefined4 *)(iVar5 + 0x15c) = *(undefined4 *)(param_1 + 0x69);
    *(undefined4 *)(iVar5 + 0x160) = *(undefined4 *)(param_1 + 0x6d);
    *(undefined4 *)(iVar5 + 0x164) = *(undefined4 *)(param_1 + 0x71);
    puVar9 = (undefined4 *)(iVar5 + 0x178);
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar7 = (undefined4 *)(param_1 + 0x75);
    *(undefined4 *)(iVar5 + 0x188) = 100;
    *(undefined4 *)(iVar5 + 0x148) = *puVar7;
    *(undefined4 *)(iVar5 + 0x14c) = *(undefined4 *)(param_1 + 0x79);
    *(undefined4 *)(iVar5 + 0x150) = *(undefined4 *)(param_1 + 0x7d);
    *(undefined4 *)(iVar5 + 0x154) = *(undefined4 *)(param_1 + 0x81);
    *(undefined4 *)(iVar5 + 0x168) = *puVar7;
    *(undefined4 *)(iVar5 + 0x16c) = *(undefined4 *)(param_1 + 0x79);
    *(undefined4 *)(iVar5 + 0x170) = *(undefined4 *)(param_1 + 0x7d);
    *(undefined4 *)(iVar5 + 0x174) = *(undefined4 *)(param_1 + 0x81);
    puVar9 = (undefined4 *)(iVar5 + 0x18c);
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
    *(undefined4 *)(iVar5 + 0x19c) = 100;
    return 1;
  }
  return 0;
}


