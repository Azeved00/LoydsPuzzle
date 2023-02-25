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


#ifndef _NODE_
#define _NODE_
//struct to wrap a board
typedef struct
{
	int depth;
	int val;
	Board* b;
}Node;

//function to compare 2 nodes
class cmp
{
	public:
		bool operator() (Node a, Node b) 
		{
			bool temp = (a.val > b.val);
			temp |= (a.val == b.val && a.depth > b.depth);
			return temp;
		}	
};
#endif

//Greedy Search with heuristic
//here the heuristic in question is an argument of the greedy search 
//main idea is simply to allways develop the best possible node
bool greedy(Board start, Board goal,int (*heuristic)(Board* smth,Board*goal))
{
	
	//priority queue so taht the best node is always on top
	priority_queue<Node,vector<Node>,cmp> Q;
	Q.push({0,heuristic(&start,&goal),&start});

	//set to hold the visited
	//makes use of strComp from base
	set<char*, strComp> visited;

	int dist=INF;
	int boardsSeen = 0;
	
	Board* temp;
	while(!Q.empty())
	{
		//take the top out of the stack
		temp = Q.top().b;
		int depth = Q.top().depth;
		Q.pop();
	
		boardsSeen++;


		// is the board being seen worse than the corrent solution?
		// is the board valid ?
		// was the board seen already ?
		char * strng = temp-> toString();
		if(dist<=depth||!temp->isValid() || visited.find(strng) != visited.end())
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
		//and calculate its heuristics
		for(int i = 0; i < 4; i++)
		{
			Board * smth = temp ->moveWhite(i);
			int stat = heuristic(smth,&goal);
			Q.push({depth+1,stat,smth});

		}
	}

	printf("-> Solution Found\n -> Path to solution:\n");
	temp->printBoard();
	printf("STATS:\n");
	printf("-> %d seen boards\n-> %d distance from start to goal\n",boardsSeen,dist);
	return 1;

}

