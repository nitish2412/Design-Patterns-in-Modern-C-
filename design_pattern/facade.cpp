#include <iostream>
using namespace std;

// Subsystem 1: Lighting
class Lighting {
public:
    void turnOnLights() {
        cout << "Lights are turned ON.\n";
    }
    void turnOffLights() {
        cout << "Lights are turned OFF.\n";
    }
};

// Subsystem 2: Heating
class Heating {
public:
    void turnOnHeating() {
        cout << "Heating system is turned ON.\n";
    }
    void turnOffHeating() {
        cout << "Heating system is turned OFF.\n";
    }
};

// Subsystem 3: Entertainment
class Entertainment {
public:
    void turnOnTV() {
        cout << "TV is turned ON.\n";
    }
    void turnOffTV() {
        cout << "TV is turned OFF.\n";
    }
    void playMusic() {
        cout << "Music is playing.\n";
    }
};
// Facade
class HomeFacade {
private:
    Lighting lighting;
    Heating heating;
    Entertainment entertainment;

public:
    void turnOnAll() {
        cout << "Turning ON all systems...\n";
        lighting.turnOnLights();
        heating.turnOnHeating();
        entertainment.turnOnTV();
        entertainment.playMusic();
    }

    void turnOffAll() {
        cout << "Turning OFF all systems...\n";
        lighting.turnOffLights();
        heating.turnOffHeating();
        entertainment.turnOffTV();
    }
};
int main() {
    HomeFacade home;
    
    cout << "Client interacts with the HomeFacade:\n";
    home.turnOnAll();
    
    cout << "\nAfter some time...\n";
    home.turnOffAll();
    
    return 0;
}
