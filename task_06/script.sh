#! /bin/sh

echo "read from the device"
cat /dev/eudyptula

echo ""
echo "write to the device"
echo 19aa2fa32708 > /dev/eudyptula
echo "Succeed"