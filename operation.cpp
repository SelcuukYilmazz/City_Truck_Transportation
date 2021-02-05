#include "operation.h"
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "Packages.h"
#include "Truck.h"
#include <fstream>
#include <vector>
#include "Cities.h"
using namespace std;



Operation::Operation() {}

int Operation::operation_execute(string dests,string packages,string trucks,string missions)
{
    vector<Cities> stations;
    vector<Packages> sort_packages;
    Packages *stack_Top = new Packages;
    Truck *queue_Top = new Truck;
    Truck *moving_Truck = new Truck;
    Stack<Packages> *truck = new Stack<Packages>;
    int city_index =0;
    string myText;
    string temp_package;
    string temp_truck;
    string starting_station,midway_station,target_station;
    int cargo_take_start,cargo_take_midway,cargo_leave_midway;
    int repeat;


    //We set stations here

    ifstream City_names(dests);
    while (getline (City_names, myText)) {

        // Output the text from the file

        Cities *a = new Cities(myText,new Stack<Packages>,new Queue<Truck>);
        stations.push_back(*a);
    }
    City_names.close();



    //We set initial packages here

    ifstream Package_location(packages);
    while (getline (Package_location, myText)) {
        while (true)
        {
            int pos = myText.substr(0).find(" ");
            temp_package = myText.substr(0,pos);
            if (myText.substr(pos+1) == stations[city_index].getCityName())
            {
                stations[city_index].packages.push(temp_package);
                city_index=0;
                temp_package="";
                break;
            }
            else{
                city_index++;
            }
        }
    }
    Package_location.close();

    //We set initial garages here

    ifstream Truck_location(trucks);
    while (getline (Truck_location, myText)) {
        int pos = myText.substr(0).find(" ");
        temp_truck = myText.substr(0,pos);
        myText = myText.substr(pos+1);
        pos = myText.substr(0).find(" ");
        while (true)
        {

            if (myText.substr(0,pos) == stations[city_index].getCityName())
            {
                myText = myText.substr(pos+1);
                stations[city_index].trucks.enqueue(*(new Truck(temp_truck,myText)));
                city_index=0;
                temp_truck="";
                break;
            }
            else{
                city_index++;
            }
        }
    }
    Truck_location.close();


//We do all missions here

    ifstream Missions(missions);

    while (getline (Missions, myText)) {
        int pos = myText.substr(0).find("-");
        int one_time=0;

        starting_station = myText.substr(0,pos);
        myText = myText.substr(pos+1);
        pos = myText.find("-");

        midway_station = myText.substr(0,pos);
        myText = myText.substr(pos+1);
        pos = myText.find("-");

        target_station = myText.substr(0,pos);
        myText = myText.substr(pos+1);
        pos = myText.find("-");

        cargo_take_start = stoi(myText.substr(0,pos));
        myText = myText.substr(pos+1);
        pos = myText.find("-");

        cargo_take_midway = stoi(myText.substr(0,pos));
        myText = myText.substr(pos+1);
        pos = myText.find(",");

        //Take items from start

        while (true){
            if (starting_station == stations[city_index].getCityName())
            {
                for (int i = 0; i < cargo_take_start ; i++)
                {
                    stations[city_index].packages.getTop(*stack_Top);
                    truck->push(*stack_Top);
                    stations[city_index].packages.pop();
                }
                stations[city_index].trucks.getFront(*queue_Top);
                stations[city_index].trucks.dequeue();
                moving_Truck = queue_Top;
                city_index=0;
                break;
            }
            else{
                city_index++;
            }
        }

        //We take items from midway

        while (true){
            if (midway_station == stations[city_index].getCityName())
            {
                for (int i = 0; i < cargo_take_midway ; i++)
                {
                    stations[city_index].packages.getTop(*stack_Top);
                    truck->push(*stack_Top);
                    stations[city_index].packages.pop();
                }
                city_index=0;
                break;
            }
            else{
                city_index++;
            }
        }

        //We put some items to midway here

        while (true){

            if (midway_station == stations[city_index].getCityName())
            {
                while(pos!=-1){
                    cargo_leave_midway = stoi(myText.substr(0,pos));
                    myText = myText.substr(pos+1);
                    pos = myText.find(",");
                    repeat = truck->size();


                    for (int i = 0; i < repeat ; i++)
                    {


                        truck->getTop(*stack_Top);
                        sort_packages.insert(sort_packages.begin(),*stack_Top);
                        truck->pop();
                    }

                    stations[city_index].packages.push(sort_packages[cargo_leave_midway]);

                    sort_packages[cargo_leave_midway].id="";
                }
                cargo_leave_midway = stoi(myText.substr(0,pos));
                myText = myText.substr(pos+1);
                repeat = truck->size();


                for (int i = 0; i < repeat ; i++)
                {



                    truck->getTop(*stack_Top);
                    sort_packages.insert(sort_packages.begin(),*stack_Top);
                    truck->pop();
                }
                stations[city_index].packages.push(sort_packages[cargo_leave_midway]);

                sort_packages[cargo_leave_midway].id="";


                for (int i = sort_packages.size()-1; i >=0; i--)
                {
                    if (sort_packages[i].id!="")
                    {
                        truck->push(sort_packages[i]);
                    }
                }
                sort_packages.clear();
                city_index=0;
                break;
            }
            else{
                city_index++;
            }
        }

        //We put all items to target city here

        while(true)
        {
            if (target_station == stations[city_index].getCityName())
            {
                repeat = truck->size();
                for (int i = 0; i < repeat; i++)
                {
                    truck->getTop(*stack_Top);
                    stations[city_index].packages.push(*stack_Top);
                    truck->pop();
                }
                stations[city_index].trucks.enqueue(*moving_Truck);
                city_index=0;
                break;
            }
            else{
                city_index++;
            }

        }
        one_time=0;
    }

    //Display method

    while (true)
    {
        for (int i = 0; i <stations.size(); i++) {
            cout<<stations[i].getCityName()<<endl;
            cout<<"Packages:"<<endl;
            repeat = stations[i].packages.size();
            for (int j = 0; j < repeat; j++)
            {
                stations[i].packages.getTop(*stack_Top);
                cout<<stack_Top->id<<endl;
                stations[i].packages.pop();

            }
            cout<<"Trucks:"<<endl;
            repeat = stations[i].trucks.size();
            for (int j = 0; j < repeat; j++)
            {
                stations[i].trucks.getFront(*queue_Top);
                cout<<queue_Top->id<<endl;
                stations[i].trucks.dequeue();
            }
            cout<<"-------------"<<endl;

        }
        break;
    }

    Missions.close();
    return 0;
}


