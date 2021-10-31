/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Mappa

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

***************************************************************************************************/

#ifndef ZYDIS_FUZZSHARED_H
#define ZYDIS_FUZZSHARED_H

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>
#include <Zycore/LibC.h>

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

typedef ZyanUSize(*ZydisStreamRead)(void *ctx, ZyanU8 *buf, ZyanUSize max_len);

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

#if defined(ZYDIS_FUZZ_AFL_FAST) || defined(ZYDIS_LIBFUZZER)
#   define ZYDIS_MAYBE_FPUTS(x, y)
#else
#   define ZYDIS_MAYBE_FPUTS(x, y) fputs(x, y)
#endif

#define ZYDIS_SANITIZE_MASK(var, type, mask)      var = (type)((ZyanUSize)(var) & (mask))
#define ZYDIS_SANITIZE_ENUM(var, type, max_value) var = (type)((ZyanUSize)(var) % (max_value + 1))

/* ============================================================================================== */
/* Function declarations                                                                          */
/* ============================================================================================== */

#if defined(ZYDIS_FUZZ_AFL_FAST) || defined(ZYDIS_LIBFUZZER)

#define ZydisPrintInstruction(...)

#else

void ZydisPrintInstruction(const ZydisDecodedInstruction *instruction,
    const ZyanU8 *instruction_bytes);

#endif

void ZydisValidateEnumRanges(const ZydisDecodedInstruction *insn);
void ZydisValidateInstructionIdentity(const ZydisDecodedInstruction *insn1,
    const ZydisDecodedInstruction *insn2);
void ZydisReEncodeInstruction(const ZydisDecoder *decoder, const ZydisDecodedInstruction *insn1,
    const ZyanU8 *insn1_bytes);

// One `ZydisFuzzTarget` must be defined for every fuzz target project
extern int ZydisFuzzTarget(ZydisStreamRead read_fn, void *stream_ctx);

/* ============================================================================================== */

#endif /* ZYDIS_FUZZSHARED_H */
