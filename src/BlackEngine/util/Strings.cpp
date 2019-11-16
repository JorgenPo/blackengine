//
// Created by popof on 28.10.2018.
//

#include "Strings.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

namespace black {

bool Strings::IsEndsWith(const std::string& str, const std::string& ending) {
  return iends_with(str, ending);
}

std::string Strings::ToUpper(const std::string& str) {
  return to_upper_copy(str);
}

std::string Strings::ToLower(const std::string& str) {
  return to_lower_copy(str);
}

std::string Strings::Trim(const std::string& str) {
  return trim_copy(str);
}

std::string Strings::TrimLeft(const std::string& str) {
  return trim_left_copy(str);
}

std::string Strings::TrimRight(const std::string& str) {
  return trim_right_copy(str);
}

std::string Strings::ReplaceFirst(const std::string& str, const std::string& pattern, const std::string& replacement) {
  return replace_first_copy(str, pattern, replacement);
}

std::string Strings::ReplaceLast(const std::string& str, const std::string& pattern, const std::string& replacement) {
  return replace_last_copy(str, pattern, replacement);
}

std::string Strings::EraseAll(const std::string& str, const std::string& pattern) {
  return erase_all_copy(str, pattern);
}

std::vector<std::string> Strings::Split(std::string str, const std::string& delimiter) {
  std::vector<std::string> splitVector;
  split(splitVector, str, is_any_of(delimiter));

  return splitVector;
}

}