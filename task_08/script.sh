#! /bin/sh

echo "read from the device"
cat /sys/kernel/debug/eudyptula/id

echo ""
echo "write to the device"
echo 19aa2fa32708 > /sys/kernel/debug/eudyptula/id
echo "Succeed"
