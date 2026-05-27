/*
 * Program: i76.exe
 * Function: bind_vtfc_six_face_map_slots
 * Entry: 004b0190
 * Signature: undefined4 __cdecl bind_vtfc_six_face_map_slots(uint param_1, char * param_2, byte * param_3)
 */


/* [i76 level/static/material baseline v48]
   name: bind_vtfc_six_face_map_slots
   confidence: high
   module: material_vtfc
   Binds VTFC six-face MAP slots. Static material path differs but reuses embedded resource naming
   patterns.
   note: Name already matches baseline. */

undefined4 __cdecl bind_vtfc_six_face_map_slots(uint param_1,char *param_2,byte *param_3)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte *_Str1;
  char **ppcVar6;
  byte *pbVar7;
  char *pcVar8;
  char *pcVar9;
  byte *pbVar10;
  byte local_28 [16];
  char *local_18 [4];
  char *local_8;
  char *local_4;
  
  _Str1 = param_3;
  local_18[0] = &DAT_004ffe2c;
  local_18[1] = s_BK_map_004ffe24;
  local_18[2] = s_RT_map_004ffe1c;
  local_18[3] = s_LF_map_004ffe14;
  local_8 = s_TP_map_004ffe0c;
  local_4 = s_UN_map_004ffe04;
  param_3 = (byte *)0x0;
  ppcVar6 = local_18;
  do {
    iVar3 = _strnicmp((char *)_Str1,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar4 = 0xffffffff;
      pcVar8 = param_2;
      do {
        pcVar9 = pcVar8;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pbVar7 = (byte *)(pcVar9 + -uVar4);
      pbVar10 = local_28;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar10 = pbVar10 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pbVar10 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar10 = pbVar10 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar8 = *ppcVar6;
      do {
        pcVar9 = pcVar8;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pbVar7 = local_28;
      do {
        pbVar10 = pbVar7;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar10 = pbVar7 + 1;
        bVar2 = *pbVar7;
        pbVar7 = pbVar10;
      } while (bVar2 != 0);
      pbVar7 = (byte *)(pcVar9 + -uVar4);
      pbVar10 = pbVar10 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar10 = pbVar10 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pbVar10 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar10 = pbVar10 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(param_1,local_28,_Str1);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar6 = ppcVar6 + 1;
    param_3 = param_3 + 1;
    _Str1 = _Str1 + 0xd;
    if (5 < (int)param_3) {
      return 1;
    }
  } while( true );
}


