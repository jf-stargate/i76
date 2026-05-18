/*
 * Program: i76.exe
 * Function: test_swept_aabb_axis_interval_collision
 * Entry: 0043df10
 * Signature: undefined4 __cdecl test_swept_aabb_axis_interval_collision(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, float param_10, float param_11, float param_12, float * param_13, undefined4 * param_14, float param_15)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Tests swept interval overlap against an
   expanded axis-aligned volume and returns the collision side/direction selector. */

undefined4 __cdecl
test_swept_aabb_axis_interval_collision
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float param_9,float param_10,float param_11,float param_12,
          float *param_13,undefined4 *param_14,float param_15)

{
  float fVar1;
  float fVar2;
  char cVar3;
  float10 fVar4;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if ((param_4 <= _DAT_004bd208) || (_DAT_004bd20c <= param_4)) {
    fVar1 = ((param_7 - param_15) - param_1) / param_4;
    local_8 = ((param_15 + param_10) - param_1) / param_4;
  }
  else {
    if (param_1 < param_7 - param_15) {
      return 0;
    }
    if (param_15 + param_10 < param_1) {
      return 0;
    }
    local_8 = 1e+30;
    fVar1 = _DAT_004bd210;
  }
  if (fVar1 <= local_8) {
    local_c = local_8;
    local_10 = fVar1;
  }
  else {
    local_10 = local_8;
    local_c = fVar1;
  }
  fVar1 = local_10;
  if (_DAT_004bd200 <= local_c) {
    if ((param_6 <= _DAT_004bd208) || (_DAT_004bd20c <= param_6)) {
      fVar2 = ((param_9 - param_15) - param_3) / param_6;
      local_4 = ((param_15 + param_12) - param_3) / param_6;
    }
    else {
      if (param_3 < param_9 - param_15) {
        return 0;
      }
      if (param_15 + param_12 < param_3) {
        return 0;
      }
      local_4 = 1e+30;
      fVar2 = _DAT_004bd210;
    }
    local_8 = fVar2;
    if (local_4 < fVar2) {
      local_8 = local_4;
      local_4 = fVar2;
    }
    if (local_4 < _DAT_004bd200) {
      return 0;
    }
    if (local_10 < local_8) {
      local_10 = local_8;
    }
    cVar3 = fVar1 < local_8;
    if (local_4 < local_c) {
      local_c = local_4;
    }
    if ((param_5 <= _DAT_004bd208) || (_DAT_004bd20c <= param_5)) {
      fVar1 = ((param_8 - param_15) - param_2) / param_5;
      param_15 = ((param_15 + param_11) - param_2) / param_5;
    }
    else {
      if (param_2 < param_8 - param_15) {
        return 0;
      }
      if (param_15 + param_11 < param_2) {
        return 0;
      }
      param_15 = 1e+30;
      fVar1 = _DAT_004bd210;
    }
    local_8 = fVar1;
    if (param_15 < fVar1) {
      local_8 = param_15;
      param_15 = fVar1;
    }
    if (param_15 < _DAT_004bd200) {
      return 0;
    }
    if (local_10 < local_8) {
      cVar3 = '\x02';
      local_10 = local_8;
    }
    if (param_15 < local_c) {
      local_c = param_15;
    }
    if (((local_10 <= local_c) && (_DAT_004bd200 <= local_c)) &&
       (fVar4 = get_runtime_update_delta_seconds(), fVar1 = _DAT_004bd200,
       (float10)local_10 <= fVar4)) {
      if (local_10 < _DAT_004bd200) {
        return 0;
      }
      *param_13 = local_10;
      if (cVar3 == '\0') {
        if (fVar1 < param_4) {
          *param_14 = 0xbf800000;
          param_14[1] = fVar1;
          param_14[2] = fVar1;
          return 1;
        }
        *param_14 = 0x3f800000;
        param_14[1] = fVar1;
        param_14[2] = fVar1;
        return 1;
      }
      if (cVar3 == '\x01') {
        if (fVar1 < param_6) {
          *param_14 = fVar1;
          param_14[1] = fVar1;
          param_14[2] = 0xbf800000;
          return 1;
        }
        *param_14 = fVar1;
        param_14[1] = fVar1;
        param_14[2] = 0x3f800000;
        return 1;
      }
      if (cVar3 == '\x02') {
        if (fVar1 < param_5) {
          *param_14 = fVar1;
          param_14[1] = 0xbf800000;
          param_14[2] = fVar1;
          return 1;
        }
        *param_14 = fVar1;
        param_14[1] = 0x3f800000;
        param_14[2] = fVar1;
        return 1;
      }
      return 1;
    }
  }
  return 0;
}


