#include <iostream>

using namespace std;

void DFS(int u, int A[][8], int n) {
  static int visited[8]{0};

  if (visited[u] == 0) {
    cout << u << ", " << flush;
    visited[u] = 1;
    for (int v = 1; v < n; v++) {
      if (A[u][v] == 1 && visited[v] == 0) {
        DFS(v, A, n);
      }
    }
  }
}

void DFS_WeaklyConnected(int A[][8], int n) {
  for (int v = 1; v < n; v++) {
    DFS(v, A, n);
  }
}

int main() {
  // int A[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
  //                {0, 0, 1, 1, 1, 0, 0, 0},
  //                {0, 1, 0, 1, 0, 0, 0, 0},
  //                {0, 1, 1, 0, 1, 1, 0, 0},
  //                {0, 1, 0, 1, 0, 1, 0, 0},
  //                {0, 0, 0, 1, 1, 0, 1, 1},
  //                {0, 0, 0, 0, 0, 1, 0, 0},
  //                {0, 0, 0, 0, 0, 1, 0, 0}};
  // cout << "Vertex: 4 -> " << flush;
  // DFS(4, A, 8);
  // cout << endl;

  // below directed graph is weakly connected, meaning not all vertices are
  // reachable from all other vertices
  int A[8][8] = {
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 1, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 0},
  };

  // If we choose 7 because all vertices are reachable from it
  int source = 7;
  cout << "Vertex: " << source << " -> " << flush;
  DFS(source, A, 8);
  cout << endl;

  // cout << "DFS_WeaklyConnected: " << flush;
  // DFS_WeaklyConnected(A, 8);
  // cout << endl;

  return 0;
}