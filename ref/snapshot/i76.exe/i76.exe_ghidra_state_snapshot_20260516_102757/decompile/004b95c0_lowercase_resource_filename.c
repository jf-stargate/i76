/*
 * Program: i76.exe
 * Function: lowercase_resource_filename
 * Entry: 004b95c0
 * Signature: char * __cdecl lowercase_resource_filename(char * param_1)
 */


/* i76 second-pass rename
   old_name: FUN_004b95c0
   suggested_name: lowercase_resource_filename
   basis: tolower helper used by resource enumeration/registration. */

char * __cdecl lowercase_resource_filename(char *param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  
  cVar2 = *param_1;
  pcVar4 = param_1;
  while (cVar2 != '\0') {
    iVar3 = tolower((int)cVar2);
    *pcVar4 = (char)iVar3;
    pcVar1 = pcVar4 + 1;
    pcVar4 = pcVar4 + 1;
    cVar2 = *pcVar1;
  }
  return param_1;
}


