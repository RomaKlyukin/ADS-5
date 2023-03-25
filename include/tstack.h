// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
const int size = 100;
template<typename T, const int size>
class TStack {
 private:
  T* arr;
  int top;
  
 public:
  TStack() {
    arr = new T[size];
    top = -1;
  }
  T get() const {
    return arr[top];
  }
  bool isEmpty() const {
    return top == -1;
  }
  bool isFull() const {
    return top == size-1;
  }
  void pop() {
    if (top >= 0)
      top--;
  }
  void push(T item) {
    if (top < size-1)
      arr[++top] = item;
  }
  ~TStack() {
    delete[] arr;
  }
};

#endif  // INCLUDE_TSTACK_H_
