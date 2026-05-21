/*
 * Program: i76shell.dll
 * Function: construct_shell_surface_context
 * Entry: 10037a50
 * Signature: int __fastcall construct_shell_surface_context(int param_1)
 */


int __fastcall construct_shell_surface_context(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  LPVOID pvVar4;
  undefined4 *puVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_10040336;
  local_c = ExceptionList;
  if (DAT_100f6368 == 0) {
    ExceptionList = &local_c;
    iVar3 = select_shell_display_mode_and_backend
                      ((int *)0x5,0,param_1 + 0x30,DAT_100f701c,DAT_100f7018,0);
  }
  else {
    ExceptionList = &local_c;
    iVar3 = select_shell_display_mode_and_backend
                      ((int *)0x1,0,param_1 + 0x30,DAT_100f701c,DAT_100f7018,0);
  }
  if (iVar3 == 0) {
    shutdown_shell_display_backend_candidate();
    log_or_report_shell_ddraw_error_candidate(s_vdriver_error_1004d568);
                    /* WARNING: Subroutine does not return */
    exit(2);
  }
  *(undefined4 *)(param_1 + 0x3bc) = 0x280;
  *(undefined4 *)(param_1 + 0x3c0) = 0x1e0;
  *(int *)(param_1 + 0x3c4) = *(int *)(param_1 + 0x3bc) + -1;
  *(int *)(param_1 + 0x3c8) = *(int *)(param_1 + 0x3c0) + -1;
  iVar3 = *(int *)(param_1 + 0x3bc) + -1;
  *(int *)(param_1 + 0x5c) = iVar3;
  *(int *)(param_1 + 0x48) = iVar3;
  *(int *)(param_1 + 0x34) = iVar3;
  iVar3 = *(int *)(param_1 + 0x3c0) + -1;
  *(int *)(param_1 + 0x60) = iVar3;
  *(int *)(param_1 + 0x4c) = iVar3;
  *(int *)(param_1 + 0x38) = iVar3;
  pvVar4 = HeapAlloc(DAT_10051c50,9,*(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc));
  *(undefined4 *)(param_1 + 0x44) = pvVar4;
  if (pvVar4 == (LPVOID)0x0) {
    shutdown_shell_display_backend_candidate();
    log_or_report_shell_ddraw_error_candidate(s_vdriver_error_1004d568);
                    /* WARNING: Subroutine does not return */
    exit(2);
  }
  pvVar4 = HeapAlloc(DAT_10051c50,9,*(int *)(param_1 + 0x3bc) * *(int *)(param_1 + 0x3c0));
  *(undefined4 *)(param_1 + 0x58) = pvVar4;
  if (pvVar4 == (LPVOID)0x0) {
    shutdown_shell_display_backend_candidate();
    log_or_report_shell_ddraw_error_candidate(s_vdriver_error_1004d568);
                    /* WARNING: Subroutine does not return */
    exit(2);
  }
  uVar1 = *(undefined4 *)(param_1 + 0x34);
  uVar2 = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  *(undefined4 *)(param_1 + 0xb8) = uVar2;
  *(undefined4 *)(param_1 + 0x90) = uVar2;
  *(undefined4 *)(param_1 + 0x7c) = uVar2;
  *(int *)(param_1 + 0x6c) = param_1 + 0x30;
  *(undefined4 **)(param_1 + 0x80) = (undefined4 *)(param_1 + 0x44);
  *(undefined4 **)(param_1 + 0xa8) = (undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  *(undefined4 *)(param_1 + 0x9c) = uVar2;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(int *)(param_1 + 0x94) = param_1 + 0x30;
  puVar5 = operator_new(4);
  local_4 = 0;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5 = FUN_10037260(puVar5);
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x18) = puVar5;
  puVar5 = operator_new(4);
  local_4 = 1;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5 = FUN_10037260(puVar5);
  }
  *(undefined4 **)(param_1 + 0x1c) = puVar5;
  DAT_100f5668 = 0xff;
  iVar3 = 1;
  do {
    (&DAT_100f5668)[iVar3] = (char)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x100);
  *(undefined4 *)(param_1 + 0x3cc) = 0;
  *(undefined4 *)(param_1 + 0x3d0) = 0xffffffff;
  ExceptionList = local_c;
  return param_1;
}


