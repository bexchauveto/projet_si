----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:26:05 04/15/2016 
-- Design Name: 
-- Module Name:    main_proc - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity main_proc is
	Generic( SIZE : Natural := 8);
	Port( CLK : in STD_LOGIC;
			RST : in STD_LOGIC;
			QA : inout STD_LOGIC_VECTOR( SIZE-1 downto 0);
			QB : inout STD_LOGIC_VECTOR( SIZE-1 downto 0));
end main_proc;

architecture Behavioral of main_proc is




begin

--Compteur d'instruction

--Mémoire d'instruction

--Banc de registres

--ALU

--Mémoire des données



end Behavioral;

