#ifndef I76_CLASS_DISPATCH_V102_H
#define I76_CLASS_DISPATCH_V102_H
/* Interstate '76: evidence-scoped reconstructed C layout vocabulary.
 * Not recovered original source. This is a portable 32-bit-address layout model,
 * NOT a declaration of host-native callable function pointers or class runtime allocation size.
 * Retail x86 addresses are represented as uint32_t so layout assertions work on 64-bit hosts.
 */
#include <stdint.h>
#include <stddef.h>
typedef uint32_t I76Addr32;

/* Forward-only: full 0xB0 world node is defined by the v101 header. */
typedef struct I76_WorldNode_0xB0 I76_WorldNode_0xB0;
/* Conceptual original call boundaries: runtime_factory(void) -> opaque runtime pointer;
 * initialize/pre_update/post_update(world_node) -> return ignored;
 * damage(world_node, damage_context, vector_context) -> uint32_t.
 * Actual ABI must be taken from the retail x86 binary, not these host declarations.
 */
#pragma pack(push,1)
typedef struct I76_ClassDescriptor_0x34 {
    uint32_t class_id;            /* +00, original class lookup */
    I76Addr32 runtime_factory;    /* +04, zero-argument callback, returns opaque ptr */
    I76Addr32 initialize;         /* +08, phase callback(world_node) */
    I76Addr32 pre_update;         /* +0C, phase callback(world_node) */
    I76Addr32 post_update;        /* +10, phase callback(world_node) */
    I76Addr32 slot_14;           /* +14 unresolved, zero in all 27 retail entries */
    I76Addr32 slot_18;           /* +18 unresolved, zero in all 27 retail entries */
    I76Addr32 slot_1c;           /* +1C unresolved callable/NULL */
    I76Addr32 slot_20;           /* +20 unresolved callable/NULL */
    I76Addr32 slot_24;           /* +24 unresolved callable/NULL */
    I76Addr32 damage;            /* +28, callback(world, opaque, opaque) returns 32 bits */
    I76Addr32 slot_2c;           /* +2C unresolved callable/NULL */
    I76Addr32 slot_30;           /* +30 unresolved callable/NULL; NOT post callback */
} I76_ClassDescriptor_0x34;

typedef struct I76_Class31RuntimeObserved_0x04 {
    I76Addr32 animation_context; /* +00: original 0046F2B0 store */
} I76_Class31RuntimeObserved_0x04;

typedef struct I76_Class34RuntimeObserved_0x80 {
    uint8_t unknown_00_07[0x08];
    I76Addr32 animation_context; /* +08: original 0045F810 store */
    uint8_t unknown_0c_77[0x78-0x0c];
    I76Addr32 root_world_node;   /* +78: original root-ancestor resolver */
    I76Addr32 self_world_node;   /* +7C: original callback receiver */
} I76_Class34RuntimeObserved_0x80;

typedef struct I76_Class32_33VisualRuntimeObserved_0x10 {
    uint8_t unknown_00_03[4];
    uint32_t local_visual_state; /* +04: 0046DFE0 local-player condition */
    I76Addr32 self_world_node;   /* +08: original callback receiver */
    uint32_t damage_visual_selector;/* +0C: 1 for class 0x20, 2 for 0x21 */
} I76_Class32_33VisualRuntimeObserved_0x10;
#pragma pack(pop)

_Static_assert(sizeof(I76_ClassDescriptor_0x34)==0x34,"descriptor stride");
_Static_assert(offsetof(I76_ClassDescriptor_0x34,initialize)==0x08,"init offset");
_Static_assert(offsetof(I76_ClassDescriptor_0x34,pre_update)==0x0c,"pre offset");
_Static_assert(offsetof(I76_ClassDescriptor_0x34,post_update)==0x10,"post offset");
_Static_assert(offsetof(I76_ClassDescriptor_0x34,damage)==0x28,"damage offset");
_Static_assert(sizeof(I76_ClassDescriptor_0x34[27])==0x57c,"27 descriptors end before clasfn string");
_Static_assert(sizeof(I76_Class31RuntimeObserved_0x04)==0x04,"class31 observed minimum extent");
_Static_assert(sizeof(I76_Class34RuntimeObserved_0x80)==0x80,"class34 observed minimum extent");
_Static_assert(offsetof(I76_Class34RuntimeObserved_0x80,root_world_node)==0x78,"class34 root offset");
_Static_assert(sizeof(I76_Class32_33VisualRuntimeObserved_0x10)==0x10,"class32/33 observed minimum extent");
_Static_assert(offsetof(I76_Class32_33VisualRuntimeObserved_0x10,self_world_node)==0x08,"class32/33 world offset");
#endif
