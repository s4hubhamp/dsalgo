// This file implements Kruskals algorithm for finding minimum spanning trees with union-find data structure
// Kruskals algorithm selects smallest edge from graph each time such that the vertices at the edge don't form cycles

// find the root index for vertex
function find(set_union, vertex) {
    if(set_union[vertex] < 0) {
        return vertex;
    }

    return find(set_union, set_union[vertex]);
}

function union(set_union, s1, s2) {
    // find the root for both s1 and s2
    let s1_root = find(set_union, s1);
    let s2_root = find(set_union, s2);

    console.assert(set_union[s1_root] < 0 && set_union[s2_root] < 0);

    // we will make root with highest number of nodes as parent
    if(Math.abs(set_union[s1_root]) > Math.abs(set_union[s2_root])) {
        // reset total nodes
        set_union[s1_root] = set_union[s1_root] + set_union[s2_root];
        // make s1 as the parent
        set_union[s2_root] = s1_root;
    } else {
        // reset total nodes
        set_union[s2_root] = set_union[s1_root] + set_union[s2_root];
        // make s2 as parent
        set_union[s1_root] = s2_root;
    }
}

function same_component(set_union, s1, s2)
{
    return find(set_union, s1) === find(set_union, s2);
}

function Kruskals(graph) {
    // number of vertices
    let N = graph.length - 1;
    let cost = 0;
    let sorted_edges = [];
    for(let u = 1; u < graph.length; u++) {
        for(let v = 1; v < graph[u].length; v++) {
            if(graph[u][v]) {
                sorted_edges.push({
                    u, v, w: graph[u][v],
                });
            }
        }
    }

    // sort by eedge weight
    sorted_edges.sort((a, b) => b.w - a.w);


    // (-) indicates that the vertex is parent of itself(or a root of tree) and (1) indicates that tree has 1 element.
    let set_union = new Array(N + 1).fill(-1);

    let i = 0;
    // pick the smallest edge as long as the edge does not form a cycle
    while(i < N - 1) {
        let {u, v, w} = sorted_edges.pop();
        
        // to detect if an edge forms a cycle we need to know if the vertices u and v are part of same component
        if(same_component(set_union, u, v)) {
            // just ignore this edge
            continue;
        }

        // now the edge is between two non connected components, thus we will unite two components
        union(set_union, u, v);
        // we can consider union operation as a spanning tree edge selection operation
        cost += w;
        i++;
    }

    return cost;
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

console.assert(Kruskals(cost) === 71);
