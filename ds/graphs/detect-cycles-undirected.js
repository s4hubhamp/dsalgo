function isCyclicUtil(graph, v, parent, visited) {
  visited[v] = true;

  for (let neighbor = 1; neighbor < graph.edges[v].length; neighbor++) {
    // check if there is an edge
    if (graph.edges[v][neighbor] === 0) continue;

    // if the edge exists but it's the parent node which called
    if (neighbor === parent) continue;

    // if neighbor has been already visited
    if (visited[neighbor] === true) {
      return true;
    }

    if (isCyclicUtil(graph, neighbor, v, visited)) {
      return true;
    }
  }

  return false;
}

function isCyclic(graph) {
  // graph can have disconnected components hence we will check all the vertices explicitely
  const visited = new Array(graph.edges.length).fill(false);

  for (let u = 1; u < graph.edges.length; u++) {
    if (!visited[u]) {
      if (isCyclicUtil(graph, u, -1, visited)) return true;
    }
  }

  return false;
}

const graph = {
  isDirected: false,
  edges: [
    [0, 0, 0, 0],
    [0, 0, 1, 1],
    [0, 1, 0, 1],
    [0, 1, 1, 0],
  ],
};

console.log(isCyclic(graph));
