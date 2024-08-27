#include<iostream>
#include<stack>
using namespace std;

//Command Interface
class Command{

    public:
        virtual void execute()=0;
        virtual void undo()=0;
        virtual ~Command(){}
};

// Light receiver class.
class Light{

    public:
        void turnOn(){
            cout<<"Truning light on.\n";
        }

        void turnOff(){
            cout<<"Truning light off.\n";
        }


};

// Receiver: Stereo
class Stereo {
public:
    void on() {
        cout << "Stereo is ON.\n";
    }

    void off() {
        cout << "Stereo is OFF.\n";
    }

    void setCD() {
        cout << "Stereo is set to play CD.\n";
    }

    void setVolume(int volume) {
        cout << "Stereo volume set to " << volume << ".\n";
    }
};


// concreate Command calss

class LightOnCommand:public Command{

    private:
        Light *light;
    public:
        LightOnCommand(Light *l1):light(l1){ }
        void execute() override{
            light->turnOn();
        }

        void undo() override{
             light->turnOff();
        }

};

// concreate Command calss

class LightOffCommand:public Command{

    private:
        Light *light;
    public:
        LightOffCommand(Light *l1):light(l1){ }
        void execute() override{
            light->turnOff();
        }

        void undo() override{
             light->turnOn();
        }

};

// Concrete Command: StereoOnWithCDCommand
class StereoOnWithCDCommand : public Command {
    private:
        Stereo* stereo;

    public:
        StereoOnWithCDCommand(Stereo* s) : stereo(s) {}

        void execute() override {
            stereo->on();
            stereo->setCD();
            stereo->setVolume(11);
        }
        void undo() override{
            stereo->off();
        }
};

// Concrete Command: StereoOffCommand
class StereoOffCommand : public Command {
    private:
        Stereo* stereo;

    public:
        StereoOffCommand(Stereo* s) : stereo(s) {}

        void execute() override {
            stereo->off();
        }
        void undo() override{
            stereo->on();
            stereo->setCD();
            stereo->setVolume(11);
        }
};

//Invoker Remotecontrol

class RemoteControl{
    private:
        Command *slot;
        stack<Command*> undo_list;
    public:
        void setCommand(Command *cmd){
            this->slot=cmd;
        }
        void pressButton(){
            if(slot){
                slot->execute();
                undo_list.push(slot);
            }
        }

        void pressUndoButton(){
            if(!undo_list.empty()){
                undo_list.top()->undo();
                undo_list.pop();
            }
        }


};


int main(){
    cout<<"Hello World\n";

    Light *livingRoomLight;
    Stereo *musicplayer;
    Command *lighton = new LightOnCommand(livingRoomLight);
    Command *lightoff = new LightOffCommand(livingRoomLight);
    
    Command *stereoon = new StereoOnWithCDCommand(musicplayer);
    Command *stereooff = new StereoOffCommand(musicplayer);
    // Create the invoker
    RemoteControl remote;
    remote.setCommand(lighton);
    remote.pressButton();

    // Use the remote to turn off the light
    remote.setCommand(lightoff);
    remote.pressButton();

    remote.setCommand(stereoon);
    remote.pressButton();

    remote.setCommand(stereooff);
    remote.pressButton();


    cout<<"***********************Undo Button*******************\n";
    remote.pressUndoButton();
    remote.pressUndoButton();
    remote.pressUndoButton();
    remote.pressUndoButton();

    return 0;
}