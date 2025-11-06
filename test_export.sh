#!/bin/bash
# Quick Export Test Script for Minishell
# Run this in both bash and minishell to compare outputs

echo "=== BASIC EXPORT TESTS ==="
export TEST1=hello
echo "TEST1=$TEST1"

export TEST2="hello world"
echo "TEST2=$TEST2"

export TEST3
echo "TEST3=$TEST3"

echo ""
echo "=== INVALID IDENTIFIER TESTS ==="
export 1VAR=value 2>&1 | head -1
export VAR-NAME=value 2>&1 | head -1
export = 2>&1 | head -1

echo ""
echo "=== MULTIPLE EXPORTS ==="
export A=1 B=2 C=3
echo "A=$A B=$B C=$C"

echo ""
echo "=== OVERWRITE EXISTING ==="
export MYVAR=first
echo "MYVAR=$MYVAR"
export MYVAR=second
echo "MYVAR=$MYVAR"

echo ""
echo "=== EXPORT WITH EXPANSION ==="
export HOMECOPY=$HOME
echo "HOMECOPY=$HOMECOPY"

echo ""
echo "=== EXPORT WITH SPECIAL CHARS ==="
export SPECIAL="a=b=c"
echo "SPECIAL=$SPECIAL"

export PATH2="/usr/bin:/bin"
echo "PATH2=$PATH2"

echo ""
echo "=== VALID VARIABLE NAMES ==="
export _VAR=underscore
export VAR_123=mixed
export ALLCAPS=caps
echo "_VAR=$_VAR VAR_123=$VAR_123 ALLCAPS=$ALLCAPS"

echo ""
echo "=== EXIT STATUS ==="
export VALID=yes
echo "Valid export exit status: $?"

export 123INVALID=no 2>/dev/null
echo "Invalid export exit status: $?"

echo ""
echo "=== EXPORT DISPLAY (first 10 lines) ==="
export | head -10

echo ""
echo "=== CLEANUP ==="
unset TEST1 TEST2 TEST3 A B C MYVAR HOMECOPY SPECIAL PATH2 _VAR VAR_123 ALLCAPS VALID
echo "Tests complete!"
