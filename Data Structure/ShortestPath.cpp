#include "ShortestPath.h"
#include <limits>
#include <random>
#include <raylib.h>

ShortestPath::ShortestPath() {}
ShortestPath::~ShortestPath() {}

void ShortestPath::addNode(Vector2 pos, int id) {
    nodes.emplace_back(pos, id);
}

void ShortestPath::addEdge(int startId, int endId, int weight) {
    ShPNode* startNode = getNodeById(startId);
    ShPNode* endNode = getNodeById(endId);
    if (startNode && endNode) {
        edges.emplace_back(startNode, endNode, weight);
    }
}

void ShortestPath::renderGraph() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (auto& edge : edges) {
        edge.update();
        edge.render();
    }

    for (auto& node : nodes) {
        node.draw();
    }

    EndDrawing();
}

void ShortestPath::clearGraph() {
    nodes.clear();
    edges.clear();
}

void ShortestPath::highlightPath(int endId) {
    ShPNode* current = getNodeById(endId);
    if (!current) return;

    while (current != nullptr) {
        current->highlight(true);
        ShPNode* prev = current->getPrev();
        if (prev) {
            for (auto& edge : edges) {
                if (edge.getStartNode() == prev && edge.getEndNode() == current) {
                    edge.setColor(RED);
                }
            }
        }
        current = prev;
    }
}

ShPNode* ShortestPath::getNodeById(int id) {
    for (auto& node : nodes) {
        if (node.getId() == id) {
            return &node;
        }
    }
    return nullptr;
}

/**
 * Tạo đồ thị ngẫu nhiên
 * @param numNodes Number of nodes to create
 * @param edgeProbability Probability of an edge between any two nodes (excluding chain)
 * @param minWeight Minimum edge weight
 * @param maxWeight Maximum edge weight
 */
void ShortestPath::createRandomGraph(int numNodes, float edgeProbability, int maxWeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(50, GetScreenWidth() - 50);  // X bounds with margin
    std::uniform_real_distribution<float> posY(50, GetScreenHeight() - 50); // Y bounds with margin
    std::bernoulli_distribution edgeDist(edgeProbability);

    clearGraph();

    // Add nodes with random positions
    for (int i = 0; i < numNodes; ++i) {
        Vector2 pos = { posX(gen), posY(gen) };
        addNode(pos, i);
    }

    // Add chain edges to ensure connectivity (undirected)
    for (int i = 0; i < numNodes - 1; ++i) {
        int w = rand() % maxWeight;
        addEdge(i, i + 1, w);
        addEdge(i + 1, i, w); // Add reverse edge for undirected graph
    }

    // Add random edges
    for (int i = 0; i < numNodes - 2; ++i) {
        for (int j = i + 2; j < numNodes; ++j) {
            if (edgeDist(gen)) {
                int w = rand() % maxWeight;
                addEdge(i, j, w);
                addEdge(j, i, w); // Add reverse edge for undirected graph
            }
        }
    }
}

/**
 * Initialize Dijkstra's algorithm
 * @param startId ID of the starting node
 */
void ShortestPath::startDijkstra(int startId) {
    ShPNode* startNode = getNodeById(startId);
    if (!startNode) return;

    // Reset all nodes
    for (auto& node : nodes) {
        node.setDis(std::numeric_limits<int>::max());
        node.setPrev(nullptr);
        node.highlight(false);
        node.visited = false;
    }

    startNode->setDis(0);
    pq = std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode>(); // Reset priority queue
    pq.push(startNode);
    isRunning = true;
}

/**
 * Process one step of Dijkstra's algorithm with highlighting
 * @return true if there are more steps, false if finished
 */
bool ShortestPath::stepDijkstra() {
    if (!isRunning || pq.empty()) {
        isRunning = false;
        return false;
    }

    ShPNode* current = pq.top();
    pq.pop();

    if (current->visited) return true; // Skip if already processed

    current->visited = true;
    current->highlight(true); // Highlight the node being processed

    // Update neighbors
    for (auto& edge : edges) {
        if (edge.getStartNode() == current) {
            ShPNode* neighbor = edge.getEndNode();
            int newDist = current->getDis() + edge.getWeight();
            if (newDist < neighbor->getDis()) {
                neighbor->setDis(newDist);
                neighbor->setPrev(current);
                pq.push(neighbor);
            }
        }
    }

    return true; // More steps available
}