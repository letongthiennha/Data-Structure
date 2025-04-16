#include "ShortestPath.h"
#include <limits>
#include <random>
#include <raylib.h>
#include <chrono>
#include <thread>
#include <sstream>

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
        ShPPointer* newEdge = &edges.back();
        startNode->addOutgoingEdge(newEdge);
        endNode->addIncomingEdge(newEdge);
    }
}
ShPNode* ShortestPath::getNodeAtPosition(Vector2 mousePos) {
    for (auto& node : nodes) {
        float distance = Vector2Distance(mousePos, node.getPos());
        if (distance < ShPNode::getRadius()) {
            return &node;
        }
    }
    return nullptr;
}

void ShortestPath::adjustNodePositions() {
    const float k_rep = 10000.0f;
    const float k_collinear = 500.0f;
    const float k_edge_rep = 100.0f;
    const float minDistance = 50.0f;
    const float collinearThreshold = 1.0f;
    const float edgeRepulsionDistance = 30.0f;
    const float timeStep = 0.1f;
    const float damping = 0.5f;
    const int maxIterations = 500;

    for (int iter = 0; iter < maxIterations; ++iter) {
        for (auto& nodeC : nodes) {
            Vector2 force = { 0.0f, 0.0f };
            for (const auto& nodeD : nodes) {
                if (&nodeC == &nodeD) continue;
                Vector2 dir = { nodeC.getPos().x - nodeD.getPos().x, nodeC.getPos().y - nodeD.getPos().y };
                float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
                if (dist > 0.0f) {
                    float magnitude = k_rep / (dist * dist);
                    force.x += magnitude * (dir.x / dist);
                    force.y += magnitude * (dir.y / dist);
                }
            }
            for (size_t i = 0; i < nodes.size(); ++i) {
                for (size_t j = i + 1; j < nodes.size(); ++j) {
                    if (&nodes[i] == &nodeC || &nodes[j] == &nodeC) continue;
                    Vector2 posA = nodes[i].getPos();
                    Vector2 posB = nodes[j].getPos();
                    Vector2 posC = nodeC.getPos();
                    Vector2 AB = { posB.x - posA.x, posB.y - posA.y };
                    float AB_length = sqrt(AB.x * AB.x + AB.y * AB.y);
                    if (AB_length > 0.0f) {
                        Vector2 AC = { posC.x - posA.x, posC.y - posA.y };
                        float t = (AC.x * AB.x + AC.y * AB.y) / (AB_length * AB_length);
                        t = std::clamp(t, 0.0f, 1.0f);
                        Vector2 projection = { posA.x + t * AB.x, posA.y + t * AB.y };
                        Vector2 perp = { posC.x - projection.x, posC.y - projection.y };
                        float distance = sqrt(perp.x * perp.x + perp.y * perp.y);
                        if (distance < collinearThreshold && distance > 0.0f) {
                            float magnitude = k_collinear * (collinearThreshold - distance) / distance;
                            force.x += magnitude * perp.x;
                            force.y += magnitude * perp.y;
                        }
                    }
                }
            }
            for (const auto& edge : edges) {
                ShPNode* startNode = edge.getStartNode();
                ShPNode* endNode = edge.getEndNode();
                if (&nodeC == startNode || &nodeC == endNode) continue;
                Vector2 start = edge.getTailPos();
                Vector2 end = edge.getHeadPos();
                Vector2 nodePos = nodeC.getPos();
                Vector2 edgeDir = { end.x - start.x, end.y - start.y };
                float edgeLength = sqrt(edgeDir.x * edgeDir.x + edgeDir.y * edgeDir.y);
                if (edgeLength > 0.0f) {
                    Vector2 toNode = { nodePos.x - start.x, nodePos.y - start.y };
                    float t = (toNode.x * edgeDir.x + toNode.y * edgeDir.y) / (edgeLength * edgeLength);
                    t = std::clamp(t, 0.0f, 1.0f);
                    Vector2 projection = { start.x + t * edgeDir.x, start.y + t * edgeDir.y };
                    Vector2 perp = { nodePos.x - projection.x, nodePos.y - projection.y };
                    float distance = sqrt(perp.x * perp.x + perp.y * perp.y);
                    if (distance < edgeRepulsionDistance && distance > 0.0f) {
                        float magnitude = k_edge_rep * (edgeRepulsionDistance - distance) / distance;
                        force.x += magnitude * perp.x;
                        force.y += magnitude * perp.y;
                    }
                }
            }
            nodeC.m_pos.x += force.x * timeStep * damping;
            nodeC.m_pos.y += force.y * timeStep * damping;
            nodeC.m_pos.x = std::clamp(nodeC.m_pos.x, 50.0f, static_cast<float>(GetScreenWidth() - 50));
            nodeC.m_pos.y = std::clamp(nodeC.m_pos.y, 50.0f, static_cast<float>(GetScreenHeight() - 50));
        }
    }
}

void ShortestPath::renderGraph() {
    ClearBackground(RAYWHITE);
    for (auto& edge : edges) {
        edge.update();
        edge.render();
    }
    for (auto& node : nodes) {
        node.draw();
    }
}

void ShortestPath::clearGraph() {
    nodes.clear();
    edges.clear();
    pq = std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode>();
    processedEdges.clear();
    current = nullptr;
    edgeIndex = 0;
    lastCheckedEdge = nullptr;
    visitedNodes.clear();
    isRunning = false;
}

ShPNode* ShortestPath::getNodeById(int id) {
    for (auto& node : nodes) {
        if (node.getId() == id) {
            return &node;
        }
    }
    return nullptr;
}

void ShortestPath::createRandomGraph() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> nodeDist(6, 11);
    std::uniform_real_distribution<float> offsetDist(-100.0f, 200.0f);
    std::uniform_int_distribution<int> weightDist(1, 11);

    clearGraph();
    int numNodes = nodeDist(gen);
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());
    float xStep = (screenWidth - 100.0f) / (numNodes - 1);
    float yMid = screenHeight / 2.0f;

    for (int i = 0; i < numNodes; ++i) {
        float x = 50.0f + i * xStep;
        float y = yMid + offsetDist(gen);
        Vector2 pos = { x, std::clamp(y, 50.0f, screenHeight - 50.0f) };
        addNode(pos, i);
        adjustNodePositions();
    }

    for (int i = 0; i < numNodes - 1; ++i) {
        int weight = weightDist(gen);
        addEdge(i, i + 1, weight);
    }

    for (int i = 0; i < numNodes - 2; ++i) {
        float EdgeProbability = 0.8f;
        for (int j = i + 2; j < numNodes; ++j) {
            std::bernoulli_distribution EdgeDist(EdgeProbability);
            EdgeProbability /= 2.0f;
            if (EdgeDist(gen)) {
                int w = rand() % 11;
                while (!w) w = rand() % 11;
                addEdge(i, j, w);
            }
        }
    }
}

void ShortestPath::startDijkstra(int startId) {
    ShPNode* startNode = getNodeById(startId);
    if (!startNode) return;

    for (auto& node : nodes) {
        node.setDis(std::numeric_limits<int>::max());
        node.setPrev(nullptr);
        node.highlight(false);
        node.visited = false;
    }

    for (auto& edge : edges) {
        edge.setColor(BLACK);
    }

    startNode->setDis(0);
    startNode->highlight(true);

    pq = std::priority_queue<ShPNode*, std::vector<ShPNode*>, CompareNode>();
    pq.push(startNode);

    processedEdges.clear(); // Reset global processed edges
    isRunning = true;
    current = nullptr;
    edgeIndex = 0;
    lastCheckedEdge = nullptr;
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
    return lhs.r != rhs.r || lhs.g != rhs.g || lhs.b != rhs.b || lhs.a != rhs.a;
}

bool ShortestPath::stepDijkstra() {
    // If the algorithm is not running, terminate
    if (!isRunning) return false;

    // Case 1: No current node, select the next node from the priority queue
    if (current == nullptr) {
        while (!pq.empty()) {
            ShPNode* u = pq.top();
            pq.pop();
            if (!u->visited) {
                current = u;
                current->visited = true;
                current->highlight(true);
                edgeIndex = 0;
                isHighlightingEdge = true;
                currentHighlightedEdge = nullptr;
                currentStep = 1; // Highlights "u = vertex in Q with smallest dist[]"
                return true;
            }
        }
        // Priority queue is empty, algorithm is complete
        isRunning = false;
        currentStep = -1;
        return false;
    }

    // Case 2: Current node exists, process its edges step-by-step
    if (isHighlightingEdge) {
        // Combine outgoing and incoming edges for undirected graph
        const auto& outgoingEdges = current->getOutgoingEdges();
        const auto& incomingEdges = current->getIncomingEdges();
        std::vector<ShPPointer*> allEdges;
        allEdges.reserve(outgoingEdges.size() + incomingEdges.size());
        allEdges.insert(allEdges.end(), outgoingEdges.begin(), outgoingEdges.end());
        allEdges.insert(allEdges.end(), incomingEdges.begin(), incomingEdges.end());

        // Use a set to avoid processing the same edge multiple times
        std::unordered_set<ShPPointer*> uniqueEdges;
        for (auto& edge : allEdges) {
            if (uniqueEdges.find(edge) == uniqueEdges.end()) {
                uniqueEdges.insert(edge);
            }
        }

        // Process each unique edge
        while (edgeIndex < uniqueEdges.size()) {
            auto it = uniqueEdges.begin();
            std::advance(it, edgeIndex);
            ShPPointer* edge = *it;
            if (processedEdges.find(edge) == processedEdges.end()) {
                currentHighlightedEdge = edge;
                currentHighlightedEdge->setColor(ORANGE);
                isHighlightingEdge = false;
                currentStep = 5; // Highlights "for each neighbor v of u:"
                return true;
            }
            edgeIndex++;
        }
        // All edges processed, move to the next node
        current->highlight(false);
        current = nullptr;
        currentStep = 0; // Highlights "while Q is not empty:"
        return true;
    }
    else {
        if (currentHighlightedEdge != nullptr) {
            // Determine neighbor node (could be start or end node due to undirected graph)
            ShPNode* neighbor = (currentHighlightedEdge->getStartNode() == current) ?
                currentHighlightedEdge->getEndNode() : currentHighlightedEdge->getStartNode();
            int alt = current->getDis() + currentHighlightedEdge->getWeight();
            if (alt < neighbor->getDis()) {
                // Reset the color of the previous edge in the shortest path
                if (neighbor->getPrev() != nullptr) {
                    for (auto& edge : edges) {
                        if ((edge.getStartNode() == neighbor->getPrev() && edge.getEndNode() == neighbor) ||
                            (edge.getStartNode() == neighbor && edge.getEndNode() == neighbor->getPrev())) {
                            edge.setColor(BLACK);
                            break;
                        }
                    }
                }
                // Update neighbor's distance and predecessor
                neighbor->setDis(alt);
                neighbor->setPrev(current);
                currentHighlightedEdge->setColor(RED);
                pq.push(neighbor);
                currentStep = 8; // Highlights "if alt < dist[v]:"
            }
            else {
                currentHighlightedEdge->setColor(GRAY);
                currentStep = 7; // Highlights "alt = dist[u] + length(u, v)"
            }
            processedEdges.insert(currentHighlightedEdge);
            currentHighlightedEdge = nullptr;
            edgeIndex++;
            isHighlightingEdge = true;
            return true;
        }
    }
    return false;
}
void ShortestPath::saveState() {
    GraphState state;
    for (auto& node : nodes) {
        int prevId = node.getPrev() ? node.getPrev()->getId() : -1;
        state.nodeDistPrev.push_back({ node.getDis(), prevId });
        state.nodeVisited.push_back(node.visited);
    }
    for (auto& edge : edges) {
        state.edgeColors.push_back(edge.getColor());
    }
    state.currentStep = currentStep;
    states.push_back(state);
    currentStateIndex = states.size() - 1;
}

void ShortestPath::applyState(int index) {
    if (index < 0 || index >= states.size()) return;
    const GraphState& state = states[index];
    for (size_t i = 0; i < nodes.size(); ++i) {
        nodes[i].setDis(state.nodeDistPrev[i].first);
        int prevId = state.nodeDistPrev[i].second;
        nodes[i].setPrev(prevId == -1 ? nullptr : getNodeById(prevId));
        nodes[i].visited = state.nodeVisited[i];
        nodes[i].highlight(false); // Reset highlight
    }
    for (size_t i = 0; i < edges.size(); ++i) {
        edges[i].setColor(state.edgeColors[i]);
    }
    currentStep = state.currentStep;
}

void ShortestPath::nextState() {
    if (currentStateIndex < static_cast<int>(states.size()) - 1) {
        applyState(++currentStateIndex);
    }
}

void ShortestPath::prevState() {
    if (currentStateIndex > 0) {
        applyState(--currentStateIndex);
    }
}

std::string ShortestPath::getEdgeListAsString() const {
    std::string edgeList;
    for (const auto& edge : edges) {
        int startId = edge.getStartNode()->getId();
        int endId = edge.getEndNode()->getId();
        int weight = edge.getWeight();
        edgeList += std::to_string(startId) + " " + std::to_string(endId) + " " + std::to_string(weight) + "\n";
    }
    return edgeList;
}