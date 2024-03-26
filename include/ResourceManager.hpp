
#ifndef SKELETON_RESOURCE_MANAGER_HPP
#define SKELETON_RESOURCE_MANAGER_HPP
#include "resource.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <string>
namespace skeleton {
class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();
  void add(Resource *resource);
  Resource *get(std::string name);

private:
  std::map<std::string, Resource *> resources;
};
} // namespace skeleton
#endif
