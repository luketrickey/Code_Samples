module top;

	wire [7:0]result;
	wire overflow;
	reg [7:0]input1;
	reg [7:0]input2;
	reg [3:0]opcode;
	calculator_m calculator(result, overflow, input1, input2, opcode);

	initial begin
		$monitor("input1: ", input1, "\t input2: ",input2,"\t opcode: ",opcode,"\t overflow: ",overflow,"\t result: ",result);
	end	

	initial begin
		input1 = 10; input2 = 5; opcode = 0;
		#2 opcode = 2;
		#2 opcode = 3;
		#2 opcode = 4;
		#2 opcode = 5;
		#2 opcode = 6;
		#2 opcode = 7;
		#2 opcode = 8;
		#2 opcode = 9;
		#2 opcode = 10;
		#2 opcode = 11;
	end

endmodule

module calculator_m(output reg [7:0]result, output reg overflow, input [7:0]input1, input2, input [3:0]opcode);

	always@(*) begin

		if(!opcode) begin
			{overflow, result} = input1 + input2;
		end
		else if(opcode == 1) begin
			{overflow, result} = input1 + input2;
		end
		else if(opcode == 2) begin
			{overflow, result} = input1 - input2;
		end
		else if(opcode == 3) begin
			{overflow, result} = input1 * input2;		
		end
		else if(opcode == 4) begin
			{overflow, result} = input1 / input2;		
		end
		else if(opcode == 5) begin
			{overflow, result} = input1 % input2;		
		end
		else if(opcode == 6) begin
			{overflow, result} = input1 && input2;		
		end
		else if(opcode == 7) begin
			{overflow, result} = input1 || input2;		
		end
		else if(opcode == 8) begin
			{overflow, result} = ~input1;		
		end
		else if(opcode == 9) begin
			if(input1 < input2) begin
				{overflow, result} = 1;
			end
			else begin
				{overflow, result} = 0;
			end		
		end
		else if(opcode == 10) begin
			{overflow, result} = (input1 == input2);		
		end
		else if(opcode == 11) begin
			{overflow, result} = (input1 > input2);
		end
		else begin
			{overflow, result} = 0;
		end
	end
endmodule
