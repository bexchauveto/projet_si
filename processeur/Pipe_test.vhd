
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Pipe_test IS
END Pipe_test;
 
ARCHITECTURE behavior OF Pipe_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Pipe
    PORT(
         Ain : IN  std_logic_vector(7 downto 0);
         OPin : IN  std_logic_vector(7 downto 0);
         Bin : IN  std_logic_vector(7 downto 0);
         Cin : IN  std_logic_vector(7 downto 0);
         Aout : OUT  std_logic_vector(7 downto 0);
         OPout : OUT  std_logic_vector(7 downto 0);
         Bout : OUT  std_logic_vector(7 downto 0);
         Cout : OUT  std_logic_vector(7 downto 0);
         CLK : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal Ain : std_logic_vector(7 downto 0) := (others => '0');
   signal OPin : std_logic_vector(7 downto 0) := (others => '0');
   signal Bin : std_logic_vector(7 downto 0) := (others => '0');
   signal Cin : std_logic_vector(7 downto 0) := (others => '0');
   signal CLK : std_logic := '0';

 	--Outputs
   signal Aout : std_logic_vector(7 downto 0);
   signal OPout : std_logic_vector(7 downto 0);
   signal Bout : std_logic_vector(7 downto 0);
   signal Cout : std_logic_vector(7 downto 0);

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Pipe PORT MAP (
          Ain => Ain,
          OPin => OPin,
          Bin => Bin,
          Cin => Cin,
          Aout => Aout,
          OPout => OPout,
          Bout => Bout,
          Cout => Cout,
          CLK => CLK
        );

   CLK <= not CLK after 50ns;
	Ain <= x"A9" after 150ns;
	OPin <= x"AA" after 150ns;
	Bin <= x"AB" after 150ns;
	Cin <= x"AC" after 150ns;

END;
