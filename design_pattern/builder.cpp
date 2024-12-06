#include<iostream>
#include<memory>
using namespace std;

// step first define a product

class Computer{
    private:
    public:
        string cpu;
        string gpu;
        int ram;       // in GB
        int storage;   // in GB

        void showConfiguration() const {
            cout << "Computer Configuration:\n";
            cout << "CPU: " << cpu << "\n";
            cout << "GPU: " << gpu << "\n";
            cout << "RAM: " << ram << " GB\n";
            cout << "Storage: " << storage << " GB\n";
        }

};

//Step 2: Define the Builder Interface
// Builder Interface
class ComputerBuilder {
    public:
        virtual void setCPU(const string& cpu) = 0;
        virtual void setGPU(const string& gpu) = 0;
        virtual void setRAM(int ram) = 0;
        virtual void setStorage(int storage) = 0;
        virtual unique_ptr<Computer> getComputer() = 0;
        virtual ~ComputerBuilder() {}
};

//Step 3: Implement Concrete Builders
// ConcreteBuilder: GamingComputerBuilder
class GamingComputerBuilder : public ComputerBuilder {
    private:
        unique_ptr<Computer> computer;

    public:
        GamingComputerBuilder() {
            computer = make_unique<Computer>();
        }

        void setCPU(const string& cpu) override {
            computer->cpu = cpu;
        }

        void setGPU(const string& gpu) override {
            computer->gpu = gpu;
        }

        void setRAM(int ram) override {
            computer->ram = ram;
        }

        void setStorage(int storage) override {
            computer->storage = storage;
        }

        unique_ptr<Computer> getComputer() override {
            return move(computer);
        }
};

// ConcreteBuilder: OfficeComputerBuilder
class OfficeComputerBuilder : public ComputerBuilder {
    private:
        unique_ptr<Computer> computer;

    public:
        OfficeComputerBuilder() {
            computer = make_unique<Computer>();
        }

        void setCPU(const string& cpu) override {
            computer->cpu = cpu;
        }

        void setGPU(const string& gpu) override {
            computer->gpu = gpu;
        }

        void setRAM(int ram) override {
            computer->ram = ram;
        }

        void setStorage(int storage) override {
            computer->storage = storage;
        }

        unique_ptr<Computer> getComputer() override {
            return move(computer);
        }
};
//Step 4: Define the Director

// Director
class ComputerDirector {
    public:
        void buildGamingComputer(ComputerBuilder& builder) {
            builder.setCPU("Intel i9");
            builder.setGPU("NVIDIA RTX 4090");
            builder.setRAM(32);
            builder.setStorage(2000);
        }

        void buildOfficeComputer(ComputerBuilder& builder) {
            builder.setCPU("Intel i5");
            builder.setGPU("Integrated GPU");
            builder.setRAM(16);
            builder.setStorage(512);
        }
};



int main(){
    cout<<"Hello world\n";
    ComputerDirector *director =new ComputerDirector();

    // Build a Gaming Computer
    GamingComputerBuilder gamingBuilder;
    director->buildGamingComputer(gamingBuilder);
    unique_ptr<Computer> gamingComputer = gamingBuilder.getComputer();
    gamingComputer->showConfiguration();

    cout << "\n";

    // Build an Office Computer
    OfficeComputerBuilder officeBuilder;
    director->buildOfficeComputer(officeBuilder);
    unique_ptr<Computer> officeComputer = officeBuilder.getComputer();
    officeComputer->showConfiguration();
    return 0;
}