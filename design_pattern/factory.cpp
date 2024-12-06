#include<iostream>
using namespace std;

class Document{

    public:
        virtual void open()=0;
        virtual ~Document(){

        }
};

class WordDocumentOpen:public Document{

    public:
        void open() override{
            cout<<"word document opend\n";
        }
};

class PdfDocumentOpen:public Document{

    public:
        void open() override{
            cout<<"PDF document opend\n";
        }
};

class Application{

    public:
        virtual Document* createDocument()=0;
        virtual ~Application(){}
};

class WordApplication: public Application{
    public:
        Document* createDocument(){
            return new WordDocumentOpen();
        }
};

class PdfApplication: public Application{
    public:
        Document* createDocument(){
            return new PdfDocumentOpen();
        }
};


int main(){
    cout<<"Hello World\n";
    Application *app = new WordApplication();
    Document* doc=app->createDocument();
    doc->open();
    app=new PdfApplication();
    doc=app->createDocument();
    doc->open();

    return 0;
}