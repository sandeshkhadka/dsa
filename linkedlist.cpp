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

template <typename T> class LinkedList {
private:
  std::shared_ptr<struct Node<T>> head;

  std::shared_ptr<struct Node<T>> create_node(T data) {
    auto node = std::make_shared<struct Node<T>>(data);
    return node;
  }

  public : LinkedList(T data) {
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

template <typename T> void print(T a) { std::cout << a << "\t"; }

int main() {
  LinkedList<int> l(1);
  l.insert(2);
  l.insert(3);
  l.for_all(print);
  std::cout << std::endl;
  l.insert(222222, 2);
  l.insert(333, 3);
  l.for_all(print);
  std::cout << std::endl;
  l.remove();
  l.for_all(print);
  std::cout << std::endl;
  l.remove(0);
  l.remove(1);
  l.for_all(print);
  std::cout << std::endl;
  l.remove();
  l.for_all(print);
  std::cout << std::endl;
  l.remove();
  l.for_all(print);
  std::cout << std::endl;
}
