/*
 * Program: i76.exe
 * Function: read_zfsf_record_to_buffer_bool
 * Entry: 004b9ba0
 * Signature: bool __cdecl read_zfsf_record_to_buffer_bool(undefined4 * param_1, char * param_2, SIZE_T * param_3, uint * param_4, int param_5)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Public ZFSF read wrapper that looks up a
   record and decodes it into a caller-provided buffer, returning success/failure. */

bool __cdecl
read_zfsf_record_to_buffer_bool
          (undefined4 *param_1,char *param_2,SIZE_T *param_3,uint *param_4,int param_5)

{
  uint *puVar1;
  
  puVar1 = read_zfsf_record_payload(param_1,param_2,param_3,param_4,param_5);
  return puVar1 != (uint *)0x0;
}


