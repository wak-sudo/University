// Wojciech Kieloch

module main(input clk, nrst, step, down, output logic[3:0] out);

  logic[3:0] outs;
  logic[3:0] q;
  logic en, sndInput;
  counterPart p0(en, clk, down, nrst, q[0], outs[0]);
  counterPart p1(sndInput, clk, down, nrst, q[1], outs[1]);
  counterPart p2(outs[1], clk, down, nrst, q[2], outs[2]);
  counterPart p3(outs[2], clk, down, nrst, q[3], outs[3]);
  always_comb begin
    if(step == 1) begin
  	 	en = 0;
      sndInput = 1;
    end
	  else begin 
      en = 1;
      sndInput = outs[0];
    end
    out = q; 
  end

endmodule 

module counterPart(input t, clk, down, nrst, output logic q, o);

  wire nq;
  tff_a_reset ff(q, nq, clk, t, nrst);
  always_comb begin
  if(down == 1)
    o = nq & t;
  else o = q & t;
  end

endmodule

module tff_a_reset(output q, nq, input clk, t, nrst);

	wire d;
  dff_a_reset dff(q, nq, clk, d, nrst);
  assign d = (nq & t) | (q & ~t);

endmodule

module dff_a_reset(output q, nq, input clk, d, nrst);
  wire o1, o2, o3, o4;

  nand G1(o1, o4, o2);
  nand G2(o2, o1, clk, nrst);
	nand G3(o3, o2, clk, o4);
  nand G4(o4, o3, d, nrst);

	nand GQ(q, o2, nq);
  nand GNQ(nq, nrst, o3, q);
  
endmodule
