#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,1,1,1> pkt_t;

// Free-running: no start signal and no AXI-Lite registers, since the block
// design has no processor to drive them. Each call passes one pixel, and
// enable is a plain input port, for a switch or a constant.
void Video_invert(hls::stream<pkt_t> &axis_in, hls::stream<pkt_t> &axis_out, bool enable) {

#pragma HLS INTERFACE axis port=axis_in
#pragma HLS INTERFACE axis port=axis_out
#pragma HLS INTERFACE ap_none port=enable
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

    // Local variables for pixel processing

    pkt_t in_pkt, out_pkt;

    axis_in.read(in_pkt);

    // Copy side channel fields

    out_pkt.keep = in_pkt.keep;
    out_pkt.strb = in_pkt.strb;
    out_pkt.user = in_pkt.user;
    out_pkt.last = in_pkt.last;
    out_pkt.id   = in_pkt.id;
    out_pkt.dest = in_pkt.dest;

    // Data processing: invert if enable, else pass through

    ap_uint<8> px = in_pkt.data;

    if (enable) {

        out_pkt.data = (ap_uint<8>)(255 - px);

    } else {

        out_pkt.data = px;

    }

    axis_out.write(out_pkt);

}
