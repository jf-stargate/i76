/*
 * Program: i76.exe
 * Function: set_directdraw_error_message
 * Entry: 00433d90
 * Signature: undefined __cdecl set_directdraw_error_message(LPCSTR param_1)
 */


void __cdecl set_directdraw_error_message(LPCSTR param_1)

{
  CHAR local_100 [256];
  
  local_100[0] = '\0';
  wvsprintfA(local_100,param_1,&stack0x00000008);
  lstrcatA(local_100,(LPCSTR)&DAT_004f1508);
  lstrcpyA((LPSTR)&DAT_005fdb00,local_100);
  return;
}


