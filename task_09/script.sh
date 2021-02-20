#! /bin/sh

echo "read from id"
cat /sys/kernel/eudyptula/id
echo ""

echo "write to the id"
echo 19aa2fa32708 > /sys/kernel/eudyptula/id
echo "Succeed"

echo "read from jiffies"
cat /sys/kernel/eudyptula/jiffies
echo ""

echo "write to foo: 'test_input'"
echo test_input > /sys/kernel/eudyptula/foo
echo "Succeed"

echo "read from foo"
cat /sys/kernel/eudyptula/foo
