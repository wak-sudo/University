// Wojciech Kieloch

typedef enum {NOP, INIT, OUT, SWAP, SUB} e_op_flags;

module gcd(
  input clk, nrst, start,
  input[7:0] ina, inb,
  output logic ready,
  output logic[7:0] out);
  
  e_op_flags opFlags;
  logic equalFlag, asmallerFlag;
  
  gcd_control ctrl(
    clk, nrst, start,
    equalFlag, asmallerFlag,
    opFlags,
    ready);
  
  gcd_data data(
    clk, nrst, ina, inb,
    opFlags,
  	equalFlag, asmallerFlag,
    out);
  
endmodule

module gcd_control(
  input clk, nrst, start,
  input equalFlag, asmallerFlag,
  output e_op_flags opFlags,
  output logic ready);
  
  const logic READY = 1, BUSY = 0;
  
  logic state;
  
  always_comb begin
    
    ready = state;
 
    case(state)
      READY: begin
        if(start)
          opFlags = INIT;
        else opFlags = NOP;   
      end
      BUSY: begin
        if(equalFlag)
          opFlags = OUT;
        else if (asmallerFlag)
          opFlags = SWAP;
        else opFlags = SUB;
      end
      default: opFlags = NOP;
    endcase
    
  end
  
  always_ff @(posedge clk, negedge nrst) begin
    
    if(!nrst) state <= READY;
    else
      case(state)
        READY:
          if(start) state <= BUSY;
        BUSY:
          if(equalFlag) state <= READY;
      endcase
    
  end
  
endmodule

module gcd_data(
  input clk, nrst,
  input[7:0] ina, inb,
  input e_op_flags opFlags,
  output equalFlag, asmallerFlag,
  output logic[7:0] out);
  
  logic[7:0] a, b;
  
  always_comb begin
    equalFlag = (a == b);
    asmallerFlag = (a < b);
  end
  
  always_ff @(posedge clk, negedge nrst) begin
    if(!nrst) begin
      a <= 0;
      b <= 0;
    end
    else case(opFlags)
      INIT: begin
        a <= ina;
      	b <= inb;
      end
      OUT: out <= a;
      SWAP: begin
        b <= a;
        a <= b;
      end
      SUB: a <= a-b;
      default: begin end
    endcase
    
  end
  
endmodule
