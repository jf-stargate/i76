/*
 * Program: i76.exe
 * Function: parse_world_object_placement_record
 * Entry: 00469b00
 * Signature: undefined __cdecl parse_world_object_placement_record(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: sscanf pattern for world object placement */

void __cdecl parse_world_object_placement_record(char *param_1)

{
  char cVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  size_t _Count;
  char *pcVar7;
  undefined4 local_cc;
  char local_c8 [200];
  
  local_cc._0_3_ = CONCAT12(DAT_004f150a,DAT_004f1508);
  puVar2 = open_resource_file_into_memory(param_1);
  DAT_0058d900 = 0;
  if (puVar2 != (uint *)0x0) {
    DAT_00588df8 = puVar2;
    puVar2 = (uint *)strpbrk((char *)puVar2,(char *)&local_cc);
    pcVar7 = local_c8;
    for (iVar4 = 0x32; iVar4 != 0; iVar4 = iVar4 + -1) {
      pcVar7[0] = '\0';
      pcVar7[1] = '\0';
      pcVar7[2] = '\0';
      pcVar7[3] = '\0';
      pcVar7 = pcVar7 + 4;
    }
    if ((0 < (int)puVar2 - (int)DAT_00588df8) && (DAT_00588df8 != (uint *)0x0)) {
      strncpy(local_c8,(char *)DAT_00588df8,(int)puVar2 - (int)DAT_00588df8);
    }
    puVar3 = local_cc;
    DAT_00588df8 = puVar2;
    if (puVar2 != (uint *)0x0) {
      do {
        iVar4 = -1;
        uVar6 = 0;
        pcVar7 = (char *)&local_cc;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        DAT_00588df8 = puVar2;
        if (iVar4 == -2) break;
        while ((char)*puVar2 != local_c8[uVar6 - 4]) {
          uVar5 = 0xffffffff;
          uVar6 = uVar6 + 1;
          pcVar7 = (char *)&local_cc;
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          if (~uVar5 - 1 <= uVar6) goto LAB_00469bcc;
        }
        puVar2 = (uint *)((int)puVar2 + 1);
      } while( true );
    }
LAB_00469bcc:
    if (local_c8[0] != '\0') {
      iVar4 = _strnicmp(local_c8,s___004f2710,1);
      if (iVar4 != 0) {
        iVar4 = DAT_0058d900 * 0x60;
        sscanf(local_c8,s_____d__d__d__s__s__s__f__s__f__s_004f8652 + 2,
               &DAT_00588e00 + DAT_0058d900 * 0x18,&DAT_00588e04 + iVar4,&DAT_00588e08 + iVar4,
               &DAT_00588e0c + iVar4,&DAT_00588e19 + iVar4,&DAT_00588e26 + iVar4,
               &DAT_00588e34 + iVar4,&DAT_00588e38 + iVar4,&DAT_00588e48 + iVar4,
               &DAT_00588e4c + iVar4,&DAT_00588e5c + iVar4);
        DAT_0058d900 = DAT_0058d900 + 1;
      }
      _Count = 0xffffffff;
      if (DAT_00588df8 != (uint *)0x0) {
        puVar3 = (uint *)strpbrk((char *)DAT_00588df8,(char *)&local_cc);
        _Count = (int)puVar3 - (int)DAT_00588df8;
      }
      pcVar7 = local_c8;
      for (iVar4 = 0x32; iVar4 != 0; iVar4 = iVar4 + -1) {
        pcVar7[0] = '\0';
        pcVar7[1] = '\0';
        pcVar7[2] = '\0';
        pcVar7[3] = '\0';
        pcVar7 = pcVar7 + 4;
      }
      if ((0 < (int)_Count) && (DAT_00588df8 != (uint *)0x0)) {
        strncpy(local_c8,(char *)DAT_00588df8,_Count);
      }
      DAT_00588df8 = puVar3;
      if (puVar3 != (uint *)0x0) {
        do {
          iVar4 = -1;
          uVar6 = 0;
          pcVar7 = (char *)&local_cc;
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          if (iVar4 == -2) break;
          while ((char)*DAT_00588df8 != local_c8[uVar6 - 4]) {
            uVar5 = 0xffffffff;
            uVar6 = uVar6 + 1;
            pcVar7 = (char *)&local_cc;
            do {
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            if (~uVar5 - 1 <= uVar6) goto LAB_00469bcc;
          }
          DAT_00588df8 = (uint *)((int)DAT_00588df8 + 1);
        } while( true );
      }
      goto LAB_00469bcc;
    }
    release_resource_file_reference(param_1);
  }
  return;
}


