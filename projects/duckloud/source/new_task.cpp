#include <iostream>

#include "factory.h"
#include "handleton.h"
#include "base.h"

using namespace ilrd;



class Task1: public Base
{
public:
    Task1(int num): Base(num), m_num(num)
    {}

    int GetNum()
    {
    	return m_num;
	}

private:
    int m_num;
};

void FactoryUpdate() __attribute__((constructor));


void FactoryUpdate()
{
    Factory<Base,std::string,int>* factory = Handleton<Factory<Base,std::string,int>>::GetInstance();
    std::cout << "new_task.so added\n";
    factory->Add("Task1", 
    			 [](int num){ return std::unique_ptr<Base>( new Task1(num)); });
}