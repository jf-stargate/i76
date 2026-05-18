/*
 * Program: i76.exe
 * Function: merge_system_log_tag
 * Entry: 0048f840
 * Signature: undefined __cdecl merge_system_log_tag(int * param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence merge */

void __cdecl merge_system_log_tag(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  
  piVar6 = DAT_006543b4;
  iVar1 = *param_1;
  iVar2 = *param_2;
  iVar3 = 0;
  if (0 < DAT_0059c540) {
    puVar5 = &DAT_0059c4a4;
    do {
      if (*(int *)*puVar5 == iVar2) {
        puVar4 = &DAT_0059c4a0 + iVar3 * 8;
        *(undefined4 *)((&DAT_0059c4a4)[iVar3 * 2] + 0xc) = 0;
        goto LAB_0048f886;
      }
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 2;
    } while (iVar3 < DAT_0059c540);
  }
  puVar4 = (undefined *)0x0;
LAB_0048f886:
  if (((puVar4 == (undefined *)0x0) &&
      (((iVar3 = world_object_has_optional_runtime_flag(iVar2), iVar3 == 0 &&
        (iVar3 = world_object_has_optional_runtime_flag(iVar1), iVar3 == 0)) || (DAT_004c2724 == 0))
      )) && (DAT_006543a0 < DAT_0065438c)) {
    for (; (piVar7 = (int *)0x0, piVar6 < DAT_006543a0 && (piVar7 = piVar6, *piVar6 != iVar1));
        piVar6 = piVar6 + 0x24) {
    }
    if (piVar7 == (int *)0x0) {
      *DAT_006543a0 = iVar1;
      DAT_006543a0[1] = (int)param_1;
      DAT_006543a0[3] = 1;
      DAT_006543a0[2] = 1000000;
      DAT_006543a0[4] = iVar2;
      DAT_006543a0[6] = 0;
      piVar7 = DAT_006543a0;
      DAT_006543a0 = DAT_006543a0 + 0x24;
    }
    else {
      if (piVar7[3] == 8) {
        return;
      }
      piVar7[(piVar7[3] + 1) * 4] = iVar2;
      piVar7[piVar7[3] * 4 + 6] = 0;
      piVar7[3] = piVar7[3] + 1;
    }
    if (DAT_0059c540 < 0x14) {
      *(int **)(&DAT_0059c4a0 + DAT_0059c540 * 8) = piVar7;
      (&DAT_0059c4a4)[DAT_0059c540 * 2] = piVar7 + piVar6[3] * 4;
      DAT_0059c540 = DAT_0059c540 + 1;
    }
    increment_refcount_recursive_for_object_tree(iVar2,s_merge_004fad14);
  }
  return;
}


