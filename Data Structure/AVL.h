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
        std::vector<AVLNode*> path;
        size_t currentPathIndex;
        float highlightTimer;
        bool skipAnimations;
        OperationPhase phase;
        OperationInfo() : currentPathIndex(0), highlightTimer(0.0f), skipAnimations(false), phase(PATH_FINDING) {}
    } currOperationInfo;

    // AVL Tree operations
    AVLNode* insertNode(AVLNode* node, int value, std::vector<AVLNode*>* path = nullptr);
    AVLNode* balanceNode(AVLNode* node);
    AVLNode* findHelper(AVLNode* node, int value, std::vector<AVLNode*>* path = nullptr);
    AVLNode* removeHelper(AVLNode* node, int value, std::vector<AVLNode*>* path = nullptr);
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