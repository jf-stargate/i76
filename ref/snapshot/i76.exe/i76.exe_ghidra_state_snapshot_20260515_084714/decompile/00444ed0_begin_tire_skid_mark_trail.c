/*
 * Program: i76.exe
 * Function: begin_tire_skid_mark_trail
 * Entry: 00444ed0
 * Signature: undefined __cdecl begin_tire_skid_mark_trail(undefined4 * param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Allocates/initializes a
   tire skid trail record from the free-list and stores the first point and owner object. */

void __cdecl begin_tire_skid_mark_trail(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  float10 fVar2;
  
  if (DAT_0052bb98 != (undefined4 *)0x0) {
    DAT_0052bb98[4] = 1;
    DAT_0052bb98[2] = param_2;
    DAT_0052bb98[1] = DAT_0052bb94;
    DAT_0052bb94 = DAT_0052bb94 + 1;
    fVar2 = get_multiplayer_or_runtime_seconds();
    DAT_0052bb98[3] = (float)(fVar2 - (float10)_DAT_004bd348);
    puVar1 = DAT_0052bb98;
    DAT_0052bb98[5] = *param_1;
    puVar1[6] = param_1[1];
    puVar1[7] = param_1[2];
    DAT_0052bb98 = (undefined4 *)*DAT_0052bb98;
  }
  return;
}


