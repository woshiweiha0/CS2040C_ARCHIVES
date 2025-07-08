#include "graph.h"
#include "shortest_path.h"
#include "heap.hpp"

Path shortestPath(const Graph& g, int source, int dest) {
    int n = g.num_vertices();

    if (source < 0 || source >= n || dest < 0 || dest >= n) {
        throw std::runtime_error("Invalid source or destination vertex");
    }

    if (source == dest) { // Source is same as destination
        return Path(0, { source });
    }

    vector<int> distance(n, -1); // -1 means unreachable
    vector<int> prev(n, -1); // Stores the previous vertex on the shortest path

    Heap<GraphEdge> pq;
    pq.insert(GraphEdge(source, 0));
    distance[source] = 0;

    while (!pq.empty()) {
        GraphEdge current = pq.extractMax();  // Extract node with smallest distance (negated)
        int u = current.dest();
        int dist = -current.weight(); // Stored distance (negated)

        // Lazy deletion: skip this node if better path already found
        if (dist > distance[u]) {
            continue;
        }

        // Exit early when destination reached
        if (u == dest) {
            break;
        }

        // Explore all neighbours of current vertex
        for (GraphEdge edge : g.edges_from(u)) {
            int v = edge.dest();
            int weight = edge.weight();
            int new_dist = distance[u] + weight;

            // If v is unvisited or found shorter path to v
            if (distance[v] == -1 || new_dist < distance[v]) {
                distance[v] = new_dist;
                prev[v] = u;
                pq.insert(GraphEdge(v, -new_dist)); // Insert with negated distance to simulate min-heap
            }
        }
    }

    if (distance[dest] == -1) { // Destination was never reached
        throw std::runtime_error("No path found");
    }

    // Reconstruct path from destination to source
    vector<int> path;
    for (int v = dest; v != -1; v = prev[v]) {
        path.insert(path.begin(), v); // Prepend each vertex to the path
    }

    return Path(distance[dest], path);
}
