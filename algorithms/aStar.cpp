//complexity:
//
#ifndef _BASE_
#include "../base.cpp"
#endif

#ifndef _QUEUE_
#define _QUEUE_
#include <queue>
#endif

#ifndef _MAP_
#define _MAP_
#include <map>
#endif

#ifndef _NODE_
#define _NODE_

//a struct to wrap a board
typedef struct
{
	int depth;
	int val;
	Board* b;
}Node;

//a function to compare 2 nodes 
//it is done this way (a class and an operator overload)
//so that we can use this in the priority queue
class cmp
{
	public:
		bool operator() (Node a, Node b) 
		{
			bool temp = (a.val > b.val);
			//temp |= (a.val == b.val && a.depth > b.depth);
			return temp;
		}	
};
#endif


//A Start Search 
// only expands nodes it evaluates as the best
// to evaluate a node as best he takes an heuristic and adds the depth
// it then expands the lowest possible value (in the heap)
bool aStar(Board start, Board goal, int (*heuristic)(Board* smth,Board*goal))
{
	//we use a heap here so that the best node is allways on top
	priority_queue<Node,vector<Node>,cmp> Q;

	//we use a set with a custom cmp function(defined in base)
	//to save the boards that were already expanded
	map<char *,int,strComp> visited;	

	Q.push({0,heuristic(&start,&goal),&start});

	int dist=0;
	int boardsSeen = 0;
	
	Board* temp;
	while(!Q.empty())
	{
		//take the top out of the stack
		temp = Q.top().b;
		int depth = Q.top().depth;
		Q.pop();

					boardsSeen++;

		//is the board the goal ?
			if(temp->check(&goal)) 
			{
				//in A* the first answer is the best answer so we just return the result
				dist = depth;

				break;
			}

		for(int i = 0; i < 4; i++)
		{
			Board * smth = temp ->moveWhite(i);
			int stat = heuristic(smth,&goal)+ depth+1;


			// is the board valid ?
			if(!smth->isValid())
			{
				delete smth;
				continue;
			}

			//is the board the goal ?
			if(smth->check(&goal)) 
			{
				//in A* the first answer is the best answer so we just return the result
				dist = depth;
				Q.push({depth+1,stat,smth});
				break;
			}

			// was the board seen already ?
			char * strng = smth-> toString();
			auto it = visited.find(strng);
			if(it != visited.end())
			{
				if(visited[strng] > stat)
					visited.erase(it);
				
				else
				{
					delete smth;
					free(strng);
					continue;
				}

			}

		
		
			//expand temporary node in all 4 directions
			//calculate heuristic of those nodes
			//add depth and put them in heap
			Q.push({depth+1,stat,smth});

		}
		visited.insert({temp->toString(),depth});

	}
	
	printf("-> Solution Found\n -> Path to solution:\n");
	temp->printBoard();
	printf("STATS:\n");
	printf("-> %d seen boards\n-> %d distance from start to goal\n",boardsSeen,dist);
	return 1;


}

