#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(){uint32_t in[]={0,0x80000000,0x3f800000,0xbf800000,0x3fc90fdb,0x40490fdb,0x42c80000};for(int r=0;r<4;r++)for(int i=0;i<7;i++){uint16_t cw=0x37f+0x400*r,old;float a,s,c;memcpy(&a,in+i,4);__asm__ volatile("fnstcw %0":"=m"(old));__asm__ volatile("fldcw %0"::"m"(cw));__asm__ volatile("flds %2; fsincos; fstps %0; fstps %1":"=m"(c),"=m"(s):"m"(a):"st");__asm__ volatile("fldcw %0"::"m"(old));uint32_t sb,cb;memcpy(&sb,&s,4);memcpy(&cb,&c,4);printf("%08X %X %08X %08X\n",in[i],cw,sb,cb);}}
