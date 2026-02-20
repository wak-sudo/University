// Wojciech Kieloch

module minmax(output[3:0] max, min, input[3:0] a, b);
  always_comb begin
  if(a > b) begin
    max[3:0] = a[3:0];
    min[3:0] = b[3:0];
  end
   else begin
     max[3:0] = b[3:0];
     min[3:0] = a[3:0];
   end
  end
endmodule

module sorter(output logic [15:0] o, input [15:0] i);
  logic[3:0] x[4];
  logic[3:0] cmax[5], cmin[5];
  assign x[0] = i[3:0];
  assign x[1] = i[7:4];
  assign x[2] = i[11:8];
  assign x[3] = i[15:12];
  minmax c1(cmax[0], cmin[0], x[0], x[1]);
  minmax c2(cmax[1], cmin[1], x[2], x[3]);
  minmax c3(cmax[2], cmin[2], cmin[0], cmin[1]);
  minmax c4(cmax[3], cmin[3], cmax[0], cmax[1]);
  minmax c5(cmax[4], cmin[4], cmin[3], cmax[2]);
  always_comb begin
    o[3:0] = cmin[2];
    o[7:4] = cmin[4];
    o[11:8] = cmax[4];
    o[15:12] = cmax[3];
  end
endmodule