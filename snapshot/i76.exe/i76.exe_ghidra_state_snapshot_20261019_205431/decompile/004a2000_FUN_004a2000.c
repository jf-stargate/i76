/*
 * Program: i76.exe
 * Function: FUN_004a2000
 * Entry: 004a2000
 * Signature: undefined4 * __stdcall FUN_004a2000(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_004a2000(void)

{
  LPVOID pvVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  pvVar1 = DAT_005aaac8;
  puVar2 = DAT_005a82dc;
  if (DAT_005a82dc == (undefined4 *)0x0) {
    if (DAT_005aaac8 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    draw_classifier_display(DAT_005aaac8);
    unlink_and_release_world_object_node_refcounted(pvVar1,s_chnkmgr_004fe71c);
    puVar2 = DAT_005a82dc;
    if (DAT_005a82dc == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
  }
  DAT_005a82dc = (undefined4 *)puVar2[0x10];
  puVar2[0x10] = 0;
  effect_target_list_scan_context_helper_004382e0(puVar2);
  fVar3 = get_network_or_session_runtime_seconds();
  puVar2[0xf] = (float)(fVar3 - (float10)_DAT_004beaa0);
  return puVar2;
}


