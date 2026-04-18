// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int MaxSize>
class TStack {
 private:
  T data[MaxSize];
  int top_index;

 public:
  TStack() : top_index(0) {}

  void push(const T& value) {
    if (top_index < MaxSize) {
      data[top_index++] = value;
    }
  }

  T pop() {
    if (top_index > 0) {
      return data[--top_index];
    }
    return T();
  }

  T top() const {
    if (top_index > 0) {
      return data[top_index - 1];
    }
    return T();
  }

  bool is_empty() const {
    return top_index == 0;
  }

  int get_size() const {
    return top_index;
  }
};

#endif  // INCLUDE_TSTACK_H_
