/*
 * Program: i76.exe
 * Function: create_vehicle_damage_child_effect_objects
 * Entry: 0046e6e0
 * Signature: undefined __cdecl create_vehicle_damage_child_effect_objects(int param_1, undefined4 param_2, int param_3)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Creates child world
   objects/effects for damaged vehicle parts, using handgn/part geometry and parent transforms. */

void __cdecl create_vehicle_damage_child_effect_objects(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  LPVOID pvVar2;
  float *pfVar3;
  float *pfVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  LPVOID pvVar9;
  int *piVar10;
  undefined4 *puVar11;
  int *piVar12;
  float *pfVar13;
  undefined4 *puVar14;
  char *pcVar15;
  LPVOID local_29c;
  undefined4 local_298;
  float local_294;
  float local_290;
  float local_28c;
  int local_288;
  LPVOID local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  char local_260 [8];
  char local_258 [4];
  char local_254 [4];
  char local_250 [8];
  char local_248 [8];
  char local_240 [4];
  char local_23c [4];
  char local_238 [8];
  char local_230 [8];
  char local_228 [4];
  char local_224 [4];
  char local_220 [16];
  char local_210 [4];
  char local_20c [4];
  char local_208 [8];
  char local_200 [80];
  undefined4 local_1b0;
  int local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  char local_178 [4];
  char local_174 [4];
  char local_170 [12];
  undefined4 local_164;
  undefined4 local_160;
  LPVOID local_15c;
  LPVOID local_158;
  int local_154;
  undefined4 local_150;
  undefined4 local_14c;
  char local_148 [4];
  char local_144 [4];
  char local_140 [4];
  char local_13c;
  char local_133 [4];
  char local_12f [4];
  char local_12b [4];
  char local_127 [15];
  int local_118 [18];
  LPVOID local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  pvVar9 = local_29c;
  pvVar2 = local_29c;
  if (param_1 == 1) {
    local_298 = 6;
    local_290 = 1.5358897;
    local_28c = 0.41;
    local_294 = 1.14;
    local_29c = (LPVOID)0x3d4ccccd;
    pvVar2 = (LPVOID)target_reticle_context_helper_00458f40(param_3,0x2b);
    pvVar9 = (LPVOID)0x3;
    if (pvVar2 != (LPVOID)0x0) {
      get_world_object_class_id((int)pvVar2,1);
    }
  }
  if (param_1 == 2) {
    pvVar9 = (LPVOID)0x4;
    local_298 = 5;
    local_290 = -1.9373155;
    local_28c = -0.81;
    local_294 = 1.16;
    local_29c = (LPVOID)0xbdf5c28f;
    pvVar2 = (LPVOID)target_reticle_context_helper_00458f40(param_3,0x2c);
    if (pvVar2 != (LPVOID)0x0) {
      get_world_object_class_id((int)pvVar2,1);
    }
  }
  local_118[0] = param_3;
  local_118[1] = 0;
  if (pvVar2 == (LPVOID)0x0) {
    piVar10 = &DAT_004faed8;
  }
  else {
    piVar10 = (int *)((int)pvVar2 + 0x18);
  }
  piVar12 = local_118 + 2;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *piVar12 = *piVar10;
    piVar10 = piVar10 + 1;
    piVar12 = piVar12 + 1;
  }
  local_cc = 6;
  local_c8 = local_298;
  local_d0 = pvVar9;
  register_hardpoint_carrier(local_118);
  local_284 = allocate_world_object_node(0);
  *(undefined4 *)((int)local_284 + 0x6c) = 0x33;
  local_288 = 0x12;
  local_280 = 0x42f00000;
  local_27c = 0;
  local_270 = 0;
  local_26c = 0;
  local_278 = 4;
  local_268 = 2;
  world_reader_null_handler((byte *)s_xbulg1_xdf_004f8a84,local_260,0);
  local_258[0] = s_wmgr2_wav_004f8a78[0];
  local_258[1] = s_wmgr2_wav_004f8a78[1];
  local_258[2] = s_wmgr2_wav_004f8a78[2];
  local_258[3] = s_wmgr2_wav_004f8a78[3];
  local_254[0] = s_wmgr2_wav_004f8a78[4];
  local_254[1] = s_wmgr2_wav_004f8a78[5];
  local_254[2] = s_wmgr2_wav_004f8a78[6];
  local_254[3] = s_wmgr2_wav_004f8a78[7];
  local_250[0] = s_wmgr2_wav_004f8a78[8];
  local_250[1] = s_wmgr2_wav_004f8a78[9];
  world_reader_null_handler((byte *)s_xbulc1_xdf_004f8a6c,local_248,0);
  local_240[0] = s_wmgr1_wav_004f8a60[0];
  local_240[1] = s_wmgr1_wav_004f8a60[1];
  local_240[2] = s_wmgr1_wav_004f8a60[2];
  local_240[3] = s_wmgr1_wav_004f8a60[3];
  local_23c[0] = s_wmgr1_wav_004f8a60[4];
  local_23c[1] = s_wmgr1_wav_004f8a60[5];
  local_23c[2] = s_wmgr1_wav_004f8a60[6];
  local_23c[3] = s_wmgr1_wav_004f8a60[7];
  local_238[0] = s_wmgr1_wav_004f8a60[8];
  local_238[1] = s_wmgr1_wav_004f8a60[9];
  world_reader_null_handler((byte *)s_xbulb1_xdf_004f8a54,local_230,0);
  local_228[0] = s_hssr1_wav_004f8a48[0];
  local_228[1] = s_hssr1_wav_004f8a48[1];
  local_228[2] = s_hssr1_wav_004f8a48[2];
  local_228[3] = s_hssr1_wav_004f8a48[3];
  local_224[0] = s_hssr1_wav_004f8a48[4];
  local_224[1] = s_hssr1_wav_004f8a48[5];
  local_224[2] = s_hssr1_wav_004f8a48[6];
  local_224[3] = s_hssr1_wav_004f8a48[7];
  local_220[0] = s_hssr1_wav_004f8a48[8];
  local_220[1] = s_hssr1_wav_004f8a48[9];
  world_reader_null_handler((byte *)s_xbulb1_xdf_004f8a54,local_230,0);
  local_210[0] = s_hssr2_wav_004f8a3c[0];
  local_210[1] = s_hssr2_wav_004f8a3c[1];
  local_210[2] = s_hssr2_wav_004f8a3c[2];
  local_210[3] = s_hssr2_wav_004f8a3c[3];
  local_20c[0] = s_hssr2_wav_004f8a3c[4];
  local_20c[1] = s_hssr2_wav_004f8a3c[5];
  local_20c[2] = s_hssr2_wav_004f8a3c[6];
  local_20c[3] = s_hssr2_wav_004f8a3c[7];
  local_208[0] = s_hssr2_wav_004f8a3c[8];
  local_208[1] = s_hssr2_wav_004f8a3c[9];
  initialize_ordnance_instance(&local_288);
  if (pvVar2 == (LPVOID)0x0) {
    pvVar2 = allocate_world_object_node(param_3);
    pfVar3 = (float *)zone_satellite_map_context_helper_00493da0(local_c0,local_290);
    pfVar4 = local_80;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar4 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar3 = (float *)((int)pvVar2 + 0x18);
    pfVar4 = compose_matrix_or_transform_a(local_c0,local_80,pfVar3);
    pfVar13 = pfVar3;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar13 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar13 = pfVar13 + 1;
    }
    pfVar4 = (float *)zone_satellite_map_context_helper_00493e00(local_c0,0.08726646);
    pfVar13 = local_40;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar13 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar13 = pfVar13 + 1;
    }
    pfVar4 = compose_matrix_or_transform_a(local_c0,local_40,pfVar3);
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar3 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar3 = pfVar3 + 1;
    }
    *(double *)((int)pvVar2 + 0x40) = (double)local_28c;
    *(double *)((int)pvVar2 + 0x48) = (double)local_294;
    *(double *)((int)pvVar2 + 0x50) = (double)(float)local_29c;
  }
  *(undefined4 *)((int)pvVar2 + 0x6c) = 0x32;
  pvVar9 = allocate_world_object_node((int)pvVar2);
  set_world_object_class_and_register_runtime((int)pvVar9,0x29);
  puVar11 = &DAT_004faed8;
  puVar14 = (undefined4 *)((int)pvVar9 + 0x18);
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar14 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar14 = puVar14 + 1;
  }
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s__45_Handgun_004f8a30
                                );
  uVar7 = 0xffffffff;
  do {
    pcVar15 = pcVar5;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar15 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar15;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar5 = pcVar15 + -uVar7;
  pcVar15 = local_200;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar15 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar15 = pcVar15 + 1;
  }
  local_1b0 = 1;
  local_1a8 = 1;
  local_190 = 1;
  local_180 = 0;
  local_17c = 0;
  local_178[0] = s_h45ch_wav_004f8a24[0];
  local_178[1] = s_h45ch_wav_004f8a24[1];
  local_178[2] = s_h45ch_wav_004f8a24[2];
  local_178[3] = s_h45ch_wav_004f8a24[3];
  local_174[0] = s_h45ch_wav_004f8a24[4];
  local_174[1] = s_h45ch_wav_004f8a24[5];
  local_174[2] = s_h45ch_wav_004f8a24[6];
  local_174[3] = s_h45ch_wav_004f8a24[7];
  local_1ac = param_1;
  local_194 = 0xfffffff;
  local_170[0] = s_h45ch_wav_004f8a24[8];
  local_170[1] = s_h45ch_wav_004f8a24[9];
  local_150 = 0xfffffff;
  local_160 = local_298;
  local_1a4 = 0x2d;
  local_14c = 0x2d;
  local_148[0] = s_3sp_empty_on_004f8a14[0];
  local_148[1] = s_3sp_empty_on_004f8a14[1];
  local_148[2] = s_3sp_empty_on_004f8a14[2];
  local_148[3] = s_3sp_empty_on_004f8a14[3];
  local_144[0] = s_3sp_empty_on_004f8a14[4];
  local_144[1] = s_3sp_empty_on_004f8a14[5];
  local_144[2] = s_3sp_empty_on_004f8a14[6];
  local_144[3] = s_3sp_empty_on_004f8a14[7];
  local_140[0] = s_3sp_empty_on_004f8a14[8];
  local_140[1] = s_3sp_empty_on_004f8a14[9];
  local_140[2] = s_3sp_empty_on_004f8a14[10];
  local_140[3] = s_3sp_empty_on_004f8a14[0xb];
  local_13c = s_3sp_empty_on_004f8a14[0xc];
  local_1a0 = 0x40200000;
  local_19c = 0;
  local_198 = 0x40400000;
  local_18c = 0x42f00000;
  local_188 = 0x12;
  local_164 = 0xf0;
  local_184 = 0x3e4ccccd;
  local_133[0] = s_3sp_empty_off_004f8a04[0];
  local_133[1] = s_3sp_empty_off_004f8a04[1];
  local_133[2] = s_3sp_empty_off_004f8a04[2];
  local_133[3] = s_3sp_empty_off_004f8a04[3];
  local_12f[0] = s_3sp_empty_off_004f8a04[4];
  local_12f[1] = s_3sp_empty_off_004f8a04[5];
  local_12f[2] = s_3sp_empty_off_004f8a04[6];
  local_12f[3] = s_3sp_empty_off_004f8a04[7];
  local_12b[0] = s_3sp_empty_off_004f8a04[8];
  local_12b[1] = s_3sp_empty_off_004f8a04[9];
  local_12b[2] = s_3sp_empty_off_004f8a04[10];
  local_12b[3] = s_3sp_empty_off_004f8a04[0xb];
  local_127[0] = s_3sp_empty_off_004f8a04[0xc];
  local_127[1] = s_3sp_empty_off_004f8a04[0xd];
  local_154 = param_3;
  local_15c = pvVar9;
  local_158 = pvVar2;
  mount_weapon_on_hardpoint(local_200);
  return;
}


