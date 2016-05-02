library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

--use IEEE.NUMERIC_STD.ALL;

entity InstCounter is
    Port ( clk : in  STD_LOGIC;
           sens : in  STD_LOGIC;
           load : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           en : in  STD_LOGIC;
           din : in  STD_LOGIC_VECTOR (7 downto 0);
           dout : out  STD_LOGIC_VECTOR (7 downto 0));
end InstCounter;

architecture Behavioral of InstCounter is

signal cpt : STD_LOGIC_VECTOR (7 downto 0);

begin

-- domaine concurrent
dout <= cpt;

counter : process (clk) is
 -- signaux locaux
begin
	if rising_edge(clk) then  -- ou if (signal'event and signal = '1')
		if rst = '0' then
			cpt <= x"00";
		elsif en = '1' then
			if load = '1' then
				cpt <= din;
			elsif sens = '1' then
				cpt <= cpt + x"01";
			else
				cpt <= cpt - x"01";
			end if;
		end if;
	end if;
end process;

end Behavioral;
