#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*Key Components

    Component:
        Abstract base class/interface that defines the common operations for both composites and leaf objects.

    Leaf:
        Represents individual objects (end nodes) in the composition. Implements the common operations.

    Composite:
        Represents a group of components (e.g., folders containing files). Implements the common operations and also manages child components.

    Client:
        Uses the Component interface to interact with both composites and leaves uniformly.
 */       

class FileSystemComponent {
    public:
        virtual void display() = 0; // Pure virtual function for displaying the component
        virtual ~FileSystemComponent() = default;
};

class Folder : public FileSystemComponent {
    private:
        string name;
        vector<FileSystemComponent*> children; // Holds child components
    public:
        Folder(const string& name) : name(name) {}
        
        void add(FileSystemComponent* component) {
            children.push_back(component);
        }

        void display() override {
            cout << "Folder: " << name << endl;
            for (auto child : children) {
                child->display(); // Delegate display to child components
            }
        }

        ~Folder() {
            for (auto child : children) {
                delete child; // Clean up dynamically allocated children
            }
        }
};


class File : public FileSystemComponent {
    private:
        string name;
    public:
        File(const string& name) : name(name) {}
        void display() override {
            cout << "File: " << name << endl;
        }
};


int main(){
    cout<<"Hello world\n";
    // Create files
    FileSystemComponent* file1 = new File("file1.txt");
    FileSystemComponent* file2 = new File("file2.txt");
    FileSystemComponent* file3 = new File("file3.txt");

    // Create folders
    Folder* folder1 = new Folder("Folder1");
    Folder* folder2 = new Folder("Folder2");

    // Build the tree structure
    folder1->add(file1);
    folder1->add(file2);

    folder2->add(file3);
    folder2->add(folder1); // Nest folder1 inside folder2

    // Display the file system structure
    folder2->display();

    // Clean up
    delete folder2; // Automatically cleans up children

    return 0;
}