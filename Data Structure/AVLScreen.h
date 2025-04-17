#pragma once
#include "Button.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    float x, y;
    float targetX, targetY;

    AVLNode(int k, float xPos, float yPos) : key(k), left(nullptr), right(nullptr), height(1), x(xPos), y(yPos), targetX(xPos), targetY(yPos) {}
};

class AVLTree {
public:
    AVLNode* root;
    std::vector<int> insertQueue;
    bool animating = false;

    AVLTree() : root(nullptr) {}

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int key, float x, float y, float offset) {
        if (!node) {
            AVLNode* newNode = new AVLNode(key, x, -50);
            newNode->targetX = x;
            newNode->targetY = y;
            return newNode;
        }

        if (key < node->key)
            node->left = insert(node->left, key, x - offset, y + 50, offset / 2);
        else if (key > node->key)
            node->right = insert(node->right, key, x + offset, y + 50, offset / 2);
        else
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insert(int key) {
        insertQueue.push_back(key);
        animating = true;
    }

    void processInsertion() {
        if (!insertQueue.empty()) {
            int key = insertQueue.front();
            insertQueue.erase(insertQueue.begin());
            root = insert(root, key, 400, 50, 200);
            setTargetPositions(root, 400, 50, 200);
        }
    }

    void setTargetPositions(AVLNode* node, float x, float y, float offset) {
        if (!node) return;
        node->targetX = x;
        node->targetY = y;
        setTargetPositions(node->left, x - offset, y + 50, offset / 2);
        setTargetPositions(node->right, x + offset, y + 50, offset / 2);
    }

    void updateNodePosition(AVLNode* node) {
        if (!node) return;
        float speed = 5.0f;
        if (std::abs(node->x - node->targetX) > 1 || std::abs(node->y - node->targetY) > 1) {
            node->x += (node->targetX - node->x) * 0.1f;
            node->y += (node->targetY - node->y) * 0.1f;
            animating = true;
        }
        updateNodePosition(node->left);
        updateNodePosition(node->right);
    }

    void drawNode(AVLNode* node) {
        if (!node) return;

        if (node->left) {
            DrawLine(node->x, node->y, node->left->x, node->left->y, BLACK);
            drawNode(node->left);
        }
        if (node->right) {
            DrawLine(node->x, node->y, node->right->x, node->right->y, BLACK);
            drawNode(node->right);
        }
        DrawCircle(node->x, node->y, 20, BLUE);
        DrawText(std::to_string(node->key).c_str(), node->x - 5, node->y - 5, 20, WHITE);
    }

    void drawTree() {
        if (root)
            drawNode(root);
    }
};


