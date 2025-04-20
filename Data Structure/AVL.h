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
    CREATE,
    RANDOM,
    UPDATE,
    FIND
};

enum OperationPhase {
    PATH_FINDING,
    MODIFICATION
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
        std::vector<AVLNode*> path;
        float highlightTimer;
        size_t currentPathIndex;
        bool skipAnimations;
        OperationPhase phase;
        OperationInfo() : currNode(nullptr), newNode(nullptr), removeVal(0), findVal(0),
            isStarted(false), isComplete(false), isFound(false), highlightTimer(0.0f),
            currentPathIndex(0), skipAnimations(false), phase(PATH_FINDING) {
        }
    } currOperationInfo;

    // AVL Tree operations
    AVLNode* insertNode(AVLNode* node, int value, std::vector<AVLNode*>& path);
    AVLNode* balanceNode(AVLNode* node);
    AVLNode* findHelper(AVLNode* node, int value, std::vector<AVLNode*>& path);
    AVLNode* removeHelper(AVLNode* node, int value, std::vector<AVLNode*>& path);
    AVLNode* findMin(AVLNode* node);
    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    void findInsertionPath(AVLNode* node, int value, std::vector<AVLNode*>& path);
    void findRemovalPath(AVLNode* node, int value, std::vector<AVLNode*>& path);
    void findPath(AVLNode* node, int value, std::vector<AVLNode*>& path);

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
    AVLNode* find(int value);
    void remove(int value);

    void clearTree(AVLNode* node);
};