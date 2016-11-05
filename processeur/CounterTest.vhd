--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:45:08 05/16/2016
-- Design Name:   
-- Module Name:   /home/irobire/projet_si/projet_si/processeur/CounterTest.vhd
-- Project Name:  processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: InstCounter
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
 
ENTITY CounterTest IS
END CounterTest;
 
ARCHITECTURE behavior OF CounterTest IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT InstCounter
    PORT(
         clk : IN  std_logic;
         sens : IN  std_logic;
         load : IN  std_logic;
         rst : IN  std_logic;
         en : IN  std_logic;
         din : IN  std_logic_vector(7 downto 0);
         dout : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal sens : std_logic := '0';
   signal load : std_logic := '0';
   signal rst : std_logic := '0';
   signal en : std_logic := '0';
   signal din : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal dout : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: InstCounter PORT MAP (
          clk => clk,
          sens => sens,
          load => load,
          rst => rst,
          en => en,
          din => din,
          dout => dout
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;

      rst <= '0' after 0ns, '1' after 50 ns;
		din <= "00000000" after 0ns, "00001011" after 100ns, "00000000" after 120ns;
		sens <= '1' after 0ns, '0' after 130ns;
		en <= '1' after 50ns, '0' after 300ns;
		load <= '1' after 100ns, '0' after 110ns;

      wait;
   end process;

END;
