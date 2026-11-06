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
 fninit
 mov $0x493c50,%eax
 call *%eax
 mov $0x4c2730,%ecx
 mov $472,%edx
 call read_exact
 mov $0x5dcec0,%ecx
 mov $8,%edx
 call read_exact
 mov $quality,%ecx
 mov $4,%edx
 call read_exact
 pushl quality
 mov $0x4907e0,%eax
 call *%eax
 add $4,%esp
 mov $0x4c2730,%esi
 xor %edi,%edi
 mov $scratch,%ebp
 # Original numerical prefix: entry after peripheral frame setup.
 # Only its continuation at 00490B23 is replaced with ADD ESP,4;RET.
 mov $0x490a8b,%eax
 call *%eax
 mov %eax,out
 mov $4,%eax
 mov $1,%ebx
 mov $out,%ecx
 mov $4,%edx
 int $0x80
 mov $4,%eax
 mov $1,%ebx
 mov $0x6442c8,%ecx
 mov $8,%edx
 int $0x80
 mov $4,%eax
 mov $1,%ebx
 mov $0x6442e0,%ecx
 mov $12,%edx
 int $0x80
 mov $4,%eax
 mov $1,%ebx
 mov $0x6442f0,%ecx
 mov $144,%edx
 int $0x80
 jmp done
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
.lcomm scratch,32
.lcomm quality,4
.section .note.GNU-stack,"",@progbits
