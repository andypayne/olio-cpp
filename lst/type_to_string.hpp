#include <string>

// TODO: Consider using the namespace technique described here:
// https://stackoverflow.com/a/37425306

template <typename T>
std::string type_to_string(T item) {
  return std::to_string(item);
}

std::string type_to_string(const char* item) {
  return item;
}

