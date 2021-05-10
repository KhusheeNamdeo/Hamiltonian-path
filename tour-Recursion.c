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

int findtour(struct landmark *node) {
	int i;

	printf("testing at node %d\n", node->id);
	node->visited = 1;
	path[nodesvisited++] = node;
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
				printf("    going in for findtour %d\n", nodes[i].id);
				if(findtour(&nodes[i]) == 1)
					return 1;
			}
		}
	}
	node->visited = 0;
	nodesvisited--;
	printf("    not found: leaving from node %d\n", node->id);
	return 0;
}

void main() {
	int i, j;
	int id; char name[20];

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

	if(findtour(&nodes[0])) {
		printf("path found\n");
		for(i = 0; i < nodesvisited; i++)
			printf("   %d %s ->\n", path[i]->id, path[i]->name);
	}
	else {
		printf("no path exists\n");
	}
}
