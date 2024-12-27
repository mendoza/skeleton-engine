#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include <skeleton/Core/Logger.hpp>
#include "guid.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace skeleton {
class Node {
public:
  Node() {
    uid = skeleton::guid::generate();
    this->name = "Node";
  }
  Node(std::string uid) : uid(uid) { this->name = "Node"; }

  virtual ~Node() {
    if (children.size() > 0) {
      std::string msg = "Parent " + name + " (" + uid + ") destroyed with " +
                        std::to_string(children.size()) + " children";
      skeleton::Logger::get_instance()->info(msg);
    } else {
      std::string msg = name + " (" + uid + ") destroyed";
      skeleton::Logger::get_instance()->info(msg);
    }
    for (auto child : children) {
      delete child;
    }
  }

  void add_child(Node *child) { children.push_back(child); }
  void remove_child(std::string uid) {
    // delete the child with the uid using vector erase-remove idiom
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [uid](Node *child) {
                                    if (child->get_uid() == uid) {
                                      delete child;
                                      return true;
                                    }
                                    return false;
                                  }),
                   children.end());
  }
  Node *get_child(std::string uid) {
    for (auto child : children) {
      if (child->get_uid() == uid) {
        return child;
      }
    }
    return nullptr;
  }

  Node *find_node(std::string uid) {
    if (this->uid == uid) {
      return this;
    }
    for (auto child : children) {
      auto node = child->find_node(uid);
      if (node != nullptr) {
        return node;
      }
    }
    return nullptr;
  }

  std::string get_uid() { return uid; }
  std::string get_name() { return name; }
  std::vector<Node *> children;

protected:
  std::string uid;
  std::string name;
};
} // namespace skeleton
#endif
