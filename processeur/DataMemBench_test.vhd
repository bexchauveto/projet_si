
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY DataMemBench_test IS
END DataMemBench_test;
 
ARCHITECTURE behavior OF DataMemBench_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT DataMemBench
    PORT(
         ADDR : IN  std_logic_vector(7 downto 0);
         DIN : IN  std_logic_vector(7 downto 0);
         RW : IN  std_logic;
         RST : IN  std_logic;
         CLK : IN  std_logic;
         DOUT : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal ADDR : std_logic_vector(7 downto 0) := (others => '0');
   signal DIN : std_logic_vector(7 downto 0) := (others => '0');
   signal RW : std_logic := '0';
   signal RST : std_logic := '0';
   signal CLK : std_logic := '0';

 	--Outputs
   signal DOUT : std_logic_vector(7 downto 0);

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: DataMemBench PORT MAP (
          ADDR => ADDR,
          DIN => DIN,
          RW => RW,
          RST => RST,
          CLK => CLK,
          DOUT => DOUT
        );

   CLK <= not CLK after 50ns;
	RST <= '1' after 200ns, '0' after 600ns;
	RW <= '1' after 200ns, '0' after 400ns;
	DIN <= x"AA" after 300ns;
	ADDR <= x"05" after 300ns;

END;
