module top;
	reg clk;
	reg [5:0]setMin;
	reg [3:0]setHr;
	reg setPm;
	reg set;
	reg [5:0]alarmMin;
	reg [3:0]alarmHr;
	reg alarmPm;
	reg alarm;
	reg snooze;
	wire [5:0]minutes;
	wire [3:0]hours;
	wire pm;
	wire alarmSound;
clock clock_1(minutes, hours, pm, alarmSound, clk, set, setMin, setHr, setPm, alarm, alarmMin, alarmHr, alarmPm);

initial begin
	clk = 0;
	repeat(100000000)begin
		#1 clk = !clk;
	end
end

initial begin
	#1 snooze = 0;
	setHr = 9;
	setMin = 45;
	setPm = 0;
	alarmHr = 10;
	alarmMin = 0;
	alarmPm = 0;
	snooze = 0;
end

initial begin
	#5 set = 1;
	#1 set = 0;
	alarm = 1;
	#45 alarm = 0;
end
endmodule

module clock(output reg [5:0]minutes, output reg [3:0]hours, output reg pm, output reg alarmSound, input clk, input set, input [5:0]setMin, input [3:0]setHr, input setPm, input alarm, input [5:0]alarmMin, input [3:0]alarmHr, input alarmPm, input snooze);
	reg [2:0]snoozeCount = 0;
	initial begin
		minutes = 0;
		hours = 12;
		pm = 0;
		alarmSound = 0;
	end
	always@(posedge clk)begin
		minutes = minutes + 1;
		if(minutes >= 60)begin
			minutes = 0;
			hours = hours + 1;
		end
		if((hours == 12) && (minutes == 0))begin
			pm = !pm;
		end
		if(hours >= 13)begin
			hours = 1;
		end
		if(set == 1)begin
			minutes = setMin;
			hours = setHr;
		end
		if(alarm == 1)begin
			if((minutes == alarmMin) && (hours == alarmHr) && (pm == alarmPm))begin
				alarmSound = 1;
			end
		end
	end
	always@(negedge alarm)begin
		alarmSound = 0;
	end
endmodule
