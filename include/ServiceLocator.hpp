#ifndef SKELETON_SERVICE_LOCATOR_HPP
#define SKELETON_SERVICE_LOCATOR_HPP
#include <Service.hpp>
#include <memory>
#include <type_traits>
#include <unordered_map>
namespace skeleton {
class ServiceLocator {
  private:
	static std::unordered_map<size_t, std::unique_ptr<Service>> services;

  public:
	template <typename ServiceType>
	static void Provide(std::unique_ptr<ServiceType> new_service) {
		static_assert(std::is_base_of<Service, ServiceType>::value,
					  "Typename T must inherit skeleton::Service");
		services[typeid(ServiceType).hash_code()] = std::move(new_service);
	}

	template <typename ServiceType> static ServiceType *Get() {
		static_assert(std::is_base_of<Service, ServiceType>::value,
					  "Typename T must inherit skeleton::Service");
		return static_cast<ServiceType *>(
			services[typeid(ServiceType).hash_code()].get());
	}
};
} // namespace skeleton

#endif