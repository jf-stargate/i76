/*
 * Program: i76.exe
 * Function: ordnance_damage_effect_context_helper_004a0eb0
 * Entry: 004a0eb0
 * Signature: undefined __cdecl ordnance_damage_effect_context_helper_004a0eb0(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: ordnance damage effect context helper
   based on adjacent named subsystem context. */

void __cdecl ordnance_damage_effect_context_helper_004a0eb0(float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [16];
  
  fVar4 = param_1;
  fVar1 = (float)*(double *)((int)param_1 + 0x40);
  puVar7 = (undefined4 *)((int)param_1 + 0x18);
  local_48 = (float)*(double *)((int)param_1 + 0x48);
  fVar2 = (float)*(double *)((int)param_1 + 0x50);
  local_4c = fVar1;
  local_44 = fVar2;
  probe_effect_target_surface_height_at_position
            ((double)CONCAT44(local_48,fVar1),fVar2,&param_1,&local_4c);
  fVar3 = param_1 - _DAT_004bea78;
  puVar5 = (undefined4 *)
           zone_satellite_map_context_helper_00494710
                     (&local_4c,(float *)((int)fVar4 + 0x30),local_40);
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  *(double *)((int)fVar4 + 0x40) = (double)fVar1;
  *(double *)((int)fVar4 + 0x48) = (double)fVar3;
  *(double *)((int)fVar4 + 0x50) = (double)fVar2;
  return;
}


