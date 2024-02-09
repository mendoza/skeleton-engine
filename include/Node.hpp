#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace skeleton {
template <typename T> class Node {
public:
    std::string tag;

  Node(std::string tag) : tag(tag) {}

  virtual ~Node() {
    for (auto child : children) {
      delete child;
    }
  }

  void addChild(T *child) { children.push_back(child); }

  std::vector<T *> children;
};
} // namespace skeleton
#endif
