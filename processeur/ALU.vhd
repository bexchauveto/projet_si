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
	signal Ri, Rj, Rk : STD_LOGIC_VECTOR(SIZE downto 0) := (others => '0');

begin

Rj <= A;
Rk <= B;
S <= Ri;

process()

begin
	case(Ctrl_Alu) is
		when "001" =>
			Ri := Rj + Rk;
		when "010" =>
			Ri := Rj * Rk;
		when "011" =>
			Ri := Rj - Rk;
		when "100" =>
			Ri := Rj / Rk;
		when others =>
			NULL;
	end case;
	if(Ri < '0') then
		N := '1';
	end if;
	if(Ri = '0') then
		Z := '1';
	end if;
	if(Ri(SIZE) /= '0' and Ctrl_Alu = "001") then
		C := '1';
	elsif(Ri(SIZE) /= '0') then
		O := '1';
	end if;

end;


end Behavioral;

