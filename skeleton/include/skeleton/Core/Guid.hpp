#ifndef SKELETON_GUID_HPP
#define SKELETON_GUID_HPP
#include <random>
#include <string>
namespace skeleton::core {
class Guid {
public:
  static std::string generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    const char *hex_chars = "0123456789abcdef";
    std::string guid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    for (int i = 0; i < 36; ++i) {
      if (guid[i] == 'x') {
        guid[i] = hex_chars[dis(gen)];
      } else if (guid[i] == 'y') {
        guid[i] = hex_chars[(dis(gen) & 0x3) |
                            0x8]; // Ensure the 3rd character is 8, 9, A, or B
      }
    }
    return guid;
  }
};
} // namespace skeleton::core
#endif
