/*
 * Program: i76.exe
 * Function: load_registered_resource_payload_bool
 * Entry: 004b3000
 * Signature: bool __cdecl load_registered_resource_payload_bool(char * param_1, SIZE_T * param_2, uint * param_3, int param_4)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Boolean wrapper around
   load_registered_resource_payload.
   
   I76 rename v43: load_registered_resource_payload_bool
   Boolean wrapper around registered resource payload loading. */

bool __cdecl
load_registered_resource_payload_bool(char *param_1,SIZE_T *param_2,uint *param_3,int param_4)

{
  uint *puVar1;
  
  puVar1 = load_registered_resource_payload(param_1,param_2,param_3,param_4);
  return puVar1 != (uint *)0x0;
}


