// C simulation testbench for Video_incrusion: two 32x24 gray frames with the
// number 42 drawn in, then one with the overlay off. Prints the overlaid
// corner and returns 0 if every pixel is right.
#include <iostream>
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,1,1,1> pkt_t;

void Video_incrusion(hls::stream<pkt_t> &axis_in, hls::stream<pkt_t> &axis_out,
                     ap_uint<8> binome, bool enable);

const int WIDTH  = 32;
const int HEIGHT = 24;
const int GRAY   = 64;

// The digits 4 and 2 of the IP's font, 5 pixels wide, MSB on the left
const unsigned char four[7] = {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02};
const unsigned char two[7]  = {0x1E,0x11,0x01,0x02,0x04,0x08,0x1F};

int expected(int x, int y, bool enable) {
    if (!enable || y < 10 || y >= 17) return GRAY;
    if (x >= 10 && x < 15 && ((four[y - 10] >> (14 - x)) & 1)) return 255;
    if (x >= 16 && x < 21 && ((two[y - 10] >> (20 - x)) & 1)) return 255;
    return GRAY;
}

int run_frame(bool enable, bool show) {
    hls::stream<pkt_t> axis_in, axis_out;
    int errors = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            pkt_t pix;
            pix.data = GRAY;
            pix.keep = 1;
            pix.strb = 1;
            pix.user = (x == 0 && y == 0);   // start of frame
            pix.last = (x == WIDTH - 1);     // end of line
            pix.id   = 0;
            pix.dest = 0;
            axis_in.write(pix);

            // The IP takes one pixel each call
            Video_incrusion(axis_in, axis_out, 42, enable);

            pkt_t out = axis_out.read();
            if ((int)out.data != expected(x, y, enable) || out.user != pix.user ||
                out.last != pix.last) {
                errors++;
            }
            if (show && y >= 8 && y < 19 && x >= 8 && x < 23) {
                std::cout << (out.data == 255 ? '#' : '.');
                if (x == 22) std::cout << std::endl;
            }
        }
    }
    return errors;
}

int main() {
    int errors = run_frame(true, true);
    errors += run_frame(true, false);   // the coordinates restart with each frame
    errors += run_frame(false, false);
    std::cout << (errors ? "FAIL: " : "PASS: ") << errors << " error(s)" << std::endl;
    return errors ? 1 : 0;
}
