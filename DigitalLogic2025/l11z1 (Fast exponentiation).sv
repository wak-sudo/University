// Wojciech Kieloch

module exp(
  input clk, nrst, start,
  input[15:0] inx,
  input[7:0] inn,
  output logic ready,
  output logic[15:0] out);
  
  const logic READY = 1, BUSY = 0;
  
  logic state, twoDivFlag, nZeroFlag;
  logic[15:0] a, x, fstMultArg, multProd;
  logic[7:0] n;
  
  always_comb begin
    
    ready = state;
    nZeroFlag = (n == 0);
    twoDivFlag = !n[0];
    
    if(twoDivFlag) fstMultArg = x;
    else fstMultArg = a;
    
    multProd = fstMultArg*x;
    
  end
  
  always_ff @(posedge clk, negedge nrst) begin
    if(!nrst) state <= READY; 
    else if(state == READY && start) begin
      state <= BUSY;
      a <= 1;
      x <= inx;
      n <= inn;
    end
    else if(state == BUSY) begin
      if(nZeroFlag) begin
        state <= READY;
        out <= a;
      end else if(twoDivFlag) begin
        x <= multProd;
        n <= (n >> 1);
      end else begin
        a <= multProd;
        n <= n - 1;
      end
  	end
  end
  
endmodule
