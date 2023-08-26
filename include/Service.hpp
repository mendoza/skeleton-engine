#ifndef SKELETON_SERVICE_HPP
#define SKELETON_SERVICE_HPP
#include "Logger.hpp"
namespace skeleton {
class Service {
  public:
	Service() {}
	~Service() {}

	skeleton::Logger *logger = skeleton::Logger::get_instance();
};
} // namespace skeleton
#endif