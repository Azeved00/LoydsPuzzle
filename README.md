g++ version 11.2.0
linux distro :arch linux x86_64
kernel       : 5.16.15-arch1-1


para compilar: g++ -o driver driver.cpp

para executar: ./driver

input do programa:
	2 tabuleiros, o numero das tiles separado por um espaco 
	numero do algoritmo a executar:
		1 - DFS
		2 - BFS
		3 - IDDFS
		4 - Greedy: missplaced
		5 - Greedy: manhatan distance
		6 - A*: missplaced
		7 - A*: manhatan distance


exemplo de input :
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15
2

output: caminho do 1o tabuleiro ate ao 2o tabuleiro, bem como estatisticas do algoritmo( tempo, no de tabuleiros desenvolvidos e profundidade da solucao encontrada )
