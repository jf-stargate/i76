/*
 * Program: i76.exe
 * Function: is_network_or_trip_runtime_mode
 * Entry: 00401310
 * Signature: undefined4 __stdcall is_network_or_trip_runtime_mode(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM] Predicate used throughout mission
   setup/runtime for alternate vehicle/network/trip paths. */

undefined4 is_network_or_trip_runtime_mode(void)

{
  return DAT_00501818;
}


