/**********************************
 * 简单工厂模式
 * 采用了封装、继承、多态，开放-封闭原则
 * 当我要新增一种运算的时候，只要新增一个类，并在简单工厂类中加入相应运算符
 * UML: 工厂类 关联 Operator
 * 可维护，可扩展，可复用，灵活
 **********************************/
#include <string>
#include <stdlib.h>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

namespace DP
{
    class Operator
    {
        public:
            string numA;
            string numB;

        public:
            virtual double calculate() = 0;
            bool setNumA(const string &num);
            bool setNumB(const string &num);
    };

    bool Operator::setNumA(const string &num)
    {
        numA = num;
    }

    bool Operator::setNumB(const string &num)
    {
        numB = num;
    }

    class OperatorAdd : public Operator
    {
        public:
            virtual double calculate()
            {
                return atof(numA.c_str()) + atof(numB.c_str());
            }
    };

    class OperatorMinus:public Operator
    {
        virtual double calculate()
        {
        return atof(numA.c_str()) - atof(numB.c_str());
        }
    };

    //简单工厂类
    class OperatorFactory
    {
        public:
            static Operator * createOperatorObj(const string &op)
            {
                char c = op[0];
                switch(c) 
                {
                    case '+': return new OperatorAdd();
                    case '-': return new OperatorMinus();
                    default: return NULL;
                }
            }
    };

}// end of namespace DP

int main()
{
    string op;
    cin >> op;
    DP::Operator *obj = DP::OperatorFactory::createOperatorObj(op);
    string numA, numB;
    cin >> numA >> numB;
    obj -> setNumA(numA);
    obj -> setNumB(numB);
    double result = obj -> calculate();
    cout << result << endl;

    return 0;
}
