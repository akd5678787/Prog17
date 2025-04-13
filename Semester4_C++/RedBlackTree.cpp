#include <iostream>
#include <vector>
#include <functional> // Для std::less

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct Node {
    Key key;
    Value value;
    Node* parent;
    Node* left;
    Node* right;
    bool color; // true = RED, false = BLACK

    Node(Key k, Value v) : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr), color(true) {}
};

template <typename Key, typename Value, typename Compare = std::less<Key>>
class RedBlackTree {
private:
    Node<Key, Value, Compare>* root;
    Node<Key, Value, Compare>* TNULL;
    Compare comp;  // Компаратор

    void rotateLeft(Node<Key, Value, Compare>* x);
    void rotateRight(Node<Key, Value, Compare>* x);
    void fixInsert(Node<Key, Value, Compare>* k);
    void fixDelete(Node<Key, Value, Compare>* x);
    Node<Key, Value, Compare>* successor(Node<Key, Value, Compare>* x);
    Node<Key, Value, Compare>* minimum(Node<Key, Value, Compare>* node);
    void inorder(Node<Key, Value, Compare>* node, std::vector<std::pair<Key, Value>>& result) const;
    void deleteNodeHelper(Node<Key, Value, Compare>* node, Key key);
    void rbTransplant(Node<Key, Value, Compare>* u, Node<Key, Value, Compare>* v);
    void clear(Node<Key, Value, Compare>* node); // Добавлено для очистки дерева

public:
    RedBlackTree(Compare c = Compare()) : comp(c) { // Принимаем компаратор
        TNULL = new Node<Key, Value, Compare>(Key(), Value()); // Используем значение по умолчанию
        TNULL->color = false;
        root = TNULL;
    }

    ~RedBlackTree() {
        clear(root); // Очищаем всё дерево
        delete TNULL; // Удаляем TNULL
    }

    void insert(Key key, Value value);
    Node<Key, Value, Compare>* search(Key key) const;
    void remove(Key key);
    void printTree() const; // Обход в порядке возрастания
    Node<Key, Value, Compare>* getTNULL() const { return TNULL; }
    Node<Key, Value, Compare>* getRoot() const { return root; }

    // Для удобства добавим метод для проверки пустоты дерева
    bool isEmpty() const { return root == TNULL; }
};

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::rotateLeft(Node<Key, Value, Compare>* x) {
    Node<Key, Value, Compare>* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::rotateRight(Node<Key, Value, Compare>* x) {
    Node<Key, Value, Compare>* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::fixInsert(Node<Key, Value, Compare>* k) {
    Node<Key, Value, Compare>* u;
    while (k->parent != nullptr && k->parent->color == true) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == true) { // Дядя красный
                u->color = false;
                k->parent->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { // k - левый сын
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                rotateLeft(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // Дядя
            if (u->color == true) {
                u->color = false;
                k->parent->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                rotateRight(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = false;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::insert(Key key, Value value) {
    Node<Key, Value, Compare>* node = new Node<Key, Value, Compare>(key, value);
    node->parent = nullptr;
    node->left = TNULL;
    node->right = TNULL;

    Node<Key, Value, Compare>* y = nullptr;
    Node<Key, Value, Compare>* x = root;

    while (x != TNULL) {
        y = x;
        if (comp(node->key, x->key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (comp(node->key, y->key)) {
        y->left = node;
    } else {
        y->right = node;
    }

    // Новый узел всегда красный
    node->color = true;

    fixInsert(node); // Исправление после вставки
}

template <typename Key, typename Value, typename Compare>
Node<Key, Value, Compare>* RedBlackTree<Key, Value, Compare>::search(Key key) const {
    Node<Key, Value, Compare>* curr = root;
    while (curr != TNULL) {
        if (!comp(key, curr->key) && !comp(curr->key, key)) {
            return curr; // Ключ найден
        }
        if (comp(key, curr->key)) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return TNULL; // Ключ не найден
}

template <typename Key, typename Value, typename Compare>
Node<Key, Value, Compare>* RedBlackTree<Key, Value, Compare>::minimum(Node<Key, Value, Compare>* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value, typename Compare>
Node<Key, Value, Compare>* RedBlackTree<Key, Value, Compare>::successor(Node<Key, Value, Compare>* x) {
    Node<Key, Value, Compare>* y;
    if (x->right != TNULL) {
        return minimum(x->right);
    }
    y = x->parent;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::deleteNodeHelper(Node<Key, Value, Compare>* node, Key key) {
    Node<Key, Value, Compare>* z = TNULL;
    Node<Key, Value, Compare>* x, * y;
    while (node != TNULL) {
        if (!comp(key, node->key) && !comp(node->key, key)) { // Используем компаратор для сравнения
            z = node; // Узел, который нужно удалить
        }
        if (comp(key, node->key)) { // Используем компаратор для сравнения
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (z == TNULL) {
        return; // Ключ не найден
    }

    y = z;
    bool y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = successor(z);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == false) {
        fixDelete(x);
    }
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::rbTransplant(Node<Key, Value, Compare>* u, Node<Key, Value, Compare>* v) {
    if (u->parent == nullptr) {
        root = v; // Это корень
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::fixDelete(Node<Key, Value, Compare>* x) {
    Node<Key, Value, Compare>* s;
    while (x != root && x->color == false) {
        if (x == x->parent->left) {
            s = x->parent->right; // Брат узла
            if (s->color == true) {
                s->color = false; // Превращаем его в черный
                x->parent->color = true; // Превращаем родителя в красный
                rotateLeft(x->parent);
                s = x->parent->right;
            }
            if (s->left->color == false && s->right->color == false) {
                s->color = true; // Превращаем брата в красный
                x = x->parent; // Поднимаемся к родителю
            } else {
                if (s->right->color == false) {
                    s->left->color = false; // Превращаем левую ноду в черный
                    s->color = true; // Превращаем брата в красный
                    rotateRight(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color; // Падаем от родителя
                x->parent->color = false; // Превращаем родителя в черный
                s->right->color = false; // Превращаем правого сына в черный
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left; // Брат узла
            if (s->color == true) {
                s->color = false; // Превращаем его в черный
                x->parent->color = true; // Превращаем родителя в красный
                rotateRight(x->parent);
                s = x->parent->left;
            }
            if (s->right->color == false && s->left->color == false) {
                s->color = true; // Превращаем в красный
                x = x->parent; // Поднимаемся к родителю
            } else {
                if (s->left->color == false) {
                    s->right->color = false; // Превращаем правую в черный
                    s->color = true; // Превращаем брата в красный
                    rotateLeft(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color; // Падаем от родителя
                x->parent->color = false; // Превращаем родителя в черный
                s->left->color = false; // Превращаем левую ноду в черный
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = false; // В случае если это черный узел
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::remove(Key key) {
    deleteNodeHelper(root, key);
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::printTree() const {
    std::vector<std::pair<Key, Value>> elements;
    inorder(root, elements);
    for (const auto& pair : elements) {
        std::cout << "(" << pair.first << ": " << pair.second << ") ";
    }
    std::cout << std::endl;
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::inorder(Node<Key, Value, Compare>* node, std::vector<std::pair<Key, Value>>& result) const {
    if (node != TNULL) {
        inorder(node->left, result);
        result.emplace_back(node->key, node->value);
        inorder(node->right, result);
    }
}

template <typename Key, typename Value, typename Compare>
void RedBlackTree<Key, Value, Compare>::clear(Node<Key, Value, Compare>* node) {
    if (node != TNULL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}