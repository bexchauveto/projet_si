
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY InstMemBench_test IS
END InstMemBench_test;
 
ARCHITECTURE behavior OF InstMemBench_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT InstMemBench
    PORT(
         ADDR : IN  std_logic_vector(7 downto 0);
         CLK : IN  std_logic;
         DOUT : OUT  std_logic_vector(31 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal ADDR : std_logic_vector(7 downto 0) := (others => '0');
   signal CLK : std_logic := '0';

 	--Outputs
   signal DOUT : std_logic_vector(31 downto 0);

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: InstMemBench PORT MAP (
          ADDR => ADDR,
          CLK => CLK,
          DOUT => DOUT
        );

   CLK <= not CLK after 50ns;
	ADDR <= x"05" after 200ns;

END;
