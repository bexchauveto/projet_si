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

signal IP : std_logic_vector(7 downto 0);
component InstMem is
	Port ( ADDR : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           CLK : in  STD_LOGIC;
           DOUT : out  STD_LOGIC_VECTOR (SIZE_DOUT downto 0));
end component;
component RegisterBen is
	Port ( addrA : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           addrB : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           addrW : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           W : in  STD_LOGIC;
           DATA : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           QA : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           QB : out  STD_LOGIC_VECTOR (SIZE-1 downto 0));
end component;
component Pipe is
	Port ( Ain : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           OPin : in  STD_LOGIC_VECTOR (SIZE_OP-1 downto 0);
           Bin : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Cin : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Aout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           OPout : out  STD_LOGIC_VECTOR (SIZE_OP-1 downto 0);
           Bout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Cout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
			  CLK : in STD_LOGIC);
end component;
component ALU is
	Port ( A : in  IEEE.NUMERIC_STD.SIGNED (SIZE-1 downto 0);
           B : in  IEEE.NUMERIC_STD.SIGNED (SIZE-1 downto 0);
           Ctrl_Alu : in  STD_LOGIC_VECTOR (2 downto 0);
           S : out  IEEE.NUMERIC_STD.SIGNED (SIZE-1 downto 0);
           N : out  STD_LOGIC;
           O : out  STD_LOGIC;
           Z : out  STD_LOGIC;
           C : out  STD_LOGIC);
end component;
component DataMem is
	Port ( ADDR : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           DIN : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           RW : in  STD_LOGIC;
           RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           DOUT : out  STD_LOGIC_VECTOR (SIZE-1 downto 0));
end component;
begin

--Compteur d'instruction


--Mémoire d'instruction

--LI/DI

--Banc de registres

--DI/EX

--ALU

--Ex/Mem

--Mémoire des données

--Mem/RE

end Behavioral;

