/*
Luke Trickey, Sam Medeiros
Microcontrollers Using C
Wayne Bynoe
4/13/18
Tic-Tac-Toe Final Project
*/
#include <stdio.h>

void drawpixel(int x_vga, int y_vga, short color) //This is the pixel drawing function from the previous labs.
{
	volatile char *pixel_address = (volatile char*) (0x08000000 + (y_vga <<7) + (x_vga));
	*pixel_address = color;
}

void clearscreen () //The clearscreen function is also from the previous labs.
{
	int x_vga, y_vga;
	for (x_vga = 0; x_vga <=79; x_vga = x_vga + 1)
	{
		for (y_vga = 0; y_vga <=59; y_vga = y_vga + 1)
		{
			drawpixel(x_vga, y_vga, 0);
		}
	}
}

void drawcharacter(int x_char, int y_char, char mychar //The final function from the previous labs.
{
	volatile char* character_buffer = (char *) (0x09000000 + (y_char <<7) + x_char);
	*character_buffer = mychar;
}

int check(int x, int board[]) //The check function is used to check the state of the tic-tac-toe board and determines if one of the players has won.
{
	if(board[0] == x) //As an example, the first if statement checks the state of the upper left corner.
	{
		if(board[3] == x) //The second set of nested if statements checks the adjacent squares. If none of the squares adjacent to the square being checked 
		{				  //are filled with the same int (1 for x, 0 for o), then the function stops checking for a win condition.
			if(board[6] == x) //Finally, if two adjacent squares have the same int, the last square is checked to see if a win condition has been established.
			{
				return 0;  //Once it is determined that a player has won, the function returns a 0, which will break the while loop in the main function and end the game.
			}
		}
		if(board[4] == x)
		{
			if(board[8] == x)
			{
				return 0;
			}
		}
		if(board[1] == x)
		{
			if(board[2] == x)
			{
				return 0;
			}
		}
	}
	if(board[1] == x) //The same process is used to check win conditions from each square other than the center. Because only one win condition is possible from square 1,
	{				  //the function only needs to check that condition. This leads to some if statements being simpler than others.
		if(board[4] == x)
		{
			if(board[7] == x)
			{
				return 0;
			}
		}
	}
	if(board[2] == x)
	{
		if(board[5] == x)
		{
			if(board[8] == x)
			{
				return 0;
			}
		}
		if(board[4] == x)
		{
			if(board[6] == x)
			{
				return 0;
			}
		}
	}
	if(board[3] == x)
	{
		if(board[4] == x)
		{
			if(board[5] == x)
			{
				return 0;
			}
		}
	}
	if(board[6] == x)
	{
		if(board[7] == x)
		{
			if(board[8] == x)
			{
				return 0;
			}
		}
	}
	return 1;
}

void boarddraw(int board[]) //The boarddraw function simply checks the state of the playing board and draws a new shape wherever a player makes a move.
{
	if(board[0] == 1) //This statement checks to see if the 0 square should have an x in it. If it should, the function draws an x on the screen in the specified square.
	{
		drawpixel(19, 24, 4);
		drawpixel(20, 25, 4);
		drawpixel(21, 26, 4);
		drawpixel(22, 27, 4);
		drawpixel(23, 28, 4);
		drawpixel(23, 24, 4);
		drawpixel(22, 25, 4);
		drawpixel(21, 26, 4);
		drawpixel(20, 27, 4);
		drawpixel(19, 28, 4);
	}
	if(board[0] ==0) //Conversely, if the board needs an o on that space instead, the function will draw an o there.
	{
		drawpixel(21, 24, 2);
		drawpixel(22, 24, 2);
		drawpixel(23, 25, 2);
		drawpixel(23, 26, 2);
		drawpixel(23, 27, 2);
		drawpixel(22, 28, 2);
		drawpixel(21, 28, 2);
		drawpixel(20, 28, 2);
		drawpixel(19, 27, 2);
		drawpixel(19, 26, 2);
		drawpixel(19, 25, 2);
		drawpixel(20, 24, 2);
	}
	if(board[1] == 1) //The function repeats this process for each square.
	{
		drawpixel(34, 24, 4);
		drawpixel(35, 25, 4);
		drawpixel(36, 26, 4);
		drawpixel(37, 27, 4);
		drawpixel(38, 28, 4);
		drawpixel(38, 24, 4);
		drawpixel(37, 25, 4);
		drawpixel(36, 26, 4);
		drawpixel(35, 27, 4);
		drawpixel(34, 28, 4);
	}
	if(board[1] == 0)
	{
		drawpixel(36, 24, 2);
		drawpixel(37, 24, 2);
		drawpixel(38, 25, 2);
		drawpixel(38, 26, 2);
		drawpixel(38, 27, 2);
		drawpixel(37, 28, 2);
		drawpixel(36, 28, 2);
		drawpixel(35, 28, 2);
		drawpixel(34, 27, 2);
		drawpixel(34, 26, 2);
		drawpixel(34, 25, 2);
		drawpixel(35, 24, 2);
	}
	if(board[2] == 1)
	{
		drawpixel(50, 24, 4);
		drawpixel(51, 25, 4);
		drawpixel(52, 26, 4);
		drawpixel(53, 27, 4);
		drawpixel(54, 28, 4);
		drawpixel(54, 24, 4);
		drawpixel(53, 25, 4);
		drawpixel(52, 26, 4);
		drawpixel(51, 27, 4);
		drawpixel(50, 28, 4);
	}
	if(board[2] == 0)
	{
		drawpixel(52, 24, 2);
		drawpixel(53, 24, 2);
		drawpixel(54, 25, 2);
		drawpixel(54, 26, 2);
		drawpixel(54, 27, 2);
		drawpixel(53, 28, 2);
		drawpixel(52, 28, 2);
		drawpixel(51, 28, 2);
		drawpixel(50, 27, 2);
		drawpixel(50, 26, 2);
		drawpixel(50, 25, 2);
		drawpixel(51, 24, 2);
	}
	if(board[3] == 1)
	{
		drawpixel(19, 37, 4);
		drawpixel(20, 38, 4);
		drawpixel(21, 39, 4);
		drawpixel(22, 40, 4);
		drawpixel(23, 41, 4);
		drawpixel(23, 37, 4);
		drawpixel(22, 38, 4);
		drawpixel(21, 39, 4);
		drawpixel(20, 40, 4);
		drawpixel(19, 41, 4);
	}
	if(board[3] == 0)
	{
		drawpixel(21, 37, 2);
		drawpixel(22, 37, 2);
		drawpixel(23, 38, 2);
		drawpixel(23, 39, 2);
		drawpixel(23, 40, 2);
		drawpixel(22, 41, 2);
		drawpixel(21, 41, 2);
		drawpixel(20, 41, 2);
		drawpixel(19, 40, 2);
		drawpixel(19, 39, 2);
		drawpixel(19, 38, 2);
		drawpixel(20, 37, 2);
	}
	if(board[4] == 1)
	{
		drawpixel(34, 37, 4);
		drawpixel(35, 38, 4);
		drawpixel(36, 39, 4);
		drawpixel(37, 40, 4);
		drawpixel(38, 41, 4);
		drawpixel(38, 37, 4);
		drawpixel(37, 38, 4);
		drawpixel(36, 39, 4);
		drawpixel(35, 40, 4);
		drawpixel(34, 41, 4);
	}
	if(board[4] == 0)
	{
		drawpixel(36, 37, 2);
		drawpixel(37, 37, 2);
		drawpixel(38, 38, 2);
		drawpixel(38, 39, 2);
		drawpixel(38, 40, 2);
		drawpixel(37, 41, 2);
		drawpixel(36, 41, 2);
		drawpixel(35, 41, 2);
		drawpixel(34, 40, 2);
		drawpixel(34, 39, 2);
		drawpixel(34, 38, 2);
		drawpixel(35, 37, 2);
	}
	if(board[5] == 1)
	{
		drawpixel(50, 37, 4);
		drawpixel(51, 38, 4);
		drawpixel(52, 39, 4);
		drawpixel(53, 40, 4);
		drawpixel(54, 41, 4);
		drawpixel(54, 37, 4);
		drawpixel(53, 38, 4);
		drawpixel(52, 39, 4);
		drawpixel(51, 40, 4);
		drawpixel(50, 41, 4);
	}
	if(board[5] == 0)
	{
		drawpixel(52, 37, 2);
		drawpixel(53, 37, 2);
		drawpixel(54, 38, 2);
		drawpixel(54, 39, 2);
		drawpixel(54, 40, 2);
		drawpixel(53, 41, 2);
		drawpixel(52, 41, 2);
		drawpixel(51, 41, 2);
		drawpixel(50, 40, 2);
		drawpixel(50, 39, 2);
		drawpixel(50, 38, 2);
		drawpixel(51, 37, 2);
	}
	if(board[6] == 1)
	{
		drawpixel(19, 52, 4);
		drawpixel(20, 53, 4);
		drawpixel(21, 54, 4);
		drawpixel(22, 55, 4);
		drawpixel(23, 56, 4);
		drawpixel(23, 52, 4);
		drawpixel(22, 53, 4);
		drawpixel(21, 54, 4);
		drawpixel(20, 55, 4);
		drawpixel(19, 56, 4);
	}
	if(board[6] == 0)
	{
		drawpixel(21, 52, 2);
		drawpixel(22, 52, 2);
		drawpixel(23, 53, 2);
		drawpixel(23, 54, 2);
		drawpixel(23, 55, 2);
		drawpixel(22, 56, 2);
		drawpixel(21, 56, 2);
		drawpixel(20, 56, 2);
		drawpixel(19, 55, 2);
		drawpixel(19, 54, 2);
		drawpixel(19, 53, 2);
		drawpixel(20, 52, 2);
	}
	if(board[7] == 1)
	{
		drawpixel(34, 52, 4);
		drawpixel(35, 53, 4);
		drawpixel(36, 54, 4);
		drawpixel(37, 55, 4);
		drawpixel(38, 56, 4);
		drawpixel(38, 52, 4);
		drawpixel(37, 53, 4);
		drawpixel(36, 54, 4);
		drawpixel(35, 55, 4);
		drawpixel(34, 56, 4);
	}
	if(board[7] == 0)
	{
		drawpixel(36, 52, 2);
		drawpixel(37, 52, 2);
		drawpixel(38, 53, 2);
		drawpixel(38, 54, 2);
		drawpixel(38, 55, 2);
		drawpixel(37, 56, 2);
		drawpixel(36, 56, 2);
		drawpixel(35, 56, 2);
		drawpixel(34, 55, 2);
		drawpixel(34, 54, 2);
		drawpixel(34, 53, 2);
		drawpixel(35, 52, 2);
	}
	if(board[8] == 1)
	{
		drawpixel(50, 52, 4);
		drawpixel(51, 53, 4);
		drawpixel(52, 54, 4);
		drawpixel(53, 55, 4);
		drawpixel(54, 56, 4);
		drawpixel(54, 52, 4);
		drawpixel(53, 53, 4);
		drawpixel(52, 54, 4);
		drawpixel(51, 55, 4);
		drawpixel(50, 56, 4);
	}
	if(board[8] == 0)
	{
		drawpixel(52, 52, 2);
		drawpixel(53, 52, 2);
		drawpixel(54, 53, 2);
		drawpixel(54, 54, 2);
		drawpixel(54, 55, 2);
		drawpixel(53, 56, 2);
		drawpixel(52, 56, 2);
		drawpixel(51, 56, 2);
		drawpixel(50, 55, 2);
		drawpixel(50, 54, 2);
		drawpixel(50, 53, 2);
		drawpixel(51, 52, 2);
	}
}

int main() //The main function is the game itself and draws the playing board.
{
	int x1, x2, y1, y2; //These variables are used to draw the board.
	int q = 1;
	int games = 0;
	char gc[] = {'G', 'a', 'm', 'e', 's', ' ', 'p', 'l', 'a', 'y', 'e', 'd', ':', games}; //This was an attempt to draw the scoreboard, but it did not end up working.
	char score1[] = {'G', 'a', 'm', 'e', 's', ' ', 'w', 'o', 'n', ':', ' ', games};       //The text was displayed but the number of games played did not show up.
	char* gamecount = gc;
	char* score = score1;
	char* Xwin = "X's win!";
	char* Owin = "O's win!";
	int x_start, y_start;
	
	while(q == 1) //This loop runs continuously as long as the game is going. Once the player quits the game, this loop is broken.
	{
	clearscreen(); //It was important to include the clearscreen function here so that once a player restarts the game, the whole board would clear instead of just at the beginning of the first game.
	for(y1 = 20; y1 < 59; y1++) //These loops draw the board.
	{
		drawpixel(28, y1, 15);
	}
	for(y2 = 20; y2 < 59; y2++)
	{
		drawpixel(45, y2, 15);
	}
	for(x1 = 13; x1 < 60; x1++)
	{
		drawpixel(x1, 32, 15);
	}
	for(x2 = 13; x2 < 60; x2++)
	{
		drawpixel(x2, 47, 15);
	}

	x_start = 28;
	y_start = 5;
	while (*gamecount) //These two while loops draw the scoreboard.
	{
		drawcharacter(x_start, y_start, *gamecount);
		x_start = x_start + 1;
		gamecount = gamecount + 1;
	}
	
	x_start = 28;
	y_start = 10;
	while(*score)
	{
		drawcharacter(x_start, y_start, *score);
		x_start = x_start + 1;
		score = score + 1;
	}
	
	games = games + 1; //Counts up everytime another game is played
	int move, in, r1; //These variables are used for the player and computer moves.
	int x = 1;
	int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2}; //This array is the board itself. Each square on the board correlates to one element in the array. At first we used a 2D array in
		int i, win;								//the shape of a 3x3 square, which made more sense at the time, but in practice it was much easier to just use a 1D array.
		while(x == 1) //This while loop is the actual game. It calls the check and boarddraw functions to display the moves and check win conditions.
		{
			printf("Move? "); //This displays on the monitor program, asking the user which square they would like to fill.
			scanf("%d", &move);
			printf("%d\n", move);
			board[move] = 1;
			printf("{");
			for(x = 0; x < 9; x++) //This displays which moves have been made on the monitor program.
			{
				printf("%d ", board[x]);
			}
			printf("}\n");
			x = check(1, board); //This calls the check program to see if the player has won. Notice that the variable being set to the return value is the variable used for the while loop containing the game.
			boarddraw(board); //Sends the current board state to the boarddraw function to display the moves on the board.
			win = 1; //Sets the win variable to 1 so that if a win condition is achieved after the player makes a move, the program will know who won that game.
			if(x == 0)
			{
				break; //Checks to see if someone has won. If the player wins, the computer does not make a move after the winning move.
			}
			
			r1 = rand() % 10; //This creates a random variable between 0 and 9. The square corresponding to that number is then checked to see if it is filled or not.
			while(board[r1] != 2) //A 2 in this case represents an empty space. This is used because 0 represents o's and 1 represents x's.
			{
				r1 = rand() % 10;
			}
			move = r1;
			board[move] = 0;
			printf("{");
			for(x = 0; x < 9; x++)
			{
				printf("%d ", board[x]);
			}
			printf("}\n");
			x = check(0, board);
			boarddraw(board);
			win = 0;
		}
		if(win == 1) //Once the loop is broken by a player winning the game, the game checks which player won. It then displays the winner on the screen above the board.
		{
			x_start = 28;
			y_start = 15;
			while(*Xwin)
			{
				drawcharacter(x_start, y_start, *Xwin);
				x_start = x_start + 1;
				Xwin = Xwin + 1;
			}
		}
		if(win == 0)
		{
			x_start = 28;
			y_start = 15;
			while(*Owin)
			{
				drawcharacter(x_start, y_start, *Owin);
				x_start = x_start + 1;
				Owin = Owin + 1;
			}
		}
		printf("Winner!\n"); //These are displayed on the monitor program, telling the user that a player has won the game with the last move and asking if they would like to play again.
		printf("Play again? (y = 1, n = 0) ");
		scanf("%d", &q); //The user's decision is then sent to int q, which is the variable controlling the while loops that runs the game.
	}
}