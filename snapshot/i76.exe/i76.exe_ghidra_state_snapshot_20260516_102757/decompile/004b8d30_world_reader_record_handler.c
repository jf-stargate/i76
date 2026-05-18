/*
 * Program: i76.exe
 * Function: world_reader_record_handler
 * Entry: 004b8d30
 * Signature: undefined4 __cdecl world_reader_record_handler(byte * param_1, undefined4 param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence wrldr */

undefined4 __cdecl world_reader_record_handler(byte *param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  int local_40 [4];
  LPVOID local_30;
  uint local_2c;
  uint local_14;
  uint local_10;
  uint local_c;
  
  piVar1 = local_40;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
  }
  local_40[0] = param_3;
  local_40[1] = param_2;
  bVar2 = parse_bwd2_resource_with_descriptor_table(param_1,&DAT_00500d50,3,(byte *)local_40);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    if (local_40[0] != 0) {
      muzzle_flash_log_tag(local_40[2],local_40[3],local_40[0],local_14,local_2c);
      return 1;
    }
    if (local_30 != (LPVOID)0x0) {
      iVar3 = effect_resource_xdf_context_helper_0049e970
                        (local_40[2],local_40[3],(uint)local_30,local_14,local_2c,local_10,local_c);
      if (iVar3 == 0) {
        draw_classifier_display(local_30);
        unlink_and_release_world_object_node_refcounted(local_30,s_wrldr_004ffd3c);
      }
    }
  }
  return 1;
}


