/*
 * Program: i76.exe
 * Function: submit_display_backend_screen_edge_quads
 * Entry: 0042e850
 * Signature: undefined __stdcall submit_display_backend_screen_edge_quads(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v8 display/d3d cluster: Begins a D3D scene and submits two screen-edge quad batches
   through the indexed primitive submitter. */

void submit_display_backend_screen_edge_quads(void)

{
  float fVar1;
  float fVar2;
  float fStack_64;
  float fStack_60;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_8;
  
  (**(code **)(*DAT_005fde48 + 0x4c))(DAT_005fde48);
  fVar1 = (float)DAT_00608404;
  fVar2 = (float)DAT_00608400;
  fStack_60 = fVar1 - _DAT_004bcd4c;
  fStack_50 = _DAT_004bcd54;
  fStack_38 = _DAT_004bcd54;
  fStack_20 = _DAT_004bcd54;
  fStack_8 = _DAT_004bcd54;
  fStack_64 = _DAT_004bcd54;
  fStack_1c = _DAT_004bcd54;
  fStack_4c = fVar2;
  fStack_48 = fStack_60;
  fStack_34 = fVar2;
  fStack_30 = fVar1;
  fStack_18 = fVar1;
  submit_d3d_lit_indexed_primitive_batch_a(&fStack_64,4,0);
  fStack_64 = fVar2 - _DAT_004bcd4c;
  fStack_60 = _DAT_004bcd54;
  fStack_48 = _DAT_004bcd54;
  fStack_4c = fVar2;
  fStack_34 = fVar2;
  fStack_30 = fVar1;
  fStack_1c = fStack_64;
  fStack_18 = fVar1;
  submit_d3d_lit_indexed_primitive_batch_a(&fStack_64,4,0);
  return;
}


