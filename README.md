# GraphTheory

# Student
Filipe Ferreira Figueredo Soriano Pinto

# Algorithms
1.Prim  
2.Dijkstra  
3.Kruskal  
4.Kosaraju  
5.Floyd-Warshall

# Chosen algorithm
Floyd-Warshall

How to execute?
```
make floyd_warshall  
./floyd_warshall.bin -h
```
This will show the following instructions:
```
Help:  
-h: mostra o help  
-o <arquivo>: redireciona a saida para o 'arquivo'  
-f <arquivo>: indica o 'arquivo que contem o grafo de entrada  
-i: para especificar o vertice o qual as distancias devem se basear
```
If you don't specify a vertex then the algorithm will print the distance from all vertices to all vertices  
If you specify a vertex i then the program will show only the distance from i to all vertices  
Example:
 ```
1: (1, 0) (2, -1) (3, -1) (4, -1) (5, -1) (6, -1) (7, -1) (8, -1) (9, -1) (10, 155) (11, -1) (12, -1) (13, 94) (14, -3) (15, -1) (16, -1) (17, -1) (18, -1) (19, -1) (20, -1) 
 ```  
At first you have vertex i and between parentheses (vertex u, distance)  
If there is no path between two vertices the distance printed will be -1  
If there is a negative cycle then the program will only print this:
```
This graph has a negative cycle
```
