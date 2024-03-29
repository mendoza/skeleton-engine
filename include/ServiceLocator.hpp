#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP
#include "Service.hpp"
#include <memory>
#include <type_traits>
#include <unordered_map>
namespace skeleton {
class SkeletonRenderer;
class SkeletonSceneManager;
class ServiceLocator {

  public:
	template <typename ServiceType>
	static void provide(std::unique_ptr<ServiceType> new_service) {
		static_assert(std::is_base_of<Service, ServiceType>::value,
					  "Typename T must inherit skeleton::Service");
		services[typeid(ServiceType).hash_code()] = std::move(new_service);
	}

	template <typename ServiceType> static ServiceType *get() {
		static_assert(std::is_base_of<Service, ServiceType>::value,
					  "Typename T must inherit skeleton::Service");
		return static_cast<ServiceType *>(
			services[typeid(ServiceType).hash_code()].get());
	}

	void static shutdown_all_services() { services.clear(); }

  private:
	inline static std::unordered_map<size_t, std::unique_ptr<Service>> services;
};
} // namespace skeleton

#endif