#ifndef FACTORY2_H
#define FACTORY2_H

#include <map>
#include "basemaker.h"

#include <exception>
#include <stdexcept>

namespace CppUtils
{

/**
 * @todo write docs
 */
class Factory
{
public:
    static Factory& Instance()
    {
        static Factory factory;
        return factory;
    };
    void registerMaker(const std::string& key, IBaseMaker* maker)
    {
        if (holderMakers.find(key) != holderMakers.end()) {
            throw new std::invalid_argument("Multiple makers for given key!");
        }
        holderMakers[key] = maker;
    };
    std::unique_ptr<IBase> create(const std::string& node) const
    {
        std::string key(node);
        auto i = holderMakers.find(key);
        if (i == holderMakers.end()) {
            throw new std::invalid_argument("Unrecognized object type!");
        }
        IBaseMaker* maker = i->second;
        return maker->create(node);
    };

private:
    std::map<std::string, IBaseMaker*> holderMakers;
};
}

#endif  // FACTORY2_H
