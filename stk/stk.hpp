#ifndef STK_H
#define STK_H

#include <ostream>
#include <exception>
#include <vector>
#include <algorithm>

//class StackOverflowException : public std::runtime_error {};
class StackOverflowException {};
class StackUnderflowException {};

constexpr int kEmptyStack = -1;

template <typename T>
class Stk {
  private:
    // TODO: Back with something else
    std::vector<T> m_arr;
    int            m_top;    // kEmptyStack when empty

  public:
    // `explicit` to prevent implicit conversions from int
    explicit Stk(int maxSz)
      : m_top{kEmptyStack}
    {
      m_arr.reserve(maxSz);
    }

    void push(const T& el) {
      if (size() >= max_size()) {
        // TODO: Reallocate
        throw StackOverflowException{};
      }
      m_top++;
      m_arr.push_back(el);
    }

    T pop() {
      if (!is_empty()) {
        T topEl = m_arr[m_top];
        m_top--;
        return topEl;
      }
      throw StackUnderflowException{};
    }

    const T& top() const {
      if (!is_empty()) {
        return m_arr[m_top];
      }
      // TODO: Should an exception be thrown?
      throw StackOverflowException{};
    }

    // Top with write access
    T& writable_top() {
      if (!is_empty()) {
        return m_arr[m_top];
      }
      // TODO: Should an exception be thrown?
      throw StackOverflowException{};
    }

    int size() const {
      return (m_top + 1);
    }

    bool is_empty() const {
      return size() == 0;
    }

    // This won't work as a max since the vector can grow beyond this.
    int max_size() const {
      return m_arr.capacity();
    }

    // This could be more complicated for supporting more types T
    void clear() {
      m_top = kEmptyStack;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stk<T>& stack) {
      os << "[stk:";
      for (int i = stack.m_top; i >= 0; i--) {
        os << " " << stack.m_arr[i];
      }
      os << " ]" << std::endl;
      return os;
    }
};


#endif
