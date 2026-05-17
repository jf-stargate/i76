/*
 * Program: i76.exe
 * Function: joystick_device_poll_context_helper_004507e0
 * Entry: 004507e0
 * Signature: undefined4 __cdecl joystick_device_poll_context_helper_004507e0(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: joystick device poll context helper
   based on prior focused closure context. */

undefined4 __cdecl joystick_device_poll_context_helper_004507e0(int param_1)

{
  LPVOID pvVar1;
  
  if (param_1 != 0) {
    if (*(LPVOID *)(param_1 + 0x60) != (LPVOID)0x0) {
      xfree_global_heap(*(LPVOID *)(param_1 + 0x60));
    }
    if (*(LPVOID *)(param_1 + 100) != (LPVOID)0x0) {
      xfree_global_heap(*(LPVOID *)(param_1 + 100));
    }
    if (*(undefined4 **)(param_1 + 0x68) != (undefined4 *)0x0) {
      pvVar1 = (LPVOID)**(undefined4 **)(param_1 + 0x68);
      if (pvVar1 != (LPVOID)0x0) {
        xfree_global_heap(pvVar1);
      }
      xfree_global_heap(*(LPVOID *)(param_1 + 0x68));
    }
    if (*(undefined4 **)(param_1 + 0x6c) != (undefined4 *)0x0) {
      pvVar1 = (LPVOID)**(undefined4 **)(param_1 + 0x6c);
      if (pvVar1 != (LPVOID)0x0) {
        xfree_global_heap(pvVar1);
      }
      xfree_global_heap(*(LPVOID *)(param_1 + 0x6c));
    }
    if (*(LPVOID *)(param_1 + 0x70) != (LPVOID)0x0) {
      xfree_global_heap(*(LPVOID *)(param_1 + 0x70));
    }
  }
  return 0;
}


