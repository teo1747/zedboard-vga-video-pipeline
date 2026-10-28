----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 21.10.2025 14:57:21
-- Design Name: 
-- Module Name: bit_extraction - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
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

entity bit_extraction is
  Port (
    Din          : in  std_logic_vector(7 downto 0);
    Sel_ActVideo : in  std_logic;
    Dout         : out std_logic_vector(3 downto 0)
  );
end bit_extraction;

architecture Behavioral of bit_extraction is
begin
  process(Din, Sel_ActVideo)
  begin
    if Sel_ActVideo = '1' then
      Dout <= Din(7 downto 4);  
    else
      Dout <= (others => '0');  
    end if;
  end process;
end Behavioral;

