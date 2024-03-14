
#include<iostream>
#include<stack>
#include<fstream>
using namespace std;

class Car {
    string name;
    int numberOfMoves = 0;
public:
    Car(const string &name, int numberOfMoves) : name(name), numberOfMoves(0) {}

    string GetName(){
        return name;
    }
    int GetNumOfMoves(){
        return numberOfMoves;
    }
    void IncreaseNumOfMoves(){
        numberOfMoves++;
    }
};

int main() {
    stack<Car> parking;
    stack<Car> temp;
    int num_parking_space = 5;

    ifstream fin;
    string path = "/Users/shopangali05/Desktop/Git /example for stack  /parking.txt";
    fin.open(path);
    if(!fin.is_open())
    {
        cout << "File is not open";
    }
    else
    {
        string str, carName, command;
        while(fin >> carName >> command)
        {
            cout << carName << "->" << command << endl;
            if(command == "in")
            {
                if(parking.size() == num_parking_space)
                {
                    cout << "\t" << carName << ", there is no parking space (only " << num_parking_space << " spaces in parking)" << endl;
                }
                else
                {
                    parking.push(Car(carName,0));
                }
            }
            else if(command == "out")
            {
             while(!parking.empty()&&parking.top().GetName()!=carName){
                 temp.push(parking.top());
                 parking.pop();
             }
                if(!parking.empty())
                {
                    cout << "\t" << parking.top().GetName() << " was moved " << parking.top().GetNumOfMoves() << " times" << endl;
                    parking.pop();
                }
                else
                {
                    cout << "\tCar not found in the parking" << endl;
                }
                while(!temp.empty()){
                    parking.push(temp.top());
                    parking.top().IncreaseNumOfMoves();
                    temp.pop();
                }

            }
        }
    }
    fin.close();
    return 0;
}





/*

    output:

    Nissan was moved 0 times;

    Audi was moved 1 times;

    Tesla, there is no parking space(only 5 spaces in parking);

    Kia was moved 1 times;

    BMW was moved 1 times;
    Audi was moved 2 times;


    Toyota was moved 3 times;

    Skoda was moved 4 times;

    Lada was moved 5 times;

 */

