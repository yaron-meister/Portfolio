/*****************************************************************************
 * File name:   tree.h
 * Developer:   HRD7
 * Version: 	2
 * Date:        2019-03-17 15:44:24
 * Description: Tree display header
 *****************************************************************************/

#ifndef __TREE_H__
#define __TREE_H__

#include <string>       /* 	  string 	*/
#include <vector>       /* 	  vector	*/
#include <memory>       /*  shared_ptr	*/

namespace ilrd
{

class Entry
{
public:
    explicit Entry(const std::string& name);
    virtual ~Entry();

    const std::string& GetName() const;

    virtual void Display(unsigned depth = 0) const = 0;

    /* Find an Entry named <name> within the tree
     * Returns shared_ptr(0) on failure
     */
    virtual const std::shared_ptr<Entry>
        Find(const std::string& name) const = 0;

    Entry(const Entry& other) = delete;
    Entry& operator=(const Entry& other) = delete;

private:
    std::string m_name;
};

class File : public Entry
{
public:
    explicit File(const std::string& name);
    ~File() override;

    void Display(unsigned depth = 0) const override;
    const std::shared_ptr<Entry> Find(const std::string& name) const override;
};

class Directory : public Entry
{
public:
    static const std::shared_ptr<Entry> Create(const std::string& name);
    ~Directory() override;

    void Display(unsigned depth = 0) const override;
    const std::shared_ptr<Entry> Find(const std::string& name) const override;

private:
    std::vector<std::shared_ptr<Entry> > m_dir_data;
    explicit Directory(const std::string& name);
};

} /* namespace ilrd */

 

 
#endif     /* __TREE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
