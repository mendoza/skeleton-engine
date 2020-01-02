#pragma once
#include <sol.hpp>
#include <string>
#include <vector>
namespace Skeleton {
std::vector<std::string> getTableKeys(sol::table tab) {
  std::vector<std::string> retVal;
  for (const auto &key_value_pair : tab) {
    sol::object key = key_value_pair.first;
    // sol::object value = key_value_pair.second;
    std::string k = key.as<std::string>();
    // sol::type t = value.get_type();
    retVal.push_back(k);
    // inspect key/value, manipulate as you please
  }
  return retVal;
}

// ecs::Entity *loadEntity(sol::table entityTable) {
void loadEntity(sol::table entityTable) {
  std::vector<std::string> keys = getTableKeys(entityTable);
  for (std::string key : keys) {
    std::cout << "Esta Entidada tiene un componente: " << key << std::endl;
    std::vector<std::string> keyKeys = getTableKeys(entityTable[key]);
    for (std::string keyKey : keyKeys) {
    std::cout << "\tEste Componente tiene un atributo: " << keyKey << std::endl;
    }
  }
}
} // namespace Skeleton