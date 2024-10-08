#include <iostream>
#include <vector>

template <typename T> class Stack {
private:
  std::vector<T> items;
  int top;

public:
  Stack() { top = -1; }

  void push(T data) {
    top++;
    items.push_back(data);
  }
  /*
   * pop top element from stack
   */
  T pop() {
    if (is_empty()) {
      std::cout << "Cannont pop on empty stack";
      exit(1);
    }
    T popped = items.back();
    items.pop_back();
    top--;
    return popped;
  }
  bool is_empty() { return (top < 0); }
  /*
   * calls callback for each data value in stack
   * traverses in stack in LIFO
   */
  void for_all(void (*callback)(T data)) {
    if (is_empty()) {
      return;
    }
    for (int i = top; i >= 0; i--) {
      callback(items[i]);
    }
  }
  /*
   * retrive top element without popping it
   */
  T peek() { return items[top]; }
};
template <typename T> void print(T a) { std::cout << a << "\t"; }
int main() {

  Stack<int> s;
  for (int i = 0; i < 10; i++) {
    s.push(i);
  }
  s.for_all(print);
  std::cout << std::endl;
  for (int i = 0; i < 5; i++) {
    s.pop();
  }
  s.for_all(print);
  std::cout << std::endl;
}
