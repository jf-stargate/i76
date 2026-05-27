/*
 * Program: i76.exe
 * Function: add_world_instance_id_checked
 * Entry: 004ad450
 * Signature: undefined4 __cdecl add_world_instance_id_checked(undefined4 * param_1, int param_2, int param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence non-unique instance id */

undefined4 __cdecl
add_world_instance_id_checked(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  size_t sVar2;
  LPVOID pvVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int local_8;
  int local_4;
  
  if ((int)param_1[3] <= (int)param_1[2]) {
    sVar2 = _msize((void *)param_1[1]);
    pvVar3 = HeapReAlloc((HANDLE)*param_1,8,(LPVOID)param_1[1],sVar2 + 0x1000);
    if (pvVar3 != (LPVOID)0x0) {
      return 0;
    }
    param_1[1] = 0;
    param_1[3] = param_1[3] + 0x100;
  }
  iVar7 = 0;
  if (0 < (int)param_1[2]) {
    iVar8 = 0;
    do {
      iVar4 = is_damage_side_effects_suppressed();
      if (((iVar4 == 0) && (*(int *)(param_1[1] + iVar8) == param_2)) &&
         (((int *)(param_1[1] + iVar8))[1] == param_3)) {
        local_4 = param_3;
        _g_formatted_8char_resource_path_buffer = 0;
        _DAT_005dabb4 = 0;
        _DAT_005dabb8 = 0;
        local_8 = param_2;
        _DAT_005dabbc = 0;
        strncpy(&g_formatted_8char_resource_path_buffer,(char *)&local_8,8);
        iVar7 = _stricmp(&g_formatted_8char_resource_path_buffer,s_null_004c3280);
        if (iVar7 != 0) {
          uVar1 = 0;
          do {
            uVar5 = uVar1;
            (&g_formatted_8char_resource_path_buffer)[uVar5] =
                 (&g_formatted_8char_resource_path_buffer)[uVar5] & 0x7f;
            uVar1 = uVar5 + 1;
          } while (uVar5 + 1 < 8);
          (&DAT_005dabb1)[uVar5] = 0;
        }
        report_error();
        break;
      }
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 0x10;
    } while (iVar7 < (int)param_1[2]);
  }
  piVar6 = (int *)(param_1[2] * 0x10 + param_1[1]);
  *piVar6 = param_2;
  piVar6[1] = param_3;
  *(undefined4 *)(param_1[2] * 0x10 + 8 + param_1[1]) = param_4;
  param_1[2] = param_1[2] + 1;
  return 1;
}


