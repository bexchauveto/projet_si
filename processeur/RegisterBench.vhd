
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RegisterBench is
	 Generic (SIZE : Natural := 8);
    Port ( addrA : in  STD_LOGIC_VECTOR (3 downto 0);
           addrB : in  STD_LOGIC_VECTOR (3 downto 0);
           addrW : in  STD_LOGIC_VECTOR (3 downto 0);
           W : in  STD_LOGIC;
           DATA : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           QA : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           QB : out  STD_LOGIC_VECTOR (SIZE-1 downto 0));
end RegisterBench;

architecture Behavioral of RegisterBench is

begin

	regbench : process (CLK) is
	begin
		
	end process;

end Behavioral;

