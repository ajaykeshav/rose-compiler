add_library(roseDisassemblers OBJECT
  InstructionEnumsMips.h InstructionEnumsX86.h Assembler.C AssemblerX86.C
  AssemblerX86Init1.C AssemblerX86Init2.C AssemblerX86Init3.C
  AssemblerX86Init4.C AssemblerX86Init5.C AssemblerX86Init6.C
  AssemblerX86Init7.C AssemblerX86Init8.C AssemblerX86Init9.C
  AssemblerX86Init.C DisassemblerA64.C Disassembler.C DisassemblerMips.C
  DisassemblerM68k.C DisassemblerNull.C DisassemblerPowerpc.C DisassemblerX86.C
  Registers.C RegisterDescriptor.C SgAsmA64Instruction.C SgAsmBlock.C SgAsmExecutableFileFormat.C SgAsmExpression.C
  SgAsmFloatValueExpression.C SgAsmFunction.C SgAsmInstruction.C
  SgAsmIntegerValueExpression.C SgAsmInterpretation.C SgAsmType.C
  SgAsmM68kInstruction.C SgAsmMipsInstruction.C SgAsmNullInstruction.C SgAsmPowerpcInstruction.C
  SgAsmX86Instruction.C x86InstructionProperties.C RegisterParts.C
  BinaryInstructionCache.C)

add_dependencies(roseDisassemblers rosetta_generated)

########### install files ###############

install(
  FILES
    Assembler.h AssemblerX86.h AssemblerX86Init.h Disassembler.h
    DisassemblerA64.h DisassemblerM68k.h
    DisassemblerMips.h DisassemblerNull.h DisassemblerPowerpc.h DisassemblerX86.h
    InstructionEnumsM68k.h x86InstructionProperties.h
    InstructionEnumsA64.h InstructionEnumsMips.h InstructionEnumsX86.h
    Registers.h RegisterDescriptor.h InstructionEnumsPowerpc.h RegisterParts.h
    BinaryInstructionCache.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
