/*
 * Program: i76.exe
 * Function: special_equipment_state_context_helper_00468270
 * Entry: 00468270
 * Signature: uint __cdecl special_equipment_state_context_helper_00468270(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was vehicle_specials_runtime_special_equipment_state_helper_00468270.
   Shorten readability label. */

uint __cdecl special_equipment_state_context_helper_00468270(int param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  float10 fVar11;
  float local_10;
  float local_c;
  float local_8;
  
  uVar10 = DAT_00588dec;
  uVar9 = param_1 * 0x6cd + 0xaab;
  uVar5 = uVar9 / 0x71;
  uVar9 = uVar9 % 0x71;
  iVar8 = (&DAT_0054fa10)[uVar9];
  do {
    if (iVar8 == -1) {
      puVar7 = (undefined *)0x0;
LAB_004682c0:
      if (puVar7 == (undefined *)0x0) {
        uVar1 = (&DAT_0054fa10)[uVar9];
        (&DAT_0054fa10)[uVar9] = DAT_00588dec;
        iVar8 = uVar10 * 0x20;
        *(undefined4 *)(&DAT_0054e12c + iVar8) = uVar1;
        *(int *)(&DAT_0054e110 + iVar8) = param_1;
        fVar2 = *(float *)(param_1 + 0x30);
        fVar3 = *(float *)(param_1 + 0x34);
        fVar4 = *(float *)(param_1 + 0x38);
        local_10 = fVar2;
        local_c = fVar3;
        local_8 = fVar4;
        if ((fVar2 == _DAT_004be250) && (fVar4 == _DAT_004be250)) {
          *(undefined4 *)(&DAT_0054e118 + iVar8) = 0;
          *(undefined4 *)(&DAT_0054e114 + iVar8) = 0;
        }
        else {
          fVar11 = (float10)fpatan((float10)fVar2,(float10)fVar4);
          *(float *)(&DAT_0054e114 + iVar8) = (float)fVar11;
          iVar8 = is_vehicle_or_actor_runtime_world_object(param_1);
          if (iVar8 != 0) {
            iVar8 = get_vehicle_runtime_context(param_1);
            local_8 = *(float *)(iVar8 + 0xe8);
            local_10 = fVar2 * local_8;
            local_c = fVar3 * local_8;
            local_8 = fVar4 * local_8;
          }
          uVar10 = DAT_00588dec;
          fVar11 = (float10)fpatan((float10)local_10,(float10)local_8);
          *(float *)(&DAT_0054e118 + DAT_00588dec * 0x20) = (float)fVar11;
        }
        iVar8 = uVar10 * 0x20;
        puVar6 = (undefined4 *)entity_instance_table_context_helper_004576a0(&local_10,param_1);
        *(undefined4 *)(&DAT_0054e11c + iVar8) = *puVar6;
        *(undefined4 *)(&DAT_0054e120 + iVar8) = puVar6[1];
        *(undefined4 *)(&DAT_0054e124 + iVar8) = puVar6[2];
        *(undefined4 *)(&DAT_0054e128 + iVar8) = puVar6[3];
        uVar5 = DAT_00588dec + 1;
        DAT_00588dec = uVar5;
      }
      return uVar5;
    }
    uVar5 = iVar8 * 0x20;
    if (*(int *)(&DAT_0054e110 + uVar5) == param_1) {
      puVar7 = &DAT_0054e110 + iVar8 * 0x20;
      goto LAB_004682c0;
    }
    iVar8 = *(int *)(&DAT_0054e12c + uVar5);
  } while( true );
}


