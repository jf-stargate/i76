/*
 * Program: i76.exe
 * Function: extract_weapon_runtime_state_to_vsf_record
 * Entry: 004a3400
 * Signature: undefined4 __cdecl extract_weapon_runtime_state_to_vsf_record(int param_1, undefined4 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Serializes a weapon runtime slot
   to a VSF/WPST-style record, including relative transform and global weapon-runtime state fields.
    */

undefined4 __cdecl extract_weapon_runtime_state_to_vsf_record(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  float local_40 [16];
  
  iVar3 = param_1 * 0x4c;
  if ((&g_weapon_runtime_slot_table)[param_1 * 0x13] != param_1) {
    return 3;
  }
  puVar1 = (undefined4 *)
           compute_transform_relative_to_ancestor(local_40,(&DAT_005aab0c)[param_1 * 0x13],0);
  puVar4 = param_2;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  param_2[0x10] = (&DAT_005aab14)[param_1 * 0x13];
  param_2[0x11] = *(undefined4 *)(&DAT_005aab28 + iVar3);
  if (((*(float *)(&DAT_005aab2c + iVar3) == _DAT_004beab8) &&
      ((&DAT_005aab3c)[param_1 * 0x13] == 1)) && ((&DAT_005aab40)[param_1 * 0x13] == 1)) {
    param_2[0x12] = 1;
  }
  else {
    param_2[0x12] = 0;
  }
  param_2[0x13] = *(undefined4 *)(&DAT_005aab44 + iVar3);
  param_2[0x14] =
       *(undefined4 *)
        ((&DAT_005aab20)[param_1 * 0x13] + ((&DAT_005aab24)[param_1 * 0x13] + 1) * 0x58);
  return 1;
}


