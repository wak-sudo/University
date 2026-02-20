// Wojciech Kieloch
module pwm(input clk, input[15:0] d, input[1:0] sel, 
           output logic[15:0] cnt, cmp, top, output logic out);
  
  	assign out = (cnt < cmp);
    always_ff@(posedge clk) begin 
        case(sel)
            1: cmp <= d;
            2: top <= d;
            default:;
        endcase
        
        if (sel == 3) cnt <= d;
        else if (cnt < top) cnt <= cnt + 1;
        else cnt <= 0;

    end
endmodule
