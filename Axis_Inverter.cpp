#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<24,1,1,1> axis24_t; // 24-bit data + user/last

// top-level
void Axis_Stream_invert(hls::stream<axis24_t> &s_in,
                hls::stream<axis24_t> &m_out,
                bool VidOrig_nVideoInv) {
#pragma HLS interface axis port=s_in
#pragma HLS interface axis port=m_out
#pragma HLS interface ap_ctrl_none port=return
#pragma HLS interface s_axilite port=VidOrig_nVideoInv bundle=CTRL

    axis24_t tmp;
    // streaming loop: forward or invert
    while (!s_in.empty()) {
        s_in.read(tmp);
        if (VidOrig_nVideoInv) {
            tmp.data = ~tmp.data; // bitwise invert all 24 bits
        }
        // push to output (blocking if downstream full)
        m_out.write(tmp);
    }
}
