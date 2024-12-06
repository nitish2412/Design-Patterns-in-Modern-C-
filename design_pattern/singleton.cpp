#include<iostream>
#include <thread>
#include<mutex>
using namespace std;

class Singleton {

    private:
        static Singleton *instance;
        static mutex mutex_;
        Singleton(){
            cout<<"Private constructor is called\n";
        }
        ~Singleton(){
            cout<<"private destructor is called\n";
        }
    public:
        static Singleton* getInstance(){
            cout<<"Get Instance function is called\n";
            if(instance==nullptr){
                lock_guard<mutex> lock(mutex_);
                if(instance==nullptr){
                    
                    instance=new Singleton();
                }
            }
            return instance;
        }
        void display(){
            cout<<"Display function is called\n";
        }
};

Singleton* Singleton::instance=nullptr;
mutex Singleton::mutex_;

void ThreadFoo(){
    
    cout<<"ThreadFoo is called\n";
    Singleton* instance1= Singleton::getInstance();
    instance1->display();
}

void ThreadBar(){
    cout<<"Thread Bar is called\n";
    Singleton* instance2= Singleton::getInstance();
    instance2->display();

}


int main(){
    cout<<"Hello world\n";
    /*Singleton* instance1= Singleton::getInstance();
    instance1->display();
    
    Singleton* instance2= Singleton::getInstance();
    instance2->display();*/

    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
    return 0;
}