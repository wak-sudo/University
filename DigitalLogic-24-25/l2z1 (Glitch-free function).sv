// Wojciech Kieloch

module zadanieDrugie(output [0:0] o, input [3:0] i);
  	logic a, b, c, d;
    assign d = i[0:0];
    assign c = i[1:1];
    assign b = i[2:2];
    assign a = i[3:3];
	logic p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;
    assign p1 = a && b && !c;
    assign p2 = !c && d && a;
    assign p3 = a && !b && d;
    assign p4 = c && d && !b;
    assign p5 = a && !b && c;
  	assign p6 = c && !d && a;
  	assign p7 = c && !d && b;
    assign p8 = !a && b && c;
  	assign p9 = !a && b && d;
  	assign p10 = !c && d && b;
  	assign p11 = c && d && !a;
  	assign p12 = a && b && !d;
  	assign o = p1 || p2 || p3 || p4 || p5 || p6 || p7 || p8 || p9 || p10 || p11 || p12;
endmodule   
