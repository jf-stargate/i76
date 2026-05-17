/*
 * Program: i76.exe
 * Function: check_i76_cd2_volume_available
 * Entry: 00470ed0
 * Signature: int __stdcall check_i76_cd2_volume_available(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence I76_CD2 */

int check_i76_cd2_volume_available(void)

{
  char cVar1;
  bool bVar2;
  BOOL BVar3;
  int iVar4;
  uint uVar5;
  char *_Str1;
  int iVar6;
  char *pcVar7;
  DWORD local_4c;
  DWORD local_48;
  DWORD local_44;
  char local_40;
  undefined3 uStack_3f;
  CHAR local_20 [32];
  
  iVar6 = 0;
  bVar2 = false;
  DAT_0058d930 = 0;
  do {
    if (bVar2) {
      return DAT_0058d930;
    }
    if ((&DAT_00609520)[iVar6] != '\0') {
      _local_40 = CONCAT31((int3)((uint)PTR_DAT_004f8bac >> 8),(char)iVar6 + 'A');
      DAT_0058d930 = DAT_0058d930 + 1;
      BVar3 = GetVolumeInformationA
                        (&local_40,&DAT_00609540,0x20,&local_44,&local_48,&local_4c,local_20,0x20);
      _Str1 = (char *)(-(uint)(BVar3 != 0) & 0x609540);
      if (_Str1 != (char *)0x0) {
        uVar5 = 0xffffffff;
        pcVar7 = s_I76_CD2_004f8bdc;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        iVar4 = _strnicmp(_Str1,s_I76_CD2_004f8bdc,~uVar5 - 1);
        if (iVar4 == 0) {
          bVar2 = true;
        }
      }
    }
    iVar6 = iVar6 + 1;
    if (0x19 < iVar6) {
      return DAT_0058d930;
    }
  } while( true );
}


