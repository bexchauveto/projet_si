----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:26:05 04/15/2016 
-- Design Name: 
-- Module Name:    main_proc - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity main_proc is
	Generic( SIZE : Natural := 8;
				SIZE_REG : Natural := 4;
				SIZE_OP : Natural := 8;
				NB_REGISTERS : Natural := 16;
				SIZE_DOUT : Natural := 32);
	Port( CLK : in STD_LOGIC;
			RST : in STD_LOGIC;
			QA : inout STD_LOGIC_VECTOR( SIZE-1 downto 0);
			QB : inout STD_LOGIC_VECTOR( SIZE-1 downto 0));
end main_proc;



architecture Behavioral of main_proc is

signal DoutCount : std_logic_vector(SIZE-1 downto 0);
signal DoutInstMem : std_logic_vector(SIZE_DOUT-1 downto 0);
signal DoutLidiA : std_logic_vector(SIZE-1 downto 0);
signal DoutLidiOp : std_logic_vector(SIZE-1 downto 0);
signal DoutLidiB : std_logic_vector(SIZE-1 downto 0);
signal DoutLidiC : std_logic_vector(SIZE-1 downto 0);
signal QAtmp : std_logic_vector(SIZE-1 downto 0);
signal DoutDiexA : std_logic_vector(SIZE-1 downto 0);
signal DoutDiexOp : std_logic_vector(SIZE-1 downto 0);
signal DoutDiexB : std_logic_vector(SIZE-1 downto 0);
signal DoutDiexC : std_logic_vector(SIZE-1 downto 0);
signal DoutAluS : std_logic_vector(SIZE-1 downto 0);
signal DoutAluSsigned : ieee.numeric_std.signed(SIZE-1 downto 0);
signal DinAluAsigned : ieee.numeric_std.signed(SIZE-1 downto 0);
signal DinAluBsigned : ieee.numeric_std.signed(SIZE-1 downto 0);
signal DinAluOp : std_logic_vector(2 downto 0);
signal DoutAluO : std_logic;
signal DoutAluC : std_logic;
signal DoutAluZ : std_logic;
signal DoutAluN : std_logic;
signal DoutExmemA : std_logic_vector(SIZE-1 downto 0);
signal DoutExmemOp : std_logic_vector(SIZE-1 downto 0);
signal DoutExmemB : std_logic_vector(SIZE-1 downto 0);
signal DoutDataMem : std_logic_vector(SIZE-1 downto 0);
signal DoutMemreA : std_logic_vector(SIZE-1 downto 0);
signal DoutMemreOp : std_logic_vector(SIZE-1 downto 0);
signal DoutMemreB : std_logic_vector(SIZE-1 downto 0);
signal AFC : std_logic_vector(SIZE-1 downto 0) := x"06";
signal JMP : std_logic_vector(SIZE-1 downto 0) := x"07";
signal JMF : std_logic_vector(SIZE-1 downto 0) := x"08";
begin

--Compteur d'instruction
	instCount : entity work.InstCounter(Behavioral)
	Port map( clk => CLK,
           sens => '1',
           load => '0',
           rst => RST,
           en => '1',
           din => x"00",
           dout => DoutCount);

--Mémoire d'instruction
	instMem : entity work.InstMemBench(Behavioral)
	Port map( ADDR => DoutCount,
           CLK => CLK,
           DOUT => DoutInstMem);
--LI/DI
	lidi : entity work.Pipe(Behavioral)
	Port map( Ain => DoutInstMem(SIZE_DOUT-1 downto SIZE_DOUT-8),
           OPin => DoutInstMem(SIZE_DOUT-9 downto SIZE_DOUT-16),
           Bin => DoutInstMem(SIZE_DOUT-17 downto SIZE_DOUT-24),
           Cin => DoutInstMem(SIZE_DOUT-25 downto SIZE_DOUT-32),
           Aout => DoutLidiA,
           OPout => DoutLidiOp,
           Bout => DoutLidiB,
           Cout => DoutLidiC,
			  CLK => CLK);
--Banc de registres
	registerBen : entity work.RegisterBench(Behavioral)
	Port map( addrA => DoutLidiB,
           addrB => DoutLidiC,
           addrW => DoutMemreA,
           W => tmp,
           DATA => DoutMemreB,
           RST => RST,
           CLK => CLK,
           QA => QAtmp ,
           QB => QB);
			  
--MUX entre QA, DoutLidiB et DoutLidiOP
	muxQADoutBOP : process(QAtmp, DoutLidiB, DoutLidiOP)
	begin
		if(DoutLidiOP = AFC or DoutLidiOP = JMP or DoutLidiOP = JMF) then
			QA <= DoutLidiB;
		end if;
	end process;

--DI/EX
	diex : entity work.Pipe(Behavioral)
	Port map( Ain => DoutLidiA,
           OPin => DoutLidiOp,
           Bin => QB,
           Cin => QA,
           Aout => DoutDiexA,
           OPout => DoutDiexOp,
           Bout => DoutDiexB,
           Cout => DoutDiexC,
			  CLK => CLK);
--ALU
	lcAlu : process(DoutDiexB, DoutDiexC, DoutDiexOp)
	begin
		DinAluAsigned <= IEEE.NUMERIC_STD.signed(DoutDiexB); 
      DinAluBSigned <= IEEE.NUMERIC_STD.signed(DoutDiexC);
		case(DoutDiexOp) is
			when "00000001" => -- Add 1
				DinAluOp <= "001";
			when "00000010" => -- Mul 2
				DinAluOp <= "010";
			when "00000011" => -- Sub 3
				DinAluOp <= "011";
			when "00000100" => -- Div 4
				DinAluOp <= "100";
			when "00001001" => -- Inf 9
				DinAluOp <= "011";
			when "00001010" => -- Sup A
				DinAluOp <= "011";
			when "00001011" => -- Equ B
				DinAluOp <= "011";
			when others =>
				NULL;
		end case;
	end process;
	
	alu : entity work.ALU(Behavioral)
	Port map( A => DinAluAsigned, 
           B => DinAluBSigned,
           Ctrl_Alu => DinAluOp,
           S => DoutAluSsigned,
           N => DoutAluN,
           O => DoutAluO,
           Z => DoutAluZ,
           C => DoutAluC);
	process(DoutAluSsigned)
	begin
		DoutAluS <= std_logic_vector(DoutAluSsigned);
	end process;
--Ex/Mem
	exmem : entity work.Pipe(Behavioral)
	Port map( Ain => DoutDiexA,
           OPin => DoutDiexOp,
           Bin => DoutAluS,
			  Cin => x"00",
           Aout => DoutExmemA,
           OPout => DoutExmemOp,
           Bout => DoutExmemB,
			  CLK => CLK);
--Mémoire des données
	dataMem : entity work.DataMemBench(Behavioral)
	Port map( ADDR => tmp,
           DIN => DoutExmemB,
           RW => tmp,
           RST => RST,
           CLK => CLK,
           DOUT => DoutDataMem);

--Mem/RE
	Memre : entity work.Pipe(Behavioral)
	Port map( Ain => DoutExmemA,
           OPin => DoutExmemOp,
           Bin => tmp,
			  Cin => x"00",
           Aout => DoutMemreA,
           OPout => DoutMemreOp,
           Bout => DoutMemreB,
			  CLK => CLK);
end Behavioral;

