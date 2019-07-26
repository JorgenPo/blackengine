//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_STRINGS_H
#define BLACKENGINE_STRINGS_H

#include <common/Exported.h>
#include <string>
#include <vector>

namespace black {

/**
 * Helper methods for working with strings.
 * Actually implemented with boost::algorithm library
 */
class BLACK_EXPORTED Strings {
public:
  static bool IsEndsWith(const std::string& str, const std::string& ending);

  static std::string ToUpper(const std::string& str);
  static std::string ToLower(const std::string& str);

  static std::string Trim(const std::string& str);
  static std::string TrimLeft(const std::string& str);
  static std::string TrimRight(const std::string& str);

  static std::string ReplaceFirst(const std::string& str, const std::string& pattern, const std::string& replacement);
  static std::string ReplaceLast(const std::string& str, const std::string& pattern, const std::string& replacement);
  static std::string EraseAll(const std::string& str, const std::string& pattern);

  /**
   * Split the string into parts for a given delimiter.
   * Delimiter can contain more than one delimiter, coma separated, for example:
   * delimiter can be equal that string "\t,|,s" to split string using \t, | and s as
   * delimiters.
   *
   * @param str
   * @param delimiter
   * @return
   */
  static std::vector<std::string> Split(std::string str, const std::string& delimiter);
};

}

#endif //BLACKENGINE_STRINGS_H
