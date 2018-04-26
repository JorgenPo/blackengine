//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_MODELPARSER_H
#define BLACKENGINE_MODELPARSER_H

#include <core/render/Mesh.h>
#include <memory>
#include <fstream>
#include <core/Copyable.h>
#include <core/Exception.h>

namespace black::parsers {
    class ParseException : public Exception {
    public:
        ParseException(const std::string &message) : Exception(message) {}
    };

    class WrongModelFormatException : public Exception {
    public:
        explicit WrongModelFormatException() : Exception("Model file is corrupted") {}
    };
    /**
     * Abstract class for all model parsers
     */
    class ModelParser : public Copyable {
    public:
        /**
         * Parse model file and return model object
         * @param file File stream. If file not found exception will be thrown
         *
         * @throws FileNotFoundException If file was not opened successfuly
         * @return Loaded Model if all is ok
         */
        virtual void parse(std::string file, std::vector<float> &vertices, std::vector<unsigned int> &indices,
                           std::vector<float> &textureCoords) = 0;

        virtual int getPolygonLength() = 0;

        virtual std::string getTextureName() = 0;

        ModelParser *copy() const override = 0;
    };
}


#endif //BLACKENGINE_MODELPARSER_H
