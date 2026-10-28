----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10.12.2025 20:06:51
-- Design Name: 
-- Module Name: video_inverter_tb - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity video_inverter_tb is
--  Port ( );
end video_inverter_tb;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


architecture sim of video_inverter_tb is

    -- Component under test
    component video_inverter is
        Port (
            s00_axis_aclk    : in  std_logic;
            s00_axis_aresetn : in  std_logic;

            s00_axis_tvalid : in  std_logic;
            s00_axis_tdata  : in  std_logic_vector(7 downto 0);
            s00_axis_tlast  : in  std_logic;
            s00_axis_tuser  : in  std_logic;
            s00_axis_tready : out std_logic;

            m00_axis_tvalid : out std_logic;
            m00_axis_tdata  : out std_logic_vector(7 downto 0);
            m00_axis_tlast  : out std_logic;
            m00_axis_tuser  : out std_logic;
            m00_axis_tready : in  std_logic;

            VidOrig_nVideoInv : in std_logic
        );
    end component;

    -- Signals
    signal clk       : std_logic := '0';
    signal resetn    : std_logic := '0';

    signal s_tvalid  : std_logic := '0';
    signal s_tdata   : std_logic_vector(7 downto 0) := (others => '0');
    signal s_tlast   : std_logic := '0';
    signal s_tuser   : std_logic := '0';
    signal s_tready  : std_logic;

    signal m_tvalid  : std_logic;
    signal m_tdata   : std_logic_vector(7 downto 0);
    signal m_tlast   : std_logic;
    signal m_tuser   : std_logic;
    signal m_tready  : std_logic := '1';

    signal invert_enable : std_logic := '1';

begin

    clk <= not clk after 5 ns;


    DUT : video_inverter
        port map (
            s00_axis_aclk     => clk,
            s00_axis_aresetn  => resetn,

            s00_axis_tvalid   => s_tvalid,
            s00_axis_tdata    => s_tdata,
            s00_axis_tlast    => s_tlast,
            s00_axis_tuser    => s_tuser,
            s00_axis_tready   => s_tready,

            m00_axis_tvalid   => m_tvalid,
            m00_axis_tdata    => m_tdata,
            m00_axis_tlast    => m_tlast,
            m00_axis_tuser    => m_tuser,
            m00_axis_tready   => m_tready,

            VidOrig_nVideoInv => invert_enable
        );

    stim : process
    begin

        resetn <= '0';
        wait for 50 ns;
        resetn <= '1';
        wait for 20 ns;


        invert_enable <= '1';
        s_tvalid <= '1';

        -- Pixel 1
        s_tdata <= std_logic_vector(to_unsigned(10, 8));
        s_tuser <= '1';
        s_tlast <= '0';
        wait until rising_edge(clk);

        -- Pixel 2
        s_tdata <= std_logic_vector(to_unsigned(50, 8));
        s_tuser <= '0';
        wait until rising_edge(clk);

        -- Pixel 3
        s_tdata <= std_logic_vector(to_unsigned(200, 8));
        wait until rising_edge(clk);

        -- Pixel 4 end of line
        s_tdata <= std_logic_vector(to_unsigned(255, 8));
        s_tlast <= '1';
        wait until rising_edge(clk);

        s_tvalid <= '0';
        s_tlast  <= '0';
        wait for 40 ns;

        invert_enable <= '0';
        s_tvalid <= '1';

        s_tdata <= x"0F"; s_tuser <= '1'; wait until rising_edge(clk);
        s_tdata <= x"80"; s_tuser <= '0'; wait until rising_edge(clk);
        s_tdata <= x"FF";                 wait until rising_edge(clk);

        s_tvalid <= '0';
        wait for 50 ns;

        wait;
    end process;

end sim;
