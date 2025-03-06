///
/// Prims algorithm to find minimum spanning trees.
/// Always select the minimum edge but the edge should be connected to already selected vertices
///

function findSmallestEdge(cost, trackedVertices) {
  let smallestCostEdge = [0, 0];
  let smallestCost = +Infinity;

  for (let i = 1; i < cost.length; i++) {
    for (let j = 1; j < cost.length; j++) {
      if (cost[i][j] == 0) continue;

      // if both vertices at the edge are already used for a path then we can't
      // consider it because they will create a cycle
      if (trackedVertices.size) {
        if (!trackedVertices.has(i) && !trackedVertices.has(j)) {
          continue;
        }

        if (trackedVertices.has(i) && trackedVertices.has(j)) {
          continue;
        }
      }

      if (cost[i][j] < smallestCost) {
        smallestCost = cost[i][j];
        smallestCostEdge[0] = i;
        smallestCostEdge[1] = j;
      }
    }
  }

  return { smallestCost, smallestCostEdge };
}

function PrimsMST(cost) {
  let totalCost = 0;

  // tracks the vertices that are taken as part of spanning tree
  let trackedVertices = new Set();

  let nvertices = cost.length - 1;
  let k = 1;
  while (k < nvertices) {
    let { smallestCost, smallestCostEdge } = findSmallestEdge(cost, trackedVertices);

    console.log(smallestCostEdge[0], '-', smallestCostEdge[1]);

    totalCost += smallestCost;
    trackedVertices.add(smallestCostEdge[0]);
    trackedVertices.add(smallestCostEdge[1]);

    k++;
  }

  console.log('Total cost of spanning tree: ', totalCost);
}

// weighted undirected graph
let cost = [
  [0, 0, 0, 0, 0, 0, 0, 0],
  [0, 0, 25, 0, 0, 0, 5, 0],
  [0, 25, 0, 12, 0, 0, 0, 10],
  [0, 0, 12, 0, 8, 0, 0, 0],
  [0, 0, 0, 8, 0, 16, 0, 14],
  [0, 0, 0, 0, 16, 0, 20, 18],
  [0, 5, 0, 0, 0, 20, 0, 0],
  [0, 0, 10, 0, 14, 18, 0, 0],
];

PrimsMST(cost);
