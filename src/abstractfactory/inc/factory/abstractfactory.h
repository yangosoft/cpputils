#ifndef FACTORY3_H
#define FACTORY3_H

#include <map>
#include <vector>
#include <utility>
#include <memory>

namespace CppUtils {



/**
 * @todo write docs
 */
template<typename TKEY, typename TCREATED>
class AbstractFactory
{

public:
    using fCreate = std::function<TCREATED (const TKEY&)>;


    AbstractFactory() {}
    virtual ~AbstractFactory() {}

    bool add(const TKEY &key, fCreate createProc) {
        MapCIt it = mapFactory.find(key);
        if (it != mapFactory.end()) return false;

        mapFactory[key].createProc = createProc;
        

        return true;
    }

    bool exists(const TKEY &key) {
        return (mapFactory.find(key) != mapFactory.end() );
    }

    

    TCREATED createInstance(const TKEY &key) {
        MapIt it = mapFactory.find(key);
        if (it == mapFactory.end()) return nullptr;

        auto td = it->second;
        if (!td.createProc) { 
            return nullptr;
        }

        TCREATED new_class_created = td.createProc(key);

        return new_class_created;
    }

    


protected:


    struct FactoryData {
        fCreate createProc;
    };

//     typedef typename std::map<TKEY, FactoryData>::const_iterator MapCIt;
//     typedef typename std::map<TKEY, FactoryData>::iterator MapIt;
    using MapIt = typename std::map<TKEY, FactoryData>::iterator;
    using MapCIt = typename std::map<TKEY, FactoryData>::const_iterator;
    


    std::map<TKEY, FactoryData> mapFactory;


};

}

#endif // FACTORY2_H
