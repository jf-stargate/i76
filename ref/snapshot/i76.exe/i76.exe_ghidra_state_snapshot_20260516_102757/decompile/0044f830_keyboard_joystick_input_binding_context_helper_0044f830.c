/*
 * Program: i76.exe
 * Function: keyboard_joystick_input_binding_context_helper_0044f830
 * Entry: 0044f830
 * Signature: undefined __stdcall keyboard_joystick_input_binding_context_helper_0044f830(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was input_device_binding_keyboard_joystick_input_helper_0044f830.
   Shorten readability label while preserving keyboard/joystick input binding context. */

void keyboard_joystick_input_binding_context_helper_0044f830(void)

{
  float fVar1;
  ushort uVar2;
  int *piVar3;
  uint uVar4;
  float *pfVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  int iVar6;
  float10 fVar7;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  float local_c;
  float local_8;
  
  local_14 = (int)DAT_00536788;
  local_18 = (int)DAT_00536789;
  local_1c = (int)DAT_0053678a;
  iVar6 = (int)DAT_00536787;
  local_10 = (int)DAT_0053678b;
  local_20 = iVar6;
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  uVar2 = 0;
  if (iVar6 != 0) {
    uVar2 = 0x1000;
  }
  if (local_14 != 0) {
    uVar2 = uVar2 | 0x100;
  }
  if (local_18 != 0) {
    uVar2 = uVar2 | 0x10;
  }
  if (local_1c != 0) {
    uVar2 = uVar2 | 1;
  }
  if (uVar2 == 0) {
    iVar6 = *(int *)(DAT_004f5238 * 0x20 + 0x4f5248);
  }
  else {
    iVar6 = 0;
    switch(DAT_004f5238) {
    case 0:
      iVar6 = DAT_004f5258;
      if ((((uVar2 != 0x10) && (iVar6 = DAT_004f524c, uVar2 != 1)) &&
          ((iVar6 = DAT_004f5240, uVar2 != 0x1000 &&
           ((iVar6 = DAT_004f5244, uVar2 != 0x1001 && (iVar6 = DAT_004f5250, uVar2 != 0x100)))))) &&
         (iVar6 = 0, uVar2 == 0x101)) {
        iVar6 = DAT_004f5254;
      }
      break;
    case 1:
      iVar6 = DAT_004f5278;
      if (((uVar2 != 0x10) && (iVar6 = DAT_004f526c, uVar2 != 1)) &&
         ((iVar6 = DAT_004f5260, uVar2 != 0x1000 &&
          (((iVar6 = DAT_004f5264, uVar2 != 0x1001 && (iVar6 = DAT_004f5270, uVar2 != 0x100)) &&
           (iVar6 = 1, uVar2 == 0x101)))))) {
        iVar6 = DAT_004f5274;
      }
      break;
    case 2:
      iVar6 = DAT_004f5298;
      if ((((uVar2 != 0x10) && (iVar6 = DAT_004f528c, uVar2 != 1)) &&
          (iVar6 = DAT_004f5280, uVar2 != 0x1000)) &&
         (((iVar6 = DAT_004f5284, uVar2 != 0x1001 && (iVar6 = DAT_004f5290, uVar2 != 0x100)) &&
          (iVar6 = 2, uVar2 == 0x101)))) {
        iVar6 = DAT_004f5294;
      }
      break;
    case 3:
      iVar6 = DAT_004f52b8;
      if (((uVar2 != 0x10) && (iVar6 = DAT_004f52ac, uVar2 != 1)) &&
         (((iVar6 = DAT_004f52a0, uVar2 != 0x1000 &&
           ((iVar6 = DAT_004f52a4, uVar2 != 0x1001 && (iVar6 = DAT_004f52b0, uVar2 != 0x100)))) &&
          (iVar6 = 3, uVar2 == 0x101)))) {
        iVar6 = DAT_004f52b4;
      }
      break;
    case 4:
      iVar6 = DAT_004f52d8;
      if (((uVar2 != 0x10) && (iVar6 = DAT_004f52cc, uVar2 != 1)) &&
         ((iVar6 = DAT_004f52c0, uVar2 != 0x1000 &&
          (((iVar6 = DAT_004f52c4, uVar2 != 0x1001 && (iVar6 = DAT_004f52d0, uVar2 != 0x100)) &&
           (iVar6 = 4, uVar2 == 0x101)))))) {
        iVar6 = DAT_004f52d4;
      }
      break;
    case 5:
      iVar6 = DAT_004f52f8;
      if (((((uVar2 != 0x10) && (iVar6 = DAT_004f52ec, uVar2 != 1)) &&
           (iVar6 = DAT_004f52e0, uVar2 != 0x1000)) &&
          ((iVar6 = DAT_004f52e4, uVar2 != 0x1001 && (iVar6 = DAT_004f52f0, uVar2 != 0x100)))) &&
         (iVar6 = 5, uVar2 == 0x101)) {
        iVar6 = DAT_004f52f4;
      }
      break;
    case 6:
    case 7:
      iVar6 = 6;
    }
  }
  uVar4 = get_primary_vehicle_weapon_target_object(*piVar3);
  if ((local_10 == 0) || (uVar4 == 0)) {
    DAT_004f5238 = iVar6;
    switch(iVar6) {
    case 0:
      DAT_00536770 = 0xffffffa8;
      _DAT_00536780 = 0xfffffffe;
      _DAT_00536778 = 0xfffffffd;
      break;
    case 1:
      DAT_00536770 = 0xffffffd3;
      _DAT_00536780 = 0xfffffffe;
      _DAT_00536778 = 0;
      break;
    case 2:
      _DAT_00536778 = 0xfffffff3;
      DAT_00536770 = 0;
      _DAT_00536780 = 0;
      break;
    case 3:
      _DAT_00536778 = 6;
      DAT_00536770 = 0;
      _DAT_00536780 = 0;
      break;
    case 4:
      DAT_00536770 = 0x5d;
      _DAT_00536780 = 2;
      _DAT_00536778 = 0xfffffffd;
      break;
    case 5:
      DAT_00536770 = 0x2d;
      _DAT_00536780 = 2;
      _DAT_00536778 = 0;
      break;
    case 6:
      DAT_00536770 = 0xa0;
      _DAT_00536780 = 2;
      _DAT_00536778 = 0xfffffffe;
      break;
    case 7:
      DAT_00536770 = 0xa0;
      _DAT_00536780 = 2;
      _DAT_00536778 = 0;
    }
  }
  else {
    iVar6 = *piVar3;
    local_44 = *(float *)(iVar6 + 0x30);
    local_40 = *(float *)(iVar6 + 0x34);
    local_3c = *(float *)(iVar6 + 0x38);
    local_2c = local_44;
    local_28 = local_40;
    local_24 = local_3c;
    pfVar5 = (float *)entity_instance_table_context_helper_004576a0(&local_54,uVar4);
    local_50 = *pfVar5 - (float)*(double *)(iVar6 + 0x40);
    local_4c = pfVar5[1] - (float)*(double *)(iVar6 + 0x48);
    local_48 = pfVar5[2] - (float)*(double *)(iVar6 + 0x50);
    fVar7 = (float10)fpatan((float10)local_2c,(float10)local_3c);
    local_8 = (float)fVar7;
    fVar7 = (float10)fpatan((float10)local_50,(float10)local_48);
    local_c = local_8 - (float)fVar7;
    if (local_c <= _DAT_004bd8bc) {
      if (local_c < _DAT_004bd8c4) {
        local_c = local_c - _DAT_004bd8c8;
      }
    }
    else {
      local_c = local_c - _DAT_004bd8c0;
    }
    local_c = -local_c;
    local_38 = local_50;
    local_34 = local_4c;
    local_30 = local_48;
    if ((local_c < _DAT_004bd8cc) && (_DAT_004bd8d0 < local_c)) {
      DAT_00536770 = ftol();
    }
    fVar7 = (float10)fpatan((float10)SQRT(local_24 * local_24 +
                                          local_28 * local_28 + local_2c * local_2c),
                            (float10)local_40);
    local_c = (float)fVar7;
    fVar7 = (float10)fpatan((float10)SQRT(local_30 * local_30 +
                                          local_34 * local_34 + local_38 * local_38),
                            (float10)local_4c);
    local_8 = (float)fVar7;
    fVar1 = local_c - local_8;
    if (fVar1 <= _DAT_004bd8bc) {
      if (fVar1 < _DAT_004bd8c4) {
        fVar1 = fVar1 - _DAT_004bd8c8;
      }
    }
    else {
      fVar1 = fVar1 - _DAT_004bd8c0;
    }
    if ((fVar1 < _DAT_004bd8d8) && (_DAT_004bd8dc < fVar1)) {
      _DAT_00536778 = ftol();
    }
  }
  _DAT_005367a4 = 0x10000;
  if ((DAT_004f5238 == 2) && ((local_10 == 0 || (uVar4 == 0)))) {
    cockpit_gauge_context_helper_0045ade0();
  }
  else {
    gear_indicator_context_helper_0045add0();
  }
  if ((DAT_004f5238 == 4) &&
     (uVar2 = compare_runtime_camera_distance_threshold(1.012291), CONCAT22(extraout_var,uVar2) == 1
     )) {
    iVar6 = is_vehicle_weapon_fire_gate_locked_ready(*piVar3,1);
    if (iVar6 == 0) {
      world_object_texture_binding_apply_helper_0046e2e0(*piVar3,1);
    }
  }
  else {
    iVar6 = is_vehicle_weapon_fire_gate_locked_ready(*piVar3,1);
    if (iVar6 != 0) {
      world_object_texture_binding_clear_helper_0046e360(*piVar3,1);
    }
  }
  if ((DAT_004f5238 == 0) &&
     (uVar2 = compare_runtime_camera_distance_threshold(-0.9250245),
     CONCAT22(extraout_var_00,uVar2) == -1)) {
    iVar6 = is_vehicle_weapon_fire_gate_locked_ready(*piVar3,2);
    if (iVar6 == 0) {
      world_object_texture_binding_apply_helper_0046e2e0(*piVar3,2);
    }
  }
  else {
    iVar6 = is_vehicle_weapon_fire_gate_locked_ready(*piVar3,2);
    if (iVar6 != 0) {
      world_object_texture_binding_clear_helper_0046e360(*piVar3,2);
    }
  }
  if (local_20 != 0) {
    DAT_00536787 = '\0';
  }
  if (local_14 != 0) {
    DAT_00536788 = '\0';
  }
  if (local_18 != 0) {
    DAT_00536789 = '\0';
  }
  if (local_1c != 0) {
    DAT_0053678a = '\0';
  }
  return;
}


