/* Linux i386 research shim. Original PE instructions are supplied privately.
 * Services replaced: PE loading, grid/backing installation, Linux I/O only.
 * Sampler bytes and all x87 operations run unchanged on the CPU. */
.global _start
.section .text
_start:
 mov $192,%eax
 mov $0x400000,%ebx
 mov $0x300000,%ecx
 mov $7,%edx
 mov $0x32,%esi
 mov $-1,%edi
 xor %ebp,%ebp
 int $0x80
 cmp $0x400000,%eax
 jne fail
 mov $0x400000,%ecx
 mov $0x300000,%edx
 call read_exact
 mov $192,%eax
 mov $0x40000000,%ebx
 mov $0x800000,%ecx
 mov $3,%edx
 mov $0x32,%esi
 mov $-1,%edi
 xor %ebp,%ebp
 int $0x80
 cmp $0x40000000,%eax
 jne fail
 mov $0x40000000,%ecx
 mov $0x800000,%edx
 call read_exact
 mov $count,%ecx
 mov $4,%edx
 call read_exact
 mov count,%esi
 fninit
loop_case:
 test %esi,%esi
 jz done
 mov $input,%ecx
 mov $24,%edx
 call read_exact
 mov $out,%edi
 xor %eax,%eax
 mov $6,%ecx
 rep stosl
 cmpl $0,input
 jne world
 pushl input+12
 pushl input+4
 mov $0x493160,%eax
 call *%eax
 add $8,%esp
 mov %eax,out
 jmp output
world:
 pushl input+16
 pushl input+12
 pushl input+8
 pushl input+4
 mov $0x493550,%eax
 call *%eax
 add $16,%esp
 fstpt out
 fnstcw out+14
 mov -12(%esp),%eax
 mov %eax,out+16
 mov -28(%esp),%eax
 mov %eax,out+20
 pushl input+16
 pushl input+12
 pushl input+8
 pushl input+4
 mov $0x4927b0,%eax
 call *%eax
 add $16,%esp
 mov %eax,out+10
output:
 mov $4,%eax
 mov $1,%ebx
 mov $out,%ecx
 mov $24,%edx
 int $0x80
 cmp $24,%eax
 jne fail
 dec %esi
 jmp loop_case
read_exact:
 test %edx,%edx
 jz read_done
 mov $3,%eax
 xor %ebx,%ebx
 int $0x80
 test %eax,%eax
 jle fail
 add %eax,%ecx
 sub %eax,%edx
 jmp read_exact
read_done:
 ret
fail:
 mov $1,%ebx
 jmp exit
done:
 xor %ebx,%ebx
exit:
 mov $1,%eax
 int $0x80
.section .bss
.lcomm count,4
.lcomm input,24
.lcomm out,24
.section .note.GNU-stack,"",@progbits
