/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - linkage_arm.S                                           *
 *   Copyright (C) 2009-2011 Ari64                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined(__thumb__)
#define GLOBAL_FUNCTION(name)		\
    ".align 2;\n"			\
    ".globl " name ";\n"		\
    ".thumb;\n"                         \
    ".thumb_func;\n"                    \
    ".hidden " name ";\n"		\
    ".type " name ", %function;\n"	\
    name ":\n"
#else
#define GLOBAL_FUNCTION(name)  \
    ".align 2;\n"			\
    ".globl " name ";\n"		\
    ".hidden " name ";\n"		\
    ".type " name ", %function;\n"	\
    name ":\n"
#endif

#define LOCAL_FUNCTION(name)            \
    ".align 2;\n"                       \
    ".hidden " name ";\n"               \
    ".type " name ", %function;\n"      \
    name ":\n"

#define GLOBAL_VARIABLE(name, size_)    \
    ".global " name ";\n"               \
    ".hidden " name ";\n"               \
    ".type "   name ", %object;\n"      \
    ".size "   name ", " size_ "\n"

#define BSS_SECTION  ".bss\n"
#define TEXT_SECTION ".text\n"
#define END_SECTION

//asm(".cpu arm9tdmi");
#ifndef __ARM_NEON__
#if (defined(__VFP_FP__) && !defined(__SOFTFP__) && defined(__ARM_PCS_VFP))
asm(".fpu vfp");
#else
asm(".fpu softvfp");
#endif
#else
asm(".fpu neon");
#endif
asm(".eabi_attribute 20, 1");
asm(".eabi_attribute 21, 1");
#ifndef __ARM_NEON__
asm(".eabi_attribute 23, 3");
#endif
asm(".eabi_attribute 24, 1");
asm(".eabi_attribute 25, 1");
asm(".eabi_attribute 26, 2");
#ifndef __ARM_NEON__
#if (defined(__VFP_FP__) && !defined(__SOFTFP__) && defined(__ARM_PCS_VFP))
asm(".eabi_attribute 28, 1");
#endif
#endif
asm(".eabi_attribute 30, 6");
asm(".eabi_attribute 18, 4");
//.file    "linkage_arm.S"

asm(
    BSS_SECTION
    "\n"
    "    .align   12\n"
    GLOBAL_VARIABLE("extra_memory", "33554432")
    GLOBAL_VARIABLE("dynarec_local", "64")
    GLOBAL_VARIABLE("next_interupt", "4")
    GLOBAL_VARIABLE("cycle_count", "4")
    GLOBAL_VARIABLE("last_count", "4")
    GLOBAL_VARIABLE("pending_exception", "4")
    GLOBAL_VARIABLE("pcaddr", "4")
    GLOBAL_VARIABLE("stop", "4")
    GLOBAL_VARIABLE("invc_ptr", "4")
    GLOBAL_VARIABLE("address", "4")
    GLOBAL_VARIABLE("readmem_dword", "8")
    GLOBAL_VARIABLE("cpu_dword", "8")
    GLOBAL_VARIABLE("cpu_word", "4")
    GLOBAL_VARIABLE("cpu_hword", "2")
    GLOBAL_VARIABLE("cpu_byte", "1")
    GLOBAL_VARIABLE("FCR0", "4")
    GLOBAL_VARIABLE("FCR31", "4")
    GLOBAL_VARIABLE("reg", "256")
    GLOBAL_VARIABLE("hi", "8")
    GLOBAL_VARIABLE("lo", "8")
    GLOBAL_VARIABLE("g_cp0_regs", "128")
    GLOBAL_VARIABLE("reg_cop1_simple", "128")
    GLOBAL_VARIABLE("reg_cop1_double", "128")
    GLOBAL_VARIABLE("rounding_modes", "16")
    GLOBAL_VARIABLE("branch_target", "4")
    GLOBAL_VARIABLE("PC", "4")
    GLOBAL_VARIABLE("fake_pc", "132")
    GLOBAL_VARIABLE("ram_offset", "4")
    GLOBAL_VARIABLE("mini_ht", "256")
    GLOBAL_VARIABLE("restore_candidate", "512")
    GLOBAL_VARIABLE("memory_map", "4194304")
    "\n"
    "extra_memory:\n"
    "    .space    33554432+64+4+4+4+4+4+4+4+4+8+8+4+2+2+4+4+256+8+8+128+128+128+16+4+4+132+4+256+512+4194304\n"
    "\n"
    "    dynarec_local     = extra_memory      + 33554432\n"
    "    next_interupt     = dynarec_local     + 64\n"
    "    cycle_count       = next_interupt     + 4\n"
    "    last_count        = cycle_count       + 4\n"
    "    pending_exception = last_count        + 4\n"
    "    pcaddr            = pending_exception + 4\n"
    "    stop              = pcaddr            + 4\n"
    "    invc_ptr          = stop              + 4\n"
    "    address           = invc_ptr          + 4\n"
    "    readmem_dword     = address           + 4\n"
    "    cpu_dword         = readmem_dword     + 8\n"
    "    cpu_word          = cpu_dword         + 8\n"
    "    cpu_hword         = cpu_word          + 4\n"
    "    cpu_byte          = cpu_hword         + 2 /* 1 byte free */\n"
    "    FCR0              = cpu_hword         + 4\n"
    "    FCR31             = FCR0              + 4\n"
    "    reg               = FCR31             + 4\n"
    "    hi                = reg               + 256\n"
    "    lo                = hi                + 8\n"
    "    g_cp0_regs        = lo                + 8\n"
    "    reg_cop1_simple   = g_cp0_regs        + 128\n"
    "    reg_cop1_double   = reg_cop1_simple   + 128\n"
    "    rounding_modes    = reg_cop1_double   + 128\n"
    "    branch_target     = rounding_modes    + 16\n"
    "    PC                = branch_target     + 4\n"
    "    fake_pc           = PC                + 4\n"
    "    ram_offset        = fake_pc           + 132\n"
    "    mini_ht           = ram_offset        + 4\n"
    "    restore_candidate = mini_ht           + 256\n"
    "    memory_map        = restore_candidate + 512\n"
    "\n"
    END_SECTION
    "\n"
    TEXT_SECTION
    "\n"
    "    .align   2\n"
    "    .jiptr_offset1  : .word jump_in-(.jiptr_pic1+8)\n"
    "    .jiptr_offset2  : .word jump_in-(.jiptr_pic2+8)\n"
    "    .jdptr_offset1  : .word jump_dirty-(.jdptr_pic1+8)\n"
    "    .jdptr_offset2  : .word jump_dirty-(.jdptr_pic2+8)\n"
    "    .tlbptr_offset1 : .word tlb_LUT_r-(.tlbptr_pic1+8)\n"
    "    .tlbptr_offset2 : .word tlb_LUT_r-(.tlbptr_pic2+8)\n"
    "    .htptr_offset1  : .word hash_table-(.htptr_pic1+8)\n"
    "    .htptr_offset2  : .word hash_table-(.htptr_pic2+8)\n"
    "    .htptr_offset3  : .word hash_table-(.htptr_pic3+8)\n"
    "    .dlptr_offset   : .word dynarec_local+28-(.dlptr_pic+8)\n"
    "    .outptr_offset  : .word out-(.outptr_pic+8)\n"
    );


asm(
    GLOBAL_FUNCTION("dyna_linker")
    "    /* r0 = virtual target address */\n"
    "    /* r1 = instruction to patch */\n"
    "    ldr    r4, .tlbptr_offset1\n"
    ".tlbptr_pic1:\n"
    "    add    r4, pc, r4\n"
    "    lsr    r5, r0, #12\n"
    "    mov    r12, r0\n"
    "    cmp    r0, #0xC0000000\n"
    "    mov    r6, #4096\n"
#ifdef __thumb__
    "    it     ge\n"
#endif /*__thumb__*/
    "    ldrge  r12, [r4, r5, lsl #2]\n"
    "    mov    r2, #0x80000\n"
    "    ldr    r3, .jiptr_offset1\n"
    ".jiptr_pic1:\n"
    "    add    r3, pc, r3\n"
    "    tst    r12, r12\n"
    "    sub    r6, r6, #1\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  r12, r0\n"
    "    ldr    r7, [r1]\n"
    "    eor    r2, r2, r12, lsr #12\n"
    "    and    r6, r6, r12, lsr #12\n"
    "    cmp    r2, #2048\n"
    "    add    r12, r7, #2\n"
#ifdef __thumb__
    "    it     cs\n"
#endif /*__thumb__*/
    "    orrcs  r2, r6, #2048\n"
    "    ldr    r5, [r3, r2, lsl #2]\n"
    "    lsl    r12, r12, #8\n"
    "    /* jump_in lookup */\n"
    ".A1:\n"
    "    movs   r4, r5\n"
    "    beq    .A3\n"
    "    ldr    r3, [r5]\n"
    "    ldr    r5, [r4, #12]\n"
    "    teq    r3, r0\n"
    "    bne    .A1\n"
    "    ldr    r3, [r4, #4]\n"
    "    ldr    r4, [r4, #8]\n"
    "    tst    r3, r3\n"
    "    bne    .A1\n"
    ".A2:\n"
    "    mov    r5, r1\n"
    "    add    r1, r1, r12, asr #6\n"
    "    teq    r1, r4\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  pc, r4 /* Stale i-cache */\n"
    "    bl     add_link\n"
    "    sub    r2, r4, r5\n"
    "    and    r1, r7, #0xff000000\n"
    "    lsl    r2, r2, #6\n"
    "    sub    r1, r1, #2\n"
    "    add    r1, r1, r2, lsr #8\n"
    "    str    r1, [r5]\n"
    "    mov    pc, r4\n"
    ".A3:\n"
    "    /* hash_table lookup */\n"
    "    cmp    r2, #2048\n"
    "    ldr    r3, .jdptr_offset1\n"
    ".jdptr_pic1:\n"
    "    add    r3, pc, r3\n"
    "    eor    r4, r0, r0, lsl #16\n"
#ifdef __thumb__
    "    it     cc\n"
#endif /*__thumb__*/
    "    lslcc  r2, r0, #9\n"
    "    ldr    r6, .htptr_offset1\n"
    ".htptr_pic1:\n"
    "    add    r6, pc, r6\n"
    "    lsr    r4, r4, #12\n"
#ifdef __thumb__
    "    it     cc\n"
#endif /*__thumb__*/
    "    lsrcc  r2, r2, #21\n"
    "    bic    r4, r4, #15\n"
    "    ldr    r5, [r3, r2, lsl #2]\n"
#ifdef __thumb__
    "    ldr    r7, [r6, r4]\n"
    "    add    r6, r6, r4\n"
#else /*__thumb__*/
    "    ldr    r7, [r6, r4]!\n"
#endif /*__thumb__*/
    "    teq    r7, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r6, #4]\n"
    "    ldr    r7, [r6, #8]\n"
    "    teq    r7, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r6, #12]\n"
    "    /* jump_dirty lookup */\n"
    ".A6:\n"
    "    movs   r4, r5\n"
    "    beq    .A8\n"
    "    ldr    r3, [r5]\n"
    "    ldr    r5, [r4, #12]\n"
    "    teq    r3, r0\n"
    "    bne    .A6\n"
    ".A7:\n"
    "    ldr    r1, [r4, #8]\n"
    "    /* hash_table insert */\n"
    "    ldr    r2, [r6]\n"
    "    ldr    r3, [r6, #4]\n"
    "    str    r0, [r6]\n"
    "    str    r1, [r6, #4]\n"
    "    str    r2, [r6, #8]\n"
    "    str    r3, [r6, #12]\n"
    "    mov    pc, r1\n"
    ".A8:\n"
    "    mov    r4, r0\n"
    "    mov    r5, r1\n"
    "    bl     new_recompile_block\n"
    "    tst    r0, r0\n"
    "    mov    r0, r4\n"
    "    mov    r1, r5\n"
    "    beq    dyna_linker\n"
    "    /* pagefault */\n"
    "    mov    r1, r0\n"
    "    mov    r2, #8\n"
    "\n"
    LOCAL_FUNCTION("exec_pagefault")
    "    /* r0 = instruction pointer */\n"
    "    /* r1 = fault address */\n"
    "    /* r2 = cause */\n"
    "    ldr    r3, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
#ifdef __thumb__
    "    mvn    r6, vF000000F\n"
#else /*__thumb__*/
    "    mvn    r6, #0xF000000F\n"
#endif /*__thumb__*/
    "    ldr    r4, [fp, #g_cp0_regs+16-dynarec_local] /* Context */\n"
    "    bic    r6, r6, #0x0F800000\n"
    "    str    r0, [fp, #g_cp0_regs+56-dynarec_local] /* EPC */\n"
    "    orr    r3, r3, #2\n"
    "    str    r1, [fp, #g_cp0_regs+32-dynarec_local] /* BadVAddr */\n"
    "    bic    r4, r4, r6\n"
    "    str    r3, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    and    r5, r6, r1, lsr #9\n"
    "    str    r2, [fp, #g_cp0_regs+52-dynarec_local] /* Cause */\n"
    "    and    r1, r1, r6, lsl #9\n"
    "    str    r1, [fp, #g_cp0_regs+40-dynarec_local] /* EntryHi */\n"
    "    orr    r4, r4, r5\n"
    "    str    r4, [fp, #g_cp0_regs+16-dynarec_local] /* Context */\n"
    "    mov    r0, #0x80000000\n"
    "    bl     get_addr_ht\n"
    "    mov    pc, r0\n"
    "\n"
#ifdef __thumb__
    "    .align 2\n"
    "vF000000F:\n"
    "  .word    0xF000000F\n"
#endif /*__thumb__*/
    "/* Special dynamic linker for the case where a page fault\n"
    "   may occur in a branch delay slot */\n"
    GLOBAL_FUNCTION("dyna_linker_ds")
    "    /* r0 = virtual target address */\n"
    "    /* r1 = instruction to patch */\n"
    "    ldr    r4, .tlbptr_offset2\n"
    ".tlbptr_pic2:\n"
    "    add    r4, pc, r4\n"
    "    lsr    r5, r0, #12\n"
    "    mov    r12, r0\n"
    "    cmp    r0, #0xC0000000\n"
    "    mov    r6, #4096\n"
#ifdef __thumb__
    "    it     ge\n"
#endif /*__thumb__*/
    "    ldrge  r12, [r4, r5, lsl #2]\n"
    "    mov    r2, #0x80000\n"
    "    ldr    r3, .jiptr_offset2\n"
    ".jiptr_pic2:\n"
    "    add    r3, pc, r3\n"
    "    tst    r12, r12\n"
    "    sub    r6, r6, #1\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  r12, r0\n"
    "    ldr    r7, [r1]\n"
    "    eor    r2, r2, r12, lsr #12\n"
    "    and    r6, r6, r12, lsr #12\n"
    "    cmp    r2, #2048\n"
    "    add    r12, r7, #2\n"
#ifdef __thumb__
    "    it     cs\n"
#endif /*__thumb__*/
    "    orrcs  r2, r6, #2048\n"
    "    ldr    r5, [r3, r2, lsl #2]\n"
    "    lsl    r12, r12, #8\n"
    "    /* jump_in lookup */\n"
    ".B1:\n"
    "    movs   r4, r5\n"
    "    beq    .B3\n"
    "    ldr    r3, [r5]\n"
    "    ldr    r5, [r4, #12]\n"
    "    teq    r3, r0\n"
    "    bne    .B1\n"
    "    ldr    r3, [r4, #4]\n"
    "    ldr    r4, [r4, #8]\n"
    "    tst    r3, r3\n"
    "    bne    .B1\n"
    ".B2:\n"
    "    mov    r5, r1\n"
    "    add    r1, r1, r12, asr #6\n"
    "    teq    r1, r4\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  pc, r4 /* Stale i-cache */\n"
    "    bl     add_link\n"
    "    sub    r2, r4, r5\n"
    "    and    r1, r7, #0xff000000\n"
    "    lsl    r2, r2, #6\n"
    "    sub    r1, r1, #2\n"
    "    add    r1, r1, r2, lsr #8\n"
    "    str    r1, [r5]\n"
    "    mov    pc, r4\n"
    ".B3:\n"
    "    /* hash_table lookup */\n"
    "    cmp    r2, #2048\n"
    "    ldr    r3, .jdptr_offset2\n"
    ".jdptr_pic2:\n"
    "    add    r3, pc, r3\n"
    "    eor    r4, r0, r0, lsl #16\n"
#ifdef __thumb__
    "    it     cc\n"
#endif /*__thumb__*/
    "    lslcc  r2, r0, #9\n"
    "    ldr    r6, .htptr_offset2\n"
    ".htptr_pic2:\n"
    "    add    r6, pc, r6\n"
    "    lsr    r4, r4, #12\n"
#ifdef __thumb__
    "    it     cc\n"
#endif /*__thumb__*/
    "    lsrcc  r2, r2, #21\n"
    "    bic    r4, r4, #15\n"
    "    ldr    r5, [r3, r2, lsl #2]\n"
#ifdef __thumb__
    "    ldr    r7, [r6, r4]\n"
    "    add    r6, r6, r4\n"
#else /*__thumb__*/
    "    ldr    r7, [r6, r4]!\n"
#endif /*__thumb__*/
    "    teq    r7, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r6, #4]\n"
    "    ldr    r7, [r6, #8]\n"
    "    teq    r7, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r6, #12]\n"
    "    /* jump_dirty lookup */\n"
    ".B6:\n"
    "    movs   r4, r5\n"
    "    beq    .B8\n"
    "    ldr    r3, [r5]\n"
    "    ldr    r5, [r4, #12]\n"
    "    teq    r3, r0\n"
    "    bne    .B6\n"
    ".B7:\n"
    "    ldr    r1, [r4, #8]\n"
    "    /* hash_table insert */\n"
    "    ldr    r2, [r6]\n"
    "    ldr    r3, [r6, #4]\n"
    "    str    r0, [r6]\n"
    "    str    r1, [r6, #4]\n"
    "    str    r2, [r6, #8]\n"
    "    str    r3, [r6, #12]\n"
    "    mov    pc, r1\n"
    ".B8:\n"
    "    mov    r4, r0\n"
    "    bic    r0, r0, #7\n"
    "    mov    r5, r1\n"
    "    orr    r0, r0, #1\n"
    "    bl     new_recompile_block\n"
    "    tst    r0, r0\n"
    "    mov    r0, r4\n"
    "    mov    r1, r5\n"
    "    beq    dyna_linker_ds\n"
    "    /* pagefault */\n"
    "    bic    r1, r0, #7\n"
#ifdef __thumb__
    "    mov    r2, v80000008	/* High bit set indicates pagefault in delay slot */\n"
#else /*__thumb__*/
    "    mov    r2, #0x80000008 /* High bit set indicates pagefault in delay slot */\n"
#endif /*__thumb__*/
    "    sub    r0, r1, #4\n"
    "    b      exec_pagefault\n"
    "\n"
#ifdef __thumb__
    "    .align 2\n"
    "v80000008:\n"
    "  .word    0x80000008\n"
#endif /*__thumb__*/
    GLOBAL_FUNCTION("jump_vaddr_r0")
    "    eor    r2, r0, r0, lsl #16\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r1")
    "    eor    r2, r1, r1, lsl #16\n"
    "    mov    r0, r1\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r2")
    "    mov    r0, r2\n"
    "    eor    r2, r2, r2, lsl #16\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r3")
    "    eor    r2, r3, r3, lsl #16\n"
    "    mov    r0, r3\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r4")
    "    eor    r2, r4, r4, lsl #16\n"
    "    mov    r0, r4\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r5")
    "    eor    r2, r5, r5, lsl #16\n"
    "    mov    r0, r5\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r6")
    "    eor    r2, r6, r6, lsl #16\n"
    "    mov    r0, r6\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r8")
    "    eor    r2, r8, r8, lsl #16\n"
    "    mov    r0, r8\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r9")
    "    eor    r2, r9, r9, lsl #16\n"
    "    mov    r0, r9\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r10")
    "    eor    r2, r10, r10, lsl #16\n"
    "    mov    r0, r10\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r12")
    "    eor    r2, r12, r12, lsl #16\n"
    "    mov    r0, r12\n"
    "    b      jump_vaddr\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr_r7")
    "    eor    r2, r7, r7, lsl #16\n"
    "    add    r0, r7, #0\n"
    "\n"
    GLOBAL_FUNCTION("jump_vaddr")
    "    ldr    r1, .htptr_offset3\n"
    ".htptr_pic3:\n"
    "    add    r1, pc, r1\n"
    "    mvn    r3, #15\n"
    "    and    r2, r3, r2, lsr #12\n"
#ifdef __thumb__
    "    ldr    r2, [r1, r2]\n"
    "    add    r1, r1, r2\n"
#else /*__thumb__*/
    "    ldr    r2, [r1, r2]!\n"
#endif /*__thumb__*/
    "    teq    r2, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r1, #4]\n"
    "    ldr    r2, [r1, #8]\n"
    "    teq    r2, r0\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  pc, [r1, #12]\n"
    "    str    r10, [fp, #cycle_count-dynarec_local]\n"
    "    bl     get_addr\n"
    "    ldr    r10, [fp, #cycle_count-dynarec_local]\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("verify_code_ds")
    "    str    r8, [fp, #branch_target-dynarec_local]\n"
    "\n"
    GLOBAL_FUNCTION("verify_code_vm")
    "    /* r0 = instruction pointer (virtual address) */\n"
    "    /* r1 = source (virtual address) */\n"
    "    /* r2 = target */\n"
    "    /* r3 = length */\n"
    "    cmp    r1, #0xC0000000\n"
    "    blt    verify_code\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    lsr    r4, r1, #12\n"
    "    add    r5, r1, r3\n"
    "    sub    r5, #1\n"
    "    ldr    r6, [r12, r4, lsl #2]\n"
    "    lsr    r5, r5, #12\n"
    "    movs   r7, r6\n"
    "    bmi    .D5\n"
    "    add    r1, r1, r6, lsl #2\n"
    "    lsl    r6, r6, #2\n"
    ".D1:\n"
    "    add    r4, r4, #1\n"
    "    teq    r6, r7, lsl #2\n"
    "    bne    .D5\n"
    "    ldr    r7, [r12, r4, lsl #2]\n"
    "    cmp    r4, r5\n"
    "    bls    .D1\n"
    "\n"
    GLOBAL_FUNCTION("verify_code")
    "    /* r1 = source */\n"
    "    /* r2 = target */\n"
    "    /* r3 = length */\n"
    "    tst    r3, #4\n"
    "    mov    r4, #0\n"
    "    add    r3, r1, r3\n"
    "    mov    r5, #0\n"
#ifdef __thumb__
    "    it     ne\n"
#endif /*__thumb__*/
    "    ldrne  r4, [r1], #4\n"
    "    mov    r12, #0\n"
#ifdef __thumb__
    "    it     ne\n"
#endif /*__thumb__*/
    "    ldrne  r5, [r2], #4\n"
    "    teq    r1, r3\n"
    "    beq    .D3\n"
    ".D2:\n"
    "    ldr    r7, [r1], #4\n"
    "    eor    r9, r4, r5\n"
    "    ldr    r8, [r2], #4\n"
    "    orrs   r9, r9, r12\n"
    "    bne    .D4\n"
    "    ldr    r4, [r1], #4\n"
    "    eor    r12, r7, r8\n"
    "    ldr    r5, [r2], #4\n"
    "    cmp    r1, r3\n"
    "    bcc    .D2\n"
    "    teq    r7, r8\n"
    ".D3:\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    teqeq  r4, r5\n"
    ".D4:\n"
    "    ldr    r8, [fp, #branch_target-dynarec_local]\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  pc, lr\n"
    ".D5:\n"
    "    bl     get_addr\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("cc_interrupt")
    "    ldr    r0, [fp, #last_count-dynarec_local]\n"
    "    mov    r1, #0\n"
    "    mov    r2, #0x1fc\n"
    "    add    r10, r0, r10\n"
    "    str    r1, [fp, #pending_exception-dynarec_local]\n"
    "    and    r2, r2, r10, lsr #19\n"
    "    add    r3, fp, #restore_candidate-dynarec_local\n"
    "    str    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    ldr    r4, [r2, r3]\n"
    "    mov    r10, lr\n"
    "    tst    r4, r4\n"
    "    bne    .E4\n"
    ".E1:\n"
    "    bl     gen_interupt\n"
    "    mov    lr, r10\n"
    "    ldr    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    ldr    r0, [fp, #next_interupt-dynarec_local]\n"
    "    ldr    r1, [fp, #pending_exception-dynarec_local]\n"
    "    ldr    r2, [fp, #stop-dynarec_local]\n"
    "    str    r0, [fp, #last_count-dynarec_local]\n"
    "    sub    r10, r10, r0\n"
    "    tst    r2, r2\n"
    "    bne    .E3\n"
    "    tst    r1, r1\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    moveq  pc, lr\n"
    ".E2:\n"
    "    ldr    r0, [fp, #pcaddr-dynarec_local]\n"
    "    bl     get_addr_ht\n"
    "    mov    pc, r0\n"
    ".E3:\n"
    "    add    r12, fp, #28\n"
    "    ldmia  r12, {r4, r5, r6, r7, r8, r9, sl, fp, pc}\n"
    ".E4:\n"
    "    /* Move 'dirty' blocks to the 'clean' list */\n"
    "    lsl    r5, r2, #3\n"
    "    str    r1, [r2, r3]\n"
    "    mov    r6,    #0\n"
    ".E5:\n"
    "    lsrs   r4, r4, #1\n"
    "    add    r0, r5, r6\n"
#ifdef __thumb__
    "    it     cs\n"
#endif /*__thumb__*/
    "    blcs   clean_blocks\n"
    "    add    r6, r6, #1\n"
    "    tst    r6, #31\n"
    "    bne    .E5\n"
    "    b      .E1\n"
    "\n"
    GLOBAL_FUNCTION("do_interrupt")
    "    ldr    r0, [fp, #pcaddr-dynarec_local]\n"
    "    bl     get_addr_ht\n"
    "    ldr    r1, [fp, #next_interupt-dynarec_local]\n"
    "    ldr    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    str    r1, [fp, #last_count-dynarec_local]\n"
    "    sub    r10, r10, r1\n"
    "    add    r10, r10, #2\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("fp_exception")
    "    mov    r2, #0x10000000\n"
    ".E7:\n"
    "    ldr    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    mov    r3, #0x80000000\n"
    "    str    r0, [fp, #g_cp0_regs+56-dynarec_local] /* EPC */\n"
    "    orr    r1, #2\n"
    "    add    r2, r2, #0x2c\n"
    "    str    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    str    r2, [fp, #g_cp0_regs+52-dynarec_local] /* Cause */\n"
    "    add    r0, r3, #0x180\n"
    "    bl     get_addr_ht\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("fp_exception_ds")
    "    mov    r2, #0x90000000 /* Set high bit if delay slot */\n"
    "    b      .E7\n"
    "\n"
    GLOBAL_FUNCTION("jump_syscall")
    "    ldr    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    mov    r3, #0x80000000\n"
    "    str    r0, [fp, #g_cp0_regs+56-dynarec_local] /* EPC */\n"
    "    orr    r1, #2\n"
    "    mov    r2, #0x20\n"
    "    str    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    str    r2, [fp, #g_cp0_regs+52-dynarec_local] /* Cause */\n"
    "    add    r0, r3, #0x180\n"
    "    bl     get_addr_ht\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("indirect_jump_indexed")
    "    ldr    r0, [r0, r1, lsl #2]\n"
    "\n"
    GLOBAL_FUNCTION("indirect_jump")
    "    ldr    r12, [fp, #last_count-dynarec_local]\n"
    "    add    r2, r2, r12 \n"
    "    str    r2, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    mov    pc, r0\n"
    "\n"
    GLOBAL_FUNCTION("jump_eret")
    "    ldr    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    ldr    r0, [fp, #last_count-dynarec_local]\n"
    "    bic    r1, r1, #2\n"
    "    add    r10, r0, r10\n"
    "    str    r1, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    str    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    bl     check_interupt\n"
    "    ldr    r1, [fp, #next_interupt-dynarec_local]\n"
    "    ldr    r0, [fp, #g_cp0_regs+56-dynarec_local] /* EPC */\n"
    "    str    r1, [fp, #last_count-dynarec_local]\n"
    "    subs   r10, r10, r1\n"
    "    bpl    .E11\n"
    ".E8:\n"
    "    add    r6, fp, #reg+256-dynarec_local\n"
    "    mov    r5, #248\n"
    "    mov    r1, #0\n"
    ".E9:\n"
    "    ldr    r2, [r6, #-8]!\n"
    "    ldr    r3, [r6, #4]\n"
    "    eor    r3, r3, r2, asr #31\n"
    "    subs   r3, r3, #1\n"
    "    adc    r1, r1, r1\n"
    "    subs   r5, r5, #8\n"
    "    bne    .E9\n"
    "    ldr    r2, [fp, #hi-dynarec_local]\n"
    "    ldr    r3, [fp, #hi+4-dynarec_local]\n"
    "    eors   r3, r3, r2, asr #31\n"
    "    ldr    r2, [fp, #lo-dynarec_local]\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    ldreq  r3, [fp, #lo+4-dynarec_local]\n"
#ifdef __thumb__
    "    it     eq\n"
#endif /*__thumb__*/
    "    eoreq  r3, r3, r2, asr #31\n"
    "    subs   r3, r3, #1\n"
    "    adc    r1, r1, r1\n"
    "    bl     get_addr_32\n"
    "    mov    pc, r0\n"
    ".E11:\n"
    "    str    r0, [fp, #pcaddr-dynarec_local]\n"
    "    bl     cc_interrupt\n"
    "    ldr    r0, [fp, #pcaddr-dynarec_local]\n"
    "    b      .E8\n"
    "\n"
    GLOBAL_FUNCTION("new_dyna_start")
    "    ldr    r12, .dlptr_offset\n"
    ".dlptr_pic:\n"
    "    add    r12, pc, r12\n"
    "    ldr    r1, .outptr_offset\n"
    ".outptr_pic:\n"
    "    add    r1, pc, r1\n"
    "    mov    r0, #0xa4000000\n"
    "    stmia  r12, {r4, r5, r6, r7, r8, r9, sl, fp, lr}\n"
    "    sub    fp, r12, #28\n"
    "    ldr    r4, [r1]\n"
    "    add    r0, r0, #0x40\n"
    "    bl     new_recompile_block\n"
    "    ldr    r0, [fp, #next_interupt-dynarec_local]\n"
    "    ldr    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    str    r0, [fp, #last_count-dynarec_local]\n"
    "    sub    r10, r10, r0\n"
    "    mov    pc, r4\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r0")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r0, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r1")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r1, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r2")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r2, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r3")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r3, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r4")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r4, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r5")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r5, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r6")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r6, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r7")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r7, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r8")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r8, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r9")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r9, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r10")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r10, #12    \n"
    "    b      invalidate_addr_call\n"
    "\n"
    GLOBAL_FUNCTION("invalidate_addr_r12")
    "    stmia  fp, {r0, r1, r2, r3, r12, lr}\n"
    "    lsr    r0, r12, #12    \n"
    "\n"
    LOCAL_FUNCTION("invalidate_addr_call")
    "    bl     invalidate_block\n"
    "    ldmia  fp, {r0, r1, r2, r3, r12, pc}\n"
    "\n"
    GLOBAL_FUNCTION("write_rdram_new")
    "    ldr    r3, [fp, #ram_offset-dynarec_local]\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    ldr    r0, [fp, #cpu_word-dynarec_local]\n"
    "    str    r0, [r2, r3, lsl #2]\n"
    "    b      .E12\n"
    "\n"
    GLOBAL_FUNCTION("write_rdramb_new")
    "    ldr    r3, [fp, #ram_offset-dynarec_local]\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    ldrb   r0, [fp, #cpu_byte-dynarec_local]\n"
    "    eor    r2, r2, #3\n"
    "    strb   r0, [r2, r3, lsl #2]\n"
    "    b      .E12\n"
    "\n"
    GLOBAL_FUNCTION("write_rdramh_new")
    "    ldr    r3, [fp, #ram_offset-dynarec_local]\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    ldrh   r0, [fp, #cpu_hword-dynarec_local]\n"
    "    eor    r2, r2, #2\n"
    "    lsl    r3, r3, #2\n"
    "    strh   r0, [r2, r3]\n"
    "    b      .E12\n"
    "\n"
    GLOBAL_FUNCTION("write_rdramd_new")
    "    ldr    r3, [fp, #ram_offset-dynarec_local]\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "/*    ldrd    r0, [fp, #cpu_dword-dynarec_local]*/\n"
    "    ldr    r0, [fp, #cpu_dword-dynarec_local]\n"
    "    ldr    r1, [fp, #cpu_dword+4-dynarec_local]\n"
    "    add    r3, r2, r3, lsl #2\n"
    "    str    r0, [r3, #4]\n"
    "    str    r1, [r3]\n"
    "    b      .E12\n"
    "\n"
    LOCAL_FUNCTION("do_invalidate")
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    ".E12:\n"
    "    ldr    r1, [fp, #invc_ptr-dynarec_local]\n"
    "    lsr    r0, r2, #12\n"
    "    ldrb   r2, [r1, r0]\n"
    "    tst    r2, r2\n"
    "    beq    invalidate_block\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("read_nomem_new")
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #8\n"
    "    tst    r12, r12\n"
    "    bmi    tlb_exception\n"
    "    ldr    r0, [r2, r12, lsl #2]\n"
    "    str    r0, [fp, #readmem_dword-dynarec_local]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("read_nomemb_new")
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #8\n"
    "    tst    r12, r12\n"
    "    bmi    tlb_exception\n"
    "    eor    r2, r2, #3\n"
    "    ldrb   r0, [r2, r12, lsl #2]\n"
    "    str    r0, [fp, #readmem_dword-dynarec_local]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("read_nomemh_new")
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #8\n"
    "    tst    r12, r12\n"
    "    bmi    tlb_exception\n"
    "    lsl    r12, r12, #2\n"
    "    eor    r2, r2, #2\n"
    "    ldrh   r0, [r2, r12]\n"
    "    str    r0, [fp, #readmem_dword-dynarec_local]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("read_nomemd_new")
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #8\n"
    "    tst    r12, r12\n"
    "    bmi    tlb_exception\n"
    "    lsl    r12, r12, #2\n"
    "/*    ldrd    r0, [r2, r12]*/\n"
    "    add    r3, r2, #4\n"
    "    ldr    r0, [r2, r12]\n"
    "    ldr    r1, [r3, r12]\n"
    "    str    r0, [fp, #readmem_dword+4-dynarec_local]\n"
    "    str    r1, [fp, #readmem_dword-dynarec_local]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("write_nomem_new")
    "    str    r3, [fp, #24]\n"
    "    str    lr, [fp, #28]\n"
    "    bl     do_invalidate\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    ldr    lr, [fp, #28]\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r3, [fp, #24]\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #0xc\n"
    "    tst    r12, #0x40000000\n"
    "    bne    tlb_exception\n"
    "    ldr    r0, [fp, #cpu_word-dynarec_local]\n"
    "    str    r0, [r2, r12, lsl #2]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("write_nomemb_new")
    "    str    r3, [fp, #24]\n"
    "    str    lr, [fp, #28]\n"
    "    bl     do_invalidate\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    ldr    lr, [fp, #28]\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r3, [fp, #24]\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #0xc\n"
    "    tst    r12, #0x40000000\n"
    "    bne    tlb_exception\n"
    "    eor    r2, r2, #3\n"
    "    ldrb   r0, [fp, #cpu_byte-dynarec_local]\n"
    "    strb   r0, [r2, r12, lsl #2]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("write_nomemh_new")
    "    str    r3, [fp, #24]\n"
    "    str    lr, [fp, #28]\n"
    "    bl     do_invalidate\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    ldr    lr, [fp, #28]\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r3, [fp, #24]\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #0xc\n"
    "    lsls   r12, #2\n"
    "    bcs    tlb_exception\n"
    "    eor    r2, r2, #2\n"
    "    ldrh   r0, [fp, #cpu_hword-dynarec_local]\n"
    "    strh   r0, [r2, r12]\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("write_nomemd_new")
    "    str    r3, [fp, #24]\n"
    "    str    lr, [fp, #28]\n"
    "    bl     do_invalidate\n"
    "    ldr    r2, [fp, #address-dynarec_local]\n"
    "    add    r12, fp, #memory_map-dynarec_local\n"
    "    ldr    lr, [fp, #28]\n"
    "    lsr    r0, r2, #12\n"
    "    ldr    r3, [fp, #24]\n"
    "    ldr    r12, [r12, r0, lsl #2]\n"
    "    mov    r1, #0xc\n"
    "    lsls   r12, #2\n"
    "    bcs    tlb_exception\n"
    "    add    r3, r2, #4\n"
    "    ldr    r0, [fp, #cpu_dword+4-dynarec_local]\n"
    "    ldr    r1, [fp, #cpu_dword-dynarec_local]\n"
    "/*    strd    r0, [r2, r12]*/\n"
    "    str    r0, [r2, r12]\n"
    "    str    r1, [r3, r12]\n"
    "    mov    pc, lr\n"
    "\n"
    LOCAL_FUNCTION("tlb_exception")
    "    /* r1 = cause */\n"
    "    /* r2 = address */\n"
    "    /* r3 = instr addr/flags */\n"
    "    ldr    r4, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    add    r5, fp, #memory_map-dynarec_local\n"
    "    lsr    r6, r3, #12\n"
    "    orr    r1, r1, r3, lsl #31\n"
    "    orr    r4, r4, #2\n"
    "    ldr    r7, [r5, r6, lsl #2]\n"
    "    bic    r8, r3, #3\n"
    "    str    r4, [fp, #g_cp0_regs+48-dynarec_local] /* Status */\n"
    "    mov    r6, #0x6000000\n"
    "    str    r1, [fp, #g_cp0_regs+52-dynarec_local] /* Cause */\n"
    "    orr    r6, r6, #0x22\n"
    "    ldr    r0, [r8, r7, lsl #2]\n"
    "    add    r4, r8, r1, asr #29\n"
    "    add    r5, fp, #reg-dynarec_local\n"
    "    str    r4, [fp, #g_cp0_regs+56-dynarec_local] /* EPC */\n"
    "    mov    r7, #0xf8\n"
    "    ldr    r8, [fp, #g_cp0_regs+16-dynarec_local] /* Context */\n"
    "    lsl    r1, r0, #16\n"
    "    lsr    r4, r0,    #26\n"
    "    and    r7, r7, r0, lsr #18\n"
#ifdef __thumb__
    "    mvn    r9, vF000000F\n"
#else /*__thumb__*/
    "    mvn    r9, #0xF000000F\n"
#endif /*__thumb__*/
    "    sub    r2, r2, r1, asr #16\n"
    "    bic    r9, r9, #0x0F800000\n"
    "    rors   r6, r6, r4\n"
    "    mov    r0, #0x80000000\n"
#ifdef __thumb__
    "    it     cs\n"
#endif /*__thumb__*/
    "    ldrcs  r2, [r5, r7]\n"
    "    bic    r8, r8, r9\n"
    "    tst    r3, #2\n"
    "    str    r2, [r5, r7]\n"
    "    add    r4, r2, r1, asr #16\n"
    "    add    r6, fp, #reg+4-dynarec_local\n"
    "    asr    r3, r2, #31\n"
    "    str    r4, [fp, #g_cp0_regs+32-dynarec_local] /* BadVAddr */\n"
    "    add    r0, r0, #0x180\n"
    "    and    r4, r9, r4, lsr #9\n"
#ifdef __thumb__
    "    it     ne\n"
#endif /*__thumb__*/
    "    strne  r3, [r6, r7]\n"
    "    orr    r8, r8, r4\n"
    "    str    r8, [fp, #g_cp0_regs+16-dynarec_local] /* Context */\n"
    "    bl     get_addr_ht\n"
    "    ldr    r1, [fp, #next_interupt-dynarec_local]\n"
    "    ldr    r10, [fp, #g_cp0_regs+36-dynarec_local] /* Count */\n"
    "    str    r1, [fp, #last_count-dynarec_local]\n"
    "    sub    r10, r10, r1\n"
    "    mov    pc, r0    \n"
    "\n"
    GLOBAL_FUNCTION("breakpoint")
    "    /* Set breakpoint here for debugging */\n"
    "    mov    pc, lr\n"
    "\n"
    GLOBAL_FUNCTION("__clear_cache_bugfix")
    "    /*  The following bug-fix implements __clear_cache (missing in Android)  */\n"
    "    push   {r7, lr}\n"
    "    mov    r2, #0\n"
    "    mov    r7, #0x2\n"
    "    add    r7, r7, #0xf0000\n"
    "    svc    0x00000000\n"
    "    pop    {r7, pc}\n"
    "\n"
    END_SECTION
    );
