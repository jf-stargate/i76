/*
 * Program: i76.exe
 * Function: validate_mission_revision_chunks
 * Entry: 004b4610
 * Signature: undefined4 __cdecl validate_mission_revision_chunks(int * param_1, char * param_2)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Validates mission revision/mandatory
   chunk tags; reports unknown revision chunks or missing mandatory chunks.
   
   I76 rename v43: validate_mission_revision_chunks
   Revision chunk validator used for WREV/RREV/OREV/etc. */

undefined4 __cdecl validate_mission_revision_chunks(int *param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined **ppuVar4;
  int iVar5;
  undefined4 local_304;
  char local_300 [4];
  undefined1 local_2fc;
  char local_200 [256];
  char local_100 [256];
  
  iVar5 = 0;
  pcVar3 = &g_mission_revision_required_chunk_table;
  do {
    uVar1 = *(undefined4 *)pcVar3;
    local_304._3_1_ = (undefined1)((uint)uVar1 >> 0x18);
    local_304 = uVar1;
    if (CONCAT22(CONCAT11(*pcVar3,(char)((uint)uVar1 >> 8)),
                 CONCAT11((char)((uint)uVar1 >> 0x10),local_304._3_1_)) == *param_1) {
      if (iVar5 != 0) {
        if (param_1[2] == *(int *)(iVar5 * 8 + 0x50043c)) {
          return 1;
        }
        strncpy(local_300,(char *)param_1,4);
        local_2fc = 0;
        report_error();
        return 0;
      }
      _splitpath(param_2,(char *)&local_304,local_300,local_100,local_200);
      ppuVar4 = &g_mission_revision_extension_table;
      iVar5 = 0;
      do {
        iVar2 = _stricmp(*ppuVar4,local_200);
        if (iVar2 == 0) {
          if (param_1[2] == *(int *)(iVar5 * 8 + 0x5003bc)) {
            return 1;
          }
          report_error();
          return 0;
        }
        ppuVar4 = ppuVar4 + 2;
        iVar5 = iVar5 + 1;
      } while (ppuVar4 < &g_mission_revision_required_chunk_table);
      report_error();
      return 1;
    }
    pcVar3 = pcVar3 + 8;
    iVar5 = iVar5 + 1;
  } while (pcVar3 < s_Error___mandatory__s_chunk_not_f_00500470);
  strncpy(local_300,(char *)param_1,4);
  report_error();
  return 1;
}


