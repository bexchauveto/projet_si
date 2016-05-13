--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:10:13 05/13/2016
-- Design Name:   
-- Module Name:   /home/irobire/projet_si/projet_si/processeur/TESTMAIN.vhd
-- Project Name:  processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: main_proc
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY TESTMAIN IS
END TESTMAIN;
 
ARCHITECTURE behavior OF TESTMAIN IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT main_proc
    PORT(
         CLK : IN  std_logic;
         RST : IN  std_logic;
         QA : INOUT  std_logic_vector(7 downto 0);
         QB : INOUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal RST : std_logic := '0';

	--BiDirs
   signal QA : std_logic_vector(7 downto 0);
   signal QB : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: main_proc PORT MAP (
          CLK => CLK,
          RST => RST,
          QA => QA,
          QB => QB
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for CLK_period*10;
		RST <= '1';

      -- insert stimulus here 

      wait;
   end process;

END;
