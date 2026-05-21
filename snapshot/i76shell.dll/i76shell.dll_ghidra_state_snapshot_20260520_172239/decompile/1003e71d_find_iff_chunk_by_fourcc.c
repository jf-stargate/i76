/*
 * Program: i76shell.dll
 * Function: find_iff_chunk_by_fourcc
 * Entry: 1003e71d
 * Signature: short * __cdecl find_iff_chunk_by_fourcc(short * param_1, int param_2)
 */


short * __cdecl find_iff_chunk_by_fourcc(short *param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  short *psVar3;
  short *psVar4;
  bool bVar5;
  
  psVar2 = (short *)(param_2 + 0xc);
  do {
    for (; (char)*psVar2 == '\0'; psVar2 = (short *)((int)psVar2 + 1)) {
    }
    iVar1 = 2;
    bVar5 = false;
    psVar3 = psVar2;
    psVar4 = param_1;
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar5 = *psVar3 == *psVar4;
      psVar3 = psVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (bVar5);
    if (bVar5) {
      return psVar2 + 4;
    }
    psVar2 = (short *)((int)psVar2 + CONCAT11((char)psVar2[3],(char)((ushort)psVar2[3] >> 8)) + 8);
  } while( true );
}


