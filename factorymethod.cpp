#include<iostream>
using namespace std;

class Product{
    public:
        virtual ~Product() {}
        virtual string petSound() const = 0;
};

class Dog : public Product {
    public:
        string petSound() const override {
            return "Bow Bow..";
        }
};

class Cat : public Product {
    public:
        string petSound() const override {
            return "Mew Mew..";
        }
};

class PetFactory{
    public:
        virtual ~PetFactory() {}
        //virtual Product* FactoryMethod(string producttype) const = 0;
        virtual Product* FactoryMethod() const = 0;

};

class ConcreateFactory1 : public PetFactory{

    public:
        Product* FactoryMethod() const override {
            return new Dog();
        }
            
         
};

class ConcreateFactory2 : public PetFactory{

    public:
        Product* FactoryMethod() const override {
            return new Cat();
        }
            
         
};





/*class ConcreateFactory1 : public PetFactory{

    public:
        Product* FactoryMethod(string producttype) const override {
            Product *p=NULL;
            if(producttype=="dog"){
                p=new Dog;
            }
            if(producttype=="cat"){
                p=new Cat();
            }
            return p;
         }
         
};*/

int main(){
    cout<<"hello world\n";
    PetFactory *pf =new ConcreateFactory1();
    Product *p =pf->FactoryMethod();
    cout<<p->petSound()<<"\n";
    pf=new ConcreateFactory2();
    p=pf->FactoryMethod();
    cout<<p->petSound()<<"\n";
    
    /*Product *p1=pf->FactoryMethod("cat");
    if(p1==NULL){
        cout<<"NULL pointer\n";
    }
    else{
        string s=p1->petSound();
        cout<<s<<"\n";
    }

    p1=pf->FactoryMethod("dog");
    if(p1==NULL){
        cout<<"NULL pointer\n";
    }
    else{
        string s=p1->petSound();
        cout<<s<<"\n";
    }*/
    
    return 0;
}