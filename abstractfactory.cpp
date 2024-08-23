#include<iostream>
using namespace std;

// abstract product A
class Button{
    public:
        virtual void paint() = 0;
        virtual ~Button(){
            cout<<"Buttone obj deleted\n";
        }
};
//concreate product A1
class WindowsButton:public Button{
    public:
        void paint() override{
            cout<<"product of Button: windowsButton\n";
        }
};

//concreate product A2
class MacOsButton:public Button{
    public:
        void paint() override{
            cout<<"product of Button: MacosButton \n";
        }
};

//Abstract product B

class CheckBox{

    public:
        virtual void paint()=0;
        virtual ~CheckBox(){
             cout<<"Checkbox obj deleted\n";
        }
};


//concreate product B1
class WindowsCheckBox:public CheckBox{
    public:
        void paint() override{
            cout<<"product of Chcekbox: windowsCheckbox\n";
        }
};

//concreate product B2
class MacOsCheckBox:public CheckBox{
    public:
        void paint() override{
            cout<<"product of Checkbox: MacosCheckBox \n";
        }
};

//Abstract Factory

class GUIFactory{
    public:
        virtual Button* createButton()=0;
        virtual CheckBox* createCheckBox()=0;
        virtual ~GUIFactory(){
             cout<<"GUI obj deleted\n";
        }
};

// Concrete Factory 1
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WindowsButton();
    }
    CheckBox* createCheckBox(){
        return new WindowsCheckBox();
    }
};

// Concrete Factory 2
class MacosFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacOsButton();
    }
    CheckBox* createCheckBox(){
        return new MacOsCheckBox();
    }
};

// Client
class Application {
private:
    GUIFactory* factory;
    Button* button;
    CheckBox* checkbox;

public:
    Application(GUIFactory* f) : factory(f) {
        button = factory->createButton();
        checkbox = factory->createCheckBox();
    }

    void paint() {
        button->paint();
        checkbox->paint();
    }

    ~Application() {
         cout<<"Application obj deleted\n";
        delete button;
        delete checkbox;
    }
};



int main(){

    cout<<"hello world \n";
    //for windows style
    GUIFactory* factory = new WindowsFactory();
    Button *wbutton  =factory->createButton();
    CheckBox *wcheckbox =factory->createCheckBox();
    wbutton->paint();
    wcheckbox->paint();
    wbutton->paint();
    wcheckbox->paint();

    //for mac os style
    factory = new MacosFactory();
    Button *mbutton  =factory->createButton();
    CheckBox *mcheckbox =factory->createCheckBox();
    wbutton->paint();
    wcheckbox->paint();

    //another way creating object
    cout<<"************************Another way creating object******************************\n";
    //GUIFactory* factory = nullptr;
    Application* app = nullptr;

    // Windows style
    factory = new WindowsFactory();
    app = new Application(factory);
    app->paint();
    delete app;
    delete factory;

    // MacOS style
    factory = new MacosFactory();
    app = new Application(factory);
    app->paint();
    delete app;
    delete factory;

    return 0;
}