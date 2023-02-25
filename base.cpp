#ifndef _BASE_
#define _BASE_

#define MAX 16
#define SIDE 4 
#define SPACE MAX+2*SIDE


#include <iostream>
#include <string.h>
#include <utility>

using namespace std;

#define set0(a)memset(a, 0, sizeof a)
#define INF 40000000
#define Min(a,b) ((a>=b)*(b) + (a<b)*(a))
#define Abs(a)  ((a>=0)*(a) - (a<0)*(a))

//from an integer to a char in base 16 
//0 - 9 stay and will simply return its character conterpart 
//10 - 36 will assume the letters A - Z (uppercase)
//37 - 62 will assume the letters a - z (lowercase)
char toBase16 (int a);

//function to copy a string src to another string dest
//the strcpy function from string.h wasnt working becouse of the leading \0
void strCpy (char * src, char * dest);

//function to compare 2 char arrays 
//wrapper for strcmp 
//this will be used for map and set comparisson functions
//to determine wich boards were visited or not
//return 1 if a<b and 0 otherwise
class strComp 
{
	public:
		bool operator() (char* a, char* b)const ;
};

class Board
{
	private: 
		char values[SPACE];
		short zeroX;
		short zeroY;
		bool  valid;
		

	public:
		//atributes:
		Board* parent;
		//constructors:	
		//Creating a new board by reading input from stdin
		Board();

		//creating a board from an array of valules 
		//and the position of the white tile
		Board(char vals[SPACE],int posX,int posY,Board* parent);		
	

		//Methods
		//Moving the white tile to 1 of the 4 possible directions
		//this function returns null if the piece 0 goes out of bounds
		//and returns a new board with the 0 moved to a certain direction
		//0 is up, 1 is left, 2 is down, 3 is left 
		Board* moveWhite(int direction);	
		
		//this function will calculate the inversion of the board
		//and then xor the result with the row of the white space
		//itll then return the group this board belongs to
		//returns 1 if the group is even inversion odd white space row (or vice versa)
		//and returns 0 if the group is even inversion and white space row(or vice versa)
		bool group(); 

		//this function will return true if the board in cause is valid
		//if it isnt valid then it will return false 
		//the logic to check if the board is valid or not is actually defined in the constructur called after the move white function
		//after shifting the white tile to a certain direction the constructor will determine if the move is valid or not
		bool isValid();
		
		
		//simple function to print the array values to the screan in the form of a matrix 
		//serves to imitate a board
		char* toString();

		//function to print a path to a board
		void printBoard();

		// to check if one board is the same as another
		// will also check if the board was seen in its path
		bool check(Board* end);

		//heuristics
		//this methods do not belong to the class 
		//but they can acess all of the privete atributes
		friend int manhatanDistance(Board* a, Board* goal);
		friend int misplaced(Board* a,Board* goal);
};

//IMPLEMENTATION OF FUNCTIONS
Board::Board(char vals[SPACE],int posX,int posY, Board* p)
{
	strCpy(values,vals);
	zeroX = posX;
	zeroY = posY;
	parent = p;	

	//this line is just boundary checking
	//if it is inside the bondry then it will set valid to 1
	//otherwise valid will be 0 and the board will be invalid
	valid = (posX >= 0 && posX < 4 && posY >= 0 && posY < 4);
			
}
char* Board::toString()
{
	char* temp = (char *)malloc(17 * sizeof(char));	
	for(int i = 0; i < MAX; i++)
		temp[i] = values[i+SIDE];
	temp[16]='\0';
	return temp;
}
void  Board::printBoard()
{
	if(this->parent != NULL)
		parent->printBoard();
	for(int i = 4;i<SPACE;i+=4)
		printf("%c %c %c %c\n",values[i],values[i+1],values[i+2],values[i+3]);
}
bool Board::check(Board* a)
{
	if(a==NULL)return false;
	char* t1 = a-> toString();
	char* t2 = this->toString();

	if(strcmp(t1,t2) == 0)return true;
	free(t1);
	free(t2);
	return this->check(a->parent);

}
Board::Board()
{
	set0(values);
	zeroX = 0;
	zeroY = 0;
	valid = 1;
	parent = NULL;
	for(int i = 0; i < SIDE; i++)
	{
		for(int j = 0; j < SIDE; j++)
		{	
			short temp; 
			scanf("%hd",&temp);
			
			zeroX += i*(temp==0);
			zeroY += j*(temp==0);
			
			values[(i+1)*SIDE + j] = toBase16(temp);
		}
	}
}
bool Board::group()
{
	int count=0;
	for(int i=0; i < MAX; i++)
		for(int j= i+1; j<MAX;j++)
			count += ( values[i+SIDE]>values[j+SIDE]  && values[j+SIDE]!= '0');
		
	return ((count%2) ^ (zeroX%2));
}

Board* Board::moveWhite(int direction)
{
	char temp[SPACE];
	set0(temp);
	strCpy(temp, values);
		
	short posX = zeroX;
	short posY = zeroY;

	short pos = posX*SIDE + posY + SIDE; 

	switch(direction)
	{
		//move up
		case 0:
			temp[pos] = temp[pos-4];
			pos -= 4;
			posX-= 1;
			temp[pos] = '0';
			break;

		//move right	
		case 1:
			temp[pos] = temp[pos+1];
			pos += 1;
			posY+= 1;
			temp[pos] = '0';
			break;
		
		//move down
		case 2:
			temp[pos] = temp[pos+4];
			pos += 4;
			posX+= 1;
			temp[pos] = '0';
			break;

		//move left
		case 3:
			temp[pos] = temp[pos-1];
			pos -= 1;
			posY-= 1;
			temp[pos] = '0';
			break;	
		}
	return new Board(temp,posX,posY,this);
}
bool Board::isValid()
{
	return valid;
}

int misplaced(Board* a, Board* goal)
{
	int count = 0;
	for(int i = 0; i < MAX; i++)
		count += (a->values[i+SIDE] != goal->values[i+SIDE]);
	return count;
}
int manhatanDistance(Board* a, Board* goal)
{
	int count = 0;
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++) 
			for (int k = 0; k < 4; k++) 
				for (int l = 0; l < 4; l++) 
						count+= (a->values[(i+1)*SIDE+j] == goal->values[(k+1)*SIDE+l])* Abs(k-i)+Abs(l-j); 
	return count;
}	



char toBase16 (int a)
{
	char temp = '\0';
	
	temp += (a < 10) * (a + '0');
	temp += (a >= 10 && a < 36) * (a - 10 +  'A'); 
	temp += (a >= 36) * (a - 36 + 'a') ;

	return temp;
}

void strCpy(char * dest, char * src)
{
	for(int i = 0; i < MAX; i++)
		dest[i+SIDE]  = src[i+SIDE];
}


bool strComp::operator()(char * a, char * b) const 
{
	return (strcmp(a,b)>0);	
}

#endif
