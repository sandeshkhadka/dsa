#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename KeyT, typename ValueT> struct BNode {
  ValueT data;
  KeyT key;
  std::shared_ptr<struct BNode> left;
  std::shared_ptr<struct BNode> right;
  std::shared_ptr<struct BNode> parent;
  BNode(KeyT key, ValueT data) {
    this->data = data;
    this->key = key;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
  }
};
template <typename KeyT, typename ValueT> class BinaryTree {
private:
  std::shared_ptr<struct BNode<KeyT, ValueT>> root;

  /*
   * Inorder tree traversal. LEFT, ROOT, RIGHT
   */
  void inorder(std::shared_ptr<struct BNode<KeyT, ValueT>> node,
               void (*callback)(KeyT key, ValueT data)) {
    if (!node) {
      return;
    }
    inorder(node->left, callback);
    callback(node->key, node->data);
    inorder(node->right, callback);
  }
  /*
   * PreOrder tree traversal.  ROOT,LEFT,RIGHT
   */
  void preorder(std::shared_ptr<struct BNode<KeyT, ValueT>> node,
                void (*callback)(KeyT key, ValueT data)) {
    if (!node) {
      return;
    }
    callback(node->key, node->data);
    preorder(node->left, callback);
    preorder(node->right, callback);
  }

  /*
   * PreOrder tree traversal.  LEFT, RIGHT, ROOT
   */
  void postorder(std::shared_ptr<struct BNode<KeyT, ValueT>> node,
                 void (*callback)(KeyT key, ValueT data)) {
    if (!node) {
      return;
    }
    postorder(node->left, callback);
    postorder(node->right, callback);
    callback(node->key, node->data);
  }

  bool is_leafnode(std::shared_ptr<struct BNode<KeyT, ValueT>> node) {
    return (node->left == nullptr) && (node->right == nullptr);
  }
  /*
   * Finds the successor to the given node;
   * A succesor is the next element in the node that can replace the current
   * node and also satisfy the BST property. It is the leftmost element of right
   * subtree of the node
   */
  std::shared_ptr<struct BNode<KeyT, ValueT>>
  find_successor(std::shared_ptr<struct BNode<KeyT, ValueT>> node) {
    auto successor = node->right;
    if (!successor) {
      return node->left;
    }
    while (successor->left) {
      successor = successor->left;
    }

    return successor;
  }

  /*
   * Finds and returns the pointer to the Node with give key;
   */
  std::shared_ptr<struct BNode<KeyT, ValueT>>
  find_node(KeyT key) {
    auto cursor = root;
    auto parent = root;
    while (cursor && cursor->key != key) {
      parent = cursor;
      if (key > cursor->key) {
        cursor = cursor->right;
      } else {
        cursor = cursor->left;
      }
    }
    return cursor;
  }

  /*
   *Replaces the current node with it's successor and kills the successor
   *recursively
   */
  bool
  kill_node(std::shared_ptr<BNode<KeyT, ValueT>> node) {
    if (node == nullptr) {
      return true;
    }
    auto successor = find_successor(node);
    if (successor == nullptr) {
      // there is only one item in the tree
      if (!node->parent) {
        root = nullptr;
      } else {
        if (node == node->parent->left) {
          node->parent->left = nullptr;
        } else {
          node->parent->right = nullptr;
        }
      }
      return true;
    }
    auto successor_copy = create_node(successor->key, successor->data);
    successor_copy->left = node->left;
    successor_copy->right = node->right;

    if (successor_copy->left) {
      successor_copy->left->parent = successor_copy;
    }
    if (successor_copy->right) {
      successor_copy->right->parent = successor_copy;
    }

    if (node->parent) {
      if (node == node->parent->left) {
        node->parent->left = successor_copy;
      } else {
        node->parent->right = successor_copy;
      }
      successor_copy->parent = node->parent;
    } else {
      root = successor_copy;
    }
    return kill_node(successor);
  }

public:
  enum TraversalOption { PreOrder, InOrder, PostOrder };

  BinaryTree() { root = nullptr; }
  BinaryTree(KeyT key, ValueT data) { root = create_node(key, data); }

  bool is_empty() { return (root == nullptr); }

  /*
   * Creates and returns the pointer to a node with given key and data
   */
  std::shared_ptr<BNode<KeyT, ValueT>> create_node(KeyT key, ValueT data) {
    auto node = std::make_shared<BNode<KeyT, ValueT>>(key, data);
    return node;
  }

  /*
   * Inserts new item in the tree.
   */
  void insert(KeyT key, ValueT data) {
    if (is_empty()) {
      root = create_node(key, data);
      return;
    }
    auto cursor = root;
    while (cursor) {
      if (cursor->key == key) {
        std::stringstream s;
        s << "Key " << key << " already exist" << std::endl;
        throw s.str();
      }
      if (key > cursor->key) {
        if (cursor->right) {
          cursor = cursor->right;
        } else {
          cursor->right = create_node(key, data);
          cursor->right->parent = cursor;
          return;
        }
      } else {
        if (cursor->left) {
          cursor = cursor->left;
        } else {
          cursor->left = create_node(key, data);
          cursor->left->parent = cursor;
          return;
        }
      }
    }
  }

  /*
   * Removes the node with given key from the tree
   */
  bool remove(KeyT key) {
    auto node = find_node(key);
    if (!node) {
      return false;
    }
    return kill_node(node);
  }

  /*
   * Traverses the tree using a given traversal method.
   * Available methods of traversal:
   *    - Inorder
   *    - Preorder
   *    - Postorder
   */
  void traverse(void (*callback)(KeyT key, ValueT), TraversalOption option) {
    if (option == BinaryTree<KeyT, ValueT>::InOrder) {
      inorder(root, callback);
    }
    if (option == BinaryTree<KeyT, ValueT>::PreOrder) {
      preorder(root, callback);
    }
    if (option == BinaryTree<KeyT, ValueT>::PostOrder) {
      postorder(root, callback);
    }
  }

  /*
   * Returns root node of the tree
   */
  std::shared_ptr<BNode<KeyT, ValueT>> get_root() const { return root; }
};

/*
 * Callback function to print node;
 */
template <typename KeyT, typename ValueT> void print(KeyT key, ValueT data) {
  std::cout << key << '\t';
}

int main() {
  BinaryTree<int, int> b;
  std::vector<int> elements = {56, 30, 70, 22,  40, 60, 95, 11,
                               25, 65, 92, 100, 3,  16, 63, 67};
  for (int e : elements) {
    b.insert(e, e);
  }
  b.traverse(print, BinaryTree<int, int>::InOrder);
  std::cout << std::endl;
  b.remove(70);
  b.traverse(print, BinaryTree<int, int>::InOrder);
  std::cout << std::endl;
}
