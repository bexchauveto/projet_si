
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Pipe is
	 Generic ( SIZE : Natural := 8;
				  SIZE_OP : Natural := 8);
    Port ( Ain : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           OPin : in  STD_LOGIC_VECTOR (SIZE_OP-1 downto 0);
           Bin : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Cin : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Aout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           OPout : out  STD_LOGIC_VECTOR (SIZE_OP-1 downto 0);
           Bout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           Cout : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
			  CLK : in STD_LOGIC);
end Pipe;

architecture Behavioral of Pipe is
	signal memA : STD_LOGIC_VECTOR (SIZE-1 downto 0);
	signal memB : STD_LOGIC_VECTOR (SIZE-1 downto 0);
	signal memC : STD_LOGIC_VECTOR (SIZE-1 downto 0);
	signal memOP : STD_LOGIC_VECTOR (SIZE-1 downto 0);
begin

	process (CLK) is
	begin
		if rising_edge(CLK) then
			memA <= Ain;
			memOP <= OPin;
			memB <= Bin;
			memC <= Cin;
			Aout <= memA;
			OPout <= memOP;
			Bout <= memB;
			Cout <= memC;
		end if;
	end process;

end Behavioral;

