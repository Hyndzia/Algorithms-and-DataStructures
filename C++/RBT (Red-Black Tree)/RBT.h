#pragma once
#include <sstream>

template<typename T>
class RBT {
public:
    RBT() {
        root = nullptr;
        height = 0;
        size = 0;
    }
    ~RBT() {
        clearALL();
    }

    struct node {
        int nodeKey;
        bool isBlack;
        node* leftNode;
        node* rightNode;
        node* parentNode;
        T nodeData;

        node() : leftNode(nullptr), rightNode(nullptr), parentNode(nullptr), isBlack(false), nodeKey(0) {}

    };

    unsigned int getHeight() {
        return treeHeight(root);
    }

    node* get_root_data() {
        if (root) return root;
        else return nullptr;
    }

    void viewPreOrder() {
        if (root) return preOrder(root);
    }

    void viewInOrder() {
        if (root) return inOrder(root);
    }

    void insert(int key, const T& data) {
        node* newNode = insertNode(key, data);
        node* uncleNode;
        while ((newNode != root) && (newNode->parentNode->isBlack == false)) {
            if (newNode->parentNode == newNode->parentNode->parentNode->leftNode) {
                uncleNode = newNode->parentNode->parentNode->rightNode;
                if (uncleNode) {         //uncleNode jest czerwony
                    if (uncleNode->isBlack == false) {
                        newNode->parentNode->isBlack = true;
                        uncleNode->isBlack = true;
                        newNode->parentNode->parentNode->isBlack = false;
                        newNode = newNode->parentNode->parentNode;
                        continue;
                    }
                }
                if (newNode == newNode->parentNode->rightNode) {      //formacja trójk¹tna
                    newNode = newNode->parentNode;
                    rotateLeft(newNode->rightNode, newNode);
                }
                newNode->parentNode->isBlack = true;       //formacja liniowa
                newNode->parentNode->parentNode->isBlack = false;
                rotateRight(newNode->parentNode, newNode->parentNode->parentNode);
                break;
            }
            else {
                uncleNode = newNode->parentNode->parentNode->leftNode;
                if (uncleNode != nullptr && uncleNode->isBlack == false) {
                    newNode->parentNode->isBlack = true;
                    uncleNode->isBlack = true;
                    newNode->parentNode->parentNode->isBlack = false;
                    newNode = newNode->parentNode->parentNode;
                    continue;
                }
                if (newNode == newNode->parentNode->leftNode) {
                    newNode = newNode->parentNode;
                    rotateRight(newNode->leftNode, newNode);
                }
                newNode->parentNode->isBlack = true;
                newNode->parentNode->parentNode->isBlack = false;
                rotateLeft(newNode->parentNode, newNode->parentNode->parentNode);
                break;
            }
        }
        root->isBlack = true;
    }

    void clearALL() {
        node*& n = root;
        clear(n);
    }

    node* search(const T& dane) {
        return search(root, dane);
    }

    int getSize() {
        if (size == 0) {
            return 0;
        }
        return size;
    }
    std::string display() {
        std::ostringstream str;
        if (root != nullptr) {
            str << "(";
            str << root->nodeKey << ": ";
            if (root->isBlack == true) {
                str << " [black";
            }
            else str << " [red";
            str << " p: ";
            if (root->parentNode == nullptr) {

                str << "NULL";
            }
            else str << root->parentNode->nodeKey;
            str << " l: ";
            if (root->leftNode != nullptr) str << root->leftNode->nodeKey;
            else str << "NULL";
            str << " p: ";
            if (root->rightNode != nullptr) str << root->rightNode->nodeKey;
            else str << "NULL";
            str << "]";
            str << " (" << root->nodeData;
        }
        return str.str();
    }
private:
    void rotateRight(node* childNode, node* parentNode) {
        node* tmp = nullptr;
        node* g_parentNode = parentNode->parentNode;
        if (g_parentNode != nullptr) {
            if (g_parentNode->rightNode == parentNode) {
                g_parentNode->rightNode = childNode;
            }
            else g_parentNode->leftNode = childNode;
        }
        else root = childNode;
        tmp = childNode->rightNode;
        childNode->rightNode = parentNode;
        parentNode->leftNode = tmp;
        childNode->parentNode = g_parentNode;
        parentNode->parentNode = childNode;
        if (tmp != nullptr) tmp->parentNode = parentNode;
    }
    void rotateLeft(node* childNode, node* parentNode) {
        node* tmp = nullptr;
        node* g_parentNode = parentNode->parentNode;
        if (g_parentNode != nullptr) {
            if (g_parentNode->rightNode == parentNode) {
                g_parentNode->rightNode = childNode;
            }
            else g_parentNode->leftNode = childNode;
        }
        else root = childNode;
        tmp = childNode->leftNode;
        childNode->leftNode = parentNode;
        parentNode->rightNode = tmp;
        childNode->parentNode = g_parentNode;
        parentNode->parentNode = childNode;
        if (tmp != nullptr) tmp->parentNode = parentNode;

    }
    node* insertNode(int key, const T& data) {
        node* iter = root;
        node* prev;
        char side = 'a';
        prev = nullptr;
        while (iter != nullptr) {
            /* if (iter->nodeKey == key) { //for normal bst
                 break;
             }
             else*/ if (iter->nodeKey > key) {
                 prev = iter;
                 iter = iter->leftNode;
                 side = 'l';
             }
             else {
                 prev = iter;
                 iter = iter->rightNode;
                 side = 'p';
             }
        }
        node* n = new node;
        n->nodeKey = key;
        n->nodeData = data;
        n->leftNode = nullptr;
        n->rightNode = nullptr;
        if (prev == nullptr) {
            root = n;
            n->parentNode = nullptr;
        }
        else if (side == 'l') {
            prev->leftNode = n;
            n->parentNode = prev;
        }
        else {
            prev->rightNode = n;
            n->parentNode = prev;
        }
        ++size;
        return n;
    }
    void clear(node*& n) {
        if (n != nullptr) {
            clear(n->leftNode);
            clear(n->rightNode);
            delete n;
            n = nullptr;
        }
        size = 0;
    }
    std::string preOrder(node* root) {
        std::ostringstream str;
        if (root != nullptr) {
            str << root->nodeKey << " " << root->nodeData << "\n";
            str << preOrder(root->leftNode);
            str << preOrder(root->rightNode);
        }
    }

    std::string inOrder(node* root) {
        std::ostringstream str;
        if (root != nullptr) {
            str << inOrder(root->leftNode);
            str << root->nodeKey << " " << root->nodeData << "\n";
            str << inOrder(root->rightNode);
        }
        return str.str();
    }
    uint32_t treeHeight(node* root)
    {
        if (root != nullptr)
        {
            int height_p = treeHeight(root->rightNode);
            int height_l = treeHeight(root->leftNode);
            height = std::max(height_p, height_l) + 1;
            return height;
        }
        else return 0;
    }
    node* search(node* root, const T& data) {
        node* iter = root;
        while (iter != nullptr) {
            if (iter->nodeData == data) {
                return iter;
            }
            else if (iter->nodeData > data) {
                iter = iter->leftNode;
            }
            else {
                iter = iter->rightNode;
            }
        }
        return nullptr;
    }
    node* root;
    uint32_t height;
    uint64_t size;
};