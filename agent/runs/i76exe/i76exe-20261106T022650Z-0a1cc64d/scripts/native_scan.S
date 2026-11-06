/* Linux i386 environment only. The parent installs authenticated PE bytes,
 * terrain and grid, then single-steps unchanged original instructions.
 * int3 hands control to the bounded observer before any original read. */
.global _start
.text
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
 mov $26,%eax
 xor %ebx,%ebx
 xor %ecx,%ecx
 xor %edx,%edx
 int $0x80
 int3
fail:
 mov $1,%eax
 mov $1,%ebx
 int $0x80
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
.section .note.GNU-stack,"",@progbits
