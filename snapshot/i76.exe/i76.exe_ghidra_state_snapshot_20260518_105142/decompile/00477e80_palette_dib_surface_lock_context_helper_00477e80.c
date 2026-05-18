/*
 * Program: i76.exe
 * Function: palette_dib_surface_lock_context_helper_00477e80
 * Entry: 00477e80
 * Signature: undefined __cdecl palette_dib_surface_lock_context_helper_00477e80(int param_1, int param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: palette dib surface lock context
   helper based on adjacent named subsystem context. */

void __cdecl palette_dib_surface_lock_context_helper_00477e80(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < g_runtime_light_entry_count) {
    piVar2 = &g_runtime_light_entries;
    while (param_1 != *piVar2) {
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x1b;
      if (g_runtime_light_entry_count <= iVar1) {
        return;
      }
    }
    *(uint *)(&DAT_0058db88 + iVar1 * 0x6c) =
         -(uint)(param_2 != 0) & 8 | *(uint *)(&DAT_0058db88 + iVar1 * 0x6c) & 0xfffffff7;
  }
  return;
}


