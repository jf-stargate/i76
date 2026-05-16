/*
 * Program: i76.exe
 * Function: bind_chunk_texture_slot_from_material
 * Entry: 004a24a0
 * Signature: undefined4 __cdecl bind_chunk_texture_slot_from_material(uint param_1, int param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: strings 1234567890AB / V1 BO DY */

undefined4 __cdecl bind_chunk_texture_slot_from_material(uint param_1,int param_2,int param_3)

{
  byte *_Src;
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_2;
  _Src = (byte *)(param_2 + 0x20);
  if (*(char *)(param_2 + 0x20) != '\0') {
    iVar4 = -1;
    iVar1 = sscanf((char *)_Src,&DAT_004fe738,&param_2);
    if (iVar1 == 0) {
      iVar1 = strncmp(s_V1_BO_DY_004fe72c,(char *)_Src,8);
      if (iVar1 == 0) {
        iVar4 = 0xc;
      }
    }
    else {
      pcVar2 = strchr(PTR_s_1234567890AB_004fe708,(int)(char)param_2);
      iVar4 = (int)pcVar2 - (int)PTR_s_1234567890AB_004fe708;
    }
    if (-1 < iVar4) {
      bind_texture_resource_to_object_slot(param_1,_Src,(byte *)(iVar4 * 0x10 + param_3));
      return 1;
    }
  }
  if (*(int *)(iVar3 + 0x30) != 0) {
    iVar3 = bind_chunk_texture_slot_from_material(param_1,*(int *)(iVar3 + 0x30),param_3);
    if (iVar3 != 0) {
      return 1;
    }
  }
  return 0;
}


