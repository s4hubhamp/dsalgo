// A strongly connected component is a maximal subgraph where, for any pair of vertices u and v in the subgraph,
// there is a directed path from u to v and from v to u.
// strongly connected components are related to directed graphs, for undirected graphs we talk about connected components.

// Kosaraju algorithm for finding strongly connected components
// If we reverse the edges in a directed graph, All the vertices in a strongly connected subgraph are still reachable from one another
// Let's take for example, `A->B->C->A` if we reverse it's still strongly connected `A<-B<-C<-A`
// Step 1: (DFS Order): During the first DFS pass, we push vertices onto the stack in the order they finish. This order represents
//  the "most dependent" vertices being pushed last, meaning the vertices that "finish" later have all of their descendants explored first.
// Step 2: (Reversing the Graph): When you reverse the edges of the graph, the direction of the edges is flipped,
//  but the strong connectivity (the ability to reach each vertex from the other in both directions) is preserved.
// Step 3 (DFS on Reversed Graph): When we pop vertices from the stack in reverse finishing time order, and then run DFS
//  on the reversed graph, we effectively explore each SCC. A single DFS call starting from a vertex will explore all vertices in the SCC
//  it belongs to, because once a vertex is visited, all vertices that can reach it (in the reversed graph) are also part of the same SCC.

function dfs(adj, u, visited, stack) {
    if(visited [u]) return;

    visited[u] = true;
    for(let v of adj[u]) {
        dfs(adj, v, visited, stack);
    }
    stack.unshift(u);
}

function dfs_iter(adj, u, visited) {
    const connectedVertices = [];
    const st = [u];
    while(st.length) {
        u = st.shift();
        visited[u] = true;

        for (let v of adj[u]) {
            if(visited[v] === false) {
                st.unshift(v);
            }
        }

        connectedVertices.push(u);
    }

    return connectedVertices;
}

function Kosaraju(adj) {
    const stack = [];
    let visited = new Array(adj.length).fill(false);

    // sort all the vertices according to finishing time
    for(let u = 0; u < adj.length; u++) {
        dfs(adj, u, visited, stack);
    }

    // After reversing the edges the dfs will still be able to discover individual strongly connected components
    const rev = new Array(adj.length);
    for(let u = 0; u < adj.length; u++) {
        let edges = adj[u];
        for(let v of edges) {
            if(!rev[v]) {
                rev[v] = [];
            }

            rev[v].push(u);
        }
    }

    visited = new Array(rev.length).fill(false);
    for(let u = 0; u < rev.length; u++) {
        if(visited[u] === false) {
            console.log('component: ', dfs_iter(rev, u, visited));
        }
    }
}

const adj = [[1], [2], [0, 3], [4], [5, 7], [6], [4], []];
Kosaraju(adj);
