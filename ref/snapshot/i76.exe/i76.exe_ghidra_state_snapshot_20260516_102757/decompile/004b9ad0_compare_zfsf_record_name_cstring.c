/*
 * Program: i76.exe
 * Function: compare_zfsf_record_name_cstring
 * Entry: 004b9ad0
 * Signature: undefined __cdecl compare_zfsf_record_name_cstring(char * param_1, char * param_2)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Case-insensitive compare between a
   16-byte ZFSF record key/name and a C string, used by binary search over the live record table. */

void __cdecl compare_zfsf_record_name_cstring(char *param_1,char *param_2)

{
  _stricmp(param_1,param_2);
  return;
}


