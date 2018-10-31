//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_STRINGS_H
#define BLACKENGINE_STRINGS_H

#include <Exported.h>
#include <string>
#include <vector>

namespace black {

    /**
     * Helper methods for working with strings.
     * Actually implemented with boost::algorithm library
     */
    class BLACK_EXPORTED Strings {
    public:
        static bool IsEndsWith(std::string str, std::string ending);

        static std::string ToUpper(std::string str);
        static std::string ToLower(std::string str);

        static std::string Trim(std::string str);
        static std::string TrimLeft(std::string str);
        static std::string TrimRight(std::string str);

        static std::string ReplaceFirst(std::string str, std::string pattern, std::string replacement);
        static std::string ReplaceLast(std::string str, std::string pattern, std::string replacement);
        static std::string EraseAll(std::string str, std::string pattern);

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
        static std::vector<std::string> Split(std::string str, std::string delimiter);
    };

}


#endif //BLACKENGINE_STRINGS_H
