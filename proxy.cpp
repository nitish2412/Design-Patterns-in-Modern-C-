#include<iostream>
using namespace std;

//subject interface
class Image{
    public:
        virtual void display()=0;
        virtual ~Image(){}
};

//implementation of real Image object
class RealImage:public Image{

    private:
        string filename;
    public:
        RealImage(string f_name):filename(f_name){
            cout<<"Loading Image:"<<filename<<"\n";
        }
        void display() override{
            cout<<"Displaying Image:"<<this->filename<<"\n";
        }
};

//implementation of proxy Image object
class ProxyImage:public Image{

    private:
        RealImage *realimg;
        string filename;
    public:
        ProxyImage(string name):filename(name),realimg(nullptr){
            cout<<"proxy constructor is called\n";          
        }
        void display() override{
            if(realimg==nullptr){
                cout<<"Real object is created\n";
                realimg=new RealImage(filename);
            }
            realimg->display();
        }
};

int main(){
    cout<<"Hello World\n";
    Image *img=new ProxyImage("Loacation.jpg");
    img->display();
    cout<<"*************************Again calling display image should not creat real object.**********************\n";
    img->display();
    delete img;
    return 0;
}