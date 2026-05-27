/*
 * Program: i76.exe
 * Function: registered_resource_payload_size_context_helper
 * Entry: 004b32f0
 * Signature: undefined __cdecl registered_resource_payload_size_context_helper(char * param_1, SIZE_T * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: registered resource payload size
   context helper based on adjacent named subsystem context.
   
   I76 rename v43: registered_resource_payload_size_context_helper
   Registered resource payload-size helper/context. */

void __cdecl registered_resource_payload_size_context_helper(char *param_1,SIZE_T *param_2)

{
  load_registered_resource_payload(param_1,param_2,(uint *)0x0,0);
  return;
}


