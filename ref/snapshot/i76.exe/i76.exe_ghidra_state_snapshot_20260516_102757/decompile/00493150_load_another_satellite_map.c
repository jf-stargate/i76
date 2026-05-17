/*
 * Program: i76.exe
 * Function: load_another_satellite_map
 * Entry: 00493150
 * Signature: undefined __stdcall load_another_satellite_map(void)
 */


void load_another_satellite_map(void)

{
  close_two_handles((undefined4 *)&DAT_005a6068);
  SetFileAttributesA(s_another_sat_004faea4,0x80);
  DeleteFileA(s_another_sat_004faea4);
  return;
}


