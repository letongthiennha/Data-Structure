#pragma once
#include "AVLNode.h"
#include "Pointer.h"
#include <queue>
#include <vector>
#include <string>
#include <functional>

enum AVLOperationType {
    NONE,
    INSERT,
    REMOVE,
    SEARCH,
    CREATE,
    RANDOM,
	UPDATE,
	FIND
};

struct AVLOperation {
    AVLOperationType type;
    int value;
    int secondValue; // For operations needing two parameters
};

class AVLTree {
private:
    AVLNode* root;
    std::queue<AVLOperation> operationQueue;
    AVLOperation currentOperation;
    bool isPaused;
    float treeSpeed;
    int highlighted_line;
    std::string messageLog;
    std::vector<Pointer> pointers;
    bool skipCurrentStep;

    // Operation information
    struct OperationInfo {
        AVLNode* currNode;
        AVLNode* newNode;
        int removeVal;
        int findVal;
        bool isStarted;
        bool isComplete;
        bool isFound;
        OperationInfo() : currNode(nullptr), newNode(nullptr), removeVal(0), findVal(0),
            isStarted(false), isComplete(false), isFound(false) {
        }
    } currOperationInfo;

    // AVL Tree operations
    AVLNode* insertNode(AVLNode* node, int value);
    AVLNode* balanceNode(AVLNode* node);
    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);

    void updatePointers();
    void repositionNodes(AVLNode* node, float x, float y, float spacing);

public:
    AVLTree();
    ~AVLTree();

    void storeOperation(AVLOperationType type, int value, int secondValue = 0);
    void setSpeed(float speed);
    float getSpeed() const;
    void setStop(bool stop);
    bool isStop() const;
    void setSkip();
    void update();
    void render();
    void insert(int value);
    void create(const std::vector<int>& vals);
    void randomCreate(int amount);
    void LoadFromFile(const std::string& path);

    void clearTree(AVLNode* node);
};