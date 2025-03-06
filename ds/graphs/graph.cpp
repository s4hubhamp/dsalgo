#include <iostream>
#include <queue>

using namespace std;

#define MAX_VERTICES 1000

typedef struct edgenode {
  int y;
  int weight;
  struct edgenode* next;
} edgenode;

typedef struct {
  edgenode* edges[MAX_VERTICES + 1]; /* adjacency info */
  int degree[MAX_VERTICES + 1];      /* outdegree of each vertex */
  int nvertices;                     /* number of vertices in the graph */
  int nedges;                        /* number of edges in the graph */
  bool directed;                     /* is the graph directed? */
} graph;

void initialize_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);
int* BFS(graph* g, int start);
void find_path(int start, int end, int* parents);

void process_vertex_early(int x) {}
void process_vertex_late(int x) {}
//* process edge from x to y
void process_edge(int x, int y, int* parent) {
  printf("processing edge %d -> %d\n", x, y);
}

void initialize_graph(graph* g, bool directed) {
  int i; /* counter */
  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;

  for (i = 1; i <= MAX_VERTICES; i++) g->degree[i] = 0;
  for (i = 1; i <= MAX_VERTICES; i++) g->edges[i] = nullptr;
}

void insert_edge(graph* g, int x, int y, bool directed) {
  edgenode* p = (edgenode*)malloc(sizeof(edgenode));

  p->weight = 0;
  p->y = y;
  // insert at head
  p->next = (edgenode*)g->edges[x];
  g->edges[x] = p;
  g->degree[x]++;

  if (directed == false) {
    insert_edge(g, y, x, true);
  } else {
    g->nedges++;
  }
}

void print_graph(graph* g) {
  int i;
  edgenode* p;

  for (i = 1; i <= g->nvertices; i++) {
    cout << "vertex " << i << ": ";
    p = g->edges[i];
    while (p) {
      cout << " " << p->y;
      p = (edgenode*)p->next;
    }
    cout << "\n";
  }
}

int* BFS(graph* g, int start) {
  bool processed[MAX_VERTICES + 1];  /* which vertices have been processed */
  bool discovered[MAX_VERTICES + 1]; /* which vertices have been found */
  int* parents = (int*)malloc(sizeof(int) * (MAX_VERTICES + 1));

  for (int i = 1; i <= g->nvertices; i++) {
    processed[i] = discovered[i] = false;
    parents[i] = -1;
  }

  queue<int> q;
  int current_vertex;
  int y;
  edgenode* p;

  discovered[start] = true;
  q.push(start);

  while (q.size()) {
    current_vertex = q.front();
    process_vertex_early(current_vertex);
    processed[current_vertex] = true;
    p = g->edges[current_vertex];

    while (p != nullptr) {
      y = p->y;
      if (processed[y] == false || g->directed) {
        process_edge(current_vertex, y, parents);
      }

      if (discovered[y] == false) {
        q.push(y);
        discovered[y] = true;
        parents[y] = current_vertex;
      }

      p = p->next;
    }

    q.pop();
    process_vertex_late(current_vertex);
  }

  return parents;
}

void find_path(int start, int end, int* parents) {
  if ((start == end) || (end == -1)) {
    printf("\n%d\n", start);
  } else {
    find_path(start, parents[end], parents);
    printf(" %d", end);
  }
}

int* DFS(graph* g, int start) {
  bool processed[MAX_VERTICES + 1];  /* which vertices have been processed */
  bool discovered[MAX_VERTICES + 1]; /* which vertices have been found */
  int* parents = (int*)malloc(sizeof(int) * (MAX_VERTICES + 1));

  stack<int> stk;

  stk.emplace(start);
  discovered[start] = true;

  int current_vertex;
  int y;
  edgenode* p;

  while (!stk.empty()) {
    current_vertex = stk.top();

    process_vertex_early(current_vertex);
    processed[current_vertex] = true;
    p = g->edges[current_vertex];

    while (p != nullptr) {
      y = p->y;
      if (processed[y] == false || g->directed) {
        process_edge(current_vertex, y, parents);
      }

      if (discovered[y] == false) {
        stk.emplace(y);
        discovered[y] = true;
        parents[y] = current_vertex;
      }

      p = p->next;
    }

    stk.pop();
    process_vertex_late(current_vertex);
  }

  return parents;
}

int main() {
  graph g;
  bool directed = false;

  initialize_graph(&g, directed);
  g.nvertices = 5;
  g.nedges = 7;
  insert_edge(&g, 1, 2, directed);
  insert_edge(&g, 1, 5, directed);
  insert_edge(&g, 2, 3, directed);
  insert_edge(&g, 2, 4, directed);
  insert_edge(&g, 2, 5, directed);
  insert_edge(&g, 4, 3, directed);
  insert_edge(&g, 4, 5, directed);

  // print_graph(&g);

  // int* parents = BFS(&g, 1);
  // for (int i = 1; i <= g.nvertices; i++) {
  //   printf("vertex: %d parent: %d\n", i, parents[i]);
  // }
  // find_path(1, 5, parents);
  // find_path(1, 2, parents);
  // find_path(1, 4, parents);

  DFS(&g, 1);

  return 0;
}