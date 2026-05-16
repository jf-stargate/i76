/*
 * Program: i76.exe
 * Function: log_video_texture_memory
 * Entry: 0042fac0
 * Signature: undefined __stdcall log_video_texture_memory(void)
 */


/* i76 second-pass rename
   old_name: FUN_0042fac0
   suggested_name: log_video_texture_memory
   basis: Diagnostic string: Video card texture mem holds %d bytes. */

void log_video_texture_memory(void)

{
  int iVar1;
  int *piVar2;
  undefined1 **ppuVar3;
  undefined1 *puVar4;
  undefined4 **ppuVar5;
  undefined4 *puStack_1c;
  int *piStack_18;
  undefined1 *puStack_14;
  undefined1 auStack_10 [4];
  undefined1 local_c [12];
  
  puStack_14 = local_c;
  piStack_18 = (int *)&DAT_004bcd88;
  puStack_1c = DAT_006080b8;
  ppuVar5 = &puStack_1c;
  (**(code **)*DAT_006080b8)();
  puVar4 = auStack_10;
  ppuVar3 = &puStack_14;
  puStack_14 = (undefined1 *)0x1000;
  piVar2 = piStack_18;
  iVar1 = (**(code **)(*piStack_18 + 0x5c))(piStack_18,ppuVar3,puVar4,&puStack_1c);
  DAT_0052b914 = piVar2;
  if (iVar1 != 0) {
    ppuVar5 = (undefined4 **)0x1e8480;
    DAT_0052b914 = (int *)0x1e8480;
  }
  if ((g_resource_debug_log_file != 0) && (g_resource_debug_log_file == DAT_005a7c90)) {
    fprintf((FILE *)DAT_005a7c90,s_Video_card_texture_mem_holds__d_b_004edff4,DAT_0052b914,
            DAT_0052b914,ppuVar3,puVar4,ppuVar5);
  }
  DAT_005280e0 = (uint)((int)DAT_0052b914 < 2400000);
  return;
}


