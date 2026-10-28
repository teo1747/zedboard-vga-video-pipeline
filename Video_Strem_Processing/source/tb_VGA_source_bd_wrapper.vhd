----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 21.10.2025 16:25:10
-- Design Name: 
-- Module Name: tb_VGA_source_bd_wrapper - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

entity tb_VGA_source_bd_wrapper is
end tb_VGA_source_bd_wrapper;

architecture sim of tb_VGA_source_bd_wrapper is

  -- Component Declaration
  component VGA_source_bd_wrapper
    port (
      B : out STD_LOGIC_VECTOR (3 downto 0);
      G : out STD_LOGIC_VECTOR (3 downto 0);
      R : out STD_LOGIC_VECTOR (3 downto 0);
      clk : in STD_LOGIC;
      hsync_out_0 : out STD_LOGIC;
      reset_n : in STD_LOGIC;
      vsync_out_0 : out STD_LOGIC
    );
  end component;

  -- Signals to connect to the DUT
  signal clk        : STD_LOGIC := '0';
  signal reset_n    : STD_LOGIC := '0';
  signal hsync_out  : STD_LOGIC;
  signal vsync_out  : STD_LOGIC;
  signal B          : STD_LOGIC_VECTOR(3 downto 0);
  signal G          : STD_LOGIC_VECTOR(3 downto 0);
  signal R          : STD_LOGIC_VECTOR(3 downto 0);


  -- Clock period constant
  constant clk_period : time := 10 ns;  -- 100 MHz, the ZedBoard clock the clock wizard expects

begin

  -- Instantiate the Unit Under Test (UUT)
  uut: VGA_source_bd_wrapper
    port map (
      clk         => clk,
      reset_n     => reset_n,
      B           => B,
      G           => G,
      R           => R,
      hsync_out_0 => hsync_out,
      vsync_out_0 => vsync_out
    );

  -- Clock process
  clk_process : process
  begin
    
      
      clk <= '0';
      wait for clk_period / 2;
      clk <= '1';
      wait for clk_period / 2;
    
    
  end process;

  -- Stimulus process
  stim_proc: process
  begin
    -- Apply reset
    wait for clk_period;
    reset_n <= '0';
    wait for clk_period*2;
    reset_n <= '1';  -- Deassert reset

    -- Wait to observe behavior
    wait for 20 ms;

    -- Finish simulation
    wait;
  end process;

end sim;

