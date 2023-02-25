//complexity:
//	n -> maximum depth allowed
//	temporal O( 4 * n )
//	spatial  O( 4 ^ n )
//
#ifndef _BASE_
#include "../base.cpp"
#endif

#ifndef _QUEUE_
#define _QUEUE_
#include <queue>
#endif

#ifndef _SET_
#define _SET_
#include <set>
#endif

//Breath first Search
//develops a level of the tree at a time
//will allways lead to the best solution
//uses to much space since it has to save everything that was already seen 
bool BFS(Board start, Board goal)
{
	//set to save the visited 
	//makes use of strComp from base
	set<char*,strComp> visited;

	//uses a queue 
	//nodes of same deapth will be grouped toghether 
	//and organized with the least depth atthe front
	queue<pair<Board*,int>> Q;
	Q.push({&start,0});

		
	int dist=0;
	int boardsSeen = 0;
	
	Board* temp;
	while(!Q.empty())
	{
		//take the top out of the stack
		temp = Q.front().first;
		int depth = Q.front().second;
		Q.pop();
	
		boardsSeen++;

		// is the board valid ?
		// was the board seen already ?
		char * strng = temp-> toString();
		if(!temp->isValid() || visited.find(strng) != visited.end())
		{
			delete temp;
			free(strng);
			continue;
		}
		visited.insert(strng);


		//is the board the goal ?
		if(temp->check(&goal)) 
		{
			dist = depth;
			break;
		}	
		
		
		//expand temporary node in all 4 directions
		for(int i = 0; i < 4; i++)
			Q.push({temp->moveWhite(i), depth+1});

	}

	printf("-> Solution Found\n -> Path to solution:\n");
	temp->printBoard();
	printf("STATS:\n");
	printf("-> %d seen boards\n-> %d distance from start to goal\n",boardsSeen,dist);

	return 1;

}

