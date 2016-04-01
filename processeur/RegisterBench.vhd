
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
	 Generic ( SIZE : Natural := 8;
				  SIZE_REG : Natural := 4;
				  NB_REGISTERS : Natural := 16);
    Port ( addrA : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           addrB : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           addrW : in  STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
           W : in  STD_LOGIC;
           DATA : in  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           RST : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           QA : out  STD_LOGIC_VECTOR (SIZE-1 downto 0);
           QB : out  STD_LOGIC_VECTOR (SIZE-1 downto 0));
end RegisterBench;

architecture Behavioral of RegisterBench is
	TYPE REGISTERS IS ARRAY (0 to (NB_REGISTERS-1)) OF STD_LOGIC_VECTOR (SIZE-1 downto 0);
	signal R : REGISTERS;
	signal memAddrA : STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
	signal memAddrB : STD_LOGIC_VECTOR (SIZE_REG-1 downto 0);
begin
	
	QA <= R(memAddrA);
	QB <= R(memAddrB);
	
	regbench : process (CLK) is
	begin
		if rising_edge(CLK) then
			if RST = '0' then
				for i in 0 to (NB_REGISTERS-1) loop
					R(i) <= (others => '0');
				end loop;
			else
				memAddrA <= addrA;
				memAddrB <= addrB;
				if W = '1' then
					R(addrW) <= DATA;
				end if;
			end if;
		end if;
	end process;

end Behavioral;

