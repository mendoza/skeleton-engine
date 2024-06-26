#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include "Logger.hpp"
#include "guid.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace skeleton {
class Node {
public:
  Node() {
    tag = skeleton::guid::generate();
    this->name = "Node";
  }
  Node(std::string tag) : tag(tag) { this->name = "Node"; }

  virtual ~Node() {
    if (children.size() > 0) {
      std::string msg = "Parent " + name + " (" + tag + ") destroyed with " +
                        std::to_string(children.size()) + " children";
      skeleton::Logger::get_instance()->info(msg);
    } else {
      std::string msg = name + " (" + tag + ") destroyed";
      skeleton::Logger::get_instance()->info(msg);
    }
    for (auto child : children) {
      delete child;
    }
  }

  void add_child(Node *child) { children.push_back(child); }
  void remove_child(std::string tag) {
    // delete the child with the tag using vector erase-remove idiom
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [tag](Node *child) {
                                    if (child->get_tag() == tag) {
                                      delete child;
                                      return true;
                                    }
                                    return false;
                                  }),
                   children.end());
  }
  Node *get_child(std::string tag) {
    for (auto child : children) {
      if (child->get_tag() == tag) {
        return child;
      }
    }
    return nullptr;
  }

  Node *find_node(std::string tag) {
    if (this->tag == tag) {
      return this;
    }
    for (auto child : children) {
      auto node = child->find_node(tag);
      if (node != nullptr) {
        return node;
      }
    }
    return nullptr;
  }

  std::string get_tag() { return tag; }
  std::vector<Node *> children;

protected:
  std::string tag;
  std::string name;
};
} // namespace skeleton
#endif
