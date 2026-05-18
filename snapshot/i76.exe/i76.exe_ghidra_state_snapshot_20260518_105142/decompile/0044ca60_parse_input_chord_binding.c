/*
 * Program: i76.exe
 * Function: parse_input_chord_binding
 * Entry: 0044ca60
 * Signature: bool __cdecl parse_input_chord_binding(FILE * param_1, int * param_2, int param_3)
 */


/* i76 second-pass rename
   old_name: FUN_0044ca60
   suggested_name: parse_input_chord_binding
   basis: Parses input.map chord binding syntax and chord-too-big diagnostics. */

bool __cdecl parse_input_chord_binding(FILE *param_1,int *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char local_16a [2];
  int local_168;
  char local_164 [20];
  char local_150 [80];
  char local_100 [256];
  
  iVar6 = 0;
  *param_2 = 0;
  do {
    local_168 = 0;
    do {
      pcVar3 = fgets(local_100,0xff,param_1);
      if (pcVar3 == (char *)0x0) goto LAB_0044cc65;
      DAT_00536834 = DAT_00536834 + 1;
      pcVar3 = local_100;
      cVar2 = local_100[0];
      while (cVar2 != '\0') {
        cVar2 = *pcVar3;
        if ((cVar2 == '\n') || (cVar2 == '#')) {
          *pcVar3 = '\0';
          break;
        }
        if (*(int *)__mb_cur_max_exref < 2) {
          uVar4 = *(byte *)(*(int *)_pctype_exref + cVar2 * 2) & 8;
        }
        else {
          uVar4 = _isctype((int)cVar2,8);
        }
        if (uVar4 == 0) {
          local_168 = 1;
        }
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar2 = *pcVar1;
      }
    } while (local_168 == 0);
    if (local_100[0] == '}') {
LAB_0044cc65:
      return iVar6 != -1;
    }
    iVar6 = sscanf(local_100,s__1______s__s_004f4ad4,local_16a,local_150,local_164);
    if (iVar6 != 3) {
      report_chunk_parse_error();
      return false;
    }
    if (7 < *param_2) {
      report_chunk_parse_error();
      return false;
    }
    iVar5 = 0;
    if (0 < g_input_device_context_count) {
      pcVar3 = (char *)&DAT_0053da68;
      do {
        iVar6 = _stricmp(pcVar3,local_150);
        if (iVar6 == 0) {
          if ((&DAT_0053da50)[iVar5] == 0) {
            iVar5 = -1;
          }
          goto LAB_0044cb9e;
        }
        iVar5 = iVar5 + 1;
        pcVar3 = pcVar3 + 0x28;
      } while (iVar5 < g_input_device_context_count);
    }
    iVar5 = validate_input_device(local_150);
LAB_0044cb9e:
    iVar6 = resolve_discrete_input_channel(iVar5,local_164);
    if (iVar6 != -1) {
      *(uint *)(param_3 + 8 + *param_2 * 0xc) = (uint)(local_16a[0] == '-');
      *(undefined **)(param_3 + *param_2 * 0xc) = &DAT_00536608 + ((iVar6 >> 5) + iVar5 * 0x14) * 4;
      *(int *)(param_3 + 4 + *param_2 * 0xc) = 1 << ((byte)iVar6 & 0x1f);
      *param_2 = *param_2 + 1;
    }
  } while( true );
}


