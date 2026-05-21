/*
 * Program: i76shell.dll
 * Function: resolve_localized_shell_string_cached
 * Entry: 10037180
 * Signature: undefined4 __cdecl resolve_localized_shell_string_cached(size_t * param_1, undefined4 param_2)
 */


undefined4 __cdecl resolve_localized_shell_string_cached(size_t *param_1,undefined4 param_2)

{
  size_t sVar1;
  void *pvVar2;
  void *pvVar3;
  undefined4 local_10 [2];
  undefined4 local_8 [2];
  
  if (param_1 != (size_t *)0x0) {
    local_10[0] = param_2;
    pvVar2 = bsearch(local_10,(void *)param_1[3],param_1[1],8,(_PtFuncCompare *)&LAB_10037250);
    if (pvVar2 != (void *)0x0) {
      return *(undefined4 *)((int)pvVar2 + 4);
    }
    local_8[0] = param_2;
    pvVar2 = bsearch(local_8,(void *)param_1[2],*param_1,8,compare_localized_string_resource_key);
    if (pvVar2 != (void *)0x0) {
      pvVar3 = realloc((void *)param_1[3],param_1[1] * 8 + 8);
      if (pvVar3 != (void *)0x0) {
        param_1[3] = (size_t)pvVar3;
        *(undefined4 *)((int)pvVar3 + param_1[1] * 8) = param_2;
        *(undefined4 *)((int)pvVar3 + param_1[1] * 8 + 4) = *(undefined4 *)((int)pvVar2 + 4);
        sVar1 = param_1[1];
        param_1[1] = sVar1 + 1;
        qsort((void *)param_1[3],sVar1 + 1,8,(_PtFuncCompare *)&LAB_10037250);
      }
      param_2 = *(undefined4 *)((int)pvVar2 + 4);
    }
  }
  return param_2;
}


