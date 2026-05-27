/*
 * Program: i76.exe
 * Function: read_zfsf_record_allocated_payload
 * Entry: 004b9db0
 * Signature: undefined __cdecl read_zfsf_record_allocated_payload(undefined4 * param_1, char * param_2, SIZE_T * param_3)
 */


/* [i76 level/static/material baseline v48]
   name: read_zfsf_record_allocated_payload
   confidence: high
   module: resource_zfs
   Allocated ZFSF payload reader. Cross-reference for standalone embedded resource extraction.
   note: Name already matches baseline. */

void __cdecl read_zfsf_record_allocated_payload(undefined4 *param_1,char *param_2,SIZE_T *param_3)

{
                    /* I76 semantic baseline: read_zfsf_record_allocated_payload
                       Allocates and reads ZFSF record payload. */
  read_zfsf_record_payload(param_1,param_2,param_3,(uint *)0x0,0);
  return;
}


