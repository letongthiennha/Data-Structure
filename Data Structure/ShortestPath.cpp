#include "ShortestPath.h"
#include <limits>
#include <random>
#include <raylib.h>
#include <chrono>
#include <thread>

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
void ShortestPath::adjustNodePositions() {
    const float repulsionForce = 5000.0f; // Increased repulsion force constant
    const float minDistance = 50.0f; // Minimum distance between nodes
    const float dampingFactor = 0.85f; // Damping factor to control movement

    for (int i = 0; i < 200; ++i) { // Increased number of iterations
        for (auto& nodeA : nodes) {
            Vector2 force = { 0.0f, 0.0f };

            for (auto& nodeB : nodes) {
                if (&nodeA == &nodeB) continue;

                Vector2 dir = { nodeA.getPos().x - nodeB.getPos().x, nodeA.getPos().y - nodeB.getPos().y };
                float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

                if (dist < minDistance) {
                    float repulsion = repulsionForce / (dist * dist);
                    force.x += dir.x / dist * repulsion;
                    force.y += dir.y / dist * repulsion;
                }
            }

            // Apply damping factor to control the movement
            nodeA.m_pos.x += force.x * GetFrameTime() * dampingFactor;
            nodeA.m_pos.y += force.y * GetFrameTime() * dampingFactor;

            // Ensure nodes stay within screen bounds
            nodeA.m_pos.x = std::clamp(nodeA.m_pos.x, 50.0f, static_cast<float>(GetScreenWidth() - 50));
            nodeA.m_pos.y = std::clamp(nodeA.m_pos.y, 50.0f, static_cast<float>(GetScreenHeight() - 50));
        }
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

ShPNode* ShortestPath::getNodeById(int id) {
    for (auto& node : nodes) {
        if (node.getId() == id) {
            return &node;
        }
    }
    return nullptr;
}

/**
 * Create a random graph
 * @param numNodes Number of nodes to create
 * @param edgeProbability Probability of an edge between any two nodes (excluding chain)
 * @param maxWeight Maximum edge weight
 */
void ShortestPath::createRandomGraph(float edgeProbability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(50.0f, static_cast<float>(GetScreenWidth() - 50));  // X bounds with margin
    std::uniform_real_distribution<float> posY(50.0f, static_cast<float>(GetScreenHeight() - 50)); // Y bounds with margin
    std::bernoulli_distribution edgeDist(edgeProbability);

    clearGraph();

	int numNodes = rand() % 10;
	while (numNodes < 5) numNodes = rand() % 10;
    // Add nodes with random positions
    for (int i = 0; i < numNodes; ++i) {
        Vector2 pos = { posX(gen), posY(gen) };
        addNode(pos, i);
    }

    // Adjust node positions to avoid overlap
    adjustNodePositions();

    // Add chain edges to ensure connectivity (undirected)
    for (int i = 0; i < numNodes - 1; ++i) {
        int w = rand() % 11;
        while (!w) w = rand() % 11;
        addEdge(i, i + 1, w);
    }

    // Add random edges
    for (int i = 0; i < numNodes - 2; ++i) {
        for (int j = i + 2; j < numNodes; ++j) {
            if (edgeDist(gen)) {
                int w = rand() % 11;
                while (!w) w = rand() % 11;
                addEdge(i, j, w);
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

    // If current is null or all edges have been processed, get the next node
    if (current == nullptr || edgeIndex >= edges.size()) {
        if (!pq.empty()) {
            current = pq.top();
            pq.pop();

            // Skip if already visited
            if (visitedNodes.find(current->getId()) != visitedNodes.end()) {
                return true; // More steps available
            }

            current->visited = true;
            current->highlight(true); // Highlight the node being processed
            visitedNodes.insert(current->getId()); // Mark as visited
            edgeIndex = 0; // Reset edge index for new node
        }
        else {
            isRunning = false;
            return false; // Algorithm finished
        }
    }

    // Process one edge at a time
    while (edgeIndex < edges.size()) {
        auto& edge = edges[edgeIndex];
        if (edge.getStartNode() == current) {
            ShPNode* neighbor = edge.getEndNode();
            int newDist = current->getDis() + edge.getWeight();

            // Update neighbor's distance if shorter path found
            if (newDist < neighbor->getDis()) {
                neighbor->setDis(newDist);
                neighbor->setPrev(current);
                neighbor->highlight(true); // Highlight updated neighbor
                pq.push(neighbor);
            }

            // Highlight the edge being checked
            if (!edge.isVisited()) {
                if (neighbor->visited) {
                    edge.setColor(LIGHTGRAY); //Nếu không lấy tô xám
                }
                else {
                    edge.setColor(RED); //Nếu lấy tô đỏ 
                }
                edge.setVisited(true);
            }

            lastCheckedEdge = &edge; // Track the last checked edge
            edgeIndex++; // Move to next edge
            return true; // More steps available
        }
        edgeIndex++; // Skip edges not starting from current
    }

    // All edges for current node processed, reset current
    current = nullptr;
    return true; // More steps might be available
}

