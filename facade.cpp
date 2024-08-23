#include<iostream>
using namespace std;

//subsystem1
class Engine{

    public:
        void start(){
            cout<<"Car started\n";
        }
        void stop(){
            cout<<"Car stopped\n";
        }

};

//subsystem2
class Light{

    public:
        void turnOn(){
            cout<<"Light turn on\n";
        }

        void turnOff(){
            cout<<"Light off\n";
        }
};

//facade 
class Car{

    private:
        Engine engine;
        Light light;
    public:
        void startCar(){
            engine.start();
            light.turnOn();
        }

        void stopCar(){
            light.turnOff();
            engine.stop();
            
        }

};

int main(){

    cout<<"Hello World\n";

    Car car;
    car.startCar();
    car.stopCar();

    return 0;
}