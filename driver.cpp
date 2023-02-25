#ifndef _BASE_
#include "base.cpp"
#endif

#include <time.h>


#include "algorithms/dfs.cpp"
#include "algorithms/bfs.cpp"
#include "algorithms/iddfs.cpp"
#include "algorithms/greedy.cpp"
#include "algorithms/aStar.cpp"

int main(int argC, char* argV[])
{
	Board start;
	Board end;

	if(start.group() != end.group()) 
	{
		printf("it's not possible to reach target board!\n");
		return 0;
	}

	short op = 0;
		
	printf("dfs       : 1\n");
	printf("idfs      : 2\n");
	printf("bfs       : 3\n");
	printf("greedy    :\n");
	printf("missplaced: 4\n");
	printf("manhatan  : 5\n");
	printf("A*        :\n");
	printf("missplaced: 6\n");
	printf("manhatan  : 7\n");
	printf("\n");

	scanf("%hd",&op);
	clock_t time;
    time = clock();

    double timeTaken;

	switch(op)
	{
		case 1:
			DFS(start,end);
			break;
		case 2:
			IDDFS(start,end,30);
			break;
		case 3:
			BFS(start,end);
			break;
		case 4:
			greedy(start,end,&misplaced);
			break;
		case 5:
			greedy(start,end,&manhatanDistance);
			break;
		case 6:
			aStar(start,end,&misplaced);
			break;
		case 7:
			aStar(start,end,&manhatanDistance);
			break;

		default:
			printf("please select a valid operation!\n");
			break;
	}
    time = clock();
	timeTaken = ((double) (time)) / CLOCKS_PER_SEC;
	printf("-> %lf seconds taken\n",timeTaken);

	return 0;
}
