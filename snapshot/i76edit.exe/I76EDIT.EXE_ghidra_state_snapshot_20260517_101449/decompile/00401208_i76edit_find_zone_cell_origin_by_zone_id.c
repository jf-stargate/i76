/*
 * Program: I76EDIT.EXE
 * Function: i76edit_find_zone_cell_origin_by_zone_id
 * Entry: 00401208
 * Signature: undefined8 __cdecl i76edit_find_zone_cell_origin_by_zone_id(int param_1, int param_2, int param_3)
 */


undefined8 __cdecl i76edit_find_zone_cell_origin_by_zone_id(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = 0;
  iVar3 = 0;
  do {
    iVar2 = 0;
    do {
      if ((char)(&DAT_00439ef0)[iVar2 + iVar1] == param_1) {
        return CONCAT44(iVar3 * 0x80 + param_3,iVar2 * 0x80 + param_2);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x50);
    iVar1 = iVar1 + 0x50;
    iVar3 = iVar3 + 1;
  } while (iVar1 < 0x1900);
  if (iVar3 == 0x50) {
    uStack_8 = 0xffffffff;
    uStack_4 = 0xffffffff;
  }
  return CONCAT44(uStack_4,uStack_8);
}


