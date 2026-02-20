// Wojciech Kieloch

module memory(
  input clk, write,
  input[9:0] raddr, 
  input[9:0] waddr,
  input[15:0] dataIn,
  output[15:0] out
);

  logic[15:0] mem[1024];
  assign out = mem[raddr];
  always_ff @(posedge clk)
    if(write) mem[waddr] <= dataIn;          

endmodule

module clkRPN(
  input nrst, step,
  input[15:0] d,
  input push,
  input[1:0] op,
  output logic[15:0] out,
  output logic[9:0] cnt
);
  
  logic[15:0] prevCellOut;
  logic[15:0] dataIn;
  logic[9:0] subOneCnt, subTwoCnt, addOneCnt;
  logic write;
  logic[9:0] writePtr;
  
  memory memUnit(step, write, subTwoCnt, writePtr, dataIn, prevCellOut);

  always_comb begin 
    
    subOneCnt = (cnt == 0 ? 0 : cnt - 1);
    subTwoCnt = (cnt < 2 ? 0 : cnt - 2);
    addOneCnt = (cnt == 1023 ? 1023 : cnt + 1);
    write = (op != 0 || push == 1);
    
    if(push == 1) begin
      dataIn = d;
      writePtr = (cnt == 0 ? 0 : cnt);
    end 
    else case(op)
      0: begin dataIn = out; writePtr = subOneCnt; end
      1: begin dataIn = -out; writePtr = subOneCnt; end 
      2: begin dataIn = prevCellOut + out; writePtr = subTwoCnt; end
      3: begin dataIn = prevCellOut * out; writePtr = subTwoCnt; end
      default: begin dataIn = d; writePtr = subOneCnt; end
    endcase
      
  end 

  always_ff @(posedge step, negedge nrst) begin
    
    if(nrst != 0) begin
      out <= dataIn;
      if(push == 1)
        cnt <= addOneCnt;
      else if(op == 2 || op == 3)
        cnt <= subOneCnt;
      else cnt <= cnt;
    end 
    else begin
      out <= 0;
      cnt <= 0;
    end
    
  end
  
endmodule
