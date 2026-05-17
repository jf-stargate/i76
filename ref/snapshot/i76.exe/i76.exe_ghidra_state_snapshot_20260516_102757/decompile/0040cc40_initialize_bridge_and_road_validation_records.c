/*
 * Program: i76.exe
 * Function: initialize_bridge_and_road_validation_records
 * Entry: 0040cc40
 * Signature: undefined __stdcall initialize_bridge_and_road_validation_records(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Clears road/bridge validation globals and iterates
   class-0x0c world objects to validate bridge orthogonality. */

void initialize_bridge_and_road_validation_records(void)

{
  undefined4 *puVar1;
  int *piVar2;
  
  DAT_0051f690 = 0;
  DAT_0051f654 = 0;
  puVar1 = &DAT_0051f6b8;
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 10;
  } while ((int)puVar1 < 0x5244d8);
  piVar2 = (int *)get_current_effect_target_scan_object();
  while (piVar2 != (int *)0x0) {
    if (*(int *)(*piVar2 + 0x6c) == 0xc) {
      validate_bridge_is_orthogonal(piVar2);
    }
    piVar2 = (int *)effect_target_scan_query_context_helper_00436790();
  }
  return;
}


