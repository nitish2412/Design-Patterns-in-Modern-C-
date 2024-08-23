#include<iostream>
#include<vector>
using namespace std;

class SortingStrategy{
    
    public:
        virtual void sort(vector<int> &arr) const = 0;
        virtual ~SortingStrategy(){}
};

class SortingContext {
    private:
        SortingStrategy* strategy;
 
    public:
        SortingContext(){

        }
        SortingContext(SortingStrategy* strategy){
             this->strategy = strategy;
        }
        void setStrategy(SortingStrategy* strategy)
        {
            this->strategy = strategy;
        }
 
        void executeStrategy(vector<int>& arr)
        {
            strategy->sort(arr);
        }
};

class Bubble: public SortingStrategy{

    void sort(vector<int> &arr) const override{

        cout<<"Bubble sort\n";
    }
};

class Insertion: public SortingStrategy{

    void sort(vector<int> &arr) const override{

        cout<<"Insertion sort\n";
    }
};

class Selection: public SortingStrategy{

    void sort(vector<int> &arr) const override{

        cout<<"Selection sort\n";
    }
};

int main(){

    SortingContext *sortingcontext = new SortingContext(new Bubble());
    vector<int> arr1;
    sortingcontext->executeStrategy(arr1);

    SortingContext context;
    Insertion insertion;
    Selection selection;
    context.setStrategy(&insertion);
	context.executeStrategy(arr1); // insertion

    sortingcontext->setStrategy(&selection);
	sortingcontext->executeStrategy(arr1); // selection


    cout<<"Hello World\n";
    return 0;
}