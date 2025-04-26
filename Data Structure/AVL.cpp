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

    // Khởi tạo pseudocode cho insert
    insertPseudocode = {
        "1. If node is null:",
        "2.   Create new node with value",
        "3. Else if value < node.value:",
        "4.   node.left = insert(node.left, value)",
        "5. Else if value > node.value:",
        "6.   node.right = insert(node.right, value)",
        "7. Update height of node",
        "8. Balance node"
    };

    // Khởi tạo pseudocode cho find
    findPseudocode = {
        "1. If node is null:",
        "2.   Return null",
        "3. If value == node.value:",
        "4.   Return node",
        "5. If value < node.value:",
        "6.   Return find(node.left, value)",
        "7. Else:",
        "8.   Return find(node.right, value)"
    };

    // Khởi tạo pseudocode cho remove
    removePseudocode = {
        "1. If node is null:",
        "2.   Return null",
        "3. If value < node.value:",
        "4.   node.left = remove(node.left, value)",
        "5. Else if value > node.value:",
        "6.   node.right = remove(node.right, value)",
        "7. Else:",
        "8.   If node has no left child:",
        "9.     Return node.right",
        "10.  If node has no right child:",
        "11.    Return node.left",
        "12.  Else:",
        "13.    Find min node in right subtree",
        "14.    node.value = min.value",
        "15.    node.right = remove(node.right, min.value)",
        "16. Update height of node",
        "17. Balance node"
    };
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

    if (!currOperationInfo.skipAnimations) {
        x->currentAnimation = AVLAnimation::AVL_MOVING;
        x->animationPhase = 0.0f;
        x->opacity = 1.0f; // Đảm bảo opacity = 1
        y->currentAnimation = AVLAnimation::AVL_MOVING;
        y->animationPhase = 0.0f;
        y->opacity = 1.0f; // Đảm bảo opacity = 1
        if (T2) {
            T2->currentAnimation = AVLAnimation::AVL_MOVING;
            T2->animationPhase = 0.0f;
            T2->opacity = 1.0f; // Đảm bảo opacity = 1
        }
    }
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    if (!currOperationInfo.skipAnimations) {
        x->currentAnimation = AVLAnimation::AVL_MOVING;
        x->animationPhase = 0.0f;
        x->opacity = 1.0f; // Đảm bảo opacity = 1
        y->currentAnimation = AVLAnimation::AVL_MOVING;
        y->animationPhase = 0.0f;
        y->opacity = 1.0f; // Đảm bảo opacity = 1
        if (T2) {
            T2->currentAnimation = AVLAnimation::AVL_MOVING;
            T2->animationPhase = 0.0f;
            T2->opacity = 1.0f; // Đảm bảo opacity = 1
        }
    }
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


void AVLTree::insert(int value) {
    // Handled via operation queue in update()
}

AVLNode* AVLTree::insertNode(AVLNode* node, int value, std::vector<AVLNode*>* path) {
    if (!node) {
        currOperationInfo.modificationHighlightLines.push_back(1); // If node is null
        AVLNode* newNode = new AVLNode(value);
        currOperationInfo.modificationHighlightLines.push_back(2); // Create new node
        if (!currOperationInfo.skipAnimations) {
            newNode->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
            newNode->opacity = 0.0f;
        }
        else {
            newNode->opacity = 1.0f;
        }
        if (path) path->push_back(newNode);
        return newNode;
    }
    if (path) path->push_back(node);
    if (value < node->value) {
        currOperationInfo.modificationHighlightLines.push_back(3); // value < node.value
        node->left = insertNode(node->left, value, path);
        currOperationInfo.modificationHighlightLines.push_back(4); // node.left = insert
    }
    else if (value > node->value) {
        currOperationInfo.modificationHighlightLines.push_back(5); // value > node.value
        node->right = insertNode(node->right, value, path);
        currOperationInfo.modificationHighlightLines.push_back(6); // node.right = insert
    }
    else {
        return node;
    }
    currOperationInfo.modificationHighlightLines.push_back(7); // Update height
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    currOperationInfo.modificationHighlightLines.push_back(8); // Balance node
    return balanceNode(node);
}

AVLNode* AVLTree::findHelper(AVLNode* node, int value, std::vector<AVLNode*>* path) {
    if (!node) {
        currOperationInfo.modificationHighlightLines.push_back(1); // If node is null
        currOperationInfo.modificationHighlightLines.push_back(2); // Return null
        return nullptr;
    }
    if (path) path->push_back(node);
    if (value == node->value) {
        currOperationInfo.modificationHighlightLines.push_back(3); // value == node.value
        currOperationInfo.modificationHighlightLines.push_back(4); // Return node
        return node;
    }
    if (value < node->value) {
        currOperationInfo.modificationHighlightLines.push_back(5); // value < node.value
        currOperationInfo.modificationHighlightLines.push_back(6); // find(node.left, value)
        return findHelper(node->left, value, path);
    }
    currOperationInfo.modificationHighlightLines.push_back(7); // Else
    currOperationInfo.modificationHighlightLines.push_back(8); // find(node.right, value)
    return findHelper(node->right, value, path);
}
AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

AVLNode* AVLTree::removeHelper(AVLNode* node, int value, std::vector<AVLNode*>* path) {
    if (!node) {
        currOperationInfo.modificationHighlightLines.push_back(1); // If node is null
        currOperationInfo.modificationHighlightLines.push_back(2); // Return null
        return nullptr;
    }
    if (path) path->push_back(node);
    if (value < node->value) {
        currOperationInfo.modificationHighlightLines.push_back(3); // value < node.value
        node->left = removeHelper(node->left, value, path);
        currOperationInfo.modificationHighlightLines.push_back(4); // node.left = remove
    }
    else if (value > node->value) {
        currOperationInfo.modificationHighlightLines.push_back(5); // value > node.value
        node->right = removeHelper(node->right, value, path);
        currOperationInfo.modificationHighlightLines.push_back(6); // node.right = remove
    }
    else {
        currOperationInfo.modificationHighlightLines.push_back(7); // Else
        if (!node->left) {
            currOperationInfo.modificationHighlightLines.push_back(8); // No left child
            AVLNode* temp = node->right;
            currOperationInfo.modificationHighlightLines.push_back(9); // Return node.right
            if (!currOperationInfo.skipAnimations) {
                node->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
                node->opacity = 1.0f;
                node->animationPhase = 0.0f;
            }
            delete node;
            return temp;
        }
        else if (!node->right) {
            currOperationInfo.modificationHighlightLines.push_back(10); // No right child
            AVLNode* temp = node->left;
            currOperationInfo.modificationHighlightLines.push_back(11); // Return node.left
            if (!currOperationInfo.skipAnimations) {
                node->currentAnimation = AVLAnimation::AVL_CHANGINGOPACITY;
                node->opacity = 1.0f;
                node->animationPhase = 0.0f;
            }
            delete node;
            return temp;
        }
        currOperationInfo.modificationHighlightLines.push_back(12); // Else
        currOperationInfo.modificationHighlightLines.push_back(13); // Find min node
        AVLNode* temp = findMin(node->right);
        currOperationInfo.modificationHighlightLines.push_back(14); // node.value = min.value
        node->value = temp->value;
        currOperationInfo.modificationHighlightLines.push_back(15); // node.right = remove
        node->right = removeHelper(node->right, temp->value, path);
    }
    currOperationInfo.modificationHighlightLines.push_back(16); // Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    currOperationInfo.modificationHighlightLines.push_back(17); // Balance node
    return balanceNode(node);
}


void AVLTree::findInsertionPath(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) return;
    path.push_back(node);
    currOperationInfo.pathHighlightLines.push_back(3); // value < node.value
    if (value < node->value) {
        findInsertionPath(node->left, value, path);
    }
    else if (value > node->value) {
        currOperationInfo.pathHighlightLines.push_back(5); // value > node.value
        findInsertionPath(node->right, value, path);
    }
}

void AVLTree::findRemovalPath(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) return;
    path.push_back(node);
    currOperationInfo.pathHighlightLines.push_back(3); // value < node.value
    if (value < node->value) {
        findRemovalPath(node->left, value, path);
    }
    else if (value > node->value) {
        currOperationInfo.pathHighlightLines.push_back(5); // value > node.value
        findRemovalPath(node->right, value, path);
    }
    else {
        currOperationInfo.pathHighlightLines.push_back(7); // Found the node
        return;
    }
}

void AVLTree::findPath(AVLNode* node, int value, std::vector<AVLNode*>& path) {
    if (!node) return;
    path.push_back(node);
    currOperationInfo.pathHighlightLines.push_back(3); // value == node.value
    if (value == node->value) {
        return;
    }
    if (value < node->value) {
        currOperationInfo.pathHighlightLines.push_back(5); // value < node.value
        findPath(node->left, value, path);
    }
    else {
        currOperationInfo.pathHighlightLines.push_back(7); // Else
        findPath(node->right, value, path);
    }
}

void AVLTree::repositionNodes(AVLNode* node, float x, float y, float spacing) {
    if (!node) return;
    node->destination = { x, y };
    if (node->currentAnimation != AVLAnimation::AVL_MOVING || currOperationInfo.skipAnimations) {
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

void AVLTree::skipAnimations() {
    currOperationInfo.skipAnimations = true;

    // Hoàn thành ngay lập tức thao tác hiện tại
    if (!currOperationInfo.path.empty()) {
        currOperationInfo.modificationHighlightLines.clear();
        if (currentOperation.type == INSERT) {
            root = insertNode(root, currentOperation.value, nullptr);
            messageLog = std::to_string(currentOperation.value) + " Inserted";
            if (!currOperationInfo.modificationHighlightLines.empty()) {
                highlighted_line = currOperationInfo.modificationHighlightLines.back();
            }
        }
        else if (currentOperation.type == REMOVE) {
            root = removeHelper(root, currentOperation.value, nullptr);
            messageLog = std::to_string(currentOperation.value) + " Removed";
            if (!currOperationInfo.modificationHighlightLines.empty()) {
                highlighted_line = currOperationInfo.modificationHighlightLines.back();
            }
        }
        else if (currentOperation.type == FIND) {
            if (!currOperationInfo.path.empty()) {
                AVLNode* lastNode = currOperationInfo.path.back();
                if (lastNode && lastNode->value == currentOperation.value) {
                    lastNode->isHighlighted = true;
                    messageLog = std::to_string(currentOperation.value) + " Found";
                    currOperationInfo.modificationHighlightLines.push_back(4); // "Return node"
                }
                else {
                    messageLog = std::to_string(currentOperation.value) + " Not found";
                    currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
                }
                highlighted_line = currOperationInfo.modificationHighlightLines.back();
            }
            else {
                messageLog = std::to_string(currentOperation.value) + " Not found";
                currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
                highlighted_line = 2;
            }
        }
        else if (currentOperation.type == UPDATE) {
            AVLNode* node = findHelper(root, currentOperation.value, nullptr);
            if (!node) {
                messageLog = "Cannot find " + std::to_string(currentOperation.value);
                currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
                highlighted_line = 2;
            }
            else if (findHelper(root, currentOperation.secondValue, nullptr) != nullptr) {
                messageLog = "Value " + std::to_string(currentOperation.secondValue) + " already exists";
            }
            else {
                bool isValid = true;
                AVLNode* current = node->left;
                while (current) {
                    if (currentOperation.secondValue <= current->value) {
                        isValid = false;
                        break;
                    }
                    current = current->right;
                }
                if (isValid) {
                    current = node->right;
                    while (current) {
                        if (currentOperation.secondValue >= current->value) {
                            isValid = false;
                            break;
                        }
                        current = current->left;
                    }
                }
                if (!isValid) {
                    messageLog = "Update to " + std::to_string(currentOperation.secondValue) + " would violate BST property";
                }
                else {
                    node->value = currentOperation.secondValue;
                    messageLog = "Updated from " + std::to_string(currentOperation.value) + " to " + std::to_string(currentOperation.secondValue);
                }
            }
        }
    }

    // Xóa trạng thái animation và cập nhật vị trí
    std::function<void(AVLNode*)> resetNodeAnimations = [&](AVLNode* node) {
        if (!node) return;
        node->currentAnimation = AVLAnimation::AVL_IDLE;
        node->animationPhase = 0.0f;
        node->opacity = 1.0f;
        node->isHighlighted = false;
        node->position = node->destination;
        resetNodeAnimations(node->left);
        resetNodeAnimations(node->right);
        };
    resetNodeAnimations(root);

    // Cập nhật vị trí cây và con trỏ
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);
    updatePointers();

    // Xóa thông tin thao tác hiện tại
    currOperationInfo.path.clear();
    currOperationInfo.currentPathIndex = 0;
    currOperationInfo.highlightTimer = 0.0f;
    currOperationInfo.skipAnimations = false;
    currOperationInfo.pathHighlightLines.clear();
    currOperationInfo.modificationHighlightLines.clear();
}

void AVLTree::setSkip() {
    skipCurrentStep = true;
    skipAnimations(); // Gọi skipAnimations để hoàn thành thao tác ngay lập tức
}

void AVLTree::update() {
    if (isPaused) return;

    // Xóa highlight cho các node không nằm trong path
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

            // Cập nhật highlighted_line từ pathHighlightLines
            if (currOperationInfo.currentPathIndex < currOperationInfo.pathHighlightLines.size()) {
                highlighted_line = currOperationInfo.pathHighlightLines[currOperationInfo.currentPathIndex];
            }
            else {
                highlighted_line = 0;
            }

            currOperationInfo.currentPathIndex++;
            currOperationInfo.highlightTimer = 0.0f;
        }
    }
    else if (!currOperationInfo.path.empty()) {
        // Chuyển sang phase MODIFICATION
        currOperationInfo.phase = MODIFICATION;
        currOperationInfo.modificationHighlightLines.clear(); // Xóa highlightLines cho MODIFICATION

        if (currentOperation.type == INSERT) {
            root = insertNode(root, currentOperation.value, nullptr);
            repositionNodes(root, GetScreenWidth() / 2, 100, 200);
            messageLog = std::to_string(currentOperation.value) + " Inserted";
        }
        else if (currentOperation.type == REMOVE) {
            root = removeHelper(root, currentOperation.value, nullptr);
            repositionNodes(root, GetScreenWidth() / 2, 100, 200);
            messageLog = std::to_string(currentOperation.value) + " Removed";
        }
        else if (currentOperation.type == FIND) {
            if (!currOperationInfo.path.empty()) {
                AVLNode* lastNode = currOperationInfo.path.back();
                if (lastNode && lastNode->value == currentOperation.value) {
                    lastNode->isHighlighted = true;
                    messageLog = std::to_string(currentOperation.value) + " Found";
                    currOperationInfo.modificationHighlightLines.push_back(4); // "Return node"
                }
                else {
                    messageLog = std::to_string(currentOperation.value) + " Not found";
                    currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
                }
            }
            else {
                messageLog = std::to_string(currentOperation.value) + " Not found";
                currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
            }
        }
        else if (currentOperation.type == UPDATE) {
            AVLNode* node = findHelper(root, currentOperation.value, nullptr);
            if (!node) {
                messageLog = "Cannot find " + std::to_string(currentOperation.value);
                currOperationInfo.modificationHighlightLines.push_back(2); // "Return null"
            }
            else if (findHelper(root, currentOperation.secondValue, nullptr) != nullptr) {
                messageLog = "Value " + std::to_string(currentOperation.secondValue) + " already exists";
            }
            else {
                bool isValid = true;
                AVLNode* current = node->left;
                while (current) {
                    if (currentOperation.secondValue <= current->value) {
                        isValid = false;
                        break;
                    }
                    current = current->right;
                }
                if (isValid) {
                    current = node->right;
                    while (current) {
                        if (currentOperation.secondValue >= current->value) {
                            isValid = false;
                            break;
                        }
                        current = current->left;
                    }
                }
                if (!isValid) {
                    messageLog = "Update to " + std::to_string(currentOperation.secondValue) + " would violate BST property";
                }
                else {
                    node->value = currentOperation.secondValue;
                    messageLog = "Updated from " + std::to_string(currentOperation.value) + " to " + std::to_string(currentOperation.secondValue);
                }
            }
        }

        // Highlight dòng đầu tiên của MODIFICATION (nếu có)
        if (!currOperationInfo.modificationHighlightLines.empty()) {
            highlighted_line = currOperationInfo.modificationHighlightLines[0];
        }
        else {
            highlighted_line = 0;
        }

        currOperationInfo.path.clear();
        currOperationInfo.currentPathIndex = 0;
        currOperationInfo.highlightTimer = 0.0f;
        currOperationInfo.phase = PATH_FINDING; // Reset phase
    }

    if (!operationQueue.empty() && !isAnimating) {
        currentOperation = operationQueue.front();
        operationQueue.pop();
        highlighted_line = 0;
        currOperationInfo.pathHighlightLines.clear();
        currOperationInfo.modificationHighlightLines.clear();
        currOperationInfo.skipAnimations = (currentOperation.type == RANDOM);
        if (currOperationInfo.skipAnimations) {
            switch (currentOperation.type) {
            case INSERT:
                root = insertNode(root, currentOperation.value, nullptr);
                repositionNodes(root, GetScreenWidth() / 2, 100, 200);
                messageLog = std::to_string(currentOperation.value) + " Inserted";
                break;
            case REMOVE:
                root = removeHelper(root, currentOperation.value, nullptr);
                repositionNodes(root, GetScreenWidth() / 2, 100, 200);
                messageLog = std::to_string(currentOperation.value) + " Removed";
                break;
            case RANDOM:
                randomCreate(currentOperation.value);
                break;
            case UPDATE:
                updateVal(currentOperation.value, currentOperation.secondValue);
                break;
            }
        }
        else {
            std::vector<AVLNode*> path;
            switch (currentOperation.type) {
            case INSERT:
                findInsertionPath(root, currentOperation.value, path);
                break;
            case REMOVE:
                findRemovalPath(root, currentOperation.value, path);
                break;
            case FIND:
                findPath(root, currentOperation.value, path);
                break;
            case UPDATE:
                findPath(root, currentOperation.value, path);
                break;
            }
            currOperationInfo.path = path;
            currOperationInfo.currentPathIndex = 0;
            currOperationInfo.highlightTimer = 0.0f;
        }
    }

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
    for (int i = 0; i < amount; ++i) {
        int val = GetRandomValue(0, 100);
        while (findHelper(root, val, nullptr) != nullptr) {
            val = GetRandomValue(0, 100);
        }
        root = insertNode(root, val, nullptr);
    }
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);
    messageLog = std::to_string(amount) + " Random nodes created.";
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

    // Hiển thị bảng pseudocode
    std::vector<std::string>* pseudocode = nullptr;
    std::string title;
    if (currentOperation.type == INSERT) {
        pseudocode = &insertPseudocode;
        title = "Insert Pseudocode";
    }
    else if (currentOperation.type == FIND) {
        pseudocode = &findPseudocode;
        title = "Find Pseudocode";
    }
    else if (currentOperation.type == REMOVE) {
        pseudocode = &removePseudocode;
        title = "Remove Pseudocode";
    }

    if (pseudocode) {
        // Vẽ tiêu đề
        float x = 1100;
        float y = 650; // Di chuyển xuống dưới cùng (màn hình 1600x900)
        DrawText(title.c_str(), x, y, 20, GREEN);
        y += 30;

        // Vẽ từng dòng pseudocode
        for (size_t i = 0; i < pseudocode->size(); ++i) {
            Color textColor = (i + 1 == highlighted_line) ? RED : GREEN;
            DrawText((*pseudocode)[i].c_str(), x, y + i * 20, 16, textColor);
        }
    }
}

void AVLTree::setStop(bool stop) {
    isPaused = stop;
}

bool AVLTree::isStop() const {
    return isPaused;
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
        root = insertNode(root, val, nullptr);
    }
    repositionNodes(root, GetScreenWidth() / 2, 100, 200);
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

void AVLTree::updateVal(int oldValue, int newValue) {
    AVLNode* node = findHelper(root, oldValue, nullptr);
    if (!node) {
        messageLog = "Cannot find " + std::to_string(oldValue);
        return;
    }

    if (findHelper(root, newValue, nullptr) != nullptr) {
        messageLog = "Value " + std::to_string(newValue) + " already exists";
        return;
    }

    AVLNode* current = root;
    while (current != nullptr) {
        if (current == node) {
            bool isValid = true;

            if (node->left) {
                AVLNode* maxLeft = node->left;
                while (maxLeft->right) maxLeft = maxLeft->right;
                if (newValue <= maxLeft->value) {
                    isValid = false;
                }
            }
            if (isValid && node->right) {
                AVLNode* minRight = node->right;
                while (minRight->left) minRight = minRight->left;
                if (newValue >= minRight->value) {
                    isValid = false;
                }
            }

            if (!isValid) {
                messageLog = "Update to " + std::to_string(newValue) + " would violate BST property";
                return;
            }

            node->value = newValue;
            messageLog = "Updated from " + std::to_string(oldValue) + " to " + std::to_string(newValue);
            return;
        }

        if (newValue < current->value) {
            current = current->left;
        }
        else if (newValue > current->value) {
            current = current->right;
        }
        else {
            messageLog = "Update to " + std::to_string(newValue) + " would violate BST property";
            return;
        }
    }

    messageLog = "Update to " + std::to_string(newValue) + " would not reach the correct position";
}