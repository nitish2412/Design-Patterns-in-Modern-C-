#include<iostream>
using namespace std;


//target interface. client connect with target inteerface
class Printer{

    public:
        virtual void print()=0;
};

// Adaptee class
class LegacyPrinter{

    public:
        void printDocument(){

            cout<<"Document printed using legacy printer\n";
        }
};

//Adapter class
class PrinterAdapter:public Printer{

    private:
        LegacyPrinter legacyprinter;
    public:
        void print() override{
            legacyprinter.printDocument();
        }

};

int main(){
    cout<<"Hello World\n";
    Printer *printer = new PrinterAdapter();
    printer->print();
    return 0;
}