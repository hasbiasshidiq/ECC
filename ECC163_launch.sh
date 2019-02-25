#! /bin/bash

# Update PATH
FUNCTIONS=/lib/firmware
export PATH=$FUNCTIONS:$PATH

#!/bin/bash

mount -t configfs configfs /config
rmdir /config/device-tree/overlays/test
mkdir /config/device-tree/overlays/test

START=$(($(date +%s%N)/1000000))
echo ECC163.dtbo > /config/device-tree/overlays/test/path
END=$(($(date +%s%N)/1000000))

DIFF=$(( $END - $START -4)) #offset = 4 micro seconds
echo "Reconfigurable process took $DIFF micro seconds"

# Memory address
WRITE_ADDR=0x02000000
READ_ADDR=0x01000000

WRITE_ADDR2=0x02000000

WORK_FOLDER=/lib/firmware
: ${CS_TIME:=0}
INPUT_BIN=input_ecc163.bin
REFERENCE_BIN=output_ecc163.bin
OUTPUT_BIN=result_ecc163.bin

EXEC_TIME=0xff200040
EXTRACT_TIME=0xff200044
RESTORE_TIME=0xff200048
LATENCY_TIME=0xff20004c
DELAY_TIME=0xff200050

# Static address for AXI slave
CFG_WADDR=0xff200000
CFG_RADDR=0xff200004
CFG_CPADDR=0xff200008
CFG_WDONE=0xff20000c
CFG_NBDATA=0xff200010
CFG_RDONE=0xff200014
CFG_COMMAND=0xff200018
CFG_CSTIME=0xff20001c

# Init
input_bytes=$(wc -c < "$WORK_FOLDER/$INPUT_BIN")
inputs=$(($input_bytes/4))

output_bytes=$(wc -c < "$WORK_FOLDER/$REFERENCE_BIN")
outputs=$(($output_bytes/4))

# Flush memory for input and output placement
write_zero $READ_ADDR $inputs
write_zero $WRITE_ADDR $outputs

# Write data input from file to memory
write_input_mem $READ_ADDR $WORK_FOLDER/$INPUT_BIN

comm_axi $CFG_RADDR -w $READ_ADDR

comm_axi $CFG_NBDATA -w $inputs
comm_axi $CFG_WADDR -w $WRITE_ADDR2

comm_axi $CFG_COMMAND -w 0x1

sleep 0.1

# Read the total output from memory to file
read_output_mem $WRITE_ADDR2 $outputs $WORK_FOLDER/$OUTPUT_BIN

input_done=$(comm_axi $CFG_RDONE -o)
output_done=$(comm_axi $CFG_WDONE -o)
echo "******************************************"
echo "Input done : $input_done"
echo "Output done : $output_done"
echo "******************************************"

echo " "
echo "--------------------------PRIVATE KEY--------------------------"
xxd $INPUT_BIN
echo " "
echo "---------------------------PUBLIC KEY--------------------------"
xxd $OUTPUT_BIN

total_time=$(comm_axi $EXEC_TIME -o)
#$ echo $((32#$total_time))
echo "******************************************"

printf "Clock cycles : %d\n" $total_time
#printf %d $total_time
echo " "

umount /config
