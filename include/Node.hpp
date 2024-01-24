#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include <vector>

namespace skeleton {
class Node {
public:
  virtual void update(float delta_time) = 0;
  void add_child(Node *child) { children.push_back(child); }

protected:
  std::vector<Node *> children;
};
} // namespace skeleton
#endif