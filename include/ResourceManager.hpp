
#ifndef SKELETON_RESOURCE_MANAGER_HPP
#define SKELETON_RESOURCE_MANAGER_HPP
#include "Resource.hpp"
#include "Service.hpp"
#include <SDL.h>
#include <map>
#include <string>
namespace skeleton {
class ResourceManager : public Service {
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
