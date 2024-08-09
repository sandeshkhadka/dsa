#include <iostream>
#include <vector>

template <typename T> class Queue {
private:
  std::vector<T> items;
  int front, rear;

public:
  Queue() {
    front = -1;
    rear = 0;
  }
  void enqueue(T data) {
    items.push_back(data);
    rear++;
    if (front == -1) {
      front++;
    }
  }
  T dequeue() {
    if (is_empty()) {
      std::cout << "Cannout dequeue empty queue" << std::endl;
    }
    T dequeued = items[front];
    front++;
    return dequeued;
  }

  bool is_empty() {
    if (front == -1) {
      return true;
    }
    if (front >= rear) {
      return true;
    }
    return false;
  }
  /*
   * calls calback function for each data value in the queue
   * traverses in FIFO
   */
  void for_all(void (*callback)(T data)) {
    if (is_empty()) {
      return;
    }
    for (int i = front; i < rear; i++) {
      callback(items[i]);
    }
  }
};

template <typename T> void print(T a) { std::cout << a << "\t"; }
int main() {
  Queue<int> l;
  for (int i = 2; i < 10; i++) {
    l.enqueue(i);
  }
  l.for_all(print);
  std::cout << std::endl;
  l.for_all(print);
  std::cout << std::endl;
  for (int i = 0; i < 5; i++) {
    l.dequeue();
  }
  l.for_all(print);
  std::cout << std::endl;
}
