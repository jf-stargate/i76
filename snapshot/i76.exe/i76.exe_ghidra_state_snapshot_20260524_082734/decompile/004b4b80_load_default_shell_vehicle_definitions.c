/*
 * Program: i76.exe
 * Function: load_default_shell_vehicle_definitions
 * Entry: 004b4b80
 * Signature: int __cdecl load_default_shell_vehicle_definitions(int param_1, int param_2)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium-high] ShellMain callback slot +0x04.
   Existing function from first pass; loads/defaults shell vehicle definition records for frontend
   vehicle selection/configuration. */

int __cdecl load_default_shell_vehicle_definitions(int param_1,int param_2)

{
  load_shell_vehicle_definition(param_1,(byte *)s_vppirna1_vcf_005008dc,param_2);
  load_shell_vehicle_definition(param_1,(byte *)s_vppirna2_vcf_005008cc,param_2 + 1);
  load_shell_vehicle_definition(param_1,(byte *)s_vccameo1_vcf_005008bc,param_2 + 2);
  load_shell_vehicle_definition(param_1,(byte *)s_vccameo2_vcf_005008ac,param_2 + 3);
  load_shell_vehicle_definition(param_1,(byte *)s_vccameo3_vcf_0050089c,param_2 + 4);
  load_shell_vehicle_definition(param_1,(byte *)s_vfypony1_vcf_0050088c,param_2 + 5);
  load_shell_vehicle_definition(param_1,(byte *)s_vfypony2_vcf_0050087c,param_2 + 6);
  return param_2 + 7;
}


