/*
 * Program: i76shell.dll
 * Function: install_shell_palette_from_rgb_triplets
 * Entry: 10022900
 * Signature: undefined4 __cdecl install_shell_palette_from_rgb_triplets(int param_1)
 */


undefined4 __cdecl install_shell_palette_from_rgb_triplets(int param_1)

{
  byte *pbVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    pbVar1 = (byte *)(param_1 + iVar2);
    *(undefined2 *)(&DAT_100f64c0 + iVar2) = *(undefined2 *)pbVar1;
    (&DAT_100f64c2)[iVar2] = pbVar1[2];
    convert_shell_palette_entry_via_channel_table(pbVar1,(undefined1 *)((int)&DAT_100533f0 + iVar2))
    ;
    iVar2 = iVar2 + 3;
  } while (iVar2 < 0x300);
  set_shell_gdi_palette_entries_from_rgb6(0,0x100,&DAT_100533f0);
  DAT_100f60c4 = BitBlt(DAT_100d3120,0,0,DAT_100f700c,DAT_100f7010,DAT_100d352c,0,0,0xcc0020);
  if (DAT_100f60c4 == 0) {
    GetLastError();
    log_or_report_shell_ddraw_error_candidate(s_GDI_StretchBlt_err___d_1004af24);
  }
  *DAT_100533e8 = DAT_100536f0;
  return 0;
}


