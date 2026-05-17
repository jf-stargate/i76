/*
 * Program: i76.exe
 * Function: update_window_client_screen_metrics
 * Entry: 00433d10
 * Signature: undefined __cdecl update_window_client_screen_metrics(HWND param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Updates client rectangle dimensions and screen origin for windowed mode, or uses
   fullscreen dimensions directly. */

void __cdecl update_window_client_screen_metrics(HWND param_1)

{
  tagRECT local_10;
  
  if (DAT_00608410 == 0) {
    _DAT_00608430 = 0;
    _DAT_0060842c = 0;
    ClientToScreen(param_1,(LPPOINT)&DAT_0060842c);
    GetClientRect(param_1,&local_10);
    DAT_00608424 = local_10.right;
    DAT_00608428 = local_10.bottom;
    return;
  }
  _DAT_00608430 = 0;
  _DAT_0060842c = 0;
  DAT_00608424 = DAT_00608400;
  DAT_00608428 = DAT_00608404;
  return;
}


