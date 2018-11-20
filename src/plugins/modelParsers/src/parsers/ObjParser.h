//
// Created by popof on 05.11.2018.
//

#ifndef BLACKENGINE_OBJPARSER_H
#define BLACKENGINE_OBJPARSER_H

#include <CommonHeaders.h>
#include <util/ModelParser.h>

namespace black {

    class ObjParser : public ModelParser {
        bool isObjParsed;
        std::shared_ptr<ModelComponent> model;

    public:
        ObjParser();

        std::shared_ptr<ModelParser> copy() override;

        void parse(std::string file) override;

        bool isParsed() override;

        std::shared_ptr<ModelComponent> getModel() override;
    };
}


#endif //BLACKENGINE_OBJPARSER_H
