#!/bin/bash
# A code generator to generate calls to run_me_??
# which glues the XOMP runtime library and Fortran 77 outlined functions

# Liao 12/13/2010

# max number of subroutine parameters
# this number should be the same value as MAX_OUTLINED_FUNC_PARAMETER_COUNT
# from libxomp.h

MAX_PARAMETER_COUNT=256
echo "/* This file is automatically generated from $0 "
echo " * Maximum number of subroutine parameters is $MAX_PARAMETER_COUNT "
echo " * To regenerate run_me_callers.inc, type $0 > run_me_callers.inc */"

for ((c=1; c<=$MAX_PARAMETER_COUNT; c++))
do
  echo "      case $c:"
  echo "            XOMP_parallel_start (run_me_$c, (void*) g_parameter, *ifClauseValue, *numThread, NULL, 0);"
  echo "            break; "
done  