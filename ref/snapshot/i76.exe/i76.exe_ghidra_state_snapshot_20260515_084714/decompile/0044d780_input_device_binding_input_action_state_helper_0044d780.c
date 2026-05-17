/*
 * Program: i76.exe
 * Function: input_device_binding_input_action_state_helper_0044d780
 * Entry: 0044d780
 * Signature: int __cdecl input_device_binding_input_action_state_helper_0044d780(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: likely input_device_binding /
   input_action_state_helper based on address neighborhood and prior focused closure context. */

int __cdecl input_device_binding_input_action_state_helper_0044d780(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = param_1[5];
  iVar4 = (int)*(char *)(iVar1 + 0x15);
  if ((*(char **)(iVar1 + 0x2c) == (char *)0x0) || (**(char **)(iVar1 + 0x2c) == '\0')) {
    if ((*(char **)(iVar1 + 0x30) != (char *)0x0) && (**(char **)(iVar1 + 0x30) != '\0')) {
      **(undefined4 **)(iVar1 + 4) = 0;
      uVar3 = ftol();
      *(undefined4 *)(iVar1 + 0x1c) = uVar3;
      iVar4 = 1;
      **(undefined1 **)(iVar1 + 0x30) = 0;
    }
  }
  else {
    if (param_1[2] != 0) {
      (**(code **)((&g_input_device_callback_table)[*param_1] + 0x10))
                ((&DAT_005363f0)[*param_1 * 0x1d],param_1[1]);
    }
    iVar4 = 1;
    **(undefined4 **)(iVar1 + 4) = 0;
    *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(iVar1 + 0x10);
    **(undefined1 **)(iVar1 + 0x2c) = 0;
  }
  if (*(char *)(iVar1 + 0x15) == '\0') {
    get_runtime_frame_delta_seconds();
    if ((*(char **)(iVar1 + 0x24) != (char *)0x0) && (**(char **)(iVar1 + 0x24) != '\0')) {
      if (**(int **)(iVar1 + 4) < 0) {
        **(int **)(iVar1 + 4) = 0;
      }
      piVar2 = *(int **)(iVar1 + 4);
      iVar4 = ftol();
      *piVar2 = *piVar2 + (iVar4 * 3 << ((byte)*(undefined4 *)(iVar1 + 0x20) & 0x1f));
      if (0x5555 < **(int **)(iVar1 + 4)) {
        **(int **)(iVar1 + 4) = 0x5555;
      }
      iVar4 = *(int *)(iVar1 + 0x1c) + **(int **)(iVar1 + 4);
      *(int *)(iVar1 + 0x1c) = iVar4;
      if (0x10000 < iVar4) {
        *(undefined4 *)(iVar1 + 0x1c) = 0x10000;
      }
      iVar4 = 1;
      **(undefined1 **)(iVar1 + 0x24) = 0;
    }
    if ((*(char **)(iVar1 + 0x28) != (char *)0x0) && (**(char **)(iVar1 + 0x28) != '\0')) {
      if (0 < **(int **)(iVar1 + 4)) {
        **(int **)(iVar1 + 4) = 0;
      }
      piVar2 = *(int **)(iVar1 + 4);
      iVar4 = ftol();
      *piVar2 = *piVar2 + (iVar4 * -3 << ((byte)*(undefined4 *)(iVar1 + 0x20) & 0x1f));
      if (**(int **)(iVar1 + 4) < -0x5555) {
        **(int **)(iVar1 + 4) = -0x5555;
      }
      iVar4 = *(int *)(iVar1 + 0x1c) + **(int **)(iVar1 + 4);
      *(int *)(iVar1 + 0x1c) = iVar4;
      if (iVar4 < -0x10000) {
        *(undefined4 *)(iVar1 + 0x1c) = 0xffff0000;
      }
      iVar4 = 1;
      **(undefined1 **)(iVar1 + 0x28) = 0;
    }
    if (iVar4 == 0) {
      **(undefined4 **)(iVar1 + 4) = 0;
    }
  }
  *(char *)(iVar1 + 0x15) = (char)iVar4;
  return iVar4;
}


