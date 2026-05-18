/*
 * Program: i76.exe
 * Function: write_video_driver_log
 * Entry: 00431f60
 * Signature: undefined __cdecl write_video_driver_log(int param_1)
 */


/* i76 second-pass rename
   old_name: FUN_00431f60
   suggested_name: write_video_driver_log
   basis: Writes VIDEOLOG.TXT and DirectDraw/D3D caps diagnostics. */

void __cdecl write_video_driver_log(int param_1)

{
  FILE *_File;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char *pcVar4;
  uint uVar5;
  undefined1 auStack_402 [154];
  uint uStack_368;
  uint uStack_364;
  uint uStack_360;
  uint uStack_35c;
  uint uStack_358;
  uint uStack_354;
  uint uStack_350;
  uint uStack_34c;
  uint uStack_348;
  uint uStack_344;
  uint uStack_340;
  undefined1 local_2d8 [364];
  undefined1 local_16c [364];
  
  _File = fopen(s_VIDEOLOG_TXT_004f0708,&DAT_004f0718);
  if (_File == (FILE *)0x0) {
    return;
  }
  (**(code **)(**(int **)(param_1 + 0xa278) + 0x2c))
            (*(int **)(param_1 + 0xa278),local_16c,local_2d8);
  fprintf(_File,s_________________________DIRECT_D_004f06c4);
  fprintf(_File,s_DIRECT_DRAW_DRIVER_NAME__s_004f06a0,&stack0xfffffbe0);
  fprintf(_File,s_DIRECT_DRAW_DRIVER_DESC__s_004f067c,auStack_402);
  fprintf(_File,s_________________SELECTED_D3D_HW_D_004f0634);
  puVar2 = (undefined4 *)(param_1 + 0x644);
  puVar3 = (undefined4 *)&stack0xfffffbe0;
  for (iVar1 = 0x4f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  fprintf(_File,s_Texture_Caps_004f0624);
  if (uStack_34c == 0) {
    pcVar4 = s_None_004f061c;
LAB_00432082:
    fprintf(_File,pcVar4);
  }
  else {
    uVar5 = uStack_34c;
    if ((uStack_34c & 1) != 0) {
      fprintf(_File,s_D3DPTEXTURECAPS_PERSPECTIVE_004f05f8);
      uVar5 = uStack_34c;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPTEXTURECAPS_POW2_004f05d4);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPTEXTURECAPS_ALPHA_004f05b0);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPTEXTURECAPS_TRANSPARENCY_004f058c);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPTEXTURECAPS_BORDER_004f0568);
    }
    if ((uVar5 & 0x20) != 0) {
      pcVar4 = s_D3DPTEXTURECAPS_SQUAREONLY_004f0544;
      goto LAB_00432082;
    }
  }
  fprintf(_File,s_Texture_Filter_Caps_004f052c);
  if (uStack_348 == 0) {
    pcVar4 = s_None_004f061c;
LAB_00432113:
    fprintf(_File,pcVar4);
  }
  else {
    uVar5 = uStack_348;
    if ((uStack_348 & 1) != 0) {
      fprintf(_File,s_D3DPTFILTERCAPS_NEAREST_004f0504);
      uVar5 = uStack_348;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPTFILTERCAPS_LINEAR_004f04dc);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPTFILTERCAPS_MIPNEAREST_004f04b4);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPTFILTERCAPS_MIPLINEAR_004f048c);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPTFILTERCAPS_LINEARMIPNEAREST_004f0464);
    }
    if ((uVar5 & 0x20) != 0) {
      pcVar4 = s_D3DPTFILTERCAPS_LINEARMIPLINEAR_004f043c;
      goto LAB_00432113;
    }
  }
  fprintf(_File,s_Texture_Blend_Caps_004f0428);
  if (uStack_344 == 0) {
    pcVar4 = s_None_004f061c;
LAB_004321b6:
    fprintf(_File,pcVar4);
  }
  else {
    uVar5 = uStack_344;
    if ((uStack_344 & 1) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_DECAL_004f0408);
      uVar5 = uStack_344;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_MODULATE_004f03e8);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_DECALALPHA_004f03c8);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_MODULATEALPHA_004f03a8);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_DECALMASK_004f0388);
    }
    if ((uVar5 & 0x20) != 0) {
      fprintf(_File,s_D3DPTBLENDCAPS_MODULATEMASK_004f0368);
    }
    if ((uVar5 & 0x40) != 0) {
      pcVar4 = s_D3DPTBLENDCAPS_COPY_004f0348;
      goto LAB_004321b6;
    }
  }
  fprintf(_File,s_Source_004f0340);
  log_d3d_blend_caps(_File,uStack_35c);
  fprintf(_File,s_Dest_004f0338);
  log_d3d_blend_caps(_File,uStack_358);
  fprintf(_File,s_Alpha_004f0330);
  fprintf(_File,s_Compare_Caps_004f0320);
  if (uStack_354 == 0) {
    pcVar4 = s_None_004f061c;
LAB_004322b1:
    fprintf(_File,pcVar4);
  }
  else {
    uVar5 = uStack_354;
    if ((uStack_354 & 1) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_NEVER_004f0308);
      uVar5 = uStack_354;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_LESS_004f02ec);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_EQUAL_004f02d0);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_LESSEQUAL_004f02b4);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_GREATER_004f0298);
    }
    if ((uVar5 & 0x20) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_NOTEQUAL_004f027c);
    }
    if ((uVar5 & 0x40) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_GREATEREQUAL_004f0260);
    }
    if ((uVar5 & 0x80) != 0) {
      pcVar4 = s_D3DPCMPCAPS_ALWAYS_004f0244;
      goto LAB_004322b1;
    }
  }
  fprintf(_File,&DAT_004f0240);
  fprintf(_File,s_Compare_Caps_004f0320);
  if (uStack_360 == 0) {
    pcVar4 = s_None_004f061c;
LAB_00432374:
    fprintf(_File,pcVar4);
  }
  else {
    uVar5 = uStack_360;
    if ((uStack_360 & 1) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_NEVER_004f0308);
      uVar5 = uStack_360;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_LESS_004f02ec);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_EQUAL_004f02d0);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_LESSEQUAL_004f02b4);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_GREATER_004f0298);
    }
    if ((uVar5 & 0x20) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_NOTEQUAL_004f027c);
    }
    if ((uVar5 & 0x40) != 0) {
      fprintf(_File,s_D3DPCMPCAPS_GREATEREQUAL_004f0260);
    }
    if ((uVar5 & 0x80) != 0) {
      pcVar4 = s_D3DPCMPCAPS_ALWAYS_004f0244;
      goto LAB_00432374;
    }
  }
  log_d3d_shade_caps(_File,uStack_350);
  fprintf(_File,s_Texture_Address_Caps_004f0228);
  if (uStack_340 == 0) {
    pcVar4 = s_None_004f061c;
LAB_004323e0:
    fprintf(_File,pcVar4);
  }
  else {
    if ((uStack_340 & 1) != 0) {
      fprintf(_File,s_D3DPTADDRESSCAPS_WRAP_004f020c);
    }
    if ((uStack_340 & 2) != 0) {
      fprintf(_File,s_D3DPTADDRESSCAPS_MIRROR_004f01f0);
    }
    if ((uStack_340 & 4) != 0) {
      pcVar4 = s_D3DPTADDRESSCAPS_CLAMP_004f01d4;
      goto LAB_004323e0;
    }
  }
  fprintf(_File,s_Raster_Caps_004f01c4);
  if (uStack_364 == 0) {
    pcVar4 = s_None_004f061c;
  }
  else {
    uVar5 = uStack_364;
    if ((uStack_364 & 1) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_DITHER_004f01a4);
      uVar5 = uStack_364;
    }
    if ((uVar5 & 2) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_ROP2_004f0184);
    }
    if ((uVar5 & 4) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_XOR_004f0164);
    }
    if ((uVar5 & 8) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_PAT_004f0144);
    }
    if ((uVar5 & 0x10) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_ZTEST_004f0124);
    }
    if ((uVar5 & 0x20) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_SUBPIXEL_004f0104);
    }
    if ((uVar5 & 0x40) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_SUBPIXELX_004f00e4);
    }
    if ((uVar5 & 0x80) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_FOGVERTEX_004f00c4);
    }
    if ((uVar5 & 0x100) != 0) {
      fprintf(_File,s_D3DPRASTERCAPS_FOGTABLE_004f00a4);
    }
    if ((uVar5 & 0x200) == 0) goto LAB_004324c6;
    pcVar4 = s_D3DPRASTERCAPS_STIPPLE_004f0084;
  }
  fprintf(_File,pcVar4);
LAB_004324c6:
  log_d3d_misc_caps(_File,uStack_368);
  fclose(_File);
  return;
}


