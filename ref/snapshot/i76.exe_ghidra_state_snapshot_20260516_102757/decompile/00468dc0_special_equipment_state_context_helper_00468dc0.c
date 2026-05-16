/*
 * Program: i76.exe
 * Function: special_equipment_state_context_helper_00468dc0
 * Entry: 00468dc0
 * Signature: float10 __cdecl special_equipment_state_context_helper_00468dc0(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was vehicle_specials_runtime_special_equipment_state_helper_00468dc0.
   Shorten readability label. */

float10 __cdecl special_equipment_state_context_helper_00468dc0(uint param_1,uint param_2)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined *puVar14;
  uint uVar15;
  uint uVar16;
  undefined *puVar17;
  float10 fVar18;
  float10 fVar19;
  float10 fVar20;
  float10 fVar21;
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar8 = DAT_00588dec;
  uVar16 = param_2;
  if (param_2 < param_1) {
    uVar16 = param_1;
    param_1 = param_2;
  }
  uVar13 = ((uVar16 ^ param_1) * 0x6cd + 0xaab) % 0x9c7;
  iVar12 = (&DAT_0054b9f0)[uVar13];
  while (iVar12 != -1) {
    iVar11 = iVar12 * 0x34;
    if ((*(uint *)(&DAT_0054fbd8 + iVar11) == param_1) &&
       (*(uint *)(&DAT_0054fbdc + iVar11) == uVar16)) {
      puVar14 = &DAT_0054fbd8 + iVar12 * 0x34;
      goto LAB_00468e32;
    }
    iVar12 = *(int *)(&DAT_0054fc08 + iVar11);
  }
  puVar14 = (undefined *)0x0;
LAB_00468e32:
  if (puVar14 == (undefined *)0x0) {
    uVar15 = (param_1 * 0x6cd + 0xaab) % 0x71;
    for (iVar12 = (&DAT_0054fa10)[uVar15]; iVar12 != -1;
        iVar12 = *(int *)(&DAT_0054e12c + iVar12 * 0x20)) {
      if (*(uint *)(&DAT_0054e110 + iVar12 * 0x20) == param_1) {
        puVar17 = &DAT_0054e110 + iVar12 * 0x20;
        goto LAB_00468e87;
      }
    }
    puVar17 = (undefined *)0x0;
LAB_00468e87:
    if (puVar17 == (undefined *)0x0) {
      uVar1 = (&DAT_0054fa10)[uVar15];
      (&DAT_0054fa10)[uVar15] = DAT_00588dec;
      *(undefined4 *)(&DAT_0054e12c + iVar8 * 0x20) = uVar1;
      *(uint *)(&DAT_0054e110 + iVar8 * 0x20) = param_1;
      pfVar7 = (float *)copy_object_local_translation_vec3(&local_10,param_1 + 0x18);
      iVar8 = DAT_00588dec;
      local_1c = *pfVar7;
      fVar2 = pfVar7[1];
      local_14 = pfVar7[2];
      if ((local_1c == _DAT_004be250) && (local_14 == _DAT_004be250)) {
        iVar12 = DAT_00588dec * 0x20;
        *(undefined4 *)(&DAT_0054e118 + iVar12) = 0;
        *(undefined4 *)(&DAT_0054e114 + iVar12) = 0;
      }
      else {
        fVar18 = (float10)fpatan((float10)local_1c,(float10)local_14);
        *(float *)(&DAT_0054e114 + DAT_00588dec * 0x20) = (float)fVar18;
        iVar8 = is_vehicle_or_actor_runtime_world_object(param_1);
        if (iVar8 != 0) {
          local_10 = local_1c;
          local_c = fVar2;
          local_8 = local_14;
          iVar8 = get_vehicle_runtime_context(param_1);
          local_14 = *(float *)(iVar8 + 0xe8);
          local_1c = local_1c * local_14;
          local_c = local_c * local_14;
          local_14 = local_8 * local_14;
          local_10 = local_1c;
          local_8 = local_14;
        }
        iVar8 = DAT_00588dec;
        fVar18 = (float10)fpatan((float10)local_1c,(float10)local_14);
        *(float *)(&DAT_0054e118 + DAT_00588dec * 0x20) = (float)fVar18;
      }
      iVar8 = iVar8 * 0x20;
      puVar9 = (undefined4 *)entity_instance_table_context_helper_004576a0(&local_10,param_1);
      puVar17 = &DAT_0054e110 + iVar8;
      *(undefined4 *)(&DAT_0054e11c + iVar8) = *puVar9;
      *(undefined4 *)(&DAT_0054e120 + iVar8) = puVar9[1];
      *(undefined4 *)(&DAT_0054e124 + iVar8) = puVar9[2];
      *(undefined4 *)(&DAT_0054e128 + iVar8) = puVar9[3];
      DAT_00588dec = DAT_00588dec + 1;
    }
    for (iVar8 = (&DAT_0054fa10)[(uVar16 * 0x6cd + 0xaab) % 0x71]; iVar8 != -1;
        iVar8 = *(int *)(&DAT_0054e12c + iVar8 * 0x20)) {
      if (*(uint *)(&DAT_0054e110 + iVar8 * 0x20) == uVar16) {
        puVar10 = &DAT_0054e110 + iVar8 * 0x20;
        goto LAB_0046903b;
      }
    }
    puVar10 = (undefined *)0x0;
LAB_0046903b:
    if (puVar10 == (undefined *)0x0) {
      puVar10 = special_equipment_state_context_helper_00468c40(uVar16);
    }
    iVar8 = DAT_00588de8 * 0x34;
    *(undefined4 *)(&DAT_0054fc08 + iVar8) = (&DAT_0054b9f0)[uVar13];
    *(uint *)(&DAT_0054fbd8 + iVar8) = param_1;
    *(uint *)(&DAT_0054fbdc + iVar8) = uVar16;
    (&DAT_0054b9f0)[uVar13] = DAT_00588de8;
    fVar2 = *(float *)(puVar17 + 0xc);
    puVar14 = &DAT_0054fbd8 + iVar8;
    fVar3 = *(float *)(puVar17 + 0x14);
    fVar4 = *(float *)(puVar10 + 0xc);
    fVar6 = fVar2 - fVar4;
    fVar5 = *(float *)(puVar10 + 0x14);
    fVar18 = (float10)*(float *)(puVar17 + 0x10) - (float10)*(float *)(puVar10 + 0x10);
    fVar19 = (float10)fVar3 - (float10)fVar5;
    *(float *)(&DAT_0054fbfc + iVar8) = fVar6;
    *(float *)(&DAT_0054fc00 + iVar8) = (float)fVar18;
    *(float *)(&DAT_0054fc04 + iVar8) = (float)fVar19;
    *(float *)(&DAT_0054fbf0 + iVar8) = -fVar6;
    *(float *)(&DAT_0054fbf4 + iVar8) = (float)-fVar18;
    *(float *)(&DAT_0054fbf8 + iVar8) = (float)-fVar19;
    if ((fVar6 == _DAT_004be250) && (fVar19 == (float10)_DAT_004be250)) {
      *(undefined4 *)(&DAT_0054fbec + iVar8) = 0;
    }
    else {
      fVar21 = (float10)fpatan((float10)fVar6,fVar19);
      *(float *)(&DAT_0054fbec + iVar8) = (float)fVar21;
    }
    fVar20 = (float10)fVar4 - (float10)fVar2;
    fVar5 = fVar5 - fVar3;
    fVar21 = (float10)_DAT_004be250;
    *(float *)(&DAT_0054fbe0 + iVar8) = (float)SQRT(fVar19 * fVar19 + (float10)(fVar6 * fVar6));
    *(float *)(&DAT_0054fbe4 + iVar8) =
         (float)SQRT(fVar18 * fVar18 + fVar19 * fVar19 + (float10)(fVar6 * fVar6));
    if ((fVar20 == fVar21) && (fVar5 == _DAT_004be250)) {
      *(undefined4 *)(&DAT_0054fbe8 + iVar8) = 0;
      DAT_00588de8 = DAT_00588de8 + 1;
      return (float10)*(float *)(&DAT_0054fbe4 + iVar8);
    }
    fVar18 = (float10)fpatan(fVar20,(float10)fVar5);
    DAT_00588de8 = DAT_00588de8 + 1;
    *(float *)(&DAT_0054fbe8 + iVar8) = (float)fVar18;
  }
  return (float10)*(float *)(puVar14 + 0xc);
}


