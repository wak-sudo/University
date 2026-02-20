// Wojciech Kieloch
module mikrofala(
    input  logic clk, nrst, door, start, finish,
    output logic heat, light, bell
);

  // Kody stanów automatu
    const logic [2:0] 
        CLOSED = 3'b000, 
        COOK = 3'b001,
        PAUSE = 3'b010, 
        OPEN = 3'b011,
  		BELL = 3'b100;

    // Stan automatu
    logic [2:0] q;

    // Logika wyjść
    always_comb begin
        heat = 0; light = 0; bell = 0;
        unique case (q)
            COOK: begin light = 1; heat = 1; end
            PAUSE: begin light = 1; end
            OPEN: begin light = 1; end
            BELL: begin bell = 1; end
        	default: begin end
        endcase
    end
	
  	// Funkcja przejścia
    logic[2:0] nextState;
    always_comb begin
      nextState = CLOSED;
      unique case (q)
            CLOSED: begin
              if(door) nextState = OPEN;
              else if(start) nextState = COOK; 
              else nextState = CLOSED;
            end
            COOK: begin
              if(door) nextState = PAUSE;
              else if(finish) nextState = BELL;
              else nextState = COOK;
            end
            PAUSE: nextState = (door ? PAUSE : COOK);
            OPEN: nextState = (door ? OPEN : CLOSED);
            BELL: nextState = (door ? OPEN : BELL);
            default: nextState = 3'bxxx;
        endcase
    end

    // Przerzutnik stanu
    always_ff @(posedge clk or negedge nrst) begin
        if (!nrst)
            q <= CLOSED;
        else q <= nextState;
    end

endmodule
