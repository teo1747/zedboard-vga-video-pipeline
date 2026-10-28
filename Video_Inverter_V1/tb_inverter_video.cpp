#include <iostream>
#include "inverter.h"
using namespace std;

int main() {

    AXI_STREAM s_axis_video;
    AXI_STREAM m_axis_video;

    // --- TEST IMAGE (4x4 grayscale) ---
    const int WIDTH  = 4;
    const int HEIGHT = 4;
    ap_uint<8> img_in[HEIGHT][WIDTH] = {
        { 10,  20,  30,  40},
        { 50,  60,  70,  80},
        { 90, 100, 110, 120},
        {130, 140, 150, 160}
    };

    cout << "---- TEST START ----" << endl;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            AXI_PIXEL pix;
            pix.data = img_in[y][x];

            pix.keep = -1;     // all bytes valid
            pix.strb = -1;
            pix.user = (y == 0 && x == 0) ? 1 : 0;  // TUSER for SOF
            pix.last = (x == WIDTH - 1) ? 1 : 0;    // TLAST for end of line
            pix.id   = 0;
            pix.dest = 0;

            s_axis_video.write(pix);
        }
    }



    pixel_inverter(s_axis_video, m_axis_video, true);


    cout << "\nOutput pixels:\n";

    int i = 0;
    while (!m_axis_video.empty()) {
        AXI_PIXEL out_pix;
        m_axis_video.read(out_pix);

        i++;
    }

    return 0;
}
