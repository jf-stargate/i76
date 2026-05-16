/*
 * Program: i76.exe
 * Function: ordnance_target_selection_context_helper_004a8930
 * Entry: 004a8930
 * Signature: float10 __cdecl ordnance_target_selection_context_helper_004a8930(int param_1, float param_2, int param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: ordnance target selection context
   helper based on adjacent named subsystem context. */

float10 __cdecl
ordnance_target_selection_context_helper_004a8930
          (int param_1,float param_2,int param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float10 fVar12;
  float local_490;
  float local_48c;
  float local_488;
  float local_484;
  float local_480;
  float local_47c;
  float local_478;
  float local_474;
  float local_470;
  float local_46c;
  float local_468;
  float local_464;
  float local_460;
  float local_45c;
  float local_458;
  float local_454;
  float local_450;
  float local_44c;
  float local_448;
  float local_444 [6];
  float local_42c;
  float local_428;
  float local_424;
  double local_41c;
  double local_414;
  double local_40c;
  float local_404;
  float local_400;
  float local_3fc;
  float local_3f8;
  float local_3f4;
  float local_3f0;
  undefined4 local_3ec;
  undefined4 local_3e8;
  undefined4 local_3e4;
  undefined4 local_3e0;
  undefined4 local_3dc;
  float local_3d8 [3];
  float local_3cc [3];
  float local_3c0 [240];
  
  pfVar8 = local_3c0 + 1;
  iVar10 = 0x78;
  fVar1 = _DAT_004beb80;
  do {
    pfVar8[-1] = fVar1;
    *pfVar8 = 0.0;
    pfVar8 = pfVar8 + 2;
    iVar10 = iVar10 + -1;
    fVar1 = fVar1 - _DAT_004bebac;
  } while (iVar10 != 0);
  pfVar8 = (float *)compute_transform_relative_to_ancestor(local_444,param_3,0);
  pfVar9 = local_444;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar9 = *pfVar8;
    pfVar8 = pfVar8 + 1;
    pfVar9 = pfVar9 + 1;
  }
  local_464 = (float)local_41c;
  local_460 = (float)local_414;
  local_45c = (float)local_40c;
  pfVar8 = (float *)get_world_object_position_vector(&local_458,param_2);
  fVar1 = *pfVar8;
  fVar2 = pfVar8[1];
  fVar3 = pfVar8[2];
  local_3f8 = fVar1;
  local_3f4 = fVar2;
  local_3f0 = fVar3;
  get_world_object_damage_or_target_vectors(param_1,&local_3ec,&local_3dc);
  local_3ec = 0;
  local_3e8 = 0;
  local_3e4 = 0;
  get_world_object_damage_or_target_vectors((int)param_2,&local_404,&local_3e0);
  fVar5 = local_444[0] * _DAT_004bebb4;
  local_44c = 3.4028235e+38;
  local_448 = 0.0;
  fVar6 = local_444[1] * _DAT_004bebb4;
  fVar7 = local_444[2] * _DAT_004bebb4;
  local_484 = _DAT_004beba8 / ((fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5) - _DAT_004beba4);
  fVar4 = fVar6 * local_428 + fVar7 * local_424 + fVar5 * local_42c;
  local_48c = ((fVar4 * fVar6 + ((fVar5 * local_424 + local_428) - fVar7 * local_42c)) * local_484 -
              local_428) * param_4;
  local_488 = ((fVar4 * fVar7 + ((fVar6 * local_42c + local_424) - fVar5 * local_428)) * local_484 -
              local_424) * param_4;
  local_490 = ((fVar4 * fVar5 + ((fVar7 * local_428 + local_42c) - fVar6 * local_424)) * local_484 -
              local_42c) * param_4;
  local_458 = local_490;
  local_454 = local_48c;
  local_450 = local_488;
  weapon_mount_ordnance_query_context_helper_004a8690
            (&local_464,&local_458,&local_480,&local_470,local_3d8);
  pfVar8 = (float *)vec3_madd_xyz(&local_490,fVar1,fVar2,fVar3,local_480,local_404,local_400,
                                  local_3fc);
  local_47c = *pfVar8;
  local_478 = pfVar8[1];
  local_474 = pfVar8[2];
  local_490 = local_470 - *pfVar8;
  local_48c = local_46c - pfVar8[1];
  local_488 = local_468 - pfVar8[2];
  vec3_length(local_490,local_48c,local_488);
  if (SQRT((local_474 - local_45c) * (local_474 - local_45c) +
           (local_47c - local_464) * (local_47c - local_464)) <
      SQRT((local_468 - local_45c) * (local_468 - local_45c) +
           (local_470 - local_464) * (local_470 - local_464))) {
    iVar10 = 0x78;
    pfVar8 = (float *)register0x00000010;
    do {
      pfVar11 = pfVar8 + -2;
      fVar2 = *pfVar11 * _DAT_004beba0;
      fVar3 = fVar2 * local_444[0];
      fVar4 = fVar2 * local_444[1];
      fVar2 = fVar2 * local_444[2];
      local_484 = _DAT_004beba8 / ((fVar2 * fVar2 + fVar4 * fVar4 + fVar3 * fVar3) - _DAT_004beba4);
      fVar1 = fVar2 * local_424 + fVar3 * local_42c + fVar4 * local_428;
      local_490 = ((fVar1 * fVar3 + ((fVar2 * local_428 + local_42c) - fVar4 * local_424)) *
                   local_484 - local_42c) * param_4;
      local_48c = ((fVar1 * fVar4 + ((fVar3 * local_424 + local_428) - fVar2 * local_42c)) *
                   local_484 - local_428) * param_4;
      local_488 = ((fVar1 * fVar2 + ((fVar4 * local_42c + local_424) - fVar3 * local_428)) *
                   local_484 - local_424) * param_4;
      local_458 = local_490;
      local_454 = local_48c;
      local_450 = local_488;
      weapon_mount_ordnance_query_context_helper_004a8690
                (&local_464,&local_458,&local_480,&local_470,local_3d8);
      local_47c = local_480 * local_404 + local_3f8;
      local_478 = local_480 * local_400 + local_3f4;
      local_474 = local_480 * local_3fc + local_3f0;
      pfVar9 = (float *)vec3_subtract_xyz(local_3cc,local_470,local_46c,local_468,local_47c,
                                          local_478,local_474);
      fVar12 = vec3_length(*pfVar9,pfVar9[1],pfVar9[2]);
      pfVar8[-1] = (float)fVar12;
      if (fVar12 < (float10)local_44c) {
        local_448 = *pfVar11;
        local_44c = (float)fVar12;
      }
      iVar10 = iVar10 + -1;
      pfVar8 = pfVar11;
    } while (iVar10 != 0);
    return (float10)local_448;
  }
  return (float10)_DAT_004bebb8;
}


