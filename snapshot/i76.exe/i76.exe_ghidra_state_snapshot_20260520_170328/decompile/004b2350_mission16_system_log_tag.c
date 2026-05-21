/*
 * Program: i76.exe
 * Function: mission16_system_log_tag
 * Entry: 004b2350
 * Signature: undefined4 __cdecl mission16_system_log_tag(undefined4 * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence miss16 */

undefined4 __cdecl mission16_system_log_tag(undefined4 *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  bVar1 = is_miss16_high_color_resource_mode();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = init_registry_install_settings();
    *param_1 = DAT_004fff58;
    *(undefined2 *)(param_1 + 1) = DAT_004fff5c;
    if (CONCAT31(extraout_var_01,bVar1) != 0) {
      return 1;
    }
    return 0;
  }
  bVar1 = init_registry_install_settings();
  if (CONCAT31(extraout_var_00,bVar1) != 0) {
    *param_1 = s_miss16_004fff7c._0_4_;
    *(undefined2 *)(param_1 + 1) = s_miss16_004fff7c._4_2_;
    *(char *)((int)param_1 + 6) = s_miss16_004fff7c[6];
    return 1;
  }
  *param_1 = s_miss16_004fff7c._0_4_;
  *(undefined2 *)(param_1 + 1) = s_miss16_004fff7c._4_2_;
  *(char *)((int)param_1 + 6) = s_miss16_004fff7c[6];
  return 0;
}


