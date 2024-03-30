#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include <string>
#include <vector>

namespace skeleton {
class Node {
public:
  std::string tag;
  Node() {}
  Node(std::string tag) : tag(tag) {}

  virtual ~Node() {
    for (auto child : children) {
      delete child;
    }
  }

  void addChild(Node *child) { children.push_back(child); }
  std::string get_tag() { return tag; }

  std::vector<Node *> children;
};
} // namespace skeleton
#endif
