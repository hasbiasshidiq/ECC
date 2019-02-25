#CFILE = genericcomb.c
CFILE = ECC163.c

AUGH_TECHNO = -p xilinx -chip xc7v585t -speed 3 -package ffg1157 -freq 100M

AUGH_PARAMS = $(AUGH_TECHNO) -script cmds.transcript.txt

augh:
	rm -rf vhdl/*.vhd
	augh -v $(AUGH_PARAMS) $(CFILE) | tee compile_log.txt


