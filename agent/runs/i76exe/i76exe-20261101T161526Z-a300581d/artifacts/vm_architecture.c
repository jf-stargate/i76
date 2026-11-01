/* Original-authored explanatory C11 sketch, NOT an implemented replacement runtime.
 * Address mapping, stream, heap and gameplay services are abstract extern boundaries.
 * All guest addresses/words are 32-bit, even on a 64-bit analysis host.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
typedef uint32_t Word;
typedef uint32_t Addr32;
typedef struct { Word kind, payload; } VmToken;
typedef struct {
    Word workspace_words[1024];       /* mixed words, addresses and saved frames */
    Word host_words[40];              /* separate, mixed argument slots */
    Word condition;                   /* zero/nonzero, not C bool */
    Addr32 token_base, ip, frame, operand_cursor, host_cursor, next;
} VmNode32;
typedef struct { Word entry_index, context_count, context_words[40]; } NodeSeed;
/* Command name/prototype internals are outside this pilot; only +50 is used. */
typedef struct { uint8_t unknown_00_4f[0x50]; Word opcode; } HostRecord32;
_Static_assert(sizeof(VmNode32)==0x10bc,"node size");
_Static_assert(offsetof(VmNode32,host_words)==0x1000,"host area");
_Static_assert(offsetof(VmNode32,condition)==0x10a0,"condition");
_Static_assert(offsetof(VmNode32,token_base)==0x10a4,"tokens");
_Static_assert(offsetof(VmNode32,ip)==0x10a8,"ip");
_Static_assert(offsetof(VmNode32,frame)==0x10ac,"frame");
_Static_assert(offsetof(VmNode32,operand_cursor)==0x10b0,"operand cursor");
_Static_assert(offsetof(VmNode32,host_cursor)==0x10b4,"host cursor");
_Static_assert(offsetof(VmNode32,next)==0x10b8,"next");
_Static_assert(sizeof(NodeSeed)==168,"wire node");
_Static_assert(sizeof(VmToken)==8,"token");
_Static_assert(sizeof(HostRecord32)==0x54,"host record");

/* A conceptual bundle of original flat arguments and shared state, NOT an
 * observed original in-memory structure or original function signature. */
typedef struct {
    Addr32 command_base, media_base, position_base, actor_base, actor_count_address;
    Addr32 heap_handle;
    Word forwarded_unknown;
} MissionServices;
extern VmNode32 *mapped_node(Addr32);
extern Word read_word(Addr32);
extern void write_word(Addr32, Word);
extern Word stream_word(void);
extern Addr32 heap_alloc(Addr32 heap, Word flags, Word bytes);
extern void heap_free(Addr32 heap, Word flags, Addr32 node);
extern Word instruction_budget_latch; /* 005244DC, also consulted by some AI calls */
extern void retail_report_error(void); /* verified RET in this PE */
extern void host_execute_opcode(Word opcode, Addr32 node, MissionServices *s);
extern double mission_elapsed_seconds(void);
extern float mission_deadline; /* 005244E0 */
extern Word mission_next_state; /* 005244E4 */
extern void set_game_flow_state(Word);

/* 00410490: two passes. Allocation uses flags=0, so untouched bytes are unknown.
 * The seed is consumed from the shared stream; no universal allocator semantics.
 * Failed allocation/count validity is not repaired by this sketch. */
void load_execution_nodes(Addr32 *head, Word *count, Addr32 heap)
{
    *count=stream_word();
    if (*count==0) { *head=0; return; }
    *head=heap_alloc(heap,0,0x10bc);
    Addr32 tail=*head;
    for (Word i=1; (int32_t)i<(int32_t)*count; ++i) {
        Addr32 added=heap_alloc(heap,0,0x10bc);
        mapped_node(tail)->next=added;
        tail=added;
    }
    mapped_node(tail)->next=0;
    for (Addr32 a=*head; a; a=mapped_node(a)->next) {
        VmNode32 *n=mapped_node(a);
        n->ip=stream_word(); /* still a scalar entry INDEX during this phase */
        Word context_count=stream_word();
        for (Word k=0;k<40;++k) n->workspace_words[k]=stream_word();
        n->operand_cursor=a+4*context_count;
    }
}

/* 00412500: initialization after token/global arrays are available. */
void initialize_execution_nodes(Addr32 a, Word count, Addr32 tokens, Addr32 globals)
{
    for (Word i=0;(int32_t)i<(int32_t)count;++i) {
        VmNode32 *n=mapped_node(a);
        for (Addr32 q=a;q!=n->operand_cursor;q+=4)
            write_word(q,globals+4*read_word(q));
        n->condition=0;
        n->token_base=tokens;
        n->ip=tokens+8*n->ip;
        write_word(n->operand_cursor,0); /* saved prior frame sentinel */
        n->operand_cursor+=4;
        n->frame=n->operand_cursor;     /* points AT saved return-IP word */
        write_word(n->frame,n->ip);     /* outer synthetic return address is entry */
        n->operand_cursor+=4;
        n->host_cursor=a+0x1000;
        a=n->next;
    }
}

/* 00412CE0 bridge: source command index -> record opcode -> synchronous handler.
 * The opaque handler boundary covers the existing 96-slot dispatch, including
 * report+abort for unsupported opcode/playScene. This is not a new host ABI.
 * Actual call also carries unused counts and trailing opaque/scratch arguments.
 */
void dispatch_host(Addr32 a, Word source_index, MissionServices *s)
{
    VmNode32 *n=mapped_node(a);
    Word opcode=read_word(s->command_base+0x54*source_index+0x50);
    host_execute_opcode(opcode,a,s);
    /* Only reached when the handler returns normally. Predicates update
     * condition themselves; ordinary side effects leave it unchanged. */
    n->host_cursor=a+0x1000;
    n->ip+=8;
}

/* 00414670. Guest additions/multiplications use modulo-2^32 word arithmetic.
 * No bounds checks are added: this describes the examined retail instructions.
 * Return 0 = yielded; 1 = completed. exit(0) terminates the PROCESS.
 */
int execute_until_suspend(Addr32 a, MissionServices *s)
{
    VmNode32 *n=mapped_node(a);
    Word retired=0;
    /* Original also prepares 80 local scratch bytes and forwards their address
     * to the host. No semantic consumer was identified in this dispatcher. */
    for (;;) {
        if (retired>800) instruction_budget_latch=1;
        Word kind=read_word(n->ip);
        Word p=(kind>=1 && kind<=13) ? read_word(n->ip+4) : 0;
        switch (kind) {
        case 1: write_word(n->operand_cursor,p); n->operand_cursor+=4; n->ip+=8; break;
        case 2: write_word(n->operand_cursor,n->frame+4*p); n->operand_cursor+=4; n->ip+=8; break;
        case 3: write_word(n->operand_cursor,read_word(n->frame+4*p)); n->operand_cursor+=4; n->ip+=8; break;
        case 4: write_word(n->host_cursor,n->frame+4*p); n->host_cursor+=4; n->ip+=8; break;
        case 5: write_word(n->host_cursor,read_word(n->frame+4*p)); n->host_cursor+=4; n->ip+=8; break;
        case 6: n->operand_cursor+=4*p; n->ip+=8; break;
        case 7: n->operand_cursor-=4*p; n->ip+=8; break;
        case 8: n->ip=n->token_base+8*p; break;
        case 9: n->ip=n->condition ? n->ip+8 : n->token_base+8*p; break;
        case 10: n->ip=n->token_base+8*p; return 0; /* no fall-through increment */
        case 11:
            write_word(n->operand_cursor,n->frame);
            n->operand_cursor+=4;
            n->frame=n->operand_cursor;
            write_word(n->operand_cursor,n->ip+8);
            n->operand_cursor+=4;
            n->ip=n->token_base+8*p;
            break;
        case 12: {
            Addr32 old_frame=n->frame;
            n->ip=read_word(old_frame);
            n->operand_cursor=old_frame-(4*p+4);
            n->frame=read_word(old_frame-4);
            if (n->operand_cursor==a) return 1; /* NOT a test of frame==0 */
            break;
        }
        case 13: dispatch_host(a,p,s); break; /* dispatcher owns IP advance */
        case 14: n->condition=(n->condition==0); n->ip+=8; break;
        default: retail_report_error(); break; /* no IP advance; reporter returns */
        }
        if (++retired>=1000) exit(0);
    }
}

/* 004149F0: equivalent unified predecessor traversal, assuming host services
 * do not mutate scheduler links indirectly. Retail uses a head-removal loop
 * followed by a retained-predecessor loop. This equivalence is derived. */
void scheduler_update(Addr32 *head, Word *pending_count, MissionServices *s)
{
    if ((double)mission_deadline<=mission_elapsed_seconds())
        set_game_flow_state(mission_next_state);
    Addr32 previous=0, current=*head;
    while (current) {
        int completed=execute_until_suspend(current,s);
        Addr32 next=mapped_node(current)->next;
        if (completed) {
            --*pending_count;
            if (previous) mapped_node(previous)->next=next;
            else *head=next;
            heap_free(s->heap_handle,0,current);
        } else previous=current;
        current=next;
    }
}

extern Word runtime_outer_gate_0051f640, alternate_gate_0051f5c0;
extern int network_or_trip_mode(void);
extern void prepare_vehicle_bounds_and_progress(void); /* omitted non-VM body */
extern void update_alternate_ai(void);
extern void update_progress_compare(void);
extern void increment_damage_epoch(void); /* 004155F0 */
extern void finish_runtime_frame(void); /* omitted radar/control cleanup */
/* 0040A320: semantic orchestration; helper bundles are explanatory roles. */
void mission_runtime_update(Addr32 *head, Word *count, MissionServices *s)
{
    if (runtime_outer_gate_0051f640) return;
    prepare_vehicle_bounds_and_progress();
    if (!network_or_trip_mode() && !alternate_gate_0051f5c0)
        scheduler_update(head,count,s);
    else update_alternate_ai();
    update_progress_compare();
    increment_damage_epoch();
    finish_runtime_frame();
}
