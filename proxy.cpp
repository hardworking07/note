#include <iostream>
#include <string>
using namespace std;

class Subject
{
    public:
        virtual ~Subject() {}
        void giveGift() {}
        void giveFlower() {}
};

class Pusuit: public Subject
{
    public:
        Pusuit(const string &name):girl(name) {}

        void giveGift()
        {
            cout << "Pusuit giveGift: " << girl << endl;
        }

        void giveFlower()
        {
            cout << "Pusuit giveFlower" << girl << endl;
        }

    private:
        string girl;
};

class Proxy: public Subject
{
    public:
        Proxy(const string &name):girl(name)
    {
        pPusuit = new Pusuit(girl);
    }

        void giveGift()
        {
            cout << "Proxy giveGift" << endl;
            pPusuit->giveGift();
        }

        void giveFlower()
        {
            cout << "Proxy giveFlower" << endl;
            pPusuit->giveFlower();
        }

    private:
        string girl;
        Pusuit *pPusuit;
};

int main()
{
    Proxy daili("jiaojiao");
    daili.giveGift();
    daili.giveFlower();

    return 0;
}

