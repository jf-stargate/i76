/*
 * Program: i76.exe
 * Function: read_zfsf_record_allocated_payload
 * Entry: 004b9db0
 * Signature: undefined __cdecl read_zfsf_record_allocated_payload(undefined4 * param_1, char * param_2, SIZE_T * param_3)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Allocating ZFSF read wrapper. Allocates
   logical output size for a named record, then calls read_zfsf_record_payload. */

void __cdecl read_zfsf_record_allocated_payload(undefined4 *param_1,char *param_2,SIZE_T *param_3)

{
                    /* I76 semantic baseline: read_zfsf_record_allocated_payload
                       Allocates and reads ZFSF record payload. */
  read_zfsf_record_payload(param_1,param_2,param_3,(uint *)0x0,0);
  return;
}


