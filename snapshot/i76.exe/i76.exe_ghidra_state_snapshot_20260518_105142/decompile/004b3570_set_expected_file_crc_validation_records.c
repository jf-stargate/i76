/*
 * Program: i76.exe
 * Function: set_expected_file_crc_validation_records
 * Entry: 004b3570
 * Signature: undefined __cdecl set_expected_file_crc_validation_records(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Installs caller-provided 8-byte
   expected CRC/file validation records for subsequent validation. */

void __cdecl set_expected_file_crc_validation_records(int param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  g_expected_file_crc_record_count = param_1;
  if (0 < param_1) {
    puVar3 = &g_expected_file_crc_records;
    for (uVar1 = (uint)(param_1 * 8) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
      puVar3 = puVar3 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar3 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
  }
  return;
}


