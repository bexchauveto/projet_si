
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DataMemBench is
	 Generic (SIZE : Natural := 8);
    Port ( ADDR : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           DIN : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           RW : in  STD_LOGIC;
           RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           DOUT : out  STD_LOGIC_VECTOR (SIZE-1 downto 0));
end DataMemBench;

architecture Behavioral of DataMemBench is

begin

	databench : process (CLK) is
	begin
		if rising_edge(CLK) then
			if RST = '0' then
				
			else
				if RW = '1' then
					-- lecture
				else
					-- ecriture
				end if;
			end if;
		end if;
	end process;

end Behavioral;

