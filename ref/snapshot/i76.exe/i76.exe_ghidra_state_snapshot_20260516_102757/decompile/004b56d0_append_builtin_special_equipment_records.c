/*
 * Program: i76.exe
 * Function: append_builtin_special_equipment_records
 * Entry: 004b56d0
 * Signature: undefined __cdecl append_builtin_special_equipment_records(int param_1)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Appends localized novelty/special
   equipment records: Radar Jammer, NitrousOxide, Blower, X-Aust Brake, Structo Bmpr, Curb Feelers,
   Mud Flaps, Heated Seats, Cup Holders, using spc%02d identifiers. */

void __cdecl append_builtin_special_equipment_records(int param_1)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  undefined **local_4;
  
  PTR_s_Radar_Jammer_005007d8 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Radar_Jammer_0050086c);
  PTR_s_NitrousOxide_005007dc =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_NitrousOxide_0050085c);
  PTR_s_Blower_005007e0 =
       (undefined *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Blower_00500854);
  PTR_s_X_Aust_Brake_005007e4 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_X_Aust_Brake_00500844);
  PTR_s_Structo_Bmpr_005007e8 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Structo_Bmpr_00500834);
  PTR_s_Curb_Feelers_005007ec =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Curb_Feelers_00500824);
  PTR_s_Mud_Flaps_005007f0 =
       (undefined *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Mud_Flaps_00500818)
  ;
  PTR_s_Heated_Seats_005007f4 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Heated_Seats_00500808);
  PTR_s_Cup_Holders_005007f8 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cup_Holders_005007fc);
  iVar6 = 0;
  local_4 = &PTR_s_Radar_Jammer_005007d8;
  do {
    iVar6 = iVar6 + 1;
    sprintf((char *)(param_1 + 0x3b + DAT_005db984 * 0x54),s__s_02d_004ffea0,&PTR_DAT_004ffea8,iVar6
           );
    uVar3 = 0xffffffff;
    pcVar7 = *local_4;
    do {
      pcVar8 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar8 = pcVar7 + 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    pcVar7 = pcVar8 + -uVar3;
    pcVar8 = (char *)(param_1 + DAT_005db984 * 0x54);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 0xd;
    iVar5 = 1;
    do {
      iVar1 = iVar5 + DAT_005db984 * 0x15;
      iVar5 = iVar5 + 1;
      *(undefined4 *)(param_1 + 0x1e + iVar1 * 4) = 0;
    } while (iVar5 < 4);
    local_4 = local_4 + 1;
    DAT_005db984 = DAT_005db984 + 1;
    if ((undefined **)((int)&PTR_s_Cup_Holders_005007f8 + 3) < local_4) {
      return;
    }
  } while( true );
}


