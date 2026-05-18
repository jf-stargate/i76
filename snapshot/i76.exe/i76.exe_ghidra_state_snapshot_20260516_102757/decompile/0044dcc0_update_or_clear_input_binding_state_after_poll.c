/*
 * Program: i76.exe
 * Function: update_or_clear_input_binding_state_after_poll
 * Entry: 0044dcc0
 * Signature: undefined __stdcall update_or_clear_input_binding_state_after_poll(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: likely input_device_binding /
   input_action_state_helper based on address neighborhood and prior focused closure context. */

void update_or_clear_input_binding_state_after_poll(void)

{
  int iVar1;
  undefined4 *puVar2;
  bool bVar3;
  
                    /* I76 semantic baseline: update_or_clear_input_binding_state_after_poll
                       Input binding state cleanup/update helper after polling. */
  if (g_input_device_context_count != 0) {
    puVar2 = &DAT_00536380 + (g_input_device_context_count + -1) * 0x1d;
    iVar1 = g_input_device_context_count + -1;
    do {
      if ((&DAT_0053da50)[iVar1] != 0) {
        (**(code **)((&g_input_device_callback_table)[iVar1] + 0xc))(puVar2);
      }
      puVar2 = puVar2 + -0x1d;
      bVar3 = iVar1 != 0;
      iVar1 = iVar1 + -1;
    } while (bVar3);
  }
  puVar2 = &DAT_00536770;
  for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)&g_pending_input_action_code;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_00536808 = 0;
  DAT_0053da50 = 0;
  _DAT_0053680c = 0;
  DAT_0053da54 = 0;
  _DAT_00536810 = 0;
  _DAT_0053da58 = 0;
  _DAT_00536814 = 0;
  puVar2 = &DAT_005365c8;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00536838;
  for (iVar1 = 0xc80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &g_runtime_axis_input_binding_table;
  for (iVar1 = 0x514; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_0053ae88;
  for (iVar1 = 0xaf0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_0053da68;
  for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_input_device_callback_table = 0;
  DAT_0053675c = 0;
  _DAT_00536760 = 0;
  _DAT_0053da5c = 0;
  _DAT_00536764 = 0;
  g_input_axis_binding_count = 0;
  puVar2 = &DAT_00536380;
  for (iVar1 = 0x91; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_runtime_axis_input_binding_count = 0;
  g_input_condition_binding_count = 0;
  DAT_0053682c = 0;
  _DAT_00536830 = 0;
  DAT_00536834 = 0;
  g_input_device_context_count = 0;
  DAT_004f2848 = 1;
  _DAT_0053da60 = 0;
  _DAT_00536768 = 0;
  PTR_PTR_004f2850 = (undefined *)&PTR_world_transform_projection_context_helper_0048dc50_004f5208;
  PTR_PTR_004f2854 = (undefined *)&PTR_world_transform_projection_context_helper_0048dc50_004f2760;
  PTR_PTR_004f2858 = (undefined *)&PTR_LAB_004f53f8;
  return;
}


