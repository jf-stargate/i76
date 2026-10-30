/* Hardware x87 conversion oracle for Ghidra's RC-ignoring FISTP model.
 * Protocol: little-endian 80-bit ST0 plus uint16 control word; returns int64.
 * No proprietary bytes. Build: cc -O2 x87_fistp_service.c -o PRIVATE/x87_fistp_service
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
int main(void) {
 unsigned char request[12];
 while(fread(request,1,12,stdin)==12) {
  long double input=0;uint16_t cw,previous;int64_t value;long double cosine;
  memcpy(&input,request,10);memcpy(&cw,request+10,2);
  __asm__ volatile("fnstcw %0":"=m"(previous));
  if(cw&0x2000){uint32_t single;cw&=0x1fff;
   __asm__ volatile("fldcw %0"::"m"(cw));
   __asm__ volatile("fldt %1; fstps %0":"=m"(single):"m"(input):"st");
   __asm__ volatile("fldcw %0"::"m"(previous));
   if(fwrite(&single,1,4,stdout)!=4||fflush(stdout))return 2;continue;
  }
  if(cw&0x4000){
   long double sine=0; uint16_t sw; cw&=0x3fff;
   __asm__ volatile("fldcw %0"::"m"(cw));
   __asm__ volatile("fldt %3; fsincos; fnstsw %2; fstpt %0; fstpt %1":"=m"(cosine),"=m"(sine),"=m"(sw):"m"(input):"st");
   __asm__ volatile("fldcw %0"::"m"(previous));
   if(sw&0x400)return 4; /* Only finite |x|<2^63 supported by this bridge. */
   if(fwrite(&cosine,1,10,stdout)!=10||fwrite(&sine,1,10,stdout)!=10||fwrite(&sw,1,2,stdout)!=2||fflush(stdout))return 2;continue;
  }
  if(cw&0x8000){cw&=0x7fff;__asm__ volatile("fldcw %0"::"m"(cw));__asm__ volatile("fldt %1; fcos; fstpt %0":"=m"(cosine):"m"(input):"st");__asm__ volatile("fldcw %0"::"m"(previous));if(fwrite(&cosine,1,10,stdout)!=10||fflush(stdout))return 2;continue;}
  __asm__ volatile("fldcw %0"::"m"(cw));
  __asm__ volatile("fldt %1; fistpq %0":"=m"(value):"m"(input):"st");
  __asm__ volatile("fldcw %0"::"m"(previous));
  if(fwrite(&value,1,8,stdout)!=8||fflush(stdout))return 2;
 }
 return ferror(stdin)?3:0;
}
