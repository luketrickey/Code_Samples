module top;
	wire [3:0]fourBout;
	wire [1:0]twoBout;
	reg [3:0]fourBin;
	reg [1:0]twoBin;
	encoder_m encoder(fourBout, twoBin);
	decoder_m decoder(twoBout, fourBin);

	initial begin
		$monitor("encoder input: ", twoBin, "\t encoder output: ", fourBout, "\t decoder input: ", fourBin, "\t decoder output: ", twoBout);
	end

	initial begin
		twoBin = 0; fourBin = 0;
		#2 twoBin = 1; fourBin = 2;
		#2 twoBin = 2; fourBin = 4;
		#2 twoBin = 3; fourBin = 8;
		#2 twoBin = 37; fourBin = 13;
	end
endmodule

module encoder_m(output reg [3:0]fourBout, input [1:0]twoBin);

	always@* begin
		case(twoBin)
			0 : fourBout = 0;
			1 : fourBout = 2;
			2 : fourBout = 4;
			3 : fourBout = 8;
			default : fourBout = 4'bx;
		endcase
	end
endmodule

module decoder_m(output reg [1:0]twoBout, input [3:0]fourBin);

	always@* begin
		case(fourBin)
			0 : twoBout = 0;
			2 : twoBout = 1;
			4 : twoBout = 2;
			8 : twoBout = 3;
			default : twoBout = 4'bx;
		endcase
	end
endmodule
