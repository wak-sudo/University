// Wojciech Kieloch

module grayToBin(output logic [31:0] o, input [31:0] i);
  logic[31:0] prevRes[4];
  logic[31:0] shifted[5];
  always_comb begin
    shifted[0] = i[31:0] >> 16;
    prevRes[0] = shifted[0] ^ i[31:0];
    shifted[1] = prevRes[0] >> 8;
    prevRes[1] = shifted[1] ^ prevRes[0];
    shifted[2] = prevRes[1] >> 4;
    prevRes[2] = shifted[2] ^ prevRes[1];
    shifted[3] = prevRes[2] >> 2;
    prevRes[3] = shifted[3] ^ prevRes[2];
    shifted[4] = prevRes[3] >> 1;
    o[31:0] = shifted[4] ^ prevRes[3];
  end
endmodule