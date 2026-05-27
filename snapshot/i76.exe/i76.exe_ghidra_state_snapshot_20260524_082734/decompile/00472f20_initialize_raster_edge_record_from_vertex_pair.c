/*
 * Program: i76.exe
 * Function: initialize_raster_edge_record_from_vertex_pair
 * Entry: 00472f20
 * Signature: undefined __thiscall initialize_raster_edge_record_from_vertex_pair(void * this, uint param_1, float * param_2, float * param_3, uint param_4, uint param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Initializes an edge record
   from a projected vertex pair for polygon scanline span generation. */

void __thiscall
initialize_raster_edge_record_from_vertex_pair
          (void *this,uint param_1,float *param_2,float *param_3,uint param_4,uint param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(uint *)((int)this + 0x10) = param_4;
  *(uint *)((int)this + 0xc) = param_1;
  *(uint *)((int)this + 0x1c) = param_5;
  *(undefined4 *)((int)this + 8) = 0;
  fVar2 = param_2[1];
  *(float *)((int)this + 0x14) = param_2[2];
  fVar1 = *param_2;
  fVar3 = (*param_3 - fVar1) / (param_3[1] - fVar2);
  _DAT_0058da18 = (double)(_DAT_004f9d84 + fVar3);
  *(uint *)((int)this + 0x18) = DAT_0058da18 + 1U & 0xfffffffe;
  _DAT_0058da50 = (double)(fVar1 + ((float)(int)param_4 - fVar2) * fVar3 + (float)_DAT_004f9d88);
  *(uint *)this = DAT_0058da50 + 1U & 0xfffffffe;
  return;
}


