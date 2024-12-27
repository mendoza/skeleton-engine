#ifndef SKELETON_SERVICE_HPP
#define SKELETON_SERVICE_HPP
#include <skeleton/core/Logger.hpp>
#include <string>
namespace skeleton::core {
class Service {
public:
  Service() = default;
  virtual ~Service() = default;

protected:
  skeleton::core::Logger *logger = skeleton::core::Logger::get_instance();
  std::string tag;
};
} // namespace skeleton::core
#endif
