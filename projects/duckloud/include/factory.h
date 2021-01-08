/*****************************************************************************
 * File name:   factory.h
 * Developer:   HRD07
 * Version: 	1
 * Date:        2019-04-07 14:42:44
 * Description: Factory header
 *****************************************************************************/

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <unordered_map> /* std::unordered_map */
#include <functional>    /* std::function      */
#include <memory>        /* std::unique_ptr    */
#include <exception>     /* std::runtime_error */

namespace ilrd
{

template <typename Base, typename Key, typename Params>
class Factory
{
public:
    // typedef of cpp
    using FactoryFunc = std::function<std::unique_ptr<Base>(Params)>;

    Factory() = default;

    // Un-copyable (Un-moveable too)
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    std::unique_ptr<Base> Create(const Key& key, Params params);
    std::shared_ptr<Base> CreateShared(const Key& key, Params params);
    // Adding for an already created <key> results to a Failure
    bool Add(const Key& key, FactoryFunc creator);

    class BadKey : public std::logic_error
    {
        public:
        BadKey(const char* what_arg);
    };

    class BadCreate : public std::runtime_error
    {
        public:
        BadCreate(const char* what_arg);
    };

private:
    std::unordered_map<Key, FactoryFunc> m_map;  
};

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
/* Class Factory */  
/******************************************************************************/
template <typename Base, typename Key, typename Params>
bool 
Factory<Base, Key, Params>::
            Add(const Key& key, Factory<Base, Key, Params>::FactoryFunc creator)
{
    try
    {
        bool ret = m_map.insert({key, creator}).second;
        if (false == ret) 
        {
            m_map[key] = creator;
        }

        return (ret);
    }
    catch(const std::bad_alloc& e)
    {
        throw std::bad_alloc();
    }
    catch(const std::exception& e)
    {
        throw std::exception();
    }
}

/******************************************************************************/
template <typename Base, typename Key, typename Params>
std::unique_ptr<Base>
Factory<Base, Key, Params>::Create(const Key& key, Params params)
{
    auto search = m_map.find(key);

    if (m_map.end() == search)
    {
        throw BadKey("Key wasn't found");
    }

    try
    {
        return (search->second(params));
    }
    catch(const std::exception& e)
    {
        throw BadCreate("creator");
    }
}

/******************************************************************************/
template <typename Base, typename Key, typename Params>
std::shared_ptr<Base> 
Factory<Base, Key, Params>::CreateShared(const Key& key, Params params)
{
    return (std::move(Create(key, params)));
}

/******************************************************************************/
/* Class BadKey */
/******************************************************************************/
template <typename Base, typename Key, typename Params>
Factory<Base, Key, Params>::BadKey::BadKey(const char* what_arg) : 
                                                           logic_error(what_arg)
{}

/******************************************************************************/
/* Class BadCreate */
/******************************************************************************/
template <typename Base, typename Key, typename Params>
Factory<Base, Key, Params>::BadCreate::BadCreate(const char* what_arg) :
                                                         runtime_error(what_arg)
{}



} // namespace ilrd

#endif     /* __FACTORY_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
