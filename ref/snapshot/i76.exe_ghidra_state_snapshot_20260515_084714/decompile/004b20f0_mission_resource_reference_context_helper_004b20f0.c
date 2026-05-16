/*
 * Program: i76.exe
 * Function: mission_resource_reference_context_helper_004b20f0
 * Entry: 004b20f0
 * Signature: undefined4 __cdecl mission_resource_reference_context_helper_004b20f0(char * param_1, int param_2, FILE * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: mission resource reference context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl
mission_resource_reference_context_helper_004b20f0(char *param_1,int param_2,FILE *param_3)

{
  char *pcVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char local_100 [256];
  
  bVar2 = false;
  bVar3 = true;
  do {
    pcVar5 = fgets(local_100,param_2,param_3);
    if (pcVar5 == (char *)0x0) {
      return 0;
    }
    pcVar5 = local_100;
    pcVar8 = param_1;
    cVar4 = local_100[0];
    while (cVar4 != '\0') {
      cVar4 = *pcVar5;
      if (cVar4 == '\'') {
        bVar3 = !bVar3;
      }
      if ((cVar4 == '\n') || (cVar4 == '#')) {
        *pcVar5 = '\0';
        break;
      }
      if (bVar2) {
        if (bVar3) {
          iVar7 = tolower((int)cVar4);
          cVar4 = (char)iVar7;
        }
        *pcVar8 = cVar4;
        pcVar8 = pcVar8 + 1;
      }
      else {
        if (*(int *)__mb_cur_max_exref < 2) {
          uVar6 = *(byte *)(*(int *)_pctype_exref + cVar4 * 2) & 8;
        }
        else {
          uVar6 = _isctype((int)cVar4,8);
        }
        if (uVar6 == 0) {
          if (bVar3) {
            iVar7 = tolower((int)*pcVar5);
            *pcVar8 = (char)iVar7;
            pcVar8 = pcVar8 + 1;
            bVar2 = true;
          }
          else {
            bVar2 = true;
            *pcVar8 = *pcVar5;
            pcVar8 = pcVar8 + 1;
          }
        }
      }
      pcVar1 = pcVar5 + 1;
      pcVar5 = pcVar5 + 1;
      cVar4 = *pcVar1;
    }
    if (bVar2) {
      *pcVar8 = '\0';
      return 1;
    }
  } while( true );
}


