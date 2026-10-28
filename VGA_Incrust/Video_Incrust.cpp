#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,1,1,1> pkt_t;

// Each digit: 7 rows, each row uses lower 5 bits LSB
static const unsigned char font5x7[10][7] = {
    {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E},
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},
    {0x1E,0x11,0x01,0x02,0x04,0x08,0x1F},
    {0x1E,0x11,0x01,0x06,0x01,0x11,0x1E},
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02},
    {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E},
    {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E},
    {0x1F,0x11,0x02,0x04,0x04,0x04,0x04},
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E},
    {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C}
};

// Top-left location and spacing for the overlay
constexpr int X_OFFSET = 10;
constexpr int Y_OFFSET = 10;
constexpr int DIGIT_WIDTH = 5;
constexpr int DIGIT_HEIGHT = 7;
constexpr int DIGIT_SPACING = 1;

// Free-running: no start signal and no AXI-Lite registers, since the block
// design has no processor to drive them. Each call passes one pixel, and
// binome and enable are plain input ports, for switches or constants.
void Video_incrusion(hls::stream<pkt_t> &axis_in,
                        hls::stream<pkt_t> &axis_out,
                        ap_uint<8> binome, // 0..99
                        bool enable) {
#pragma HLS INTERFACE axis port=axis_in
#pragma HLS INTERFACE axis port=axis_out
#pragma HLS INTERFACE ap_none port=binome
#pragma HLS INTERFACE ap_none port=enable
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

    pkt_t in_pkt, out_pkt;

    // Track pixel coordinates within the frame
    static unsigned int x = 0;
    static unsigned int y = 0;
#pragma HLS RESET variable=x
#pragma HLS RESET variable=y

    axis_in.read(in_pkt);

    // If tuser==1, consider it is Start Of Frame -> reset coordinates
    if (in_pkt.user == 1) {
        x = 0;
        y = 0;
    }

    //forward pixel
    ap_uint<8> px = in_pkt.data;
    ap_uint<8> out_px = px;

    if (enable) {

        unsigned int b = (unsigned int)binome;
        unsigned int tens = (b / 10) % 10;
        unsigned int units = b % 10;


        int digit0_x = X_OFFSET;
        int digit1_x = X_OFFSET + DIGIT_WIDTH + DIGIT_SPACING;
        int digit_y   = Y_OFFSET;


        if ((int)x >= digit0_x && (int)x < (digit0_x + DIGIT_WIDTH) &&
            (int)y >= digit_y && (int)y < (digit_y + DIGIT_HEIGHT)) {

            int fx = (int)x - digit0_x;
            int fy = (int)y - digit_y;
            unsigned char row = font5x7[tens][fy];
            bool pixel_on = (row >> (DIGIT_WIDTH - 1 - fx)) & 0x1;
            if (pixel_on) out_px = 255;
        }

        else if ((int)x >= digit1_x && (int)x < (digit1_x + DIGIT_WIDTH) &&
                 (int)y >= digit_y && (int)y < (digit_y + DIGIT_HEIGHT)) {

            int fx = (int)x - digit1_x;
            int fy = (int)y - digit_y;
            unsigned char row = font5x7[units][fy];
            bool pixel_on = (row >> (DIGIT_WIDTH - 1 - fx)) & 0x1;
            if (pixel_on) out_px = 255;
        }
    }

    out_pkt.data = out_px;
    out_pkt.keep = in_pkt.keep;
    out_pkt.strb = in_pkt.strb;
    out_pkt.user = in_pkt.user;
    out_pkt.last = in_pkt.last;
    out_pkt.id   = in_pkt.id;
    out_pkt.dest = in_pkt.dest;

    axis_out.write(out_pkt);

    if (in_pkt.last == 1) {
        x = 0;
        y++;
    } else {
        x++;
    }
}
