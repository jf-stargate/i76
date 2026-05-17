/*
 * Program: i76.exe
 * Function: lzo_init_embedded_library
 * Entry: 004ba980
 * Signature: int __cdecl lzo_init_embedded_library(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe LZO1Y labels v24; confidence=high] Embedded LZO 1.00 initialization wrapper called
   once by the ZFSF decompression dispatcher. */

int __cdecl
lzo_init_embedded_library
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
          int param_8)

{
  bool bVar1;
  int iVar2;
  
  _DAT_005dbabc = 1;
  if (param_1 == 0) {
    return -1;
  }
  if ((((param_2 == 2) && (param_3 == 4)) && (param_4 == 4)) &&
     (((param_5 == 4 && (param_6 == 4)) && ((param_7 == 4 && (param_8 == 4)))))) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (!bVar1) {
    return -1;
  }
  iVar2 = lzo_runtime_config_selftest();
  return iVar2;
}


