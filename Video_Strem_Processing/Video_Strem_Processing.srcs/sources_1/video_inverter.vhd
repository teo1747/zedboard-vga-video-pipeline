library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity video_inverter is
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

        -- Inversion enabled with external switch
        VidOrig_nVideoInv : in std_logic
    );
end video_inverter;

architecture Behavioral of video_inverter is

    signal tdata_reg  : std_logic_vector(7 downto 0);
    signal tlast_reg  : std_logic;
    signal tuser_reg  : std_logic;
    signal tvalid_reg : std_logic;

begin

    s00_axis_tready <= m00_axis_tready;

    process(s00_axis_aclk)
    begin
        if rising_edge(s00_axis_aclk) then

            if s00_axis_aresetn = '0' then
                tvalid_reg <= '0';
                tdata_reg  <= (others => '0');
                tlast_reg  <= '0';
                tuser_reg  <= '0';

            else
                
                if s00_axis_tvalid = '1' and m00_axis_tready = '1' then
                    
                    -- Pixel inversion
                    if VidOrig_nVideoInv = '1' then
                        tdata_reg <= std_logic_vector(255 - unsigned(s00_axis_tdata));
                    else
                        tdata_reg <= s00_axis_tdata;
                    end if;

                    tlast_reg  <= s00_axis_tlast;
                    tuser_reg  <= s00_axis_tuser;
                    tvalid_reg <= '1';

                
                elsif m00_axis_tready = '1' then
                    tvalid_reg <= '0';
                end if;

            end if;
        end if;
    end process;

    m00_axis_tdata  <= tdata_reg;
    m00_axis_tlast  <= tlast_reg;
    m00_axis_tuser  <= tuser_reg;
    m00_axis_tvalid <= tvalid_reg;

end Behavioral;
