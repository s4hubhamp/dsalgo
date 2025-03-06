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

function kasaraju(adj) {
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
kasaraju(adj);
