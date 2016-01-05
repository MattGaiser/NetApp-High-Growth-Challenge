/* 
 * File:   main.cpp
 * Author: Matthew Gaiser
 * 147 Tuscany Hills Park NW
 * Calgary AB Canada T3L 2A2
 * 13mdg5@queensu.ca
 *
 * Created on February 23, 2015, 4:45 PM
 */

#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */

struct Municipality { // A structure to hold the data for the cities.
    string name;
    string state;
    double pop2010int;
    double pop2012int;
    double percentchange;
    bool over50000;
};
struct topMunicipality { // A structure to hold the data for the top cities.  
    string name;
    string state;
    double percentchange;
};
struct State { //A structure to hold the data for the states. 
    string name;
    double pop2010;
    double pop2012;
    double percentchange;
};
struct topState //A structure to hold the data for the top states
{
    string name;
    double percentchange;
};
int main(int argc, char** argv) {

    string finished;
    Municipality cities[19517]; 
    topMunicipality list[5];
    topMunicipality worstlist[5];
    topState statelist[5];
    State ofTheUsa[51];
    int statecounter = 0;
    int citycounter = 0;
    int valuesaver;
    int var;
    string holdvalue;
    bool fired = false;
    bool fired2 = false;
    ifstream in("75f647c2ac77-Metropolitan_Populations_2010-2012_.csv"); //Opens the file.
    if (!in.is_open()) {
        cout << "Failed to open file" << endl;
        return 1;
    }
    for (int asd = 0; asd <51;asd++) // Ensures that the starting points for state population data are controlled. 
    {
        ofTheUsa[asd].pop2010 = 0;
        ofTheUsa[asd].pop2012 = 0;  
    }
    for (var = 0; var < 3; var++) // Clears the header values, which are not data but titles that we do not need. 
    {
        (getline(in, holdvalue, ','));
    }
    for (var = 0; var < 5; var++) // Ensures that the starting information in each variable is controlled so that errors can be identified. 
    {
        list[var].percentchange = 0;
        list[var].name = "Error";
        list[var].state = "Error";
        worstlist[var].percentchange = 0;
        worstlist[var].name = "Error";
        worstlist[var].state = "Error";
        statelist[var].name = "Error";
        statelist[var].percentchange = 0; 
    }
    for (var = 0; var < 19516; var++) // Ensures that the starting information in each variable is controlled so that errors can be identified.
    {
        cities[var].name = "Error";
        cities[var].state = "Error";
    }
    for (int count = 0; count < 97580; count++)/* 97580*/ {
        
        if (((count-0) % 5 == 0)) //Collects the name of the city
        {
            (getline(in, holdvalue, ','));
            cities[citycounter].name = holdvalue;

        } else if (((count - 1) % 5) == 0) // Collects the state of the city
        {
            (getline(in, holdvalue, ','));
            cities[citycounter].state = holdvalue;
            if (fired2 == false)
            {
                fired2 = true;
                ofTheUsa[statecounter].name = holdvalue; 
            }
            else if (cities[citycounter-1].state != holdvalue) //Determines when the state the data is coming from changes. 
            {
                statecounter = statecounter + 1;
                ofTheUsa[statecounter].name = holdvalue; 
            }
        } else if (((count - 2) % 5) == 0) // Collects the population data for the year 2010  
        {
            (getline(in, holdvalue, ','));
            istringstream(holdvalue) >> valuesaver;
            cities[citycounter].pop2010int = valuesaver;
            ofTheUsa[statecounter].pop2010 = valuesaver + ofTheUsa[statecounter].pop2010;
        } else if (((count - 3) % 5) == 0) // Skips the data from 2011 as it is not useful for the task
        {
            (getline(in, holdvalue, ','));
        } else if ((count - 4) % 5 == 0) // Collects the population data for the year 2012
        {
            getline(in, holdvalue, '"');
            istringstream(holdvalue) >> valuesaver;
            cities[citycounter].pop2012int = valuesaver;
            ofTheUsa[statecounter].pop2012 = valuesaver + ofTheUsa[statecounter].pop2012;
            cities[citycounter].percentchange  = (((cities[citycounter].pop2012int - cities[citycounter].pop2010int)/cities[citycounter].pop2010int) * 100);
            for (int seld = 0; seld < 5; seld++) // Compares the current city to the other top cities identified
            {
                if (list[seld].percentchange < cities[citycounter].percentchange) // Determines whether the city is among the top cities parsed so far.
                {
                    if (cities[citycounter].pop2012int > 50000)
                    {
                        list[seld].name = cities[citycounter-1].name;
                        list[seld].percentchange = cities[citycounter].percentchange;
                        list[seld].state = cities[citycounter].state;
                        break; 
                    }
                }
                else if (worstlist[seld].percentchange > cities[citycounter].percentchange) // Determines whether the city is among the worst cities parsed so far.
                {
                    if (cities[citycounter].pop2012int > 50000)
                    {
                        worstlist[seld].name = cities[citycounter-1].name;
                        worstlist[seld].percentchange = cities[citycounter].percentchange;
                        worstlist[seld].state = cities[citycounter].state;
                        break; 
                    }
                }
                
                
            }
            
        }   
        if ((count) % 5 == 0) // Determines when the data for a city has been fully collected and moves on to the next city 
        {
            if ( fired == false)
            {
                fired = true;
            }
            else 
            {
                citycounter = citycounter+1;   
            }
        }
    }
    cout << "The cities to target based on population growth are:" << endl; // Outputs the top five cities for investment 
    for (var = 0; var < 5; var++)
            {
               cout<< " The percentage change is "  << list[var].percentchange << "% for the town of " << list[var].name <<", " << list[var].state << endl;
            }
    cout << endl; 
    cout << "The cities to avoid based on population loss are:" << endl;// Outputs the worst five cities for investment 
    for (var = 0; var < 5; var++)
            {
               cout<< " The percentage change is "  << worstlist[var].percentchange << "% for the town of " << worstlist[var].name <<", " << worstlist[var].state << endl;
            }
   
    for (int asd = 0; asd <51;asd++) // Determines the top states by population growth
    {
         ofTheUsa[asd].percentchange =(ofTheUsa[asd].pop2012 - ofTheUsa[asd].pop2010)/ (ofTheUsa[asd].pop2010)*100; 
        
         for ( var = 0; var < 5; var++)
            {if (ofTheUsa[asd].percentchange > statelist[var].percentchange)
         
            {
                statelist[var].name = ofTheUsa[asd].name;
                statelist[var].percentchange = ofTheUsa[asd].percentchange;
                break;   
            }
         }
         
    }
    cout << endl;
    cout << "The top five states for investment are:" << endl; // Outputs the top five states by population growth
    for (int asd = 0; asd <5;asd++)
    {
        cout << " "<< statelist[asd].name << " with a percentage of " <<statelist[asd].percentchange <<"%" <<endl;
    }
    cout << "Are you all done? If so, hit any letter" << endl;
    cin >> finished;
    
    return 0;
}

