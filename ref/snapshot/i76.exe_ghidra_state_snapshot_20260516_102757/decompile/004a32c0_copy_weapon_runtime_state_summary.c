/*
 * Program: i76.exe
 * Function: copy_weapon_runtime_state_summary
 * Entry: 004a32c0
 * Signature: undefined4 __cdecl copy_weapon_runtime_state_summary(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Copies weapon type/category,
   ammo/state, object/slot ids, and definition-derived fields into caller summary record. */

undefined4 __cdecl copy_weapon_runtime_state_summary(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar1 = (&DAT_005aab38)[param_1 * 0x13];
  if ((&g_weapon_runtime_slot_table)[param_1 * 0x13] != param_1) {
    return 3;
  }
  iVar2 = iVar1 * 0xd8;
  *param_2 = (&DAT_005d8930)[iVar1 * 0x36];
  param_2[1] = (&DAT_005d8934)[iVar1 * 0x36];
  param_2[7] = *(undefined4 *)
                ((&DAT_005aab20)[param_1 * 0x13] + 100 + (&DAT_005aab24)[param_1 * 0x13] * 0x58);
  param_2[2] = *(undefined4 *)(&DAT_005aab18 + param_1 * 0x4c);
  param_2[3] = *(undefined4 *)(&DAT_005d8940 + iVar2);
  param_2[4] = *(undefined4 *)(&DAT_005d895c + iVar2);
  uVar3 = ordnance_instance_runtime_context_helper_0049fb10(*(int *)(&DAT_005d8958 + iVar2));
  param_2[5] = (int)uVar3;
  param_2[6] = *(undefined4 *)
                ((&DAT_005aab20)[param_1 * 0x13] + ((&DAT_005aab24)[param_1 * 0x13] + 1) * 0x58);
  return 1;
}


