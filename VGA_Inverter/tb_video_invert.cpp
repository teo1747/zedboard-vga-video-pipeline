// C simulation testbench for Video_invert: a 4x4 frame, inverted then passed
// through. Returns 0 if every pixel and side channel is right.
#include <iostream>
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,1,1,1> pkt_t;

void Video_invert(hls::stream<pkt_t> &axis_in, hls::stream<pkt_t> &axis_out, bool enable);

const int WIDTH  = 4;
const int HEIGHT = 4;

int run_frame(bool enable) {
    hls::stream<pkt_t> axis_in, axis_out;
    int errors = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            pkt_t pix;
            pix.data = (y * WIDTH + x) * 16 + 5;
            pix.keep = 1;
            pix.strb = 1;
            pix.user = (x == 0 && y == 0);   // start of frame
            pix.last = (x == WIDTH - 1);     // end of line
            pix.id   = 0;
            pix.dest = 0;
            axis_in.write(pix);

            // The IP takes one pixel each call
            Video_invert(axis_in, axis_out, enable);

            pkt_t out = axis_out.read();
            int want = enable ? 255 - (int)pix.data : (int)pix.data;
            if ((int)out.data != want || out.user != pix.user || out.last != pix.last ||
                out.keep != pix.keep) {
                std::cout << "pixel (" << x << ", " << y << "): got " << (int)out.data
                          << ", expected " << want << std::endl;
                errors++;
            }
        }
    }
    return errors;
}

int main() {
    int errors = run_frame(true) + run_frame(false);
    std::cout << (errors ? "FAIL: " : "PASS: ") << errors << " error(s)" << std::endl;
    return errors ? 1 : 0;
}
