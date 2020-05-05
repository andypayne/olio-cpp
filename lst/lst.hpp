#ifndef LST_H
#define LST_H

#include <ostream>
#include <string>
#include <cassert>
#include "type_to_string.hpp"

class ListException {};

template <typename T>
class Lst {
  private:
    struct Node {
      Node* next{nullptr};
      Node* prev{nullptr};
      T     item{};
      // Init empty
      Node() = default;
      // Init with an item
      explicit Node(const T& item_)
        : item{item_}
      {}
      // Init with an item and pointers
      Node(const T& item_, Node* next_, Node* prev_)
        : item{item_}
        , next{next_}
        , prev{prev_}
      {}
    };

    int   m_count{0};
    Node* m_head{nullptr};
    Node* m_tail{nullptr};

    // Prevent shallow copying
    Lst(const Lst&) = delete;
    Lst& operator=(const Lst&) = delete;

  public:
    typedef Node* pos;

    Lst() = default;

    ~Lst() {
      clear();
    }

    // O(1) count
    int count() const {
      return m_count;
    }

    bool is_empty() const {
      return (m_count == 0);
    }

    void clear() {
      while (!is_empty()) {
        remove_head();
      }
    }

    void insert_head(const T& item) {
      Node* node = new Node{item};
      node->next = m_head;
      node->prev = nullptr;
      if (m_head) {
        m_head->prev = node;
      }
      if (m_tail == nullptr) {
        m_tail = node;
      }
      m_head = node;
      ++m_count;
    }

    void remove_head() {
      assert(!is_empty());
      Node* newHead = m_head->next;
      if (newHead) {
        newHead->prev = nullptr;
      }
      delete m_head;
      m_head = newHead;
      --m_count;
    }

    void insert_tail(const T& item) {
      Node* node = new Node{item};
      node->next = nullptr;
      node->prev = m_tail;
      if (m_tail != nullptr) {
        m_tail->next = node;
      }
      if (m_head == nullptr) {
        m_head = node;
      }
      m_tail = node;
      ++m_count;
    }

    void remove_tail() {
      assert(!is_empty());
      Node* newTail = m_tail->prev;
      delete m_tail;
      if (newTail) {
        newTail->next = nullptr;
        m_tail = newTail;
      } else {
        m_head = nullptr;
        m_tail = nullptr;
      }
      --m_count;
    }

    T item_at(pos node) {
      assert(!is_empty());
      assert(node != nullptr);
      return node->item;
    }

    void insert_after(pos node, const T& item) {
      assert(node != nullptr);
      Node* newNode = new Node{item};
      newNode->next = node->next;
      newNode->prev = node;
      if (newNode->next != nullptr) {
        newNode->next->prev = newNode;
      } else {
        // If the current next is null, we must be inserting at the tail
        m_tail = newNode;
      }
      node->next = newNode;
      ++m_count;
    }

    void insert_before(pos node, const T& item) {
      assert(node != nullptr);
      Node* newNode = new Node{item};
      newNode->prev = node->prev;
      newNode->next = node;
      if (newNode->prev != nullptr) {
        newNode->prev->next = newNode;
      } else {
        // If the current prev is null, we must be inserting at the head
        m_head = newNode;
      }
      node->prev = newNode;
      ++m_count;
    }

    void remove_after(pos node) {
      asset(!is_empty());
      assert(node != nullptr);
      Node* removalNode = node->next;
      node->next = removalNode->next;
      if (node->next != nullptr) {
        node->next->prev = node;
      }
      delete removalNode;
      --m_count;
    }

    void remove_before(pos node) {
      asset(!is_empty());
      assert(node != nullptr);
      Node* removalNode = node->prev;
      node->prev = removalNode->prev;
      if (node->prev != nullptr) {
        node->prev->next = node;
      }
      delete removalNode;
      --m_count;
    }

    pos find(const T& item) {
      if (is_empty()) {
        return nullptr;
      }
      // Unsorted, so linear search
      // TODO: Add tail traversal as well?
      Node* node = m_head;
      while (node != nullptr) {
        if (node->item == item) {
          return node;
        }
        node = node->next;
      }
      return nullptr;
    }

    std::string to_string() const {
      std::string str;
      str = "[lst{" + std::to_string(m_count) + "}:";
      Node* node = m_head;
      while (node != nullptr) {
        str += " ";
        str += type_to_string(node->item);
        node = node->next;
      }
      str += "]";
      return str;
    }

    friend std::ostream& operator<<(std::ostream& os, const Lst<T>& list) {
      os << list.to_string();
      return os;
    }
};

#endif
