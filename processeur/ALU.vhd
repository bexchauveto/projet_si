----------------------------------------------------------------------------------
-- Company: INSA
-- Engineer: BEX-CHAUVET - LAINE
-- 
-- Create Date:    10:42:14 04/01/2016 
-- Design Name: 
-- Module Name:    ALU - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU is
	 Generic (SIZE : Natural := 8);
    Port ( A : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           B : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Ctrl_Alu : in  STD_LOGIC_VECTOR (2 downto 0);
           S : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           N : out  STD_LOGIC;
           O : out  STD_LOGIC;
           Z : out  STD_LOGIC;
           C : out  STD_LOGIC);
end ALU;

architecture Behavioral of ALU is

	--Ri is the result register, and Rj and Rk are the operands registers
	signal Ri: STD_LOGIC_VECTOR((2*SIZE)-1 downto 0) := (others => '0');
	signal Rj, Rk: STD_LOGIC_VECTOR(SIZE downto 0) := (others => '0');

begin

Rj <= b"0"&A;
Rk <= b"0"&B;
S <= Ri(SIZE-1 downto 0);

process

begin
	case(Ctrl_Alu) is
		when "001" => -- Addition
			Ri <= b"0000000"&(Rj + Rk);
		when "010" => -- Multiplication
			Ri <= (Rj(SIZE-1 downto 0) * Rk(SIZE-1 downto 0));
		when "011" => -- Soustraction
			Ri <= b"0000000"&(Rj - Rk);
		when "100" => -- Division
			Ri <= x"00"&(conv_std_logic_vector((conv_integer(Rj)/conv_integer(Rk)), SIZE));
			--Ri <= Rj / Rk;
		when others =>
			NULL;
	end case;
	N <= Ri(SIZE);
	if(Ri(SIZE downto 0) = "00000000") then
		Z <= '1';
	end if;
	if(Ri(SIZE) /= '0' and Ctrl_Alu = "001") then
		C <= '1';
	elsif(Ri(SIZE) /= '0') then
		O <= '1';
	end if;

end process;


end Behavioral;

