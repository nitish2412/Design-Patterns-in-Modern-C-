#include<iostream>
using namespace std;

class Beverage{

    public:
        virtual string get_description()=0;
        virtual double cost()=0;

};

class CondimentDecorator:public Beverage{

    protected:
        Beverage *beverage;
    public:
        CondimentDecorator(Beverage *bev):beverage(bev)
        {}

        string get_description() override{

            return beverage->get_description();
        }

        double cost() override{
            return beverage->cost();
        }


};

class Expresso:public Beverage{

    public:
        string get_description() override{

            return "Expresso ";
        }
        double cost() override{

            return 50.0;
        }
};


class HouseBlend:public Beverage{

    public:
        string get_description() override{

            return "HouseBlend ";
        }
        double cost() override{

            return 100.0;
        }
};

class DarkRoast:public Beverage{

    public:
        string get_description() override{

            return "DarkRoast ";
        }
        double cost() override{

            return 40.0;
        }
};

class Decaf:public Beverage{

    public:
        string get_description() override{

            return "Decaf ";
        }
        double cost() override{

            return 80.0;
        }
};

class Mocha:public CondimentDecorator{

    public:
        Mocha(Beverage *bev):CondimentDecorator(bev){

        }
        string get_description() override{

            return beverage->get_description()+"with Mocha ";
        }

        double cost() override{
            return beverage->cost()+20;
        }
};

class Milk:public CondimentDecorator{

    public:
        Milk(Beverage *bev):CondimentDecorator(bev){

        }
        string get_description() override{

            return beverage->get_description()+"with Milk ";
        }

        double cost() override{
            return beverage->cost()+30;
        }
};

class Soy:public CondimentDecorator{

    public:
        Soy(Beverage *bev):CondimentDecorator(bev){

        }
        string get_description() override{

            return beverage->get_description()+"with Soy ";
        }

        double cost() override{
            return beverage->cost()+30;
        }
};

class Whip:public CondimentDecorator{

    public:
        Whip(Beverage *bev):CondimentDecorator(bev){

        }
        string get_description() override{

            return beverage->get_description()+"with Whip";
        }

        double cost() override{
            return beverage->cost()+30;
        }
};


int main(){
    cout<<"Hello World\n";
    cout<<"--------------------Testing code 1----------------\n";
    Beverage *beverage1= new Expresso();
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";
    beverage1=new CondimentDecorator(beverage1);
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";
    beverage1=new Mocha(beverage1);
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";
    beverage1=new Milk(beverage1);
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";
    beverage1=new Soy(beverage1);
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";
    beverage1=new Whip(beverage1);
    cout<<beverage1->get_description()<<" "<<beverage1->cost()<<"rs\n";

    cout<<"--------------------Testing code 2----------------\n";

    Beverage *expresso= new Expresso();
    Beverage *houseblend= new HouseBlend();
    Beverage *darkroast= new DarkRoast();
    Beverage *decaf= new Decaf();
    cout<<expresso->get_description()<<" "<<expresso->cost()<<"rs\n";
    cout<<houseblend->get_description()<<" "<<houseblend->cost()<<"rs\n";
    cout<<darkroast->get_description()<<" "<<darkroast->cost()<<"rs\n";
    cout<<decaf->get_description()<<" "<<decaf->cost()<<"rs\n";

    houseblend=new Milk(houseblend);
    cout<<houseblend->get_description()<<" "<<houseblend->cost()<<"rs\n";


    

    return 0;
}