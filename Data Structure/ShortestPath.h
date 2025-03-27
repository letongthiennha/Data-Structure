#pragma once
#include "raylib.h"
#include "ShPNode.h"
#include "ShPPointer.h"
#include <string>
#include <math.h>
#include <queue>
#include <vector>

// Comparison struct for priority queue
struct CompareNode {
    bool operator()(ShPNode* a, ShPNode* b) {
        return a->getDis() > b->getDis(); // Min-heap based on distance
    }
};

// ShortestPath class with new functions
class ShortestPath {
public:
    ShortestPath();
    ~ShortestPath();

    void addNode(Vector2 pos, int id);
    void addEdge(int startId, int endId, int weight);
    void renderGraph();
    void clearGraph();
    void highlightPath(int endId);

    // New functions
    void createRandomGraph(int numNodes, float edgeProbability, int maxWeight);
    void startDijkstra(int startId); // Initialize Dijkstra's algorithm
    bool stepDijkstra();             // Process one step with highlighting

private:
    std::vector<ShPNode> nodes;
    std::vector<ShPPointer> edges;
    std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode> pq; // Priority queue for Dijkstra
    bool isRunning = false; // Flag to track algorithm state

    ShPNode* getNodeById(int id);
};