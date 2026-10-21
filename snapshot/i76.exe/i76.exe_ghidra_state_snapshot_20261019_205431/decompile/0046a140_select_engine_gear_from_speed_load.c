/*
 * Program: i76.exe
 * Function: select_engine_gear_from_speed_load
 * Entry: 0046a140
 * Signature: int __cdecl select_engine_gear_from_speed_load(float param_1, float param_2, int param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Selects final engine
   gear/mode from speed/load and requested candidate gear using shift-curve constraints. */

int __cdecl select_engine_gear_from_speed_load(float param_1,float param_2,int param_3,int param_4)

{
  float fVar1;
  
  fVar1 = ABS(param_2 * _DAT_004be270);
  if ((param_4 == 5) && (2 < param_3)) {
    return 2;
  }
  if ((param_4 == 4) && (3 < param_3)) {
    return 3;
  }
  if (param_3 == 2) {
    if ((param_1 < _DAT_004be298) && (fVar1 < _DAT_004be2c8)) {
      return 1;
    }
  }
  else if (param_3 == 3) {
    if ((((_DAT_004be27c < param_1) && (fVar1 < _DAT_004be2b4)) ||
        ((_DAT_004be2b8 <= param_1 &&
         ((((param_1 <= _DAT_004be27c && (_DAT_004be2bc <= fVar1)) && (fVar1 <= _DAT_004be2b4)) &&
          ((fVar1 - _DAT_004be2b4) * _DAT_004be2c0 * _DAT_004be2c4 * _DAT_004be27c < param_1))))))
       || (fVar1 < _DAT_004be2bc)) {
      return 2;
    }
  }
  else if ((param_3 == 4) &&
          ((((_DAT_004be29c < param_1 && (fVar1 < _DAT_004be2a0)) ||
            ((((_DAT_004be2a4 <= param_1 && ((param_1 <= _DAT_004be27c && (_DAT_004be2a8 <= fVar1)))
               ) && (fVar1 <= _DAT_004be2a0)) &&
             ((fVar1 - _DAT_004be2a0) * _DAT_004be2ac * _DAT_004be2b0 * _DAT_004be27c < param_1))))
           || (fVar1 < _DAT_004be2a8)))) {
    return 3;
  }
  return param_3;
}


