/* Instruction boundary only. Request: op byte, ST0[10], ST1[10], CW[2], LE.
 * op 0 = FISTP qword -> int64; op 1 = FPATAN(ST1/ST0), pop -> ext80.
 * Requires x86_64 GNU C, build cc -O2. No game code or resources. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(void){unsigned char q[23];while(fread(q,1,23,stdin)==23){
 long double a=0,b=0,out=0;uint16_t cw,old;int64_t i;
 memcpy(&a,q+1,10);memcpy(&b,q+11,10);memcpy(&cw,q+21,2);
 __asm__ volatile("fnstcw %0":"=m"(old));__asm__ volatile("fldcw %0"::"m"(cw));
 if(q[0]==1){__asm__ volatile("fldt %2; fldt %1; fpatan; fstpt %0":"=m"(out):"m"(a),"m"(b):"st");}
 else if(q[0]==0){__asm__ volatile("fldt %1; fistpq %0":"=m"(i):"m"(a):"st");}
 else return 4;
 __asm__ volatile("fldcw %0"::"m"(old));
 if(fwrite(q[0]? (void*)&out:(void*)&i,1,q[0]?10:8,stdout)!=(q[0]?10:8)||fflush(stdout))return 2;
 }return ferror(stdin)?3:0;}
