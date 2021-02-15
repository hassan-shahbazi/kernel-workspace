#! /bin/sh

echo "read from id"
cat /sys/kernel/debug/eudyptula/id
echo ""

echo "write to the id"
echo 19aa2fa32708 > /sys/kernel/debug/eudyptula/id
echo "Succeed"

echo "read from jiffies"
cat /sys/kernel/debug/eudyptula/jiffies
echo ""
