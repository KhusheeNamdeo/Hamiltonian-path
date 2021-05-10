#include <stdio.h>
#include <string.h>

struct landmark {
	char name[20];
	int id;
	int visited;
};

struct landmark nodes[100];
int edges[100][100];
int numnodes;
struct landmark *path[100];
int nodesvisited = 0;

struct traversalstack {
	int stackpos;
	struct landmark *stack[100];
};

struct traversalstack stack;

void initializestack() {
	stack.stackpos = -1;
}

void push(struct landmark *node) {
	stack.stackpos++;
	stack.stack[stack.stackpos] = node;
}

void pop() {
	stack.stackpos--;
}

struct landmark* peek() {
	return stack.stack[stack.stackpos];
}

int isempty() {
	return (stack.stackpos == -1);
}

void displaystack() {
	int i;
	printf("       stack: ");
	for(i = 0; i <= stack.stackpos; i++)
		printf("%d ", stack.stack[i]->id);
	printf("\n");
}

void displaypath() {
	int i;
	printf("       path: ");
	for(i = 0; i < nodesvisited; i++)
		printf("%d ", path[i]->id);
	printf("\n");
}

int findtour(struct landmark *node) {
	int i, numneighbours;

	push(node);
	while(!isempty()) {
		node = peek();
		printf("testing at node %d\n", node->id);
		node->visited = 1;
		path[nodesvisited++] = node;
		displaystack(); displaypath();
		numneighbours = 0;
		for(i = 0; i < numnodes; i++) {
			if(i == node->id) continue;
			if(edges[node->id][nodes[i].id] == 1) {
				printf("    checking edge %d %d, visited %d numvisited %d\n", node->id, nodes[i].id,
					nodes[i].visited, nodesvisited);
				if(nodes[i].id == 0 && nodesvisited == numnodes) {
					printf("    completed tour\n");
					path[nodesvisited++] = &nodes[i];
					return 1;
				}
				if(nodes[i].visited == 0) {
					printf("    pushing %d\n", nodes[i].id);
					push(&nodes[i]);
					displaystack(); displaypath();
					numneighbours++;
				}
			}
		}

		if(numneighbours == 0) {
			pop();
			node->visited = 0;
			nodesvisited--;
			printf("    not found: leaving from node %d\n", node->id);
			displaystack(); displaypath();
			printf("         peek %d path %d\n", peek()->id, path[nodesvisited-1]->id);
			while(peek()->id == path[nodesvisited-1]->id) {
				node = peek();
				if(node->id == 0)
					return 0;
				printf("   also removing from path %d\n", node->id);
				pop();
				node->visited = 0;
				nodesvisited--;
				displaystack(); displaypath();
			}
		}
	}
}

void main() {
	int i, j;
	int id; char name[20];
	struct landmark *node;

	scanf("%d", &numnodes);
	for(i = 0; i < numnodes; i++) {
		scanf("%d %s", &id, name);
		nodes[id].id = id;
		strcpy(nodes[id].name, name);
		nodes[id].visited = 0;
	}
	for(i = 0; i < numnodes; i++)
		for(j = 0; j < numnodes; j++)
			edges[i][j] = 0;
	while(1) {
		scanf("%d %d", &i, &j);
		if(i == -1 && j == -1)
			break;
		edges[i][j] = edges[j][i] = 1;
	}

	initializestack();

	if(findtour(&nodes[0])) {
		printf("path found\n");
		for(i = 0; i < nodesvisited; i++)
			printf("   %d %s ->\n", path[i]->id, path[i]->name);
	}
	else {
		printf("no path exists\n");
	}
}
