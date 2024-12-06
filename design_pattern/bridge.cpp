#include<iostream>
using namespace std;

/*Key Components

    1. Abstraction: Defines the high-level interface and holds a reference to the implementor.
    2. Implementor: Defines the low-level interface for implementation classes.
    3. Concrete Abstraction: Extends the abstraction and delegates work to the implementor.
    4. Concrete Implementor: Provides concrete implementation of the low-level interface.
*/
//Define the Implementor Interface
class Device {
    public:
        virtual void powerOn() = 0;
        virtual void powerOff() = 0;
        virtual void setVolume(int volume) = 0;
        virtual ~Device() = default;
};
//Step 2: Create Concrete Implementors
class TV : public Device {
    public:
        void powerOn() override {
            cout << "TV is now ON\n";
        }

        void powerOff() override {
            cout << "TV is now OFF\n";
        }

        void setVolume(int volume) override {
            cout << "TV volume set to " << volume << "\n";
        }
};

class Radio : public Device {
    public:
        void powerOn() override {
            cout << "Radio is now ON\n";
        }

        void powerOff() override {
            cout << "Radio is now OFF\n";
        }

        void setVolume(int volume) override {
            cout << "Radio volume set to " << volume << "\n";
        }
};

//Define the Abstraction
class RemoteControl {
    protected:
        Device* device; // The bridge to the implementation
    public:
        RemoteControl(Device* dev) : device(dev) {}

        virtual void turnOn() = 0;  // Pure virtual method
        virtual void turnOff() = 0; // Pure virtual method
        virtual void setVolume(int volume) = 0; // Pure virtual method

        virtual ~RemoteControl() = default;
};


// concreate abstraction
class BasicRemoteControl : public RemoteControl {
    public:
        BasicRemoteControl(Device* dev) : RemoteControl(dev) {}

        void turnOn() override {
            device->powerOn();
        }

        void turnOff() override {
            device->powerOff();
        }

        void setVolume(int volume) override {
            device->setVolume(volume);
        }
};

class AdvancedRemoteControl : public RemoteControl {
    public:
        AdvancedRemoteControl(Device* dev) : RemoteControl(dev) {}

        void turnOn() override {
            device->powerOn();
        }

        void turnOff() override {
            device->powerOff();
        }

        void setVolume(int volume) override {
            device->setVolume(volume);
        }

        void mute() {
            cout << "Muting the device.\n";
            device->setVolume(0);
        }
};


int main(){
    cout<<"Hello world\n";
    Device* tv = new TV();
    Device* radio = new Radio();

    RemoteControl* basicRemote = new BasicRemoteControl(tv);
    RemoteControl* advancedRemote = new AdvancedRemoteControl(radio);

    cout << "Using Basic Remote for TV:\n";
    basicRemote->turnOn();
    basicRemote->setVolume(20);
    basicRemote->turnOff();

    cout << "\nUsing Advanced Remote for Radio:\n";
    advancedRemote->turnOn();
    advancedRemote->setVolume(10);
    static_cast<AdvancedRemoteControl*>(advancedRemote)->mute();
    advancedRemote->turnOff();

    delete basicRemote;
    delete advancedRemote;
    delete tv;
    delete radio;
    return 0;
}