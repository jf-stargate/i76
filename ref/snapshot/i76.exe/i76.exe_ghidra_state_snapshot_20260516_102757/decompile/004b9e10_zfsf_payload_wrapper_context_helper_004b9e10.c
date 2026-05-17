/*
 * Program: i76.exe
 * Function: zfsf_payload_wrapper_context_helper_004b9e10
 * Entry: 004b9e10
 * Signature: bool __cdecl zfsf_payload_wrapper_context_helper_004b9e10(char * param_1, char * param_2)
 */


/* cgpt label refinement v20: was zfsf_record_payload_wrapper_context_helper_004b9e10. Shorten
   readability label. */

bool __cdecl zfsf_payload_wrapper_context_helper_004b9e10(char *param_1,char *param_2)

{
  uint uVar1;
  
  if (((*param_2 == '?') || (*param_2 == '*')) && (*param_1 == '.')) {
    return false;
  }
  uVar1 = zfsf_payload_wrapper_context_helper_004b9e40(param_1,param_2);
  return (bool)('\x01' - (uVar1 != 1));
}


