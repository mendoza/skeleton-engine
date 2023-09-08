#ifndef SKELETON_SERVICE_HPP
#define SKELETON_SERVICE_HPP
#include "Logger.hpp"
#include <string>
namespace skeleton {
class Service {
  public:
	Service() = default;
	virtual ~Service() = default;

  protected:
	skeleton::Logger *logger = skeleton::Logger::get_instance();
	std::string tag;
};
} // namespace skeleton
#endif