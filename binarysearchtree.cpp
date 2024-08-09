#include <iostream>
#include <memory>
#include <vector>
template <typename T> struct BNode {
  T data;
  std::shared_ptr<struct BNode> left;
  std::shared_ptr<struct BNode> right;
  BNode(T data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
  }
};
template <typename T> class BinaryTree {
private:
  std::shared_ptr<struct BNode<T>> root;

  void inorder(std::shared_ptr<struct BNode<T>> node,
               void (*callback)(T data)) {
    if (!node) {
      return;
    }
    inorder(node->left, callback);
    callback(node->data);
    inorder(node->right, callback);
  }
  void preorder(std::shared_ptr<struct BNode<T>> node,
                void (*callback)(T data)) {
    if (!node) {
      return;
    }
    callback(node->data);
    preorder(node->left, callback);
    preorder(node->right, callback);
  }
  void postorder(std::shared_ptr<struct BNode<T>> node,
                 void (*callback)(T data)) {
    if (!node) {
      return;
    }
    postorder(node->left, callback);
    postorder(node->right, callback);
    callback(node->data);
  }

public:
  BinaryTree() { root = nullptr; }
  BinaryTree(T data) { root = create_node(data); }
  enum TraversalOption { PreOrder, InOrder, PostOrder };

  std::shared_ptr<BNode<T>> create_node(T data) {
    auto node = std::make_shared<BNode<T>>(data);
    return node;
  }
  void insert(T data) {
    if (is_empty()) {
      root = create_node(data);
      return;
    }
    auto cursor = root;
    while (true) {
      if (data > cursor->data) {
        if (cursor->right) {
          cursor = cursor->right;
        } else {
          cursor->right = create_node(data);
          return;
        }
      } else {
        if (cursor->left) {
          cursor = cursor->left;
        } else {
          cursor->left = create_node(data);
          return;
        }
      }
    }
  }

  void traverse(void (*callback)(T), TraversalOption option) {
    if (option == BinaryTree<T>::InOrder) {
      inorder(root, callback);
    }
    if (option == BinaryTree<T>::PreOrder) {
      preorder(root, callback);
    }
    if (option == BinaryTree<T>::PostOrder) {
      postorder(root, callback);
    }
  }
  bool is_empty() { return (root == nullptr); }

  std::shared_ptr<BNode<T>> get_root() { return root; }
};
template <typename T> void print(T data) { std::cout << data << '\t'; }
int main() {
  BinaryTree<int> b;
  std::vector<int> elements = {5, 9, 0, 1, 8, 4, 6};
  for (int e : elements) {
    b.insert(e);
  }
  b.traverse(print, BinaryTree<int>::PreOrder);
  std::cout << std::endl;
  b.traverse(print, BinaryTree<int>::InOrder);
  std::cout << std::endl;
  b.traverse(print, BinaryTree<int>::PostOrder);
  std::cout << std::endl;
}
