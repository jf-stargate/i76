/*
 * Program: i76.exe
 * Function: get_cached_world_object_aim_position
 * Entry: 00468440
 * Signature: undefined __cdecl get_cached_world_object_aim_position(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Returns a cached aiming/position
   vector for a world object used by weapon targeting. */

void __cdecl get_cached_world_object_aim_position(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  float10 fVar10;
  float local_10;
  float local_c;
  float local_8;
  
  iVar9 = DAT_00588dec;
  uVar8 = (param_2 * 0x6cd + 0xaabU) % 0x71;
  iVar7 = (&DAT_0054fa10)[uVar8];
  do {
    if (iVar7 == -1) {
      puVar6 = (undefined *)0x0;
LAB_00468490:
      if (puVar6 == (undefined *)0x0) {
        uVar1 = (&DAT_0054fa10)[uVar8];
        (&DAT_0054fa10)[uVar8] = DAT_00588dec;
        iVar7 = iVar9 * 0x20;
        *(undefined4 *)(&DAT_0054e12c + iVar7) = uVar1;
        *(int *)(&DAT_0054e110 + iVar7) = param_2;
        fVar2 = *(float *)(param_2 + 0x30);
        fVar3 = *(float *)(param_2 + 0x34);
        fVar4 = *(float *)(param_2 + 0x38);
        local_10 = fVar2;
        local_c = fVar3;
        local_8 = fVar4;
        if ((fVar2 == _DAT_004be250) && (fVar4 == _DAT_004be250)) {
          *(undefined4 *)(&DAT_0054e118 + iVar7) = 0;
          *(undefined4 *)(&DAT_0054e114 + iVar7) = 0;
        }
        else {
          fVar10 = (float10)fpatan((float10)fVar2,(float10)fVar4);
          *(float *)(&DAT_0054e114 + iVar7) = (float)fVar10;
          iVar7 = is_vehicle_or_actor_runtime_world_object(param_2);
          if (iVar7 != 0) {
            iVar7 = get_vehicle_runtime_context(param_2);
            local_8 = *(float *)(iVar7 + 0xe8);
            local_10 = fVar2 * local_8;
            local_c = fVar3 * local_8;
            local_8 = fVar4 * local_8;
          }
          iVar9 = DAT_00588dec;
          fVar10 = (float10)fpatan((float10)local_10,(float10)local_8);
          *(float *)(&DAT_0054e118 + DAT_00588dec * 0x20) = (float)fVar10;
        }
        iVar9 = iVar9 * 0x20;
        puVar5 = (undefined4 *)entity_instance_table_context_helper_004576a0(&local_10,param_2);
        *(undefined4 *)(&DAT_0054e11c + iVar9) = *puVar5;
        *(undefined4 *)(&DAT_0054e120 + iVar9) = puVar5[1];
        *(undefined4 *)(&DAT_0054e124 + iVar9) = puVar5[2];
        *(undefined4 *)(&DAT_0054e128 + iVar9) = puVar5[3];
        DAT_00588dec = DAT_00588dec + 1;
        puVar6 = &DAT_0054e110 + iVar9;
      }
      *param_1 = *(undefined4 *)(puVar6 + 0xc);
      param_1[1] = *(undefined4 *)(puVar6 + 0x10);
      param_1[2] = *(undefined4 *)(puVar6 + 0x14);
      return;
    }
    if (*(int *)(&DAT_0054e110 + iVar7 * 0x20) == param_2) {
      puVar6 = &DAT_0054e110 + iVar7 * 0x20;
      goto LAB_00468490;
    }
    iVar7 = *(int *)(&DAT_0054e12c + iVar7 * 0x20);
  } while( true );
}


