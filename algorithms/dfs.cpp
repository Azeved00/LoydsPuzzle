//complexity:
//	n -> maximum depth allowed
//	temporal O( 4 * n )
//	spatial  O( 4 ^ n )
//
#ifndef _BASE_
#include "../base.cpp"
#endif

#ifndef _STACK_
#define _STACK_
#include <stack>
#endif

//Depth first Search
//take what is first on the stack and expand it
//put the new nodes in the stack again
//repeat function until  a solution is found
bool DFS(Board start, Board goal)
{

	stack<pair<Board*,int>> S;
	S.push({&start,0});

	int dist = INF;
	int boardsSeen = 0;
	
	Board* temp;
	while(!S.empty())
	{
		//take the top out of the stack
		temp = S.top().first;
		int depth = S.top().second;
		S.pop();
	
		boardsSeen++;

		// if depth limit was exceeded
		// is the board valid ?
		// was the board seen already ?
		if(depth > 20 || !temp->isValid() || temp->check(temp->parent))
		{
			delete temp;
			continue;
		}

		// is the board the goal ?
		if(temp->check(&goal)) 
		{
			dist = depth;
			break;
		}	
		
		
		//expand temporary node in all 4 directions
		for(int i = 0; i < 4; i++)
			S.push({temp->moveWhite(i), depth+1});
	
	}

	printf("-> Solution Found\n -> Path to solution:\n");
	temp->printBoard();
	printf("STATS:\n");
	printf("-> %d seen boards\n-> %d distance from start to goal\n",boardsSeen,dist);
	return 1;

}

