// Function to perform DFS and topological sorting
function topologicalSortUtil(v, adj, visited, st) {
    
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all adjacent vertices
    for (let i of adj[v]) {
        if (!visited[i]) {
            topologicalSortUtil(i, adj, visited, st);
        }
    }

    // Push current vertex to stack which stores the result
    st.push(v);
}

// Function to perform Topological Sort
function topologicalSort(adj) {
    const V = adj.length;
    
    // Stack to store the result
    const st = [];
    const visited = Array(V).fill(false);

    //* Note that it does not matter whether you start from vertex which has zero incoming edges or not.

    // Call the recursive helper function to store
    // Topological Sort starting from all vertices one by one
    for (let i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, adj, visited, st);
        }
    }
    
    // Append contents of stack
    return st.reverse();
}

// Graph represented as an adjacency list
//const adj = [[1], [2], [], [1, 2]];
const adj = [[], [0, 2], [], [1, 2]];

const ans = topologicalSort(adj);
console.log(ans.join(" "));
