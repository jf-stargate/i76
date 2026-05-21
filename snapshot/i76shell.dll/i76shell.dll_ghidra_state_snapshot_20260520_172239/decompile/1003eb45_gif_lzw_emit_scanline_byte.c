/*
 * Program: i76shell.dll
 * Function: gif_lzw_emit_scanline_byte
 * Entry: 1003eb45
 * Signature: undefined __stdcall gif_lzw_emit_scanline_byte(void)
 */


void gif_lzw_emit_scanline_byte(void)

{
  undefined1 in_AL;
  int unaff_EDI;
  
  (&DAT_1004db25)[*(int *)(unaff_EDI + 8)] = in_AL;
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 1;
  *(int *)(unaff_EDI + 0x20) = *(int *)(unaff_EDI + 0x20) + -1;
  if (*(int *)(unaff_EDI + 0x20) == 0) {
    write_decoded_image_scanline_to_shell_surface
              (DAT_1004ee38,*(int *)(unaff_EDI + 0xc),(undefined4 *)&DAT_1004db25,
               *(undefined1 **)(unaff_EDI + 0x24));
    *(undefined4 *)(unaff_EDI + 8) = 0;
    *(undefined4 *)(unaff_EDI + 0x20) = *(undefined4 *)(unaff_EDI + 0x24);
    if (*(char *)(unaff_EDI + 0x2c) == '\0') {
      *(int *)(unaff_EDI + 0xc) = *(int *)(unaff_EDI + 0xc) + 1;
      if (*(int *)(unaff_EDI + 0x28) <= *(int *)(unaff_EDI + 0xc)) {
        *(undefined4 *)(unaff_EDI + 0xc) = 0;
      }
    }
    else {
      *(int *)(unaff_EDI + 0xc) =
           *(int *)(unaff_EDI + 0xc) + (uint)(byte)(&DAT_1004ee2e)[*(byte *)(unaff_EDI + 0x2d)];
      if (*(int *)(unaff_EDI + 0x28) <= *(int *)(unaff_EDI + 0xc)) {
        *(char *)(unaff_EDI + 0x2d) = *(char *)(unaff_EDI + 0x2d) + '\x01';
        *(uint *)(unaff_EDI + 0xc) = (uint)*(byte *)(*(byte *)(unaff_EDI + 0x2d) + 0x1004ee33);
      }
    }
  }
  return;
}


