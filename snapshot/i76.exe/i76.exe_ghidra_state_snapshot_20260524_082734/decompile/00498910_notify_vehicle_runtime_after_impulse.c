/*
 * Program: i76.exe
 * Function: notify_vehicle_runtime_after_impulse
 * Entry: 00498910
 * Signature: undefined __stdcall notify_vehicle_runtime_after_impulse(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Post-impulse vehicle runtime
   notification/update helper. */

void notify_vehicle_runtime_after_impulse(void)

{
  if (DAT_004c2724 == 1) {
    _DAT_005a6160 = 0x41a00000;
    _DAT_005a6164 = 0x41980000;
    DAT_005a6158 = 1;
    DAT_005a615c = 1;
  }
  return;
}


