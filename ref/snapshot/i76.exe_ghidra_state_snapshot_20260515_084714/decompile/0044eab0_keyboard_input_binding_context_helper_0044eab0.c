/*
 * Program: i76.exe
 * Function: keyboard_input_binding_context_helper_0044eab0
 * Entry: 0044eab0
 * Signature: undefined __cdecl keyboard_input_binding_context_helper_0044eab0(undefined4 param_1, uint param_2, int param_3)
 */


/* cgpt readability rename set B v14: Readability pass set B: keyboard input binding context helper
   based on prior focused closure context. */

void __cdecl
keyboard_input_binding_context_helper_0044eab0(undefined4 param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = (uint)param_2._2_1_;
  if (uVar2 == 0) {
    return;
  }
  if (((param_2 >> 0x10 & 0x100) != 0) && (param_2._2_1_ < 0x59)) {
    uVar2 = *(uint *)(&DAT_004f50a0 + uVar2 * 4);
  }
  if (uVar2 == 0) {
    return;
  }
  iVar3 = uVar2 - 1;
  if (param_3 == 0) {
    iVar1 = (int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5;
    (&DAT_006092e0)[iVar1] = (&DAT_006092e0)[iVar1] | 1 << ((byte)iVar3 & 0x1f);
  }
  else {
    iVar1 = (int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5;
    uVar4 = 1 << ((byte)iVar3 & 0x1f);
    if ((uVar4 & (&DAT_006092e0)[iVar1]) != 0) {
      (&DAT_006092e0)[iVar1] = ~uVar4 & (&DAT_006092e0)[iVar1];
    }
    (&DAT_006092d0)[iVar1] = (&DAT_006092d0)[iVar1] | uVar4;
  }
  switch(uVar2) {
  case 0x1d:
  case 0x70:
    if (param_3 == 0) {
      DAT_006092ec = DAT_006092ec | 0x800000;
      return;
    }
    uVar2 = 0x800000;
    if ((DAT_006092ec & 0x800000) != 0) {
      DAT_006092ec = DAT_006092ec & 0xff7fffff;
      DAT_006092dc = DAT_006092dc | 0x800000;
      return;
    }
    break;
  default:
    return;
  case 0x2a:
  case 0x36:
    if (param_3 == 0) {
      DAT_006092ec = DAT_006092ec | 0x400000;
      return;
    }
    uVar2 = 0x400000;
    if ((DAT_006092ec & 0x400000) != 0) {
      DAT_006092ec = DAT_006092ec & 0xffbfffff;
      DAT_006092dc = DAT_006092dc | 0x400000;
      return;
    }
    break;
  case 0x38:
  case 0x71:
    if (param_3 == 0) {
      DAT_006092ec = DAT_006092ec | 0x1000000;
      return;
    }
    uVar2 = 0x1000000;
    if ((DAT_006092ec & 0x1000000) != 0) {
      DAT_006092ec = DAT_006092ec & 0xfeffffff;
    }
  }
  DAT_006092dc = DAT_006092dc | uVar2;
  return;
}


