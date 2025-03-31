
#include "ShortestPathScreen.h"
#include "raylib.h"
#include "tinyfiledialogs.h"
#include <sstream>
#include <random>
#include <fstream>
#include <set>  // For edit mode

ShortestPathScreen::ShortestPathScreen()
    : animating(false), timeSinceLastStep(0), delay(0.5f),
    inputMode(false), editMode(false),  // Initialize editMode
    inputTextBox({ 300, 150 }, { 600, 400 }, WHITE, BLACK, 1000),
    submitButton() {
    sp.createRandomGraph();
    ctrl = ShPController();

    submitButton.setText("Submit", 18);
    submitButton.setSize({ 120, 40 });
    submitButton.setPosition({ 660, 570 });
    submitButton.SetColor(GRAY, LIGHTGRAY, DARKGRAY);
}

void ShortestPathScreen::render() {
    if (inputMode || editMode) {
        DrawRectangle(250, 100, 700, 500, Fade(GRAY, 0.8f));
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
        if (animating) {
            timeSinceLastStep += GetFrameTime();
            if (timeSinceLastStep >= delay) {
                timeSinceLastStep = 0;
                if (!sp.stepDijkstra()) {
                    animating = false;
                }
            }
        }
        sp.renderGraph();
        ctrl.render();
    }
}

void ShortestPathScreen::update() {
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
                std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 50));

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
                animating = false;  // Stop any ongoing animation
                inputTextBox.clearContent();
            }
            else if (editMode) {
                std::string input = inputTextBox.getText();

                // Parse the input
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

                // Remove nodes not in newNodeIds
                auto it = sp.nodes.begin();
                while (it != sp.nodes.end()) {
                    if (newNodeIds.find(it->getId()) == newNodeIds.end()) {
                        it = sp.nodes.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                // Add new nodes
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> posDistX(50.0f, static_cast<float>(GetScreenWidth() - 50));
                std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 50));
                for (int id : newNodeIds) {
                    if (sp.getNodeById(id) == nullptr) {
                        Vector2 pos = { posDistX(gen), posDistY(gen) };
                        sp.addNode(pos, id);
                    }
                }

                // Clear edges
                sp.edges.clear();

                // Add new edges
                for (const auto& edge : newEdges) {
                    int startId, endId, weight;
                    std::tie(startId, endId, weight) = edge;
                    sp.addEdge(startId, endId, weight);
                }

                // Adjust node positions
                sp.adjustNodePositions();

                editMode = false;
                animating = false;  // Stop any ongoing animation
                inputTextBox.clearContent();
            }
        }
    }
    else {
        ctrl.update();

        if (ctrl.isRandomClicked()) {
            sp.clearGraph();
            sp.createRandomGraph();
            animating = false;
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

        // Load File button functionality
        if (ctrl.isLoadFileClicked()) {
            char const* lFilterPatterns[1] = { "*.txt" };
            char const* selectedFile = tinyfd_openFileDialog(
                "Select a TXT file",    
                "",                     // Default directory (empty for current dir)
                1,                      // Number of filter patterns
                lFilterPatterns,        // Filter for .txt files
                "TXT files",            // Filter description
                0                       
            );

            if (selectedFile) {  // If a file was selected
                std::ifstream infile(selectedFile);
                if (infile.is_open()) {
                    sp.clearGraph();

                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<float> posDistX(50.0f, static_cast<float>(GetScreenWidth() - 50));
                    std::uniform_real_distribution<float> posDistY(50.0f, static_cast<float>(GetScreenHeight() - 50));

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
                    animating = false;  // Stop any ongoing animation
                }
                else {
                    tinyfd_messageBox("Error", "Cannot open file", "ok", "error", 1);
                }
            }
            // If selectedFile is NULL (user canceled), do nothing
        }

        if (ctrl.isDijkstraClicked()) {
            int startId = ctrl.getStartVertex();
            sp.startDijkstra(startId);
            timeSinceLastStep = 0;
            animating = true;
        }
    }
}