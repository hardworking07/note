#include <iostream>
using namespace std;

class Component
{
    public:
        virtual ~Component() {}
        virtual void operation() {}
};

class ConcreteComponet: public Component
{
    public:
        virtual void operation()
        {
            cout << "ConcreteComponet" << endl;
        }
};

class Decorator: public Component
{
    private:
        Component *pComponent_;
    public:
        void set(Component *ptr)
        {
            pComponent_ = ptr;
        }

        virtual void operation()
        {
            if (pComponent_ != NULL)
                pComponent_->operation();
        }
};

class ConcreteDecoratorA: public Decorator
{
    public:
        virtual void operation()
        {
            Decorator::operation();
            cout << "ConcreteDecoratorA ： dress clothes" << endl;
        }
};

class ConcreteDecoratorB: public Decorator
{
    public:
        virtual void operation()
        {
            Decorator::operation();
            cout << "ConcreteDecoratorB: dress T-bag" << endl;
        }
};


int main()
{
    Component *person = new ConcreteComponet();
    ConcreteDecoratorA *d1 = new ConcreteDecoratorA();
    ConcreteDecoratorB *d2 = new ConcreteDecoratorB();

    d1->set(person);
    d2->set(d1);
    d2->operation();

    cout << endl;
    cout << endl;
    d2->set(person);
    d1->set(d2);
    d1->operation();

    return 0;
}
