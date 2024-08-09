#include <iostream>
#include <memory>
template <typename T> struct Node {
  T data;
  std::shared_ptr<struct Node> next;
  Node(T data) {
    this->data = data;
    next = nullptr;
  }
};

template <typename T> class SinglyLinkedList {
private:
  std::shared_ptr<struct Node<T>> head;

  std::shared_ptr<struct Node<T>> create_node(T data) {
    auto node = std::make_shared<struct Node<T>>(data);
    return node;
  }

  public : SinglyLinkedList(T data) {
    head = create_node(data);
  }

  /*
   * appends data to end of the list
   */
  void insert(T data) {
    auto cursor = head;
    while (cursor->next) {
      cursor = cursor->next;
    }
    cursor->next = create_node(data);
  }

  /*
   * inserts data at index(zero based position index)
   */
  void insert(T data, int index) {
    auto cursor = head;
    for (int i = 0; i < index - 1 && cursor->next; i++) {
      cursor = cursor->next;
    }
    auto temp = create_node(data);
    temp->next = cursor->next;
    cursor->next = temp;
  }

  /*
   * remove last element from the list
   */
  void remove() {
    if (is_empty()) {
      return;
    }

    auto cursor = head;
    if (head->next) {
      while (cursor->next->next) {
        cursor = cursor->next;
      }
    } else {     // when single item is in list
      remove(0); // remove head
      return;
    }
    if (cursor->next)
      cursor->next = nullptr;
  }

  /*
   * remove item at "index" (zero-based position index)
   */
  void remove(int index) {
    if (is_empty()) {
      return;
    }
    if (index == 0) {
      head = head->next;
      return;
    }
    auto cursor = head;
    for (int i = 0; i < index - 1 && cursor->next->next; i++) {
      cursor = cursor->next;
    }
    cursor->next = nullptr;
  }

  bool is_empty() { return (head == nullptr); }

  /*
   * calls callback function for each data value in the list;
   * traverse from head to last element
   */
  void for_all(void (*callback)(T data)) {
    auto cursor = head;
    while (cursor) {
      callback(cursor->data);
      cursor = cursor->next;
    }
  }
  T gethead() { return head->data; }
};

template <typename T> struct DNode {
  T data;
  std::shared_ptr<struct DNode> prev;
  std::shared_ptr<struct DNode> next;
  DNode(T data) {
    this->data = data;
    prev = nullptr;
    next = nullptr;
  }
};

template <typename T> class DoublyLinkedList {
private:
  std::shared_ptr<struct DNode<T>> head;
  std::shared_ptr<struct DNode<T>> end;

public:
  enum TraversalOption { Forward, Backward };
  DoublyLinkedList() { head = nullptr; }
  DoublyLinkedList(T data) {
    head = create_node(data);
    end = head;
  }
  DoublyLinkedList(std::shared_ptr<Node<T>> node) {
    head = node;
    end = node;
  }
  /*
   * appends data to end of the list
   */

  // std::shared_ptr<Node<T>> create_node(T data) {
  //   return std::make_shared<Node<T>>(data);
  // }

  std::shared_ptr<DNode<T>> create_node(T data) {
    auto node = std::make_shared<DNode<T>>(data);
    return node;
  }
  std::shared_ptr<DNode<T>> create_node(T data,
                                        std::shared_ptr<DNode<T>> prev) {
    auto node = std::make_shared<DNode<T>>(data);
    node->prev = prev;
    return node;
  }
  bool is_empty() { return (head == nullptr); }
  void insert(T data) {
    if (is_empty()) {
      head = create_node(data);
      end = head;
      return;
    }
    auto cursor = head;
    while (cursor->next) {
      cursor = cursor->next;
    }
    cursor->next = create_node(data, cursor);
    end = cursor->next;
  }
  void insert(T data, int pos) {
    if (pos == 0) {
      auto node = create_node(data);
      node->next = head;
      head->prev = node;
      head = node;
      return;
    }
    auto cursor = head;
    for (int i = 0; i < pos; i++) {
      cursor = cursor->next;
      if (!cursor) {
        throw "Out of bound";
        return;
      }
    }
    auto node = create_node(data, cursor);
    node->next = cursor->next;
    cursor->next = node;
    if (node->next == nullptr) {
      end = node;
    }
  }
  void remove() {
    if (is_empty()) {
      throw "Cannot remove from empty list.";
    }
    auto cursor = head;
    if (cursor->next) {
      while (cursor->next->next) {
        cursor = cursor->next;
      }
    } else {
      head = nullptr;
      end = nullptr;
    }
    cursor->next = nullptr;
    end = cursor;
  }
  void remove(int index) {
    if (is_empty()) {
      throw "Cannot remove from empty list.";
    }
    auto cursor = head;
    for (int i = 0; i < index; i++) {
      if (cursor->next->next) {
        cursor = cursor->next;
      } else {
        throw "Out of bound";
      }
    }
    cursor->next = cursor->next->next;
    if (cursor->next) {
      cursor->next->prev = cursor;
    } else {
      end = cursor;
    }
  }

  void for_all(void (*callback)(T data), TraversalOption option = Forward) {
    if (option == Forward) {
      auto cursor = head;
      while (cursor) {
        callback(cursor->data);
        cursor = cursor->next;
      }
    } else {
      auto cursor = end;
      while (cursor) {
        callback(cursor->data);
        cursor = cursor->prev;
      }
    }
  }
};

template <typename T> void print(T a) { std::cout << a << "\t"; }

int main() {
  DoublyLinkedList<int> l(1);
  for (int i = 2; i < 10; i++) {
    l.insert(i);
  }
  l.for_all(print);
  std::cout << std::endl;
  l.for_all(print, DoublyLinkedList<int>::Backward);
  std::cout << std::endl;
  for (int i = 0; i < 5; i++) {
    l.remove();
  }
  l.for_all(print);
  std::cout << std::endl;
}
