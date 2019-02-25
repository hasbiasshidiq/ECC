CFILE = ECC163.c

AUGH_TECHNO = -p xilinx -chip xc7v585t -speed 3 -package ffg1157 -freq 100M

AUGH_PARAM1 = $(AUGH_TECHNO) -script script_init -chip-ratio 80%
AUGH_PARAM2 = $(AUGH_TECHNO) -script script_opt -chip-ratio 80%

initial:
	rm -rf vhdl/*.vhd
	augh -v $(AUGH_PARAM1) $(CFILE) | tee init_compil.log

optimized:
	rm -rf vhdl/*.vhd
	augh -v $(AUGH_PARAM2) $(CFILE) | tee optimized_compil.log

vectors:
	echo "Test vectors..."
	gcc --std=gnu99 -o test_vectors test_vectors.c
	./test_vectors > input_vectors.bin
	echo "Execution for output vectors..."
	gcc --std=gnu99 -I$(AUGH_HOME)/include -DGCC_COMPIL -o bc3 bc3.c
	cat input_vectors.bin | ./idct > output_vectors.bin
	
altera:
	augh -v -p altera -board a5soc -script script_opt ECC163.c

clean:
	rm *.log
	rm -rf vhdl/

mrpropre:
	rm *.bin
	rm idct
	rm test_vectors
