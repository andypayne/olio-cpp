#include <string>

template <typename T>
std::string type_to_string(T item) {
  return std::to_string(item);
}

std::string type_to_string(const char* item) {
  return item;
}

