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

//global variable to count boards
int boardsSeen =0;

//Iterative Depening Depth first Search
//take what is first on the stack and expand it
//put the new nodes in the stack again
//repeat function until there are no nodes in the stack
bool iddfsAux(Board start, Board goal, int maxDepth)
{
	stack<pair<Board*,int>> S;
	S.push({&start,0});

	int dist = INF;
	bool found = 0;

	Board* temp;
	while(!S.empty())
	{
		//take the top out of the stack
		temp = S.top().first;
		int depth = S.top().second;
		S.pop();
	
		boardsSeen++;

		// is the board valid ?
		// was the board seen already ?
		// was depth limit exceded ?
		if(!temp->isValid() || temp->check(temp->parent) || depth > maxDepth)
		{
			//delete the object (free the memory) and continue execution
			delete temp;
			continue;
		}

		//is the board the goal ?
		if(temp->check(&goal)) 
		{
			dist = depth;
			found = 1;
			break;
		}	
		
		
		//expand temporary node in all 4 directions
		for(int i = 0; i < 4; i++)
			S.push({temp->moveWhite(i), depth+1});
	
	}

	if(found)
	{
		printf("-> Solution Found\n -> Path to solution:\n");
		temp->printBoard();
		printf("STATS:\n");
		printf("-> %d seen boards\n-> %d distance from start to goal\n",boardsSeen,dist);
	}

	return found;
}

void IDDFS(Board start, Board goal, int maxDepth)
{
	bool flag = 0;
	for(int i = 1;i < maxDepth && !flag;i++)
		flag = iddfsAux(start,goal,i);
	
}

