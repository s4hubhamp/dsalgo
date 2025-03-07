function dijkstra(graph, start) {
    // workings:
    // once we discover a shortest path(let's say start -> X) we add it inside the array, so that
    // we can check for all the neighbours of X if there is shortest path that goes through X.
    // In languages that have inbuilt heaps we can use those, but here we are using plain array and functions `pop_min` and `push_min`
    let array = [];
    let min_distances = new Array(graph.length).fill(+Infinity);
    // from start to start distance will be 0
    min_distances[start] = 0;

    // At start we will mark the direct connected edges as the shortest distances
    graph[start].forEach((distance, vertex) => {
        if(distance) {
            min_distances[vertex] = distance;
            array.push({distance, vertex});
        }
    })

    // loop until we finish processing all entries inside the array
    while (array.length) {
        const {distance: distance_to_vertex_from_start, vertex} = pop_min(array);

        // iterate over all the connected vertices of `vertex` and check
        // if the path to those vertices that goes through `vertex` is the shortest one
        graph[vertex].forEach((distance_from_vertex_to_neighbour, neighbour) => {
            // if there is no edge
            if(distance_from_vertex_to_neighbour === 0) return;

            let current_distance_to_neighbour_from_start = min_distances[neighbour];
            let distance_to_neighbour_through_vertex = distance_to_vertex_from_start + distance_from_vertex_to_neighbour;
            if (distance_to_neighbour_through_vertex < current_distance_to_neighbour_from_start) {
                min_distances[neighbour] = distance_to_neighbour_through_vertex;
                // since we discovered a new shortest distance to neighbour. we will add this to array
                push_min(array, neighbour, distance_to_neighbour_through_vertex);
            }
        })
    }

    return min_distances;
}

// removes the closest present vertex from start
function pop_min(array) {
    let min_index = 0;
    let min_distance = array[min_index].distance;
    array.forEach(({distance}, i) => {
        if(min_distance > distance) {
            min_index = i;
        }
    })

    return array.splice(min_index, 1)[0];
}

// when we discover a new shortest path for some neighbour we use this function to add it to array.
// this checks if we already have entry for neighbour and if it is it will replace that entry
function push_min(array, neighbour_vertex, new_shorter_distance_from_start) {
    let index = array.findIndex(el => el.vertex === neighbour_vertex);
    if (index > -1) {
        array[index].distance = new_shorter_distance_from_start;
    } else {
        array.push({distance: new_shorter_distance_from_start, vertex: neighbour_vertex});
    }
}

// undirected
const graph = [
    [0, 4, 4, 0, 0, 0],
    [4, 0, 2, 0, 0, 0],
    [4, 2, 0, 3, 1, 6],
    [0, 0, 3, 0, 0, 2],
    [0, 0, 1, 0, 0, 3],
    [0, 0, 6, 2, 3, 0],
];

const start = 0;
const min_distances = dijkstra(graph, 0);
console.log(`minimum distances from vertex: ${start} to all other vertices: ${min_distances}`);
