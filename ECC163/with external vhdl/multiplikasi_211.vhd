library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;   

-- WARNING: The default VHDL generator shouldn't be used (comp 'multiplikasi_211' model 'multiplikasi')

entity multiplikasi_211 is
	port (
		-- Ports not part of access
		data_out : out std_logic_vector(63 downto 0);
		get_part : in  std_logic_vector(7 downto 0);
		inA_0 : in  std_logic_vector(31 downto 0);
		inA_1 : in  std_logic_vector(31 downto 0);
		inA_2 : in  std_logic_vector(31 downto 0);
		inA_3 : in  std_logic_vector(31 downto 0);
		inA_4 : in  std_logic_vector(31 downto 0);
		inA_5 : in  std_logic_vector(31 downto 0);
		inB_0 : in  std_logic_vector(31 downto 0);
		inB_1 : in  std_logic_vector(31 downto 0);
		inB_2 : in  std_logic_vector(31 downto 0);
		inB_3 : in  std_logic_vector(31 downto 0);
		inB_4 : in  std_logic_vector(31 downto 0);
		inB_5 : in  std_logic_vector(31 downto 0)
	);

	-- merepresentasikan perkalian 2x2
	function func2(in2_1, in2_2: in std_logic_vector(1 downto 0)) return std_logic_vector is
	variable output2 : std_logic_vector(3 downto 0);
	begin
		output2(0) := in2_1(0) and in2_2(0);
		output2(1) := (in2_1(1) and in2_2(0))xor(in2_1(0) and in2_2(1));
		output2(2) := in2_1(1) and in2_2(1);
		output2(3) := '0';
		return output2;
	end func2;
	
	-- merepresentasikan perkalian 4x4
	function func4(in4_00, in4_01, in4_10, in4_11 : in std_logic_vector(3 downto 0)) 
	return std_logic_vector is
	variable output4 : std_logic_vector(7 downto 0);
	begin
		output4(1 downto 0) := in4_00(1 downto 0);
		output4(3 downto 2) := in4_01(1 downto 0) xor in4_00(3 downto 2) xor in4_10(1 downto 0);
		output4(5 downto 4) := in4_01(3 downto 2) xor in4_11(1 downto 0) xor in4_10(3 downto 2);
		output4(7 downto 6) := in4_11(3 downto 2);
		return output4;
	end func4;
	
	-- merepresentasikan perkalian 8x8
	function func8(in8_00, in8_01, in8_10, in8_11 : in std_logic_vector(7 downto 0)) 
	return std_logic_vector is
	variable output8 : std_logic_vector(15 downto 0);
	begin
		output8(3 downto 0) := in8_00(3 downto 0);
		output8(7 downto 4) := in8_01(3 downto 0) xor in8_00(7 downto 4) xor in8_10(3 downto 0);
		output8(11 downto 8) := in8_01(7 downto 4) xor in8_11(3 downto 0) xor in8_10(7 downto 4);
		output8(15 downto 12) := in8_11(7 downto 4);
		return output8;
	end func8;
	
	-- merepresentasikan perkalian 16x16
	function func16(in16_00, in16_01, in16_10, in16_11 : in std_logic_vector(15 downto 0)) 
	return std_logic_vector is
	variable output16 : std_logic_vector(31 downto 0);
	begin
		output16(7 downto 0) := in16_00(7 downto 0);
		output16(15 downto 8) := in16_01(7 downto 0) xor in16_00(15 downto 8) xor in16_10(7 downto 0);
		output16(23 downto 16) := in16_01(15 downto 8) xor in16_11(7 downto 0) xor in16_10(15 downto 8);
		output16(31 downto 24) := in16_11(15 downto 8);
		return output16;
	end func16;
	
	-- merepresentasikan perkalian 32x32
	function func32(in32_00, in32_01, in32_10, in32_11 : in std_logic_vector(31 downto 0)) 
	return std_logic_vector is
	variable output32 : std_logic_vector(63 downto 0);
	begin
		output32(15 downto 0) := in32_00(15 downto 0);
		output32(31 downto 16) := in32_01(15 downto 0) xor in32_00(31 downto 16) xor in32_10(15 downto 0);
		output32(47 downto 32) := in32_01(31 downto 16) xor in32_11(15 downto 0) xor in32_10(31 downto 16);
		output32(63 downto 48) := in32_11(31 downto 16);
		return output32;
	end func32;
	
	-- merepresentasikan perkalian 64x64
	function func64(in64_00, in64_01, in64_10, in64_11 : in std_logic_vector(63 downto 0)) 
	return std_logic_vector is
	variable output64 : std_logic_vector(127 downto 0);
	begin
		output64(31 downto 0) := in64_00(31 downto 0);
		output64(63 downto 32) := in64_01(31 downto 0) xor in64_00(63 downto 32) xor in64_10(31 downto 0);
		output64(95 downto 64) := in64_01(63 downto 32) xor in64_11(31 downto 0) xor in64_10(63 downto 32);
		output64(127 downto 96) := in64_11(63 downto 32);
		return output64;
	end func64;
	
	-- merepresentasikan perkalian 192x192
	function func192(in192_00, in192_01, in192_02, in192_10, in192_11, in192_12, in192_20, in192_21, in192_22 : 
	in std_logic_vector(127 downto 0)) return std_logic_vector is
	variable output192 : std_logic_vector(383 downto 0);
	begin
		output192(63 downto 0) := in192_00(63 downto 0);
		output192(127 downto 64) := in192_00(127 downto 64) xor in192_01(63 downto 0) xor in192_10(63 downto 0);
		output192(191 downto 128) := in192_02(63 downto 0) xor in192_01(127 downto 64) xor in192_11(63 downto 0) xor in192_10(127 downto 64) xor in192_20(63 downto 0);
		output192(255 downto 192) := in192_02(127 downto 64) xor in192_12(63 downto 0) xor in192_11(127 downto 64) xor in192_21(63 downto 0) xor in192_20(127 downto 64);
		output192(319 downto 256) := in192_12(127 downto 64) xor in192_22(63 downto 0) xor in192_21(127 downto 64);
		output192(383 downto 320) := in192_22(127 downto 64);
		return output192;
	end func192;
	
	function pars_4(in_A, in_B : in std_logic_vector(3 downto 0)) return std_logic_vector is 
	
	variable out_pars_4 : std_logic_vector(7 downto 0);
	
	variable in_1 : std_logic_vector(1 downto 0);
	variable in_2 : std_logic_vector(1 downto 0);
	variable in_3 : std_logic_vector(1 downto 0);
	variable in_4 : std_logic_vector(1 downto 0);
	
	variable out_1 : std_logic_vector(3 downto 0);
	variable out_2 : std_logic_vector(3 downto 0);
	variable out_3 : std_logic_vector(3 downto 0);
	variable out_4 : std_logic_vector(3 downto 0);
	
	begin
		in_1 := in_A(1 downto 0);
		in_2 := in_A(3 downto 2);
		in_3 := in_B(1 downto 0);
		in_4 := in_B(3 downto 2);
		
		out_1 := func2(in_1, in_3);
		out_2 := func2(in_2, in_3);
		out_3 := func2(in_1, in_4);
		out_4 := func2(in_2, in_4);
		
		out_pars_4 := func4(out_1, out_2, out_3, out_4);
		
		return out_pars_4;	
	end pars_4;
	
	function pars_8(in_A, in_B : in std_logic_vector(7 downto 0)) return std_logic_vector is 
	
	variable out_pars_8 : std_logic_vector(15 downto 0);
	
	variable in_1 : std_logic_vector(3 downto 0);
	variable in_2 : std_logic_vector(3 downto 0);
	variable in_3 : std_logic_vector(3 downto 0);
	variable in_4 : std_logic_vector(3 downto 0);
	
	variable out_1 : std_logic_vector(7 downto 0);
	variable out_2 : std_logic_vector(7 downto 0);
	variable out_3 : std_logic_vector(7 downto 0);
	variable out_4 : std_logic_vector(7 downto 0);
	
	begin
		in_1 := in_A(3 downto 0);
		in_2 := in_A(7 downto 4);
		in_3 := in_B(3 downto 0);
		in_4 := in_B(7 downto 4);
		
		out_1 := pars_4(in_1, in_3);
		out_2 := pars_4(in_2, in_3);
		out_3 := pars_4(in_1, in_4);
		out_4 := pars_4(in_2, in_4);
		
		out_pars_8 := func8(out_1, out_2, out_3, out_4);
		
		return out_pars_8;
	end pars_8;
	
	function pars_16(in_A, in_B : in std_logic_vector(15 downto 0)) return std_logic_vector is 
	
	variable out_pars_16 : std_logic_vector(31 downto 0);
	
	variable in_1 : std_logic_vector(7 downto 0);
	variable in_2 : std_logic_vector(7 downto 0);
	variable in_3 : std_logic_vector(7 downto 0);
	variable in_4 : std_logic_vector(7 downto 0);
	
	variable out_1 : std_logic_vector(15 downto 0);
	variable out_2 : std_logic_vector(15 downto 0);
	variable out_3 : std_logic_vector(15 downto 0);
	variable out_4 : std_logic_vector(15 downto 0);
	
	begin
		in_1 := in_A(7 downto 0);
		in_2 := in_A(15 downto 8);
		in_3 := in_B(7 downto 0);
		in_4 := in_B(15 downto 8);
		
		out_1 := pars_8(in_1, in_3);
		out_2 := pars_8(in_2, in_3);
		out_3 := pars_8(in_1, in_4);
		out_4 := pars_8(in_2, in_4);
		
		out_pars_16 := func16(out_1, out_2, out_3, out_4);
		
		return out_pars_16;
	end pars_16;
	
	function pars_32(in_A, in_B : in std_logic_vector(31 downto 0)) return std_logic_vector is 
	
	variable out_pars_32 : std_logic_vector(63 downto 0);
	
	variable in_1 : std_logic_vector(15 downto 0);
	variable in_2 : std_logic_vector(15 downto 0);
	variable in_3 : std_logic_vector(15 downto 0);
	variable in_4 : std_logic_vector(15 downto 0);
	
	variable out_1 : std_logic_vector(31 downto 0);
	variable out_2 : std_logic_vector(31 downto 0);
	variable out_3 : std_logic_vector(31 downto 0);
	variable out_4 : std_logic_vector(31 downto 0);
	
	begin
		in_1 := in_A(15 downto 0);
		in_2 := in_A(31 downto 16);
		in_3 := in_B(15 downto 0);
		in_4 := in_B(31 downto 16);
		
		out_1 := pars_16(in_1, in_3);
		out_2 := pars_16(in_2, in_3);
		out_3 := pars_16(in_1, in_4);
		out_4 := pars_16(in_2, in_4);
		
		out_pars_32 := func32(out_1, out_2, out_3, out_4);
		
		return out_pars_32;
	end pars_32;
	
	function pars_64(in_A, in_B : in std_logic_vector(63 downto 0)) return std_logic_vector is 
	
	variable out_pars_64 : std_logic_vector(127 downto 0);
	
	variable in_1 : std_logic_vector(31 downto 0);
	variable in_2 : std_logic_vector(31 downto 0);
	variable in_3 : std_logic_vector(31 downto 0);
	variable in_4 : std_logic_vector(31 downto 0);
	
	variable out_1 : std_logic_vector(63 downto 0);
	variable out_2 : std_logic_vector(63 downto 0);
	variable out_3 : std_logic_vector(63 downto 0);
	variable out_4 : std_logic_vector(63 downto 0);
	
	begin
		in_1 := in_A(31 downto 0);
		in_2 := in_A(63 downto 32);
		in_3 := in_B(31 downto 0);
		in_4 := in_B(63 downto 32);
		
		out_1 := pars_32(in_1, in_3);
		out_2 := pars_32(in_2, in_3);
		out_3 := pars_32(in_1, in_4);
		out_4 := pars_32(in_2, in_4);
		
		out_pars_64 := func64(out_1, out_2, out_3, out_4);
		
		return out_pars_64;
	end pars_64;
	
	function pars_192(in_A, in_B : in std_logic_vector(191 downto 0)) return std_logic_vector is 
	
	variable out_pars_192 : std_logic_vector(383 downto 0);
	
	variable in_1 : std_logic_vector(63 downto 0);
	variable in_2 : std_logic_vector(63 downto 0);
	variable in_3 : std_logic_vector(63 downto 0);
	variable in_4 : std_logic_vector(63 downto 0);
	variable in_5 : std_logic_vector(63 downto 0);
	variable in_6 : std_logic_vector(63 downto 0);
	
	variable out_1 : std_logic_vector(127 downto 0);
	variable out_2 : std_logic_vector(127 downto 0);
	variable out_3 : std_logic_vector(127 downto 0);
	variable out_4 : std_logic_vector(127 downto 0);
	variable out_5 : std_logic_vector(127 downto 0);
	variable out_6 : std_logic_vector(127 downto 0);
	variable out_7 : std_logic_vector(127 downto 0);
	variable out_8 : std_logic_vector(127 downto 0);
	variable out_9 : std_logic_vector(127 downto 0);
	
	begin
		in_1 := in_A(63 downto 0);
		in_2 := in_A(127 downto 64);
		in_3 := in_A(191 downto 128);
		in_4 := in_B(63 downto 0);
		in_5 := in_B(127 downto 64);
		in_6 := in_B(191 downto 128);
		
		out_1 := pars_64(in_1, in_4);
		out_2 := pars_64(in_2, in_4);
		out_3 := pars_64(in_3, in_4);
		out_4 := pars_64(in_1, in_5);
		out_5 := pars_64(in_2, in_5);
		out_6 := pars_64(in_3, in_5);
		out_7 := pars_64(in_1, in_6);
		out_8 := pars_64(in_2, in_6);
		out_9 := pars_64(in_3, in_6);	
		
		out_pars_192 := func192(out_1, out_2, out_3, out_4, out_5, out_6, out_7, out_8, out_9);
		
		return out_pars_192;
	end pars_192;
	
	function partition(in_part : in std_logic_vector(7 downto 0); in_div : in unsigned(191 downto 0)) return std_logic_vector is 
	variable result_part : std_logic_vector(191 downto 0);	
	begin
	
	result_part := std_logic_vector(in_div);
	
		case in_part is
			when X"00" => return result_part(63 downto 0); --
			when X"01" => return result_part(127 downto 64); --
			when X"02" => return result_part(191 downto 128); --
			-- when X"03" => return result_part(127 downto 96); --
			-- when X"04" => return result_part(159 downto 128); --
			-- when X"05" => return result_part(191 downto 160); --
			when others	=>	return X"0000000000010000";
		end case;
			
		--return result_part;
	end partition;

end multiplikasi_211;

architecture augh of multiplikasi_211 is
--signal untuk multiplikasi
signal concated_inA 	: std_logic_vector(191 downto 0);
signal concated_inB 	: std_logic_vector(191 downto 0);

--signal untuk reduksi
signal C			 	: std_logic_vector(383 downto 0);
signal C1			 	: unsigned(383 downto 0);
signal C2			 	: unsigned(383 downto 0);
signal C3			 	: unsigned(383 downto 0);
signal C4			 	: unsigned(383 downto 0);
signal C5			 	: unsigned(383 downto 0);
signal Clast		 	: unsigned(191 downto 0);
signal T1			 	: unsigned(31 downto 0);
signal T2			 	: unsigned(31 downto 0);
signal T3			 	: unsigned(31 downto 0);
signal T4			 	: unsigned(31 downto 0);
signal T5			 	: unsigned(31 downto 0);
signal Tlast		 	: unsigned(31 downto 0);
signal T1_sl_29			: unsigned(31 downto 0);
signal T1_sl_4			: unsigned(31 downto 0);
signal T1_sl_3			: unsigned(31 downto 0);
signal T1_sr_3			: unsigned(31 downto 0);
signal T1_sr_28			: unsigned(31 downto 0);
signal T1_sr_29			: unsigned(31 downto 0);
signal T2_sl_29			: unsigned(31 downto 0);
signal T2_sl_4			: unsigned(31 downto 0);
signal T2_sl_3			: unsigned(31 downto 0);
signal T2_sr_3			: unsigned(31 downto 0);
signal T2_sr_28			: unsigned(31 downto 0);
signal T2_sr_29			: unsigned(31 downto 0);
signal T3_sl_29			: unsigned(31 downto 0);
signal T3_sl_4			: unsigned(31 downto 0);
signal T3_sl_3			: unsigned(31 downto 0);
signal T3_sr_3			: unsigned(31 downto 0);
signal T3_sr_28			: unsigned(31 downto 0);
signal T3_sr_29			: unsigned(31 downto 0);
signal T4_sl_29			: unsigned(31 downto 0);
signal T4_sl_4			: unsigned(31 downto 0);
signal T4_sl_3			: unsigned(31 downto 0);
signal T4_sr_3			: unsigned(31 downto 0);
signal T4_sr_28			: unsigned(31 downto 0);
signal T4_sr_29			: unsigned(31 downto 0);
signal T5_sl_29			: unsigned(31 downto 0);
signal T5_sl_4			: unsigned(31 downto 0);
signal T5_sl_3			: unsigned(31 downto 0);
signal T5_sr_3			: unsigned(31 downto 0);
signal T5_sr_28			: unsigned(31 downto 0);
signal T5_sr_29			: unsigned(31 downto 0);
signal Tlast_sl_7		: unsigned(31 downto 0);
signal Tlast_sl_6		: unsigned(31 downto 0);
signal Tlast_sl_3		: unsigned(31 downto 0);
signal Tlast_sr_25		: unsigned(31 downto 0);
signal Tlast_sr_26		: unsigned(31 downto 0);

begin
	
	concated_inA(31 downto 0) <= inA_0;
	concated_inA(63 downto 32) <= inA_1;
	concated_inA(95 downto 64) <= inA_2;
	concated_inA(127 downto 96) <= inA_3;
	concated_inA(159 downto 128) <= inA_4;
	concated_inA(191 downto 160) <= inA_5;
	
	concated_inB(31 downto 0) <= inB_0;
	concated_inB(63 downto 32) <= inB_1;
	concated_inB(95 downto 64) <= inB_2;
	concated_inB(127 downto 96) <= inB_3;
	concated_inB(159 downto 128) <= inB_4;
	concated_inB(191 downto 160) <= inB_5;
	
	C <= pars_192(concated_inA, concated_inB);
	
	--modular reduction
	T1 <= unsigned(C(351 downto 320));
	T1_sl_29 <= shift_left(T1, 29);
	T1_sl_4 <= shift_left(T1, 4);
	T1_sl_3 <= shift_left(T1, 3);
	T1_sr_3 <= shift_right(T1, 3);
	T1_sr_28 <= shift_right(T1, 28);
	T1_sr_29 <= shift_right(T1, 29);
	
	C1(127 downto 0) <= unsigned(C(127 downto 0));
	C1(159 downto 128) <= unsigned(C(159 downto 128)) xor T1_sl_29;
	C1(191 downto 160) <= unsigned(C(191 downto 160)) xor T1_sl_4 xor T1_sl_3 xor T1 xor T1_sr_3;
	C1(223 downto 192) <= unsigned(C(223 downto 192)) xor T1_sr_28 xor T1_sr_29;
	C1(383 downto 224) <= unsigned(C(383 downto 224));
	
	--second cycle
	T2 <= C1(319 downto 288);
	T2_sl_29 <= shift_left(T2, 29);
	T2_sl_4 <= shift_left(T2, 4);
	T2_sl_3 <= shift_left(T2, 3);
	T2_sr_3 <= shift_right(T2, 3);
	T2_sr_28 <= shift_right(T2, 28);
	T2_sr_29 <= shift_right(T2, 29);
	
	C2(95 downto 0) <= C1(95 downto 0);
	C2(127 downto 96) <= C1(127 downto 96) xor T2_sl_29;
	C2(159 downto 128) <= C1(159 downto 128) xor T2_sl_4 xor T2_sl_3 xor T2 xor T2_sr_3;
	C2(191 downto 160) <= C1(191 downto 160) xor T2_sr_28 xor T2_sr_29;
	C2(383 downto 192) <= C1(383 downto 192);
	
	--third cycle
	T3 <= C2(287 downto 256);
	T3_sl_29 <= shift_left(T3, 29);
	T3_sl_4 <= shift_left(T3, 4);
	T3_sl_3 <= shift_left(T3, 3);
	T3_sr_3 <= shift_right(T3, 3);
	T3_sr_28 <= shift_right(T3, 28);
	T3_sr_29 <= shift_right(T3, 29);
	
	C3(63 downto 0) <= C2(63 downto 0);
	C3(95 downto 64) <= C2(95 downto 64) xor T3_sl_29;
	C3(127 downto 96) <= C2(127 downto 96) xor T3_sl_4 xor T3_sl_3 xor T3 xor T3_sr_3;
	C3(159 downto 128) <= C2(159 downto 128) xor T3_sr_28 xor T3_sr_29;
	C3(383 downto 160) <= C2(383 downto 160);

	--fourth cycle
	T4 <= C3(255 downto 224);
	T4_sl_29 <= shift_left(T4, 29);
	T4_sl_4 <= shift_left(T4, 4);
	T4_sl_3 <= shift_left(T4, 3);
	T4_sr_3 <= shift_right(T4, 3);
	T4_sr_28 <= shift_right(T4, 28);
	T4_sr_29 <= shift_right(T4, 29);
	
	C4(31 downto 0) <= C3(31 downto 0);
	C4(63 downto 32) <= C3(63 downto 32) xor T4_sl_29;
	C4(95 downto 64) <= C3(95 downto 64) xor T4_sl_4 xor T4_sl_3 xor T4 xor T4_sr_3;
	C4(127 downto 96) <= C3(127 downto 96) xor T4_sr_28 xor T4_sr_29;
	C4(383 downto 128) <= C3(383 downto 128);
	
	--fifth cycle
	T5 <= C4(223 downto 192);
	T5_sl_29 <= shift_left(T5, 29);
	T5_sl_4 <= shift_left(T5, 4);
	T5_sl_3 <= shift_left(T5, 3);
	T5_sr_3 <= shift_right(T5, 3);
	T5_sr_28 <= shift_right(T5, 28);
	T5_sr_29 <= shift_right(T5, 29);
	
	C5(31 downto 0) <= C4(31 downto 0) xor T5_sl_29;
	C5(63 downto 32) <= C4(63 downto 32) xor T5_sl_4 xor T5_sl_3 xor T5 xor T5_sr_3;
	C5(95 downto 64) <= C4(95 downto 64) xor T5_sr_28 xor T5_sr_29;
	C5(383 downto 96) <= C4(383 downto 96);
	
	-- last mod operation
	Tlast <= shift_right(C5(191 downto 160), 3);
	Tlast_sl_7 <= shift_left(Tlast, 7);
	Tlast_sl_6 <= shift_left(Tlast, 6);
	Tlast_sl_3 <= shift_left(Tlast, 3);
	Tlast_sr_25 <= shift_right(Tlast, 25);
	Tlast_sr_26 <= shift_right(Tlast, 26);
	
	Clast(31 downto 0) <= C5(31 downto 0) xor Tlast_sl_7 xor Tlast_sl_6 xor Tlast_sl_3 xor Tlast;
	Clast(63 downto 32) <= C5(63 downto 32) xor Tlast_sr_25 xor Tlast_sr_26;
	Clast(159 downto 64) <= C5(159 downto 64);
	Clast(191 downto 160) <= C5(191 downto 160) and X"00000007";
	--Clast(383 downto 192) <= C5(383 downto 192);
	
	data_out <= partition(get_part, Clast);
	
	--data_out <= (others => '0');

end architecture;

