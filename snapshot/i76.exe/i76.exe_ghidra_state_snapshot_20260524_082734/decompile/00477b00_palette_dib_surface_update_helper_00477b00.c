/*
 * Program: i76.exe
 * Function: palette_dib_surface_update_helper_00477b00
 * Entry: 00477b00
 * Signature: undefined __cdecl palette_dib_surface_update_helper_00477b00(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: palette dib surface update helper
   based on adjacent named subsystem context. */

void __cdecl palette_dib_surface_update_helper_00477b00(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  
  _DAT_006435fc = 0x3f3fe4a6;
  puVar1 = &DAT_0058db00;
  for (iVar2 = 0x3621; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  g_runtime_light_entry_count = 0;
  _DAT_00643600 = 0x39dad16a;
  DAT_0058db00 = ((param_1 + 2) % 0x18 << 3) / 0x18;
  DAT_006435e0 = open_resource_file_into_memory((&PTR_s_nk_1mon1_map_004fa0b4)[DAT_0058db00 * 5]);
  puVar1 = (undefined4 *)
           zone_satellite_map_context_helper_00494460
                     (local_40,*(float *)(&DAT_004fa0b8 + DAT_0058db00 * 0x14),DAT_004fa0a0,
                      DAT_004fa0a4,DAT_004fa0a8);
  puVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_006435f0 = local_40[3];
  DAT_006435f4 = local_30;
  DAT_006435f8 = local_2c;
  return;
}


