function isCyclicUtil(graph, v, visited, isVertexOnCurrentPath) {
  visited[v] = true;
  isVertexOnCurrentPath[v] = true;

  for (let neighbor = 1; neighbor < graph.edges[v].length; neighbor++) {
    // check if there is an edge.
    if (graph.edges[v][neighbor] === 0) continue;

    // if neighbor has been already visited
    if (visited[neighbor] === true && isVertexOnCurrentPath[neighbor]) {
      return true;
    }

    if (isCyclicUtil(graph, neighbor, visited, isVertexOnCurrentPath)) {
      return true;
    }
  }

  // after we check a path we need to remove the vertex from current path
  isVertexOnCurrentPath[v] = false;
  return false;
}

function isCyclic(graph) {
  // this also tells that if all paths going out from a vertex are checked
  const visited = new Array(graph.edges.length).fill(false);
  const isVertexOnCurrentPath = new Array(graph.edges.length).fill(false);

  // we need to check all the vertices explicitely because of possible disconnected components and
  // some vertices are also unreachable from some other vertices
  for (let u = 1; u < graph.edges.length; u++) {
    if (isCyclicUtil(graph, u, visited, isVertexOnCurrentPath)) return true;
  }

  return false;
}

// const graph = {
//   isDirected: true,
//   edges: [
//     [0, 0, 0, 0],
//     [0, 0, 1, 0],
//     [0, 0, 0, 1],
//     [0, 1, 0, 0],
//   ],
// };

// const graph = {
//   isDirected: true,
//   edges: [
//     [0, 0, 0, 0],
//     [0, 0, 0, 1],
//     [0, 0, 0, 1],
//     [0, 0, 0, 0],
//   ],
// };

const graph = {
  isDirected: true,
  edges: [
    [0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0],
    [0, 0, 0, 1, 1, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0],
  ],
};

// const graph = {
//   isDirected: true,
//   edges: [
//     [0, 0, 0, 0, 0, 0],
//     [0, 0, 1, 0, 0, 0],
//     [0, 0, 0, 1, 1, 0],
//     [0, 0, 0, 0, 0, 0],
//     [0, 0, 0, 0, 0, 0],
//     [0, 0, 0, 0, 1, 0],
//   ],
// };

console.log(isCyclic(graph));
