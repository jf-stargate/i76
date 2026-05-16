/*
 * Program: i76.exe
 * Function: zfsf_decompress_record_payload_by_lzo_mode
 * Entry: 004b9fc0
 * Signature: undefined4 __thiscall zfsf_decompress_record_payload_by_lzo_mode(void * this, byte * param_1, int param_2, byte param_3, undefined4 param_4)
 */


/* [cgpt i76.exe LZO1Y labels v24; confidence=high] ZFSF compressed-record wrapper: initializes
   embedded LZO and dispatches compression byte 0x02 to LZO1X, 0x04 to LZO1Y. */

undefined4 __thiscall
zfsf_decompress_record_payload_by_lzo_mode
          (void *this,byte *param_1,int param_2,byte param_3,undefined4 param_4)

{
  int iVar1;
  undefined8 uVar2;
  void *local_4;
  
                    /* I76 semantic baseline: zfsf_decompress_record_payload_by_lzo_mode
                       Dispatches ZFSF LZO1X/LZO1Y decompression by mode. */
  local_4 = this;
  if (g_lzo_library_initialized == 0) {
    iVar1 = lzo_init_embedded_library(0x1000,2,4,4,4,4,4,4);
    if (iVar1 != 0) {
      sprintf(&g_resource_error_message,s_Error__d_during_compression_libr_00500f54);
    }
    g_lzo_library_initialized = (uint)(iVar1 == 0);
    if (g_lzo_library_initialized == 0) {
      return 0;
    }
  }
  if ((param_3 & 2) == 0) {
    if ((param_3 & 4) == 0) {
      return 0;
    }
    uVar2 = lzo1y_decompress_unsafe(param_1,param_4,param_1,param_2,(byte *)param_4,(int *)&local_4)
    ;
    iVar1 = (int)uVar2;
  }
  else {
    uVar2 = lzo1x_decompress_unsafe(param_4,param_2,param_1,param_2,(byte *)param_4,(int *)&local_4)
    ;
    iVar1 = (int)uVar2;
  }
  if (iVar1 == 0) {
    return 1;
  }
  sprintf(&g_resource_error_message,s_Error__d_during_compression_libr_00500f54);
  return 0;
}


