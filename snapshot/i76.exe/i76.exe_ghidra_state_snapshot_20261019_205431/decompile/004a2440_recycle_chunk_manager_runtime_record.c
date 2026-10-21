/*
 * Program: i76.exe
 * Function: recycle_chunk_manager_runtime_record
 * Entry: 004a2440
 * Signature: undefined __cdecl recycle_chunk_manager_runtime_record(int param_1)
 */


void __cdecl recycle_chunk_manager_runtime_record(int param_1)

{
  if (DAT_005a82e0 == 0) {
    if (DAT_005aaacc == param_1) {
      DAT_005aaac8 = *(int *)(DAT_005aaac8 + 0x68);
      DAT_005aaacc = *(int *)(DAT_005aaac8 + 0x70);
      if (DAT_005aaac8 == DAT_005aaac4) {
        DAT_005aaac8 = 0;
        DAT_005aaacc = 0;
      }
    }
    *(int *)(param_1 + 0x40) = DAT_005a82dc;
    DAT_005a82dc = param_1;
  }
  return;
}


