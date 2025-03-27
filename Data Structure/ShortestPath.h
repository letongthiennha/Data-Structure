#pragma once
#include "raylib.h"
#include "ShPNode.h"
#include "ShPPointer.h"
#include <string>
#include <math.h>
#include <queue>
#include <vector>
#include <unordered_set>

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

    void adjustNodePositions();
    void createRandomGraph(float edgeProbability);
    void startDijkstra(int startId); // Initialize Dijkstra's algorithm
    bool stepDijkstra();             // Process one step with highlighting
    

private:
    std::vector<ShPNode> nodes;
    std::vector<ShPPointer> edges;
    std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode> pq; // Priority queue for Dijkstra
    bool isRunning = false; // Flag to track algorithm state

    ShPNode* getNodeById(int id);

    // New member variables for edge processing
    ShPNode* current = nullptr;
    size_t edgeIndex = 0;
    ShPPointer* lastCheckedEdge = nullptr; // Track the last edge being checked
    std::unordered_set<int> visitedNodes;  // Track visited nodes
};