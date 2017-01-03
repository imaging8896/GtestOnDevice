#!/bin/sh

PROJ_DIR=TestAPIServer

export device=$1

################# setup #################
adb -s $device pull /system/lib64/libHCFS_api.so ./$PROJ_DIR
adb -s $device pull /system/lib64/libjansson.so ./$PROJ_DIR

python buildTest.py

rm $PROJ_DIR/libHCFS_api.so
rm $PROJ_DIR/libjansson.so

make install

adb -s $device shell su 0 setenforce 0
#########################################

adb -s $device shell "LD_LIBRARY_PATH=/data/local/tmp /data/local/tmp/API_server_test --gtest_color=yes --gtest_output=xml:/data/local/tmp/report.xml"

################# teardown #################
adb -s $device pull /data/local/tmp/HCFS_API_log .
adb -s $device pull /data/local/tmp/report.xml .

adb -s $device shell rm /data/local/tmp/API_server_test
adb -s $device shell rm /data/local/tmp/libgnustl_shared.so

adb -s $device shell su 0 setenforce 1

make clean
############################################

