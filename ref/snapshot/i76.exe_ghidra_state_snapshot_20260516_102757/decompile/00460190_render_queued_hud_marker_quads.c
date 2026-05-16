/*
 * Program: i76.exe
 * Function: render_queued_hud_marker_quads
 * Entry: 00460190
 * Signature: undefined __cdecl render_queued_hud_marker_quads(float * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Renders queued small HUD marker quads through the polygon renderer and clears the
   queue. */

void __cdecl render_queued_hud_marker_quads(float *param_1,float param_2,float param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float local_60 [5];
  undefined4 local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined4 local_4;
  
  iVar2 = 0;
  pfVar3 = local_60;
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  if (0 < DAT_0054ad40) {
    pfVar3 = (float *)&DAT_0054ae54;
    do {
      local_60[0] = (param_2 - pfVar3[-1] * _DAT_004be134) - _DAT_004be138;
      local_60[1] = (param_3 - *pfVar3 * _DAT_004be13c) - _DAT_004be140;
      local_2c = local_60[1] - _DAT_004be144;
      local_48 = local_60[0] - _DAT_004be144;
      local_10 = _DAT_004be148;
      local_4 = _DAT_004be148;
      local_28 = _DAT_004be148;
      local_1c = _DAT_004be148;
      local_40 = _DAT_004be148;
      local_34 = _DAT_004be148;
      local_60[2] = (float)_DAT_004be148;
      local_4c = _DAT_004be148;
      local_44 = local_60[1];
      local_30 = local_48;
      local_18 = local_60[0];
      local_14 = local_2c;
      if (*(int *)((int)param_1[0xf] + 8) == 1) {
        log_cache_memory_status(param_1,local_60,(float *)0x4,(uint *)pfVar3[1],(float *)0x8);
      }
      else {
        submit_lit_textured_polygon_to_renderer(param_1,local_60,4,(uint *)pfVar3[1],8);
      }
      iVar2 = iVar2 + 1;
      pfVar3 = pfVar3 + 3;
    } while (iVar2 < DAT_0054ad40);
  }
  DAT_0054ad40 = 0;
  return;
}


