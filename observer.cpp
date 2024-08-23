#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//observer interface
class Observer{

    public:
        virtual void update(int data)=0;
        virtual ~Observer(){
            cout<<"Base Observer object deleted\n";
        }
};

//subject interface or obsevable interface
class Subject{

    public:
        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        virtual void notify() = 0;
        virtual void setData(int) = 0;
        virtual ~Subject(){
            cout<<"Base Subject object deleted\n";
        }
};

class Display{

    private:
        int data;
    public:
        Display(){
           cout<<"Constructor is called\n"; 
        }

        void display_data(int data){
            cout<<"Display data is:"<<data<<"\n";
        }

        ~Display(){
            cout<<"Display object deleted\n";
        }
};

class WeatherStation:public Subject{

    private:
        vector<Observer*> observer_list;
        int temp;
    public:
        void registerObserver(Observer* o) override{
            observer_list.push_back(o);
        }
        void removeObserver(Observer* o) override {
            observer_list.erase(remove(observer_list.begin(), observer_list.end(), o), observer_list.end());
        }
        void notify(){

            for(auto obj:observer_list){
                obj->update(this->temp);
            }
        }

        void setData(int temp){
            this->temp=temp;
            this->notify();
        }

        virtual ~WeatherStation(){
            cout<<"Weather station object deleted\n";
        }
};

//observer concreate class 1;
class MobileDisplay:public Observer{

    private:
        WeatherStation *weatherStation;
        //Subject *weatherStation;
        int temp;
        Display dis;

    public:
        MobileDisplay( WeatherStation *weatherStation){

            this->weatherStation=weatherStation;
            weatherStation->registerObserver(this);
            cout<<"Register mobile display\n";
            //dis=new Display();
        }

        void update(int data) override{
            this->temp=data;
            cout<<"This data from Mobile Display:"<<this->temp<<"\n";
            dis.display_data(this->temp);
        }

        void RemoveFromList() {
            weatherStation->removeObserver(this);
            cout<<"Remove Mobile Display from list\n";
            
        }

        virtual ~MobileDisplay(){
            cout<<"Mobile display object deleted\n";
        }


};

//observer concreate class 2;
class TVDisplay:public Observer{

    private:
        WeatherStation *weatherStation;
        //Subject *weatherStation;
        int temp;
        Display dis;

    public:
        TVDisplay( WeatherStation *weatherStation){

            this->weatherStation=weatherStation;
            weatherStation->registerObserver(this);
            cout<<"Register TV display\n";
        }

        void update(int data) override{
            this->temp=data;
            cout<<"This data from TV Display:"<<this->temp<<"\n";
            dis.display_data(this->temp);
        }

        void RemoveFromList() {
            weatherStation->removeObserver(this);
            cout<<"Remove Tv Display from list\n";
            
        }

        virtual ~TVDisplay(){
            cout<<"TV display object deleted\n";
        }

};

//observer concreate class 3;
class TabDisplay:public Observer{

    private:
        WeatherStation *weatherStation;
        //Subject *weatherStation;
        int temp;
        Display dis;

    public:
        TabDisplay( WeatherStation *weatherStation){

            this->weatherStation=weatherStation;
            weatherStation->registerObserver(this);
            cout<<"Register Tab display\n";
        }

        void update(int data) override{
            this->temp=data;
            cout<<"This data from Tab Display:"<<this->temp<<"\n";
            dis.display_data(this->temp);
        }

        void RemoveFromList() {
            weatherStation->removeObserver(this);
            cout<<"Remove Tab Display from list\n";
            
        }

        virtual ~TabDisplay(){
            cout<<"TabDisplay object deleted\n";
        }

};


int main(){
    
    cout<<"Hello World\n";
    WeatherStation *weatherStation = new WeatherStation();

    //Subject *weatherStation = new WeatherStation();

    /*Observer *mobile = new MobileDisplay(weatherStation);
    Observer *tv = new TVDisplay(weatherStation);
    Observer *tab = new TabDisplay(weatherStation);*/

    MobileDisplay *mobile = new MobileDisplay(weatherStation);
    TVDisplay *tv = new TVDisplay(weatherStation);
    TabDisplay *tab = new TabDisplay(weatherStation);

    weatherStation->setData(10);

    weatherStation->setData(20);
    weatherStation->setData(30);
    weatherStation->setData(40);

    mobile->RemoveFromList();
    tv->RemoveFromList();
    tab->RemoveFromList();

    delete mobile;
    delete tv;
    delete tab;
    delete weatherStation;

    
    return 0;
}