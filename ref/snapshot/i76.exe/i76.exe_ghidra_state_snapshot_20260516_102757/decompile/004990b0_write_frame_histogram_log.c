/*
 * Program: i76.exe
 * Function: write_frame_histogram_log
 * Entry: 004990b0
 * Signature: undefined __stdcall write_frame_histogram_log(void)
 */


/* i76 second-pass rename
   old_name: FUN_004990b0
   suggested_name: write_frame_histogram_log
   basis: Writes histogram.txt and frame-rate header. */

void write_frame_histogram_log(void)

{
  FILE *_File;
  undefined4 *puVar1;
  
  _File = fopen(s_histogram_txt_004fde7c,s_w_004c2298);
  fprintf(_File,s_FrameRate_004fde6c);
  puVar1 = &DAT_005a6af8;
  do {
    fprintf(_File,s__5d_004fde64,*puVar1);
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < 0x5a6c38);
  fclose(_File);
  return;
}


