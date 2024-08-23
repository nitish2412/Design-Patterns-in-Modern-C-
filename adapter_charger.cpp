#include<iostream>
using namespace std;

//Define the Target Interface.
//This is the interface that the existing charging system expects.
class USPlug{

    public:
        virtual void connectToUSSocket()=0;
        virtual ~USPlug() = default;
};

//Implement the Existing Class. This class represents a device that uses a US plug.

class USPhoneCharger:public USPlug{

    public:
        void connectToUSSocket() override{
            cout<<"Phone is charging using USPhone charger.\n";
        }
};

// Define the New Interface. This interface is used by devices with European plugs.

class EuropeanPlug{

    public:
        virtual void connectToEuropeanSocket() = 0;
        virtual ~EuropeanPlug() =default;
};

// Implement the New Class. This class represents a device that uses a European plug.

class EuropeanLaptopCharger : public EuropeanPlug {
public:
    void connectToEuropeanSocket() override {
        std::cout <<"European Laptop Charger connected to European socket.\n";
    }
};

class ChineeseLaptopCharger {
public:
    void connectToEuropeanSocket(){
        std::cout <<"Chineese Laptop Charger connected to Chineese socket.\n";
    }
};

//implement adapter class

class PlugAdapter:public USPlug{

    private:
        EuropeanPlug *europeandevice;
    public:
        PlugAdapter(EuropeanPlug* device) : europeandevice(device) {}
        void connectToUSSocket() override{
            cout << "Adapter converts US socket to European socket.\n";
            europeandevice->connectToEuropeanSocket();
        }

};


class ChineesePlugAdapter:public USPlug{

    private:
        ChineeseLaptopCharger chineesedevice;
    public:
        void connectToUSSocket() override{
            cout << "Adapter converts Chineese socket to European socket.\n";
            chineesedevice.connectToEuropeanSocket();
        }

};


int main(){
    cout<<"Hello world\n";
    cout<<"-----------------without adapter------------------\n";
    USPlug *plug = new USPhoneCharger();
    plug->connectToUSSocket();

    EuropeanPlug *plug1 = new EuropeanLaptopCharger();
    plug1->connectToEuropeanSocket();

    cout<<"-----------------with adapter------------------\n";

    EuropeanPlug *laptopcharger = new EuropeanLaptopCharger();
    USPlug *uscharger = new PlugAdapter(laptopcharger);
    uscharger->connectToUSSocket();

    cout<<"-----------------with adapter without new adaptee interface------------------\n";
    USPlug *uscharger1 = new ChineesePlugAdapter();
    uscharger1->connectToUSSocket();

    return 0;
}