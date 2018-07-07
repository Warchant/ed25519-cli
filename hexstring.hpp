#ifndef ED25519_CLI_HEXSTRING_HPP
#define ED25519_CLI_HEXSTRING_HPP

#include <regex>
#include <string>

class Hexstring {
 private:
  std::regex reg{};
 public:
  explicit Hexstring(size_t length) {
    std::string r = "^[a-fA-F0-9]{" + std::to_string(2 * length) + "}$";
    this->reg = std::regex(r);
  }

  bool operator()(const std::string &arg) {
    return std::regex_match(arg, reg);
  }
};

#endif //ED25519_CLI_HEXSTRING_HPP
