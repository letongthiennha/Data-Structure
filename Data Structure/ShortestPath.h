//#pragma once
//#include "raylib.h"
//#include "ShPNode.h"
//#include "ShPPointer.h"
//#include <string>
//#include <math.h>
//#include <queue>
//#include <vector>
//#include <unordered_set>
//
//// Struct compare cho  priority queue
//struct CompareNode {
//    bool operator()(ShPNode* a, ShPNode* b) {
//        return a->getDis() > b->getDis(); // Min-heap based on distance

#pragma once
#include "raylib.h"
#include "ShPNode.h"
#include "ShPPointer.h"
#include <string>
#include <math.h>
#include <queue>
#include <vector>
#include <unordered_set>

struct CompareNode {
    bool operator()(ShPNode* a, ShPNode* b) {
        return a->getDis() > b->getDis();
    }
};

class ShortestPath {
public:
    ShortestPath();
    ~ShortestPath();

    void addNode(Vector2 pos, int id);
    void addEdge(int startId, int endId, int weight);
    void renderGraph();
    void clearGraph();
    void markShortestPathEdges();
    void adjustNodePositions();
    void createRandomGraph();
    void startDijkstra(int startId);
    bool stepDijkstra();
    ShPNode* getNodeById(int id);
private:
    std::vector<ShPNode> nodes;
    std::vector<ShPPointer> edges;
    std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode> pq;
    bool isRunning = false;

    ShPNode* current = nullptr;
    size_t edgeIndex = 0;
    ShPPointer* lastCheckedEdge = nullptr;
    std::unordered_set<int> visitedNodes;
};