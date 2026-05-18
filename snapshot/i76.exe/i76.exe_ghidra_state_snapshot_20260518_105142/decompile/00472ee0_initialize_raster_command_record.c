/*
 * Program: i76.exe
 * Function: initialize_raster_command_record
 * Entry: 00472ee0
 * Signature: undefined __thiscall initialize_raster_command_record(void * this, undefined4 param_1, int param_2, undefined4 param_3)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Initializes a 0x60-ish
   software raster command record with callback, control/mode, span-list fields, and default
   sentinel values. */

void __thiscall
initialize_raster_command_record(void *this,undefined4 param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)this = param_1;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x28) = 0xffffffff;
  *(undefined4 *)((int)this + 0x2c) = 0;
  DAT_0058dac0 = DAT_0058dac0 + 4;
  *(int *)((int)this + 0x34) = param_2 + DAT_0058dac0;
  return;
}


