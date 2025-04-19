#include "AVL.h"
#include "Motion.h"
#include "Pointer.h"
#include "Setting.h"
#include <algorithm> // For std::max
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

// AVL Tree operations
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
    x->currentAnimation = AVLAnimation::AVL_MOVING;
    y->currentAnimation = AVLAnimation::AVL_MOVING;
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);

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
    x->currentAnimation = AVLAnimation::AVL_MOVING;
    y->currentAnimation = AVLAnimation::AVL_MOVING;
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);

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

AVLNode* AVLTree::insertNode(AVLNode* node, int value) {
    if (!node) {
        AVLNode* newNode = new AVLNode(value);
        newNode->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
        newNode->opacity = 0.0f;
        return newNode;
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    return balanceNode(node);
}

void AVLTree::insert(int value) {
    root = insertNode(root, value);
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);
}

// Implement other operations like remove, search similarly

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
    std::function<void(AVLNode*)> updateNode = [&](AVLNode* node) {
        if (!node) return;
        node->updateAnimation(treeSpeed);
        updateNode(node->left);
        updateNode(node->right);
        };
    updateNode(root);
    updatePointers();
}

void AVLTree::render() {
    for (auto& p : pointers) {
        p.render();
    }
    std::function<void(AVLNode*)> renderNode = [&](AVLNode* node) {
        if (!node) return;
        node->render(node->position); // Pass current position
        renderNode(node->left);
        renderNode(node->right);
    };
    renderNode(root);

    // Render message log
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
    AVLOperation op{ type, value, secondValue };
    operationQueue.push(op);
}

void AVLTree::setSpeed(float speed) {
    treeSpeed = speed;
}