/*
 * Program: i76.exe
 * Function: initialize_directdraw_surface_descriptor_block
 * Entry: 004313e0
 * Signature: undefined __cdecl initialize_directdraw_surface_descriptor_block(undefined4 param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Allocates/initializes a DirectDraw surface descriptor block and invokes the
   surface creation callback. */

void __cdecl initialize_directdraw_surface_descriptor_block(undefined4 param_1)

{
  undefined *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_4;
  
  DAT_0052b91c = malloc(0x204);
  *DAT_0052b91c = 0x100;
  _DAT_005fce98 = DAT_00608424;
  _DAT_005fce90 = 0;
  _DAT_005fce84 = DAT_00608424 * 2;
  _DAT_005fce94 = 0;
  local_2c = DAT_006080c8;
  _DAT_005fce88 = DAT_00608428;
  _DAT_005fce9c = DAT_00608428;
  local_30 = DAT_006080b8;
  local_50 = &DAT_005fce80;
  local_48 = 0x300;
  local_3c = 0x40ffffff;
  local_40 = 1;
  local_38 = 0x43fa0000;
  local_34 = 0x48f42400;
  local_28 = 0x400;
  local_4c = 8;
  local_24 = DAT_006080c4;
  local_14 = 0x280;
  local_10 = 0x1e0;
  local_c = 32000;
  local_4 = param_1;
  (*DAT_00608ba8)(&local_50);
  return;
}


