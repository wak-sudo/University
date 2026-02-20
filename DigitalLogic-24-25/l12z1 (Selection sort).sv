// Wojciech Kieloch

// note: mem ops are on posedge, rest is on negedge.

typedef enum { READY_A, READY_B, READY_C,
              OUTER_A,
              INNER_A, INNER_B, INNER_C, INNER_D,
              END_A, END_B,
              SWAP_A, NOP } OpFlags;

typedef enum { READY, OUTER, INNER, END, SWAP } e_states;

typedef struct packed {
  logic start;
  logic wr;
  logic iEQseven;
  logic cLTm;
  logic jEQseven;
  logic iEQjm;
} Flags_t;

typedef struct packed {
  logic[7:0] dataIn;
  logic[2:0] addr;
  logic wr;
  logic start;
} UserData;

module selectionSort(
  input clk, nrst, start,
  input[2:0] addr,
  input wr,
  input[7:0] datain,
  output logic[7:0] dataout,
  output logic ready);

  Flags_t flags;
  OpFlags crTask; 

  UserData userData;

  always_comb begin
    userData.dataIn = datain;
    userData.addr = addr;
    userData.wr = wr;
    userData.start = start;
  end

  controlPath ctrlModule(
    .clk (clk),
    .nrst(nrst),
    .flags(flags),
    .curTask(crTask),
    .ready(ready));

  dataPath dataModule(
    .clk (clk),
    .curTask (crTask),
    .userData (userData),
    .dataOut (dataout),
    .flags (flags));

endmodule

module dataPath(
  input clk,
  input OpFlags curTask,
  input UserData userData,
  output logic[7:0] dataOut,
  output Flags_t flags);

  // mem interface:
  logic write;
  logic[7:0] dataIn;
  logic [2:0] raddr, waddr;

  memory mem(
    .write (write), 
    .clk (clk),
    .waddr(waddr),
    .raddr(raddr),
    .dataIn(dataIn),
    .dataOut(dataOut));

`define WRITE_MEM(someAddr, val) \
  begin \
  waddr = someAddr; \
  dataIn = val; \
  raddr = 0; \
  write = 1; \
  end

`define READ_MEM(someAddr) \
  begin \
  raddr = someAddr; \
  waddr = 0; \
  dataIn = 0; \
  write = 0; \
  end 

`define RW_MEM(rAddr, wAddr, val) \
  begin \
  raddr = rAddr; \
  waddr = wAddr; \
  dataIn = val; \
  write = 1; \
  end

  // variables:
  logic[7:0] c, m;
  logic [2:0] j, i, jm;

  always_comb begin
    flags.start = userData.start;
    flags.wr = userData.wr;
    flags.iEQseven = (i == 7);
    flags.cLTm = (c < m);
    flags.jEQseven = (j == 7);
    flags.iEQjm = (i == jm);

    case(curTask) // for some reason Yosys doesnt like OpFlags.READY_A etc.

      READY_A: `READ_MEM(0)
      READY_B: `WRITE_MEM(userData.addr, userData.dataIn)
      READY_C: `READ_MEM(userData.addr)
      OUTER_A: `READ_MEM(i+1)
      INNER_A: `READ_MEM(i)
      INNER_B: `READ_MEM(j+1)
      INNER_C: `READ_MEM(i)
      INNER_D: `READ_MEM(j+1)
      END_A: `READ_MEM(i+1)
      END_B: `WRITE_MEM(jm, c)
      SWAP_A: `RW_MEM(i+1, i, m)
      default: `READ_MEM(0)

    endcase

  end

  always_ff @(negedge clk) begin
    case(curTask)

      READY_A: begin
        i <= 0;
        c <= dataOut;
      end

      OUTER_A: begin
        j <= i+1;
        jm <= i;
        m <= c;
        c <= dataOut;
      end

      INNER_A: begin
        m <= c;
        jm <= j;
        c <= dataOut;
      end

      INNER_B: begin
        m <= c;
        jm <= j;
        j <= j+1;
        c <= dataOut;
      end

      INNER_C: begin
        c <= dataOut;
      end

      INNER_D: begin
        j <= j+1;
        c <= dataOut;
      end

      END_A: begin
        i <= i+1;
        c <= dataOut;
      end

      SWAP_A: begin
        i <= i+1;
        c <= dataOut;
      end

      default: begin end

    endcase
  end 


endmodule

module controlPath(
  input clk, nrst,
  input Flags_t flags,
  output OpFlags curTask,
  output logic ready);

  e_states crState;

  always_comb begin

    if(crState == READY) ready = 1;
    else ready = 0;

    case(crState)

      READY: begin

        if(flags.start)
          curTask = READY_A;
        else if(flags.wr)
          curTask = READY_B;
        else curTask = READY_C;

      end

      OUTER: begin

        if(flags.iEQseven) curTask = NOP;
        else curTask = OUTER_A;

      end

      INNER: begin

        if(flags.cLTm && flags.jEQseven) curTask = INNER_A;
        else if (flags.cLTm) curTask = INNER_B;
        else if (flags.jEQseven) curTask = INNER_C;
        else curTask = INNER_D;

      end

      END: begin

        if(flags.iEQjm) curTask = END_A;
        else curTask = END_B;

      end

      SWAP: curTask = SWAP_A;

      default: curTask = NOP;

    endcase

  end

  always_ff @(negedge clk, negedge nrst) begin
    if(!nrst) crState <= READY;
    else case(crState)

      READY: if(flags.start) crState <= OUTER;

      OUTER: if(flags.iEQseven) crState <= READY;
      else crState <= INNER;

      INNER: if(flags.jEQseven) crState <= END;

      END: if(flags.iEQjm) crState <= OUTER;
      else crState <= SWAP;

      SWAP: crState <= OUTER;

      default: begin end

    endcase
  end

endmodule

module memory(
  input write, clk,
  input[2:0] raddr, waddr,
  input[7:0] dataIn,
  output logic[7:0] dataOut);

  logic[7:0] memory[8];
  always_ff @(posedge clk) begin
    if(write) memory[waddr] <= dataIn;
    dataOut <= memory[raddr];
  end
endmodule
