#include "ShortestPathScreen.h"
#include "raylib.h"
#include "tinyfiledialogs.h"
#include "Font.h"
#include <sstream>
#include <random>
#include <fstream>
#include <set>

ShortestPathScreen::ShortestPathScreen()
    : animating(false), timeSinceLastStep(0), delay(0.8f),
    inputMode(false), editMode(false),
    inputTextBox({ 300, 150 }, { 600, 400 }, WHITE, BLACK, 1000),
    submitButton(),
    currentStep(-1) {  // Khởi tạo currentStep là -1
    ctrl = ShPController();

    submitButton.setText("Submit", 18);
    submitButton.setSize({ 120, 40 });
    submitButton.setPosition({ 660, 570 });
    submitButton.SetColor(GRAY, LIGHTGRAY, DARKGRAY);

    // Khởi tạo mã giả của thuật toán Dijkstra
    pseudoCodeLines = {
        "    while Q is not empty:",
        "        u = vertex in Q with smallest dist[]",
        "        remove u from Q",
        "        u.visited = true",
        "",
        "        for each neighbor v of u:",
        "            if v not visited:",
        "                alt = dist[u] + length(u, v)",
        "                if alt < dist[v]:",
        "                    dist[v] = alt",
        "                    prev[v] = u",
        "                    update Q with new dist[v]"
    };
}

void ShortestPathScreen::render() {
    if (inputMode || editMode) {
        DrawRectangle(250, 100, 700, 500, Fade(WHITE, 0.8f));
        inputTextBox.render();
        submitButton.drawRectangle();
        submitButton.drawText(BLACK);
        if (inputMode) {
            DrawText("Enter edge list (e.g., '0 1 5' per line)", 300, 120, 20, BLACK);
        }
        else if (editMode) {
            DrawText("Edit edge list (e.g., '0 1 5' per line)", 300, 120, 20, BLACK);
        }
    }
    else {
        if (animating && !isPaused) {
            timeSinceLastStep += GetFrameTime();
            if (timeSinceLastStep >= delay) {
                timeSinceLastStep = 0;
                if (sp.stepDijkstra()) {
                    sp.saveState(); 
                }
                else {
                    animating = false;
                }
            }
        }
        sp.renderGraph();
        ctrl.render();
        currentStep = sp.currentStep;
        // Vẽ hộp chứa mã giả ở góc dưới bên trái
        Vector2 pseudoCodePos = { 10, static_cast<float>(GetScreenHeight() - 300) };
        float width = 400;
        float height = 290;
        DrawRectangle(pseudoCodePos.x, pseudoCodePos.y, width, height, Fade(WHITE, 0.8f));

        // Vẽ từng dòng mã giả, làm nổi bật dòng tương ứng với currentStep
        float y = pseudoCodePos.y + 10;
        for (size_t i = 0; i < pseudoCodeLines.size(); ++i) {
            Color textColor = (currentStep == 8 && i >= 8 && i <= 11) || (static_cast<int>(i) == currentStep && currentStep != 8) ? RED : BLACK;
            DrawTextEx(arial, pseudoCodeLines[i].c_str(), { pseudoCodePos.x + 10, y}, 20, 1, textColor);
            y += 20;  // Mỗi dòng cách nhau 20 pixel
        }
        float statusY = pseudoCodePos.y - 30;
        if (!sp.currentStatus.empty()) {
            DrawTextEx(arial, sp.currentStatus.c_str(), { pseudoCodePos.x + 10, statusY }, 20, 1, BLUE);
        }
    }
}

void ShortestPathScreen::update() {
    delay = baseDelay / ctrl.getSpeed();
    if (inputMode || editMode) {
        inputTextBox.update();
        submitButton.update();

        if (submitButton.isClicked()) {
            if (inputMode) {
                std::string input = inputTextBox.getText();
                sp.clearGraph();

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> posDistX(50.0f, static_cast<float>(GetScreenWidth() - 50));
                std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 350));

                std::istringstream iss(input);
                std::string line;
                std::vector<int> nodeIds;

                while (std::getline(iss, line)) {
                    std::istringstream lineStream(line);
                    int startId, endId, weight;
                    if (lineStream >> startId >> endId >> weight) {
                        if (std::find(nodeIds.begin(), nodeIds.end(), startId) == nodeIds.end()) {
                            Vector2 pos = { posDistX(gen), posDistY(gen) };
                            sp.addNode(pos, startId);
                            nodeIds.push_back(startId);
                        }
                        if (std::find(nodeIds.begin(), nodeIds.end(), endId) == nodeIds.end()) {
                            Vector2 pos = { posDistX(gen), posDistY(gen) };
                            sp.addNode(pos, endId);
                            nodeIds.push_back(endId);
                        }
                        sp.addEdge(startId, endId, weight);
                    }
                }

                if (!nodeIds.empty()) {
                    sp.adjustNodePositions();
                }

                inputMode = false;
                animating = false;
                inputTextBox.clearContent();
            }
            else if (editMode) {
                std::string input = inputTextBox.getText();

                std::vector<std::tuple<int, int, int>> newEdges;
                std::set<int> newNodeIds;
                std::istringstream iss(input);
                std::string line;
                while (std::getline(iss, line)) {
                    std::istringstream lineStream(line);
                    int startId, endId, weight;
                    if (lineStream >> startId >> endId >> weight) {
                        newEdges.emplace_back(startId, endId, weight);
                        newNodeIds.insert(startId);
                        newNodeIds.insert(endId);
                    }
                }

                auto it = sp.nodes.begin();
                while (it != sp.nodes.end()) {
                    if (newNodeIds.find(it->getId()) == newNodeIds.end()) {
                        it = sp.nodes.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> posDistX(50.0f, static_cast<float>(GetScreenWidth() - 50));
                std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 350));
                for (int id : newNodeIds) {
                    if (sp.getNodeById(id) == nullptr) {
                        Vector2 pos = { posDistX(gen), posDistY(gen) };
                        sp.addNode(pos, id);
                    }
                }

                sp.edges.clear();

                for (const auto& edge : newEdges) {
                    int startId, endId, weight;
                    std::tie(startId, endId, weight) = edge;
                    sp.addEdge(startId, endId, weight);
                }

                sp.adjustNodePositions();

                editMode = false;
                animating = false;
                inputTextBox.clearContent();
            }
        }
    }
    else {
        ctrl.update();

        if (ctrl.isRandomClicked()) {
            for (int i = 0; i < 3; i++) {
                sp.clearGraph();
                sp.createRandomGraph();
                sp.clearGraph();
                sp.createRandomGraph();
                sp.clearGraph();
                sp.createRandomGraph();
            }
            animating = false;
        }

        if (ctrl.isPauseClicked()) {
            isPaused = !isPaused;
            if (isPaused) {
                ctrl.setPauseText("Resume");
            }
            else {
                ctrl.setPauseText("Pause");
            }
        }

        if (ctrl.isNextClicked() && animating) {
            if (!isPaused) {
                isPaused = true;
                ctrl.setPauseText("Resume");
            }
            sp.stepDijkstra();
        }

        if (ctrl.isPrevClicked() && animating) {
            if (!isPaused) {
                isPaused = true;
                ctrl.setPauseText("Resume");
            }
            sp.prevState();
        }

        if (ctrl.isInputClicked()) {
            inputMode = true;
            editMode = false;
            animating = false;
            inputTextBox.clearContent();
        }

        if (ctrl.isEditClicked()) {
            editMode = true;
            inputMode = false;
            animating = false;
            inputTextBox.setText(sp.getEdgeListAsString());
        }

        if (ctrl.isLoadFileClicked()) {
            char const* lFilterPatterns[1] = { "*.txt" };
            char const* selectedFile = tinyfd_openFileDialog(
                "Select a TXT file",
                "",
                1,
                lFilterPatterns,
                "TXT files",
                0
            );

            if (selectedFile) {
                for (int i = 0; i < 2; i++) {
                    std::ifstream infile(selectedFile);
                    if (infile.is_open()) {
                        sp.clearGraph();

                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_real_distribution<float> posDistX(50.0f, static_cast<float>(GetScreenWidth() - 50));
                        std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 350));

                        std::string line;
                        while (std::getline(infile, line)) {
                            std::istringstream iss(line);
                            int startId, endId, weight;
                            if (iss >> startId >> endId >> weight) {
                                if (sp.getNodeById(startId) == nullptr) {
                                    Vector2 pos = { posDistX(gen), posDistY(gen) };
                                    sp.addNode(pos, startId);
                                }
                                if (sp.getNodeById(endId) == nullptr) {
                                    Vector2 pos = { posDistX(gen), posDistY(gen) };
                                    sp.addNode(pos, endId);
                                }
                                sp.addEdge(startId, endId, weight);
                            }
                        }
                        infile.close();
                        sp.adjustNodePositions();
                        animating = false;
                    }
                    else {
                        tinyfd_messageBox("Error", "Cannot open file", "ok", "error", 1);
                    }
                }
            }
        }

        if (ctrl.isDijkstraClicked()) {
            std::string startVertexStr = ctrl.startVertexTextBox.getText();
            try {
                int startId = std::stoi(startVertexStr);
                if (sp.getNodeById(startId) != nullptr) {
                    sp.startDijkstra(startId);
                    timeSinceLastStep = 0;
                    animating = true;
                    currentStep = -1;  // Reset currentStep khi bắt đầu thuật toán
                }
                else {
                    tinyfd_messageBox("Error", "Start vertex not found in graph", "ok", "error", 1);
                }
            }
            catch (const std::invalid_argument& e) {
                tinyfd_messageBox("Error", "Invalid start vertex: enter a number", "ok", "error", 1);
            }
            catch (const std::out_of_range& e) {
                tinyfd_messageBox("Error", "Start vertex out of range", "ok", "error", 1);
            }
        }
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            draggingNode = sp.getNodeAtPosition(mousePos);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && draggingNode != nullptr) {
            Vector2 newPos = mousePos;
            newPos.x = std::clamp(newPos.x, 50.0f, static_cast<float>(GetScreenWidth() - 50));
            newPos.y = std::clamp(newPos.y, 50.0f, static_cast<float>(GetScreenHeight() - 50));
            draggingNode->setPos(newPos);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            draggingNode = nullptr;
        }
    }
}