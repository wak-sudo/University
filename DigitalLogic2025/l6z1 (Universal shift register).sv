// Wojciech Kieloch

module main (
    output logic [7:0] q,
    input [7:0] d,
    input  logic i,
    input  logic c,
    input  logic l,
    input  logic r
);
  
  // select definition:
  // 0 - no change,
  // 1 - shift right, 
  // 2 - shift left,
  // 3 - parallel loading.
  
  logic[1:0] select;
  logic[7:0] plexerOut;
  logic[7:0] dffOut;
  
  mp plexer0(select, { d[0], i, dffOut[1], dffOut[0] } , plexerOut[0]);
  mp plexer1(select, { d[1], dffOut[0], dffOut[2], dffOut[1] } , plexerOut[1]);
  mp plexer2(select, { d[2], dffOut[1], dffOut[3], dffOut[2] } , plexerOut[2]);
  mp plexer3(select, { d[3], dffOut[2], dffOut[4], dffOut[3] } , plexerOut[3]);
  mp plexer4(select, { d[4], dffOut[3], dffOut[5], dffOut[4] } , plexerOut[4]);
  mp plexer5(select, { d[5], dffOut[4], dffOut[6], dffOut[5] } , plexerOut[5]);
  mp plexer6(select, { d[6], dffOut[5], dffOut[7], dffOut[6] } , plexerOut[6]);
  mp plexer7(select, { d[7], dffOut[6], i, dffOut[7] } , plexerOut[7]);
  
  dff dff0(dffOut[0], c, plexerOut[0]);
  dff dff1(dffOut[1], c, plexerOut[1]);
  dff dff2(dffOut[2], c, plexerOut[2]);
  dff dff3(dffOut[3], c, plexerOut[3]);
  dff dff4(dffOut[4], c, plexerOut[4]);
  dff dff5(dffOut[5], c, plexerOut[5]);
  dff dff6(dffOut[6], c, plexerOut[6]);
  dff dff7(dffOut[7], c, plexerOut[7]);
  
  always_comb begin
    select[0] = l;
    select[1] = r;
    q = dffOut;
  end

endmodule

module mp(input[1:0] select, input [3:0]i, output logic o);
    always_comb begin
     case (select)
        0 : o = i[0];
        1 : o = i[1];
        2 : o = i[2];
        3 : o = i[3];
     endcase
      end
endmodule

module dff(output q, input clk, d);
    logic r, s, nr, ns, nq;
    nand gq(q, nr, nq), gnq(nq, ns, q),
    gr(nr, clk, r), gs(ns, nr, clk, s),
    gr1(r, nr, s), gs1(s, ns, d);
endmodule