class Base
{
public:
    Base(int num): m_num(num) { }
    virtual int GetNum() { return m_num; }
private:
    int m_num;
};