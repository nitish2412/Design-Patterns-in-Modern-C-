#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

class Singleton{

    private:
        static Singleton *instance;
        static mutex mutex_;

        Singleton(){

            cout<<"private constructor is called\n";
        }
        ~Singleton(){
            cout<<"private destructor is called\n";
        }
    public:
        static Singleton* getInstance(){
            
            lock_guard<mutex> lock(mutex_);
            if(!instance){
                instance = new Singleton();
            }
            return instance;
        }

        void someOperation(){
            cout<<"Do something by singleton method\n";
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mutex_;
void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    //std::cout << singleton->value() << "\n";
    singleton->someOperation();

}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    singleton->someOperation();
}

int main(){

    /*Singleton *singleton = Singleton::getInstance();
    singleton->someOperation();
    Singleton *singleton1 = Singleton::getInstance();
    singleton1->someOperation();*/


    thread th1(ThreadFoo);
    thread th2(ThreadBar);
    th1.join();
    th2.join();


    return 0;
}