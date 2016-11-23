/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 * 
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */
#if defined(__ARM_NEON__)

#if defined(__thumb__)
#define DECL_ARMMODE(x) "  .align 2\n" "  .global " x "\n" "  .thumb\n" "  .thumb_func\n" "  .type " x ", %function\n" x ":\n"
#else
#define DECL_ARMMODE(x) "  .align 4\n" "  .global " x "\n" "  .arm\n" x ":\n"
#endif

asm(
    "# void process_sinc_neon(float *out, const float *left, const float *right, const float *coeff, unsigned taps)\n"
    "# Assumes taps is >= 8, and a multiple of 8.\n"
    DECL_ARMMODE("process_sinc_neon_asm")
    DECL_ARMMODE("_process_sinc_neon_asm")
    "\n"
    "   push {r4, lr}   \n"
    "   vmov.f32 q0, #0.0\n"
    "   vmov.f32 q8, #0.0\n"
    "\n"
    "   # Taps argument (r4) goes on stack in armeabi.\n"
    "   ldr r4, [sp, #8]\n"
    "\n"
    "1:\n"
    "   # Left\n"
    "   vld1.f32 {q2-q3}, [r1]!\n"
    "   # Right\n"
    "   vld1.f32 {q10-q11}, [r2]!\n"
    "   # Coeff\n"
    "   vld1.f32 {q12-q13}, [r3, :128]!\n"
    "\n"
    "   # Left / Right\n"
    "   vmla.f32 q0, q2, q12\n"
    "   vmla.f32 q8, q10, q12\n"
    "   vmla.f32 q0, q3, q13\n"
    "   vmla.f32 q8, q11, q13\n"
    "\n"
    "   subs r4, r4, #8\n"
    "   bne 1b\n"
    "\n"
    "   # Add everything together\n"
    "   vadd.f32 d0, d0, d1\n"
    "   vadd.f32 d16, d16, d17\n"
    "   vpadd.f32 d0, d0, d16\n"
    "   vst1.f32 d0, [r0]\n"
    "   \n"
    "   pop {r4, pc}\n"
    "\n");

#endif
