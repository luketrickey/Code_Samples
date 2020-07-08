module top
	reg clk
	reg [2:0]req = 0;
	reg [2:0]callUp = 0;
	reg [2:0]callDown = 0;
	reg key = 0;
	reg bigRedButton;
	
endmodule

module elevator_m(output reg [2:0]floor, output reg [4:0]reqList, output reg [4:0]listUp, output reg [4:0]listDown, output reg up, output reg down, output reg busy, output reg open, input reg [2:0]req, input reg [2:0]callUp, input reg [2:0]callDown, input reg key, input reg bigRedButton);
parameter off = 1'b0, on = 1'b1;
reg [2:0]floor = 1; //floor starts on the first/ground floor, can go anywhere between basement (0) and penthouse (4).
reg [4:0]reqList;
reg [4:0]listUp;
reg [4:0]listDown;
reg up = off;
reg down = off;
reg busy = off;
reg open = off;

always@(callUp)begin
	listUp[callUp] = 1;
end

always@(callDown)begin
	listDown[callDown] = on;
end

always@(reqList)begin
	reqList[req] = on;
end

always@(bigRedButton)begin //if emergency button is pressed, forget all calls and open doors until button is turned off.
	reqList = off;
	listUp = off;
	listDown = off;
	up = off;
	down = off;
	open = on;
end

always@(clk)begin
	if(reqList != off)begin
		req_t(req, callUp, callDown, key, bigRedButton);
	end
	else if(listUp != off)begin
		callUp_t(req, callUp, callDown, key, bigRedButton);
	end
	else if(listDown != off)begin
		callDown_t(req, callUp, callDown, key, bigRedButton);
	end
end

task callup_t(input reg [2:0]req, input reg [2:0]callUp, input reg [2:0]callDown, input reg key, input reg bigRedButton);
	reg y = callUp;
	while(bigRedButton != on)begin //1 Make sure the emergency button has not been pressed.
		if (!busy && (listUp[floor] != on))begin //2 Call from a floor the elevator is not on. Checks to see if elevator is busy already.
			busy = on;
			if (floor < y)begin //4 Check if elevator is on a lower floor than call. Set elevator state to up and go up until on a floor that called to go up or until at a requested floor.
				up = on;
				if(floor != y)begin //5
					floor = floor + 1;
					if ((listUp[floor] == on) || (reqList[floor] == on))begin //7 Once at a called or requested floor, stop moving and open door.
						open = on;
						#5000000000 //wait 5 seconds.
						open = off;
						listUp[floor] = off;
						reqList[floor] = off;
					end //7
				end //5
			end //4
			if (floor > y)begin //6 Check if elevator is on a higher floor than call. Set elevator state to down...
				down = on;
				if(floor != y)begin //5
					floor = floor - 1;
					if ((listUp[floor] == on) || (reqList[floor] == on))begin //7 Once at called or requested floor, stop moving and open door.
						open = on;
						#5000000000 //wait 5 seconds.
						open = off;
						listUp[floor] = off;
						reqList[floor] = off;
					end //7
				end //5
			end //6
			if ((listUp == off) && (listDown == off) && (reqList == off))begin //9 If all calls have been answered, elevator stops moving.
				up = off;
				down = off;
				busy = off;
			end
			else if (reqList != off)begin //check if anyone has requested floors
				req_t(req, callUp, callDown, key, bigRedButton);
			end
			else if (listDown != off)begin //check to see if anyone else is going down.
				callDown_t(req, callUp, callDown, key, bigRedButton); //instantiate task again if there are more floors
			end
			else if (listUp != off)begin
				callUp_t(req, callUp, callDown, key, bigRedButton); //check to see if anyone is going up.
			end //9
		end //2
		else if(busy)begin
			if((listUp[floor] == on) && (up == on))begin //If the elevator is already going up and it gets to a floor where someone wants to go up, pick that person up.
				open = on;
				#5000000000 //wait 5 seconds.
				open = off;
				listUp[floor] == off;
			end
		end //2
	end //1
endtask

task callDown_t(input reg [2:0]req, input reg [2:0]callUp, input reg [2:0]callDown, input reg key, input reg bigRedButton);
	reg y = callDown;
	while(bigRedButton != on)begin //1 Make sure the emergency button has not been pressed.
		if (!busy && (listDown[floor] != on))begin //2 Call from a floor the elevator is not on. Checks to see if elevator is busy already.
			busy = on;
			if (floor < y)begin //4 Check if elevator is on a lower floor than call. Set elevator state to up and go up until on a floor that called to go down or until at a requested floor.
				up = on;
				if(floor != y)begin //5
					floor = floor + 1;
					if ((listDown[floor] == on) || (reqList[floor] == on))begin //7 Once at a called or requested floor, stop moving and open door.
						open = on;
						#5000000000 //wait 5 seconds.
						open = off;
						listDown[floor] = off;
						reqList[floor] = off;
					end //7
				end //5
			end //4
			if (floor > y)begin //6 Check if elevator is on a higher floor than call. Set elevator state to down...
				down = on;
				if(floor != y)begin //5
					floor = floor - 1;
					if ((listDown[floor] == on) || (reqList[floor] == on))begin //7 Once at called or requested floor, stop moving and open door.
						open = on;
						#5000000000 //wait 5 seconds.
						open = off;
						listDown[floor] = off;
						reqList[floor] = off;
					end //7
				end //5
			end //6
			if ((listUp == off) && (listDown == off) && (reqList == off))begin //9 If all calls have been answered, elevator stops moving.
				up = off;
				down = off;
				busy = off;
			end
			else if (reqLIst != off)begin //check if anyone has requested floors
				req_t(req, callUp, callDown, key, bigRedButton);
			end
			else if (listDown != off)begin //check to see if anyone else is going down.
				callDown_t(req, callUp, callDown, key, bigRedButton); //instantiate task again if there are more floors
			end
			else if (listUp != off)begin
				callUp_t(req, callUp, callDown, key, bigRedButton); //check to see if anyone is going up.
			end //9
		end //2
		else if(busy)begin
			if((listDown[floor] == on) && (down == on))begin //If the elevator is already going down and it gets to a floor where someone wants to go down, pick that person up.
				open = on;
				#5000000000 //wait 5 seconds.
				open = off;
				listDown[floor] == off;
			end
		end //2
	end //1
endtask

task req_t(input reg [2:0]req, input reg [2:0]callUp, input reg [2:0]callDown, input reg key, input reg bigRedButton);
	reg z = req;
	while(bigRedButton != on)begin //1 Make sure the emergency button has not been pressed.
		if((z == 4) && (key != on))begin
			reqList[z] = off;
		end
		if(busy)begin //1 If elevator is already doing something, but happens to pass by a floor that a passenger wants to stop on, let that passenger off.
			if(floor == z)begin //2
				open = on;
				#5000000000 //wait 5 seconds.
				open = off;
				reqList[floor] = off;
			end //2
		end//1
		else //3
			if(floor > z)begin //4
				busy = on;
				up = on;
				floor = floor + 1;
				if((reqList[floor] == on) || listUp[floor] == on)begin //5 Drop off passengers that are stopping on this floor or pick up passngers that are going up.
					open = on;
					#5000000000 //wait 5 seconds.
					open = off;
					reqList[floor] = off;
					listUp[floor] = off;
				end //5
			end //4
			else if(floor < z)begin //6
				busy = on;
				down = on;
				floor = floor - 1;
				if((reqList[floor] == on) || (listUp[floor] == on)begin //7 Drop off...or pick up passngers that are going down.
					open = on;
					#5000000000 //wait 5 seconds.
					open = off;
					reqList[floor] = off;
					listDown[floor] = off;
				end //7
			end //6
			if ((listUp == off) && (listDown == off) && (reqList == off))begin //9 If all calls have been answered, elevator stops moving.
				up = off;
				down = off;
				busy = off;
			end
			else if (reqLIst != off)begin //check if anyone has requested floors
				req_t(req, callUp, callDown, key, bigRedButton);
			end
			else if (listDown != off)begin //check to see if anyone else is going down.
				callDown_t(req, callUp, callDown, key, bigRedButton); //instantiate task again if there are more floors
			end
			else if (listUp != off)begin
				callUp_t(req, callUp, callDown, key, bigRedButton); //check to see if anyone is going up.
			end //9
		end //3
	end //1
endtask

endmodule
