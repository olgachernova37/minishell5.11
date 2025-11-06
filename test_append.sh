#!/bin/bash
# Test export VAR+=value functionality

echo "=== Test 1: Basic append ==="
export VAR=hello
echo "VAR=$VAR"
export VAR+=world
echo "VAR=$VAR"
echo ""

echo "=== Test 2: Append to empty variable ==="
export EMPTY
echo "EMPTY='$EMPTY'"
export EMPTY+=value
echo "EMPTY='$EMPTY'"
echo ""

echo "=== Test 3: Append multiple times ==="
export PATH2=/bin
echo "PATH2=$PATH2"
export PATH2+=":/usr/bin"
echo "PATH2=$PATH2"
export PATH2+=":/usr/local/bin"
echo "PATH2=$PATH2"
echo ""

echo "=== Test 4: Append with spaces ==="
export MSG="Hello"
echo "MSG=$MSG"
export MSG+=" World"
echo "MSG=$MSG"
echo ""

echo "=== Test 5: Append to non-existing variable ==="
unset NEWVAR 2>/dev/null
export NEWVAR+=first
echo "NEWVAR=$NEWVAR"
echo ""

echo "=== Test 6: Exit status ==="
export TEST=ok
export TEST+=more
echo "Exit status: $?"
echo "TEST=$TEST"
echo ""

echo "=== Test 7: Invalid append syntax ==="
export BAD+VALUE=test
echo "Exit status: $?"
echo ""

echo "Tests complete!"
