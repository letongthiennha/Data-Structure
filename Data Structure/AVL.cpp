#include "AVL.h"
#include "Motion.h"
#include "Pointer.h"
#include "Setting.h"
#include <algorithm>
#include <fstream>

AVLTree::AVLTree() {
    root = nullptr;
    isPaused = false;
    skipCurrentStep = false;
    treeSpeed = 1.0f;
    highlighted_line = 0;
    messageLog = "";
}

AVLTree::~AVLTree() {
    clearTree(root);
}

void AVLTree::clearTree(AVLNode* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalanceFactor(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    // Set animation for rotation
    if (!currOperationInfo.skipAnimations) {
        x->currentAnimation = AVLAnimation::AVL_MOVING;
        x->animationPhase = 0.0f;
        y->currentAnimation = AVLAnimation::AVL_MOVING;
        y->animationPhase = 0.0f;
        if (T2) {
            T2->currentAnimation = AVLAnimation::AVL_MOVING;
            T2->animationPhase = 0.0f;
        }
    }
    // Defer repositioning to update
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    // Set animation for rotation
    if (!currOperationInfo.skipAnimations) {
        x->currentAnimation = AVLAnimation::AVL_MOVING;
        x->animationPhase = 0.0f;
        y->currentAnimation = AVLAnimation::AVL_MOVING;
        y->animationPhase = 0.0f;
        if (T2) {
            T2->currentAnimation = AVLAnimation::AVL_MOVING;
            T2->animationPhase = 0.0f;
        }
    }
    // Defer repositioning to update
    return y;
}

AVLNode* AVLTree::balanceNode(AVLNode* node) {
    int bf = getBalanceFactor(node);
    if (bf > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

AVLNode* AVLTree::insertNode(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) {
        AVLNode* newNode = new AVLNode(value);
        if (!currOperationInfo.skipAnimations) {
            newNode->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
            newNode->opacity = 0.0f;
        }
        else {
            newNode->opacity = 1.0f;
        }
        path.push_back(newNode); // Include new node in path
        return newNode;
    }
    path.push_back(node); // Add current node to path
    if (value < node->value) {
        node->left = insertNode(node->left, value, path);
    }
    else if (value > node->value) {
        node->right = insertNode(node->right, value, path);
    }
    else {
        return node; // Duplicate values not allowed
    }
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    return balanceNode(node);
}

void AVLTree::insert(int value) {
    std::vector<AVLNode*> path;
    root = insertNode(root, value, path);
    currOperationInfo.path = path;
    currOperationInfo.currentPathIndex = 0;
    currOperationInfo.highlightTimer = 0.0f;
}

AVLNode* AVLTree::findHelper(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) return nullptr;
    path.push_back(node);
    if (value == node->value) return node;
    if (value < node->value) return findHelper(node->left, value, path);
    return findHelper(node->right, value, path);
}

AVLNode* AVLTree::find(int value) {
    std::vector<AVLNode*> path;
    AVLNode* result = findHelper(root, value, path);
    currOperationInfo.path = path;
    currOperationInfo.currentPathIndex = 0;
    currOperationInfo.highlightTimer = 0.0f;
    return result;
}

AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node->left) node = node->left;
    return node;
}

AVLNode* AVLTree::removeHelper(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) return nullptr;
    path.push_back(node);
    if (value < node->value) {
        node->left = removeHelper(node->left, value, path);
    }
    else if (value > node->value) {
        node->right = removeHelper(node->right, value, path);
    }
    else {
        if (!node->left) {
            AVLNode* temp = node->right;
            if (!currOperationInfo.skipAnimations) {
                node->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
                node->opacity = 1.0f; // Fade out
                node->animationPhase = 0.0f;
            }
            delete node;
            return temp;
        }
        else if (!node->right) {
            AVLNode* temp = node->left;
            if (!currOperationInfo.skipAnimations) {
                node->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
                node->opacity = 1.0f; // Fade out
                node->animationPhase = 0.0f;
            }
            delete node;
            return temp;
        }
        AVLNode* temp = findMin(node->right);
        node->value = temp->value;
        node->right = removeHelper(node->right, temp->value, path);
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    return balanceNode(node);
}

void AVLTree::remove(int value) {
    std::vector<AVLNode*> path;
    root = removeHelper(root, value, path);
    currOperationInfo.path = path;
    currOperationInfo.currentPathIndex = 0;
    currOperationInfo.highlightTimer = 0.0f;
}

void AVLTree::repositionNodes(AVLNode* node, float x, float y, float spacing) {
    if (!node) return;
    node->destination = { x, y };
    if (node->currentAnimation != AVLAnimation::AVL_MOVING) {
        node->position = node->destination;
    }
    repositionNodes(node->left, x - spacing, y + 100, spacing / 2);
    repositionNodes(node->right, x + spacing, y + 100, spacing / 2);
}

void AVLTree::updatePointers() {
    pointers.clear();
    std::function<void(AVLNode*)> update = [&](AVLNode* node) {
        if (!node) return;
        if (node->left) {
            Pointer p;
            p.setTailPos(node->position);
            p.setHeadPos(node->left->position);
            pointers.push_back(p);
            update(node->left);
        }
        if (node->right) {
            Pointer p;
            p.setTailPos(node->position);
            p.setHeadPos(node->right->position);
            pointers.push_back(p);
            update(node->right);
        }
        };
    update(root);
}

void AVLTree::update() {
    if (isPaused) return;

    // Only clear highlights for nodes not in the current path
    std::function<void(AVLNode*)> clearHighlights = [&](AVLNode* node) {
        if (!node) return;
        bool inPath = false;
        for (auto* pathNode : currOperationInfo.path) {
            if (pathNode == node) {
                inPath = true;
                break;
            }
        }
        if (!inPath) {
            node->isHighlighted = false;
        }
        clearHighlights(node->left);
        clearHighlights(node->right);
        };
    clearHighlights(root);

    // Handle highlighting sequence
    bool isAnimating = false;
    if (!currOperationInfo.path.empty() && currOperationInfo.currentPathIndex < currOperationInfo.path.size()) {
        isAnimating = true;
        currOperationInfo.highlightTimer += GetFrameTime();
        float interval = 0.5f / treeSpeed;
        if (currOperationInfo.highlightTimer >= interval) {
            if (currOperationInfo.currentPathIndex > 0) {
                currOperationInfo.path[currOperationInfo.currentPathIndex - 1]->isHighlighted = false;
            }
            AVLNode* currentNode = currOperationInfo.path[currOperationInfo.currentPathIndex];
            currentNode->isHighlighted = true;
            currOperationInfo.currentPathIndex++;
            currOperationInfo.highlightTimer = 0.0f;
        }
    }
    else if (!currOperationInfo.path.empty()) {
        // Operation complete
        if (currentOperation.type == FIND) {
            AVLNode* lastNode = currOperationInfo.path.back();
            if (lastNode->value == currentOperation.value) {
                lastNode->isHighlighted = true; // Keep final node highlighted for FIND
            }
        }
        currOperationInfo.path.clear();
        currOperationInfo.currentPathIndex = 0;
        currOperationInfo.highlightTimer = 0.0f;
        // Reposition nodes after animations
        repositionNodes(root, GetScreenWidth() / 2, 100, 200);
    }

    // Process operation queue only when no animations are active
    if (!operationQueue.empty() && !isAnimating) {
        currentOperation = operationQueue.front();
        operationQueue.pop();
        currOperationInfo.skipAnimations = (currentOperation.type == RANDOM);
        switch (currentOperation.type) {
        case INSERT:
            insert(currentOperation.value);
            messageLog = std::to_string(currentOperation.value) + " Inserted";
            break;
        case REMOVE:
            remove(currentOperation.value);
            messageLog = std::to_string(currentOperation.value) + " Removed";
            break;
        case FIND:
        {
            AVLNode* found = find(currentOperation.value);
            messageLog = std::to_string(currentOperation.value) + (found ? " Found" : " Not found");
        }
        break;
        case RANDOM:
            randomCreate(currentOperation.value);
            messageLog = std::to_string(currentOperation.value) + " Random nodes created.";
            break;
        case UPDATE:
        {
            AVLNode* node = find(currentOperation.value);
            int oldValue = node ? node->value : currentOperation.value;
            if (node) {
                node->value = currentOperation.secondValue;
                messageLog = "Updated from " + std::to_string(oldValue) + " to " + std::to_string(currentOperation.secondValue);
            }
            else {
                messageLog = "Cannot find " + std::to_string(oldValue);
            }
        }
        break;
        }
    }

    // Update node animations
    std::function<void(AVLNode*)> updateNode = [&](AVLNode* node) {
        if (!node) return;
        node->updateAnimation(treeSpeed);
        updateNode(node->left);
        updateNode(node->right);
        };
    updateNode(root);
    updatePointers();
}

void AVLTree::randomCreate(int amount) {
    clearTree(root);
    root = nullptr;
    std::vector<int> vals;
    for (int i = 0; i < amount; ++i) {
        int val = GetRandomValue(0, 100);
        while (find(val) != nullptr) {
            val = GetRandomValue(0, 100);
        }
        vals.push_back(val);
    }
    currOperationInfo.skipAnimations = true;
    create(vals);
}

void AVLTree::render() {
    for (auto& p : pointers) {
        p.render();
    }
    std::function<void(AVLNode*)> renderNode = [&](AVLNode* node) {
        if (!node) return;
        node->render(node->position);
        renderNode(node->left);
        renderNode(node->right);
        };
    renderNode(root);

    if (!messageLog.empty()) {
        DrawText(messageLog.c_str(), GetScreenWidth() / 2 - MeasureText(messageLog.c_str(), 30) / 2, 20, 30, RED);
    }
}

void AVLTree::setStop(bool stop) {
    isPaused = stop;
}

bool AVLTree::isStop() const {
    return isPaused;
}

void AVLTree::setSkip() {
    skipCurrentStep = true;
    currOperationInfo.path.clear();
    currOperationInfo.currentPathIndex = 0;
    currOperationInfo.highlightTimer = 0.0f;
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);
}

void AVLTree::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        messageLog = "Failed to open file.";
        return;
    }
    std::vector<int> vals;
    int val;
    while (file >> val) {
        vals.push_back(val);
    }
    file.close();
    create(vals);
}

void AVLTree::create(const std::vector<int>& vals) {
    clearTree(root);
    root = nullptr;
    for (int val : vals) {
        insert(val);
    }
}

void AVLTree::storeOperation(AVLOperationType type, int value, int secondValue) {
    AVLOperation op;
    op.type = type;
    op.value = value;
    op.secondValue = secondValue;
    operationQueue.push(op);
}

void AVLTree::setSpeed(float speed) {
    treeSpeed = speed;
}

float AVLTree::getSpeed() const {
    return treeSpeed;
}