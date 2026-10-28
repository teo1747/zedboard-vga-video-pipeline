-- Testbench for bit_extraction: the 4 MSBs of the pixel during active
-- video, black during blanking. Reports each step and the number of errors.
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_bit_extraction is
end tb_bit_extraction;

architecture sim of tb_bit_extraction is

  signal clk_tb          : std_logic := '0';
  signal rst_tb          : std_logic := '1';
  signal Din_tb          : std_logic_vector(7 downto 0) := (others => '0');
  signal Sel_ActVideo_tb : std_logic := '0';
  signal Dout_tb         : std_logic_vector(3 downto 0);
  signal done            : boolean := false;

  constant clk_period : time := 10 ns;

begin

  uut: entity work.bit_extraction
    port map (
      Din          => Din_tb,
      Sel_ActVideo => Sel_ActVideo_tb,
      Dout         => Dout_tb
    );

  clk_tb <= not clk_tb after clk_period / 2 when not done;

  stim: process
    variable errors : natural := 0;

    procedure apply(din : std_logic_vector(7 downto 0); act : std_logic;
                    want : std_logic_vector(3 downto 0)) is
    begin
      Din_tb          <= din;
      Sel_ActVideo_tb <= act;
      wait for clk_period;
      if Dout_tb /= want then
        report "Din = " & integer'image(to_integer(unsigned(din))) &
               ", active video = " & std_logic'image(act) & ": wrong Dout"
          severity error;
        errors := errors + 1;
      end if;
    end procedure;

  begin
    wait for clk_period;
    rst_tb <= '0';

    apply(x"B3", '1', "1011");   -- active video: the 4 MSBs
    apply(x"A1", '1', "1010");
    apply(x"A1", '0', "0000");   -- blanking: black
    apply(x"FF", '1', "1111");
    apply(x"FF", '0', "0000");
    apply(x"00", '1', "0000");
    apply(x"7F", '1', "0111");

    report "end of test, " & integer'image(errors) & " error(s)";
    done <= true;
    wait;
  end process;

end sim;
