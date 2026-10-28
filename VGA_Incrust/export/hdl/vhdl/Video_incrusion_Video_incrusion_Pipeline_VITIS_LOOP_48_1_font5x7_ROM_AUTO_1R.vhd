-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Version: 2022.2
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity Video_incrusion_Video_incrusion_Pipeline_VITIS_LOOP_48_1_font5x7_ROM_AUTO_1R is 
    generic(
             DataWidth     : integer := 5; 
             AddressWidth     : integer := 7; 
             AddressRange    : integer := 70
    ); 
    port (
 
          address0        : in std_logic_vector(AddressWidth-1 downto 0); 
          ce0             : in std_logic; 
          q0              : out std_logic_vector(DataWidth-1 downto 0);
 
          address1        : in std_logic_vector(AddressWidth-1 downto 0); 
          ce1             : in std_logic; 
          q1              : out std_logic_vector(DataWidth-1 downto 0);

          reset               : in std_logic;
          clk                 : in std_logic
    ); 
end entity; 


architecture rtl of Video_incrusion_Video_incrusion_Pipeline_VITIS_LOOP_48_1_font5x7_ROM_AUTO_1R is 
 
signal address0_tmp : std_logic_vector(AddressWidth-1 downto 0);  
signal address1_tmp : std_logic_vector(AddressWidth-1 downto 0); 

type mem_array is array (0 to AddressRange-1) of std_logic_vector (DataWidth-1 downto 0); 

signal mem0 : mem_array := (
    0 => "11110", 1 => "10001", 2 => "10001", 3 => "10001", 
    4 => "10001", 5 => "10001", 6 => "11110", 7 => "00100", 
    8 => "01100", 9 => "00100", 10 => "00100", 11 => "00100", 
    12 => "00100", 13 => "01110", 14 => "11110", 15 => "10001", 
    16 => "00001", 17 => "00010", 18 => "00100", 19 => "01000", 
    20 => "11111", 21 => "11110", 22 => "10001", 23 => "00001", 
    24 => "00110", 25 => "00001", 26 => "10001", 27 => "11110", 
    28 => "00010", 29 => "00110", 30 => "01010", 31 => "10010", 
    32 => "11111", 33 => "00010", 34 => "00010", 35 => "11111", 
    36 => "10000", 37 => "11110", 38 => "00001", 39 => "00001", 
    40 => "10001", 41 => "01110", 42 => "00110", 43 => "01000", 
    44 => "10000", 45 => "11110", 46 => "10001", 47 => "10001", 
    48 => "01110", 49 => "11111", 50 => "10001", 51 => "00010", 
    52 => "00100", 53 => "00100", 54 => "00100", 55 => "00100", 
    56 => "01110", 57 => "10001", 58 => "10001", 59 => "01110", 
    60 => "10001", 61 => "10001", 62 => "01110", 63 => "01110", 
    64 => "10001", 65 => "10001", 66 => "01111", 67 => "00001", 
    68 => "00010", 69 => "01100");



begin 

 
memory_access_guard_0: process (address0) 
begin
      address0_tmp <= address0;
--synthesis translate_off
      if (CONV_INTEGER(address0) > AddressRange-1) then
           address0_tmp <= (others => '0');
      else 
           address0_tmp <= address0;
      end if;
--synthesis translate_on
end process;
 
memory_access_guard_1: process (address1) 
begin
      address1_tmp <= address1;
--synthesis translate_off
      if (CONV_INTEGER(address1) > AddressRange-1) then
           address1_tmp <= (others => '0');
      else 
           address1_tmp <= address1;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
 
        if (ce0 = '1') then  
            q0 <= mem0(CONV_INTEGER(address0_tmp)); 
        end if;
 
        if (ce1 = '1') then  
            q1 <= mem0(CONV_INTEGER(address1_tmp)); 
        end if;

end if;
end process;

end rtl;

