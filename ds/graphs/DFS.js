function DFS(u, graph) {
  console.log(`DFS Starting Vertex: ${u}`);

  const visited = new Array(graph.edges.length).fill(false);
  const stk = [];
  stk.push(u);

  while (stk.length) {
    u = stk.pop();

    if (!visited[u]) {
      console.log(`Visited vertex: ${u}`);
      visited[u] = true;

      for (let v = 1; v < graph.edges.length; v++) {
        if (graph.edges[u][v] == 1 && !visited[v]) {
          stk.push(v);
        }
      }
    }
  }
}

// process edge from x to y
function process_edge(graph, x, y) {
  if (graph.isDirected) console.log(`One way route from ${x} --> ${y}`);
  else console.log(`Two way route from ${x} <--> ${y}`);
}

// depth first traverse the graph and explores all the possible edges that are reachable
// each edge is processed exactly once
function explore(u, graph) {
  console.log(`Explore Start Vertex: ${u}`);

  // processed will become true when we process all the edge going out from a vertex
  const processed = new Array(graph.edges.length).fill(false);
  // discovered is simply to track whether vertex has been added to the stack or not
  const discovered = new Array(graph.edges.length).fill(false);

  const stk = [];
  stk.push(u);
  discovered[u] = true;

  while (stk.length) {
    u = stk.pop();
    console.log(`Started processing vertex: ${u}`);
    processed[u] = true;

    for (let v = 1; v < graph.edges[u].length; v++) {
      // ignore if there is no edge
      if (graph.edges[u][v] === 0) continue;

      // whether to process the edge or not
      let processTheDamnEdge = false;

      // if the graph is directed,
      // neighbor might have been processed early but because of directed nature this edge can only be encountered once right now
      if (graph.isDirected) {
        processTheDamnEdge = true;
      }

      // if the neighbor is also new
      if (discovered[v] == false) {
        processTheDamnEdge = true;
        discovered[v] = true;
        stk.push(v);
      }

      // if neighbor is discovered but not processed, current edge is also new edge
      else if (processed[v] == false) {
        processTheDamnEdge = true;
      }

      if (processTheDamnEdge) process_edge(graph, u, v);
    }

    console.log(`Processed vertex: ${u}`);
  }
}

// // undirected graph
// let graph = {
//   isDirected: false,
//   edges: [
//     [0, 0, 0, 0, 0, 0, 0, 0],
//     [0, 0, 1, 1, 1, 0, 0, 0],
//     [0, 1, 0, 1, 0, 0, 0, 0],
//     [0, 1, 1, 0, 1, 1, 0, 0],
//     [0, 1, 0, 1, 0, 1, 0, 0],
//     [0, 0, 0, 1, 1, 0, 1, 1],
//     [0, 0, 0, 0, 0, 1, 0, 0],
//     [0, 0, 0, 0, 0, 1, 0, 0],
//   ],
// };

// directed graph
let graph = {
  isDirected: true,
  edges: [
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 1, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0],
  ],
};

// directed graph, 1->2, 2->3, 3->1
// let graph = {
//   isDirected: true,
//   edges: [
//     [0, 0, 0, 0],
//     [0, 0, 1, 0],
//     [0, 0, 0, 1],
//     [0, 1, 0, 0],
//   ],
// };

// undirected graph, 1-2, 2-3, 3-1
// let graph = {
//   isDirected: false,
//   edges: [
//     [0, 0, 0, 0],
//     [0, 0, 1, 1],
//     [0, 1, 0, 1],
//     [0, 1, 1, 0],
//   ],
// };

let u = 1;

DFS(u, graph);
explore(u, graph);
