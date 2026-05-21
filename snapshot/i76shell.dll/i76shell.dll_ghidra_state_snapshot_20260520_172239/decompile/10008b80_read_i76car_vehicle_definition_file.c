/*
 * Program: i76shell.dll
 * Function: read_i76car_vehicle_definition_file
 * Entry: 10008b80
 * Signature: LPVOID __cdecl read_i76car_vehicle_definition_file(size_t * param_1)
 */


LPVOID __cdecl read_i76car_vehicle_definition_file(size_t *param_1)

{
  int iVar1;
  FILE *pFVar2;
  LPVOID _DstBuf;
  int *piVar3;
  int iVar4;
  size_t local_4c;
  size_t local_48;
  LPVOID local_44;
  CHAR local_40 [64];
  
  pFVar2 = fopen(s_i76car_def_10043fa8,s_rb_10043fa4);
  if (pFVar2 == (FILE *)0x0) {
    pFVar2 = fopen(s_i76car_def_10043f98,s_wb_10043f94);
    local_48 = 0x17;
    fwrite(&local_48,4,1,pFVar2);
    local_48 = fwrite(&DAT_10043d10,0x1c,0x17,pFVar2);
    fclose(pFVar2);
    pFVar2 = fopen(s_i76car_def_10043fb8,s_rb_10043fb4);
  }
  fread(&local_4c,4,1,pFVar2);
  _DstBuf = HeapAlloc(DAT_10051c50,1,local_4c * 0x1c);
  if (_DstBuf == (LPVOID)0x0) {
    return (LPVOID)0x0;
  }
  local_44 = _DstBuf;
  fread(_DstBuf,0x1c,local_4c,pFVar2);
  fclose(pFVar2);
  local_48 = 0;
  *param_1 = local_4c;
  if (0 < (int)local_4c) {
    piVar3 = (int *)((int)_DstBuf + 4);
    do {
      iVar4 = piVar3[1];
      iVar1 = iVar4;
      if (iVar4 < *piVar3) {
        do {
          wsprintfA(local_40,s_addon__s_d_vcf_10043fc4,piVar3 + 2,iVar1 + 1);
          pFVar2 = fopen(local_40,s_rb_10043fd4);
          if (pFVar2 == (FILE *)0x0) {
            *piVar3 = iVar4;
            break;
          }
          fclose(pFVar2);
          iVar4 = iVar4 + 1;
          iVar1 = iVar1 + 1;
        } while (iVar4 < *piVar3);
      }
      local_48 = local_48 + 1;
      piVar3 = piVar3 + 7;
      _DstBuf = local_44;
    } while ((int)local_48 < (int)*param_1);
  }
  return _DstBuf;
}


