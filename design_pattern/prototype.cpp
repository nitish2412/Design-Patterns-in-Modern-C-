#include<iostream>
using namespace std;

// Abstract Prototype: Shape
class Shape {
public:
    virtual Shape* clone() const = 0; // Pure virtual function for cloning
    virtual void draw() const = 0;    // Pure virtual function for drawing
    virtual ~Shape() {}
};

//Step 2: Implement Concrete Prototypes

// Concrete Prototype: Circle
class Circle : public Shape {
    private:
        int radius;

    public:
        Circle(int r) : radius(r) {}

        // Implement clone
        Shape* clone() const override {
            return new Circle(*this); // Use copy constructor
        }

        // Implement draw
        void draw() const override {
            cout << "Drawing a Circle with radius: " << radius << endl;
        }

        void setRadius(int r) { radius = r; }
};

// Concrete Prototype: Rectangle
class Rectangle : public Shape {
    private:
        int width, height;

    public:
        Rectangle(int w, int h) : width(w), height(h) {}

        // Implement clone
        Shape* clone() const override {
            return new Rectangle(*this); // Use copy constructor
        }

        // Implement draw
        void draw() const override {
            cout << "Drawing a Rectangle with width: " << width << " and height: " << height << endl;
        }

        void setDimensions(int w, int h) { width = w; height = h; }
};


int main(){
    cout<<"Hello World\n";
    Shape* circlePrototype = new Circle(10);
    Shape* rectanglePrototype = new Rectangle(5, 7);

    // Clone shapes
    Shape* clonedCircle = circlePrototype->clone();
    Shape* clonedRectangle = rectanglePrototype->clone();

    // Customize cloned objects
    static_cast<Circle*>(clonedCircle)->setRadius(20);
    static_cast<Rectangle*>(clonedRectangle)->setDimensions(10, 15);

    // Draw original and cloned shapes
    cout << "Original Shapes:" << endl;
    circlePrototype->draw();
    rectanglePrototype->draw();

    cout << "\nCloned and Customized Shapes:" << endl;
    clonedCircle->draw();
    clonedRectangle->draw();

    // Clean up
    delete circlePrototype;
    delete rectanglePrototype;
    delete clonedCircle;
    delete clonedRectangle;
    return 0;
}