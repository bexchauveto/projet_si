--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   10:38:28 04/08/2016
-- Design Name:   
-- Module Name:   /home/laine/Documents/4a/compilo/projet_si/processeur/RegisterBench_test2.vhd
-- Project Name:  processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: RegisterBench
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
 
ENTITY RegisterBench_test2 IS
END RegisterBench_test2;
 
ARCHITECTURE behavior OF RegisterBench_test2 IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT RegisterBench
    PORT(
         addrA : IN  std_logic_vector(3 downto 0);
         addrB : IN  std_logic_vector(3 downto 0);
         addrW : IN  std_logic_vector(3 downto 0);
         W : IN  std_logic;
         DATA : IN  std_logic_vector(7 downto 0);
         RST : IN  std_logic;
         CLK : IN  std_logic;
         QA : OUT  std_logic_vector(7 downto 0);
         QB : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal addrA : std_logic_vector(3 downto 0) := (others => '0');
   signal addrB : std_logic_vector(3 downto 0) := (others => '0');
   signal addrW : std_logic_vector(3 downto 0) := (others => '0');
   signal W : std_logic := '0';
   signal DATA : std_logic_vector(7 downto 0) := (others => '0');
   signal RST : std_logic := '0';
   signal CLK : std_logic := '0';

 	--Outputs
   signal QA : std_logic_vector(7 downto 0);
   signal QB : std_logic_vector(7 downto 0);

   -- Clock period definitions
   --constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: RegisterBench PORT MAP (
          addrA => addrA,
          addrB => addrB,
          addrW => addrW,
          W => W,
          DATA => DATA,
          RST => RST,
          CLK => CLK,
          QA => QA,
          QB => QB
        );

    CLK <= not CLK after 50ns;
	 RST <= '1' after 100ns, '0' after 800ns;
	 
	 W <= '1' after 200ns;
	 addrW <= "0011" after 200ns;
	 DATA <= x"AA" after 200ns;
	 
	 addrA <= "0010" after 200ns;
	 addrB <= "0011" after 200ns;

END;


