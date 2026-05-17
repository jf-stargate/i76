/*
 * Program: i76.exe
 * Function: update_engine_gear_rpm_torque_state
 * Entry: 0046a320
 * Signature: undefined __cdecl update_engine_gear_rpm_torque_state(int param_1, float param_2, float param_3, uint param_4, int param_5, int param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Updates engine gear/mode,
   RPM-like value, and torque/power scalar from speed/load, throttle/brake flags, frame delta, and
   engine definition parameters. */

void __cdecl
update_engine_gear_rpm_torque_state
          (int param_1,float param_2,float param_3,uint param_4,int param_5,int param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  
  fVar8 = get_runtime_frame_delta_seconds();
  fVar2 = ABS(param_3);
  fVar1 = (float)fVar8;
  fVar3 = fVar2 * _DAT_004be2cc * _DAT_004be2b4;
  if (param_5 == 0) {
    iVar6 = *(int *)(param_1 + 8);
    if (iVar6 == 0) {
      *(undefined4 *)(param_1 + 8) = 1;
      iVar6 = 1;
    }
  }
  else {
    iVar6 = 0;
  }
  if ((param_6 == 2) || (param_6 == 0)) {
    iVar6 = 1;
    *(undefined4 *)(param_1 + 8) = 1;
  }
  if ((param_4 & 1) == 0) {
LAB_0046a586:
    fVar3 = fVar1 + fVar1;
    fVar4 = _DAT_004be260;
    if (((_DAT_004be260 <= fVar3) && (fVar3 <= _DAT_004be2ec)) &&
       (fVar5 = -*(float *)(param_1 + 0x1c), (float)_DAT_004be2f0 <= ABS(fVar5))) {
      fVar4 = fVar5 * fVar3 + *(float *)(param_1 + 0x1c);
    }
  }
  else {
    if ((((param_4 & 6) == 0) && (param_6 != 2)) && (param_6 != 0)) {
      iVar7 = 0;
      if (iVar6 != 0) {
        iVar6 = *(int *)(param_1 + 8);
        fVar1 = ABS(param_3 * _DAT_004be270);
        if (iVar6 == 1) {
          iVar7 = 2;
          if (param_2 <= _DAT_004be298) goto LAB_0046a52e;
        }
        else if (iVar6 == 2) {
          if ((param_6 == 5) ||
             ((((_DAT_004be274 <= param_2 || (fVar1 <= _DAT_004be28c)) &&
               ((((param_2 < _DAT_004be274 || ((_DAT_004be27c < param_2 || (fVar1 < _DAT_004be28c)))
                  ) || (_DAT_004be290 < fVar1)) ||
                ((fVar1 - _DAT_004be290) * _DAT_004be284 * _DAT_004be294 * _DAT_004be27c < param_2))
               )) && (fVar1 <= _DAT_004be290)))) goto LAB_0046a52e;
          iVar7 = 3;
        }
        else if ((((iVar6 != 3) || (param_6 == 5)) || (param_6 == 4)) ||
                (((_DAT_004be274 <= param_2 || (fVar1 <= _DAT_004be278)) &&
                 ((iVar7 = test_gear_shift_curve_region(param_2,fVar1,0.0625,40.0,0.875,106.0),
                  iVar7 != 0 && (fVar1 <= _DAT_004be280)))))) {
LAB_0046a52e:
          iVar7 = iVar6;
        }
        else {
          iVar7 = 4;
        }
        iVar7 = select_engine_gear_from_speed_load(param_2,param_3,iVar7,param_6);
      }
      *(int *)(param_1 + 8) = iVar7;
      fVar4 = _DAT_004be2d0;
      if (iVar7 != 1) {
        fVar4 = *(float *)(&DAT_004f8640 + iVar7 * 4) * fVar3 * _DAT_004be2d4 - _DAT_004be2d8;
      }
      fVar2 = fVar3 * _DAT_004be2dc * _DAT_004be2e0 * _DAT_004be2e4;
      goto LAB_0046a75a;
    }
    if ((param_4 & 1) == 0) goto LAB_0046a586;
    fVar3 = fVar1 + fVar1;
    if (_DAT_004be298 <= param_2) {
      fVar4 = param_2 * _DAT_004be2f8 - _DAT_004be2fc;
      if (((_DAT_004be260 <= fVar3) && (fVar3 <= _DAT_004be2ec)) &&
         (fVar5 = fVar4 - *(float *)(param_1 + 0x1c), (float)_DAT_004be2f0 <= ABS(fVar5))) {
        fVar4 = fVar3 * fVar5 + *(float *)(param_1 + 0x1c);
      }
      if (_DAT_004be300 < fVar4) {
        fVar4 = _DAT_004be300;
      }
    }
    else {
      fVar4 = _DAT_004be2d0;
      if (((_DAT_004be260 <= fVar3) && (fVar3 <= _DAT_004be2ec)) &&
         (fVar5 = _DAT_004be2d0 - *(float *)(param_1 + 0x1c), (float)_DAT_004be2f0 <= ABS(fVar5))) {
        fVar4 = fVar5 * fVar3 + *(float *)(param_1 + 0x1c);
      }
    }
  }
  param_2 = fVar1 + fVar1;
  if (((_DAT_004be260 <= param_2) && (param_2 <= _DAT_004be2ec)) &&
     (fVar1 = fVar2 - *(float *)(param_1 + 0x24), (float)_DAT_004be2f0 <= ABS(fVar1))) {
    fVar2 = param_2 * fVar1 + *(float *)(param_1 + 0x24);
  }
LAB_0046a75a:
  *(float *)(param_1 + 0x24) = fVar2;
  fVar1 = fVar4 - _DAT_004be304;
  *(float *)(param_1 + 0x1c) = fVar4;
  *(float *)(param_1 + 0x10) =
       (*(float *)(param_1 + 0x14) - *(float *)(param_1 + 0xc) * fVar1 * fVar1) *
       *(float *)(param_1 + 0x18);
  return;
}


