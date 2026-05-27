/*
 * Program: i76.exe
 * Function: load_project_info_file
 * Entry: 004716b0
 * Signature: undefined4 __cdecl load_project_info_file(char * param_1, char * param_2, size_t param_3)
 */


/* cgpt whole-binary semantic rename v1: references PrjInfo.txt */

undefined4 __cdecl load_project_info_file(char *param_1,char *param_2,size_t param_3)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  char *_Source;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  byte *_Str;
  uint *local_10c;
  undefined4 local_108;
  int local_104;
  byte local_100 [256];
  
  local_108 = 0;
  local_104 = get_loaded_resource_file_size(s_PrjInfo_txt_004f8c8c);
  if (local_104 == 0) {
    return local_108;
  }
  local_10c = open_resource_file_into_memory(s_PrjInfo_txt_004f8c8c);
  if (local_10c == (uint *)0x0) {
    return local_108;
  }
  iVar4 = system_cutscene_memory_context_helper_00499110
                    ((int *)&local_10c,local_100,&local_104,0x100);
  while (iVar4 != 0) {
    _Str = local_100;
    bVar2 = local_100[0];
    while (bVar2 != 0) {
      if (*(int *)__mb_cur_max_exref < 2) {
        uVar5 = *(byte *)(*(int *)_pctype_exref + (char)*_Str * 2) & 8;
      }
      else {
        uVar5 = _isctype((int)(char)*_Str,8);
      }
      if (uVar5 == 0) break;
      pbVar1 = _Str + 1;
      _Str = _Str + 1;
      bVar2 = *pbVar1;
    }
    pcVar6 = strchr((char *)_Str,0x3a);
    if ((pcVar6 != (char *)0x0) &&
       (iVar4 = _strnicmp((char *)_Str,param_1,(int)pcVar6 - (int)_Str), iVar4 == 0)) {
      cVar3 = pcVar6[1];
      goto joined_r0x004717ba;
    }
    iVar4 = system_cutscene_memory_context_helper_00499110
                      ((int *)&local_10c,local_100,&local_104,0x100);
  }
LAB_00471818:
  release_resource_file_reference(s_PrjInfo_txt_004f8c8c);
  return local_108;
joined_r0x004717ba:
  _Source = pcVar6 + 1;
  if (cVar3 == '\0') goto LAB_004717f1;
  if (*(int *)__mb_cur_max_exref < 2) {
    uVar5 = *(byte *)(*(int *)_pctype_exref + cVar3 * 2) & 8;
  }
  else {
    uVar5 = _isctype((int)cVar3,8);
  }
  if (uVar5 == 0) goto LAB_004717f1;
  cVar3 = pcVar6[2];
  pcVar6 = _Source;
  goto joined_r0x004717ba;
LAB_004717f1:
  if (*_Source != '\0') {
    strncpy(param_2,_Source,param_3);
    local_108 = 1;
  }
  goto LAB_00471818;
}


