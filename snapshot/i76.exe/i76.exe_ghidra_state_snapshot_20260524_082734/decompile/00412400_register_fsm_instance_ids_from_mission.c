/*
 * Program: i76.exe
 * Function: register_fsm_instance_ids_from_mission
 * Entry: 00412400
 * Signature: undefined __cdecl register_fsm_instance_ids_from_mission(byte * param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: instance id duplicate/missing in mission
   file
   
   I76 rename v43: fsm_register_instance_ids_from_mission
   Registers FSM instance IDs from mission data. */

void __cdecl register_fsm_instance_ids_from_mission(byte *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *_Str1;
  bool bVar7;
  int local_4;
  
  local_4 = 0;
  _Str1 = param_1;
  if (0 < param_2) {
    do {
      iVar2 = entity_instance_table_context_helper_00457630
                        (*(int *)(_Str1 + 0x50),*(int *)(_Str1 + 0x54));
      *(int *)(_Str1 + 0x58) = iVar2;
      if (iVar2 == 0) {
        report_error();
      }
      else {
        increment_refcount_recursive_for_object_tree(iVar2,&DAT_004c2a10);
      }
      iVar2 = 0;
      pbVar5 = param_1;
      do {
        if (((local_4 != iVar2) && (*(int *)(_Str1 + 0x50) == *(int *)(pbVar5 + 0x50))) &&
           (pbVar3 = _Str1, pbVar6 = pbVar5, *(int *)(_Str1 + 0x54) == *(int *)(pbVar5 + 0x54))) {
          do {
            bVar1 = *pbVar3;
            bVar7 = bVar1 < *pbVar6;
            if (bVar1 != *pbVar6) {
LAB_00412497:
              iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
              goto LAB_0041249c;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar3[1];
            bVar7 = bVar1 < pbVar6[1];
            if (bVar1 != pbVar6[1]) goto LAB_00412497;
            pbVar3 = pbVar3 + 2;
            pbVar6 = pbVar6 + 2;
          } while (bVar1 != 0);
          iVar4 = 0;
LAB_0041249c:
          if (iVar4 != 0) {
            report_error();
          }
        }
        iVar2 = iVar2 + 1;
        pbVar5 = pbVar5 + 0x60;
      } while (iVar2 < param_2);
      iVar2 = _stricmp((char *)_Str1,s_taurus_004c3320);
      if (iVar2 == 0) {
        set_fsm_registered_instance_count(*(undefined4 *)(_Str1 + 0x58));
      }
      local_4 = local_4 + 1;
      _Str1 = _Str1 + 0x60;
    } while (local_4 < param_2);
  }
  return;
}


