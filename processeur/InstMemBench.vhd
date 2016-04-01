
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity InstMemBench is
	 Generic (SIZE : Natural := 8);
    Port ( ADDR : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           CLK : in  STD_LOGIC;
           DOUT : out  STD_LOGIC_VECTOR (31 downto 0));
end InstMemBench;

architecture Behavioral of InstMemBench is

begin


end Behavioral;

