/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_CPU_DEBUG_INFO_H_
#define XENIA_CPU_DEBUG_INFO_H_

#include <cstddef>
#include <cstdint>

namespace xe {
namespace cpu {

enum DebugInfoFlags {
  DEBUG_INFO_NONE = 0,
  DEBUG_INFO_SOURCE_DISASM = (1 << 1),
  DEBUG_INFO_RAW_HIR_DISASM = (1 << 2),
  DEBUG_INFO_HIR_DISASM = (1 << 3),
  DEBUG_INFO_MACHINE_CODE_DISASM = (1 << 4),
  DEBUG_INFO_SOURCE_MAP = (1 << 5),
  DEBUG_INFO_DEFAULT = DEBUG_INFO_SOURCE_MAP,
  DEBUG_INFO_ALL_DISASM = 0xFFFF,
};

typedef struct SourceMapEntry_s {
  uint32_t source_offset;  // Original source address/offset.
  uint32_t hir_offset;     // Block ordinal (16b) | Instr ordinal (16b)
  uint32_t code_offset;    // Offset from emitted code start.
} SourceMapEntry;

class DebugInfo {
 public:
  DebugInfo();
  ~DebugInfo();

  const char* source_disasm() const { return source_disasm_; }
  void set_source_disasm(char* value) { source_disasm_ = value; }
  const char* raw_hir_disasm() const { return raw_hir_disasm_; }
  void set_raw_hir_disasm(char* value) { raw_hir_disasm_ = value; }
  const char* hir_disasm() const { return hir_disasm_; }
  void set_hir_disasm(char* value) { hir_disasm_ = value; }
  const char* machine_code_disasm() const { return machine_code_disasm_; }
  void set_machine_code_disasm(char* value) { machine_code_disasm_ = value; }

  void InitializeSourceMap(size_t source_map_count, SourceMapEntry* source_map);
  SourceMapEntry* LookupSourceOffset(uint32_t offset);
  SourceMapEntry* LookupHIROffset(uint32_t offset);
  SourceMapEntry* LookupCodeOffset(uint32_t offset);

 private:
  char* source_disasm_;
  char* raw_hir_disasm_;
  char* hir_disasm_;
  char* machine_code_disasm_;

  size_t source_map_count_;
  SourceMapEntry* source_map_;
};

}  // namespace cpu
}  // namespace xe

#endif  // XENIA_CPU_DEBUG_INFO_H_
