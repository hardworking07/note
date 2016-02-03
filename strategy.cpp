/**************************************************
 *
 * Author: Jack Yao
 * Mail  : yaolongyun2012@gmail.com
 * File  : strategy.cpp
 * Date  : 2015-12-29 07:10:03
 * Last modified: 2016-01-31 19:13:26
 *
 * Tag: 策略模式
 * Description: 如果采用简单工厂模式，每次新增一个策略，就要重新编绎工厂类，而策略模式就不用了。
 * UML：一个抽象基类，具体的策略类继承它;  Context 聚合 Strategy
 **************************************************/
#include <iostream>
#include <string>
using namespace std;

namespace DP {
    class Strategy
    {
        public:
            virtual string exe() = 0;
            virtual ~Strategy() {}
    };

    class StrategyA: public Strategy
    {
        public:
            ~StrategyA() {}

            virtual string exe()
            {
                cout << "sell by discount" << endl;
            }
    };

    class StrategyB: public Strategy
    {
        public:
            ~StrategyB() {}

            virtual string exe()
            {
                cout << "满500减100" << endl;
            }
    };

    class Context
    {
        public:
            Context(Strategy *s):strategyPtr_(s) {}
            ~Context()
            {
                if (strategyPtr_)
                {
                    delete strategyPtr_;
                    strategyPtr_ = NULL;
                }
            }

            string exe()
            {
                strategyPtr_->exe();
            }
        
        private:
            Strategy *strategyPtr_;
    };
}

int main()
{
    DP::Strategy *ptrStra = new DP::StrategyB();
    DP::Context context(ptrStra);
    context.exe(); 

    return 0;
}
