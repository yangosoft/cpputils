#ifndef BASEMAKER_H
#define BASEMAKER_H

#include <memory>

/**
 * @todo write docs
 */

namespace CppUtils
{

class IBase
{
public:
    virtual std::string type() = 0;
    virtual ~IBase(){};
};

class IBaseMaker
{
public:
    virtual std::unique_ptr<IBase> create(const std::string& name) const = 0;
    virtual ~IBaseMaker(){};
};

template <typename T>
class BaseMaker : public IBaseMaker
{
public:
    virtual std::unique_ptr<IBase> create(const std::string& node) const
    {

        return std::unique_ptr<IBase>(new T(node));
    }
};
}

#endif  // BASEMAKER_H
