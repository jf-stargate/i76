/*
 * Program: i76.exe
 * Function: get_active_cdrom_drive_letter
 * Entry: 00470d30
 * Signature: undefined1 __stdcall get_active_cdrom_drive_letter(void)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=medium-high] Returns/formats active drive
   letter used when resource paths are remapped to CD drive paths. */

undefined1 get_active_cdrom_drive_letter(void)

{
  return DAT_0058d92c;
}


