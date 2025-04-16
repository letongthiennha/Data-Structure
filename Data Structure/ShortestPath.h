#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "raylib.h"
#include "raymath.h"
#include "ShPNode.h"
#include "ShPPointer.h"
#include <string>
#include <vector>
#include <queue>
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
    void adjustNodePositions();
    void createRandomGraph();
    void saveState();
    void prevState();
    void nextState();
    void applyState(int index);
    void startDijkstra(int startId);
    bool stepDijkstra();
    ShPNode* getNodeById(int id);
    ShPNode* getNodeAtPosition(Vector2 mousePos);
    std::string getEdgeListAsString() const;
    std::vector<ShPNode> nodes;
    std::vector<ShPPointer> edges;
    int currentStep = -1;
    std::string currentStatus;

private:
    std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode> pq;
    std::unordered_set<ShPPointer*> processedEdges; // Global edge tracker
    bool isRunning = false;

    ShPNode* current = nullptr;
    size_t edgeIndex = 0;
    ShPPointer* lastCheckedEdge = nullptr;
    std::unordered_set<int> visitedNodes;
    bool isHighlightingEdge = false;        
    ShPPointer* currentHighlightedEdge = nullptr;
    struct GraphState {
        std::vector<std::pair<int, int>> nodeDistPrev; // {dis, prevId}
        std::vector<bool> nodeVisited;
        std::vector<Color> edgeColors;
        int currentStep;
    };
    std::vector<GraphState> states;
    int currentStateIndex = -1;
};
#endif