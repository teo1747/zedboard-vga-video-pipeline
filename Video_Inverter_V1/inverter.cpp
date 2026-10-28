#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"



typedef ap_axiu<8,1,1,1> AXI_PIXEL;     // 8-bit grayscale pixel
typedef hls::stream<AXI_PIXEL> AXI_STREAM;

void AXI_inverter(
    AXI_STREAM& s_axis_video,     // slave input
    AXI_STREAM& m_axis_video,     // master output
    bool VidOrig_nVideoInv        // switch: 0 = original, 1 = inverted
){
#pragma HLS INTERFACE axis port=s_axis_video
#pragma HLS INTERFACE axis port=m_axis_video

#pragma HLS INTERFACE s_axilite port=VidOrig_nVideoInv bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

    AXI_PIXEL pix_in;
    AXI_PIXEL pix_out;

    while(!s_axis_video.empty()) {
#pragma HLS PIPELINE II=1

        s_axis_video.read(pix_in);

        pix_out = pix_in;

        // ---- pixel inversion ----
        if (VidOrig_nVideoInv == true) {
            pix_out.data = 255 - pix_in.data;
        } else {
            pix_out.data = pix_in.data;
        }

        // ---- forward AXI4-Stream sideband signals ----
        pix_out.keep = pix_in.keep;
        pix_out.strb = pix_in.strb;
        pix_out.user = pix_in.user;
        pix_out.last = pix_in.last;
        pix_out.id   = pix_in.id;
        pix_out.dest = pix_in.dest;

        m_axis_video.write(pix_out);
    }
}
