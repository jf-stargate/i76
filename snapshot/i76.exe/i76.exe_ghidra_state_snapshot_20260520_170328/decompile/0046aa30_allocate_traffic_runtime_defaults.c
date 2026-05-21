/*
 * Program: i76.exe
 * Function: allocate_traffic_runtime_defaults
 * Entry: 0046aa30
 * Signature: undefined __stdcall allocate_traffic_runtime_defaults(void)
 */


/* [cgpt i76.exe texture/resource-cache rename v9; confidence=medium] Allocates a 0x30-byte class
   runtime block and initializes first two fields to 400; class-specific runtime initializer, likely
   traffic/vehicle behavior defaults. */

void allocate_traffic_runtime_defaults(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x30);
  *puVar1 = 400;
  puVar1[1] = 400;
  return;
}


