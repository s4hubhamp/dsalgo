function BFS(graph, u) {
  const discovered = new Array(graph.edges.length).fill(false);
  const parents = new Array(graph.edges.length).fill(-1);

  const q = [];
  q.push(u);
  discovered[u] = true;
  parents[u] = -1;

  while (q.length) {
    u = q.shift();
    console.log(`Visited vertex: ${u}`);

    for (let v = 1; v < graph.edges[u].length; v++) {
      // if there is no edge then continue
      if (graph.edges[u][v] === 0) continue;

      // if neighbor is new then add it to the queue
      if (!discovered[v]) {
        q.push(v);
        discovered[v] = true;
        parents[v] = u;
      }
    }
  }

  return parents;
}

function shortestPath(graph, a, b) {
  const parents = BFS(graph, a);
  let destination = b;
  const path = [destination];

  while (destination !== a && parents[destination] !== -1) {
    path.push(parents[destination]);
    destination = parents[destination];
  }

  if (destination === a) {
    console.log(`Path from ${a} -> ${b}: `, path.reverse().join(' -> '));
  } else {
    console.log(`Path from ${a} -> ${b}: `, '--');
  }
}

// process edge from x to y
function process_edge(graph, x, y) {
  if (graph.isDirected) console.log(`One way route from ${x} --> ${y}`);
  else console.log(`Two way route from ${x} <--> ${y}`);
}

// breadth first traverse the graph and explores all the edges exactly once
function explore(graph, u) {
  const discovered = new Array(graph.edges.length).fill(false);
  const processed = new Array(graph.edges.length).fill(false);

  const q = [];
  q.push(u);
  discovered[u] = true;

  while (q.length) {
    u = q.shift();

    console.log(`Started exploring vertex: ${u}`);
    for (let v = 1; v < graph.edges[u].length; v++) {
      if (graph.edges[u][v] === 0) continue;

      let processTheDamnEdge = false;
      if (graph.isDirected) {
        processTheDamnEdge = true;
      }

      if (!discovered[v]) {
        processTheDamnEdge = true;
        discovered[v] = true;
        q.push(v);
      }

      if (!processed[v]) {
        processTheDamnEdge = true;
      }

      if (processTheDamnEdge) process_edge(graph, u, v);
    }

    processed[u] = true;
  }
}

// undirected graph
let graph = {
  isDirected: false,
  edges: [
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 1, 1, 0, 0, 0],
    [0, 1, 0, 1, 0, 0, 0, 0],
    [0, 1, 1, 0, 1, 1, 0, 0],
    [0, 1, 0, 1, 0, 1, 0, 0],
    [0, 0, 0, 1, 1, 0, 1, 1],
    [0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0],
  ],
};
shortestPath(graph, 1, 5);
shortestPath(graph, 3, 6);
shortestPath(graph, 6, 3);

// directed graph
// let graph = {
//   isDirected: true,
//   edges: [
//     [0, 0, 0, 0, 0, 0, 0, 0],
//     [0, 0, 1, 0, 0, 0, 0, 0],
//     [0, 0, 0, 1, 0, 0, 0, 0],
//     [0, 1, 0, 0, 1, 0, 0, 0],
//     [0, 1, 0, 0, 0, 1, 0, 0],
//     [0, 0, 0, 1, 0, 0, 1, 0],
//     [0, 0, 0, 0, 0, 0, 0, 0],
//     [0, 0, 0, 0, 0, 1, 0, 0],
//   ],
// };
// shortestPath(graph, 1, 5);
// shortestPath(graph, 3, 6);
// shortestPath(graph, 6, 3);
