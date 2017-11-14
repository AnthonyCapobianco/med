//
//  main.cpp
//  med.cpp
//
//  Created by Anthony Capobianco on 11/11/2017.
//  Copyright © 2017 Anthony Capobianco. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#define newLine "\n"
using namespace std;

//  Ask for choice function
char ask(){
    char e;
    cout << "Please insert the letter of the drug you took:" << endl;
    cin >> e;
    return e;

};
//  Definition of vector
typedef vector<int> intvect;
//  Set default size for the vector
size_t size = 4;


//  Class definition
class drug{
public:
    intvect  doses;
    int      dose;
    char     drugID;
    string   drugName;

    void printName(){           /*  Function:         Prints drugName and assign it a letter                            */
        cout << "[" << drugID << "] " << drugName << endl;
    };

    void isRit(){
        cout << "Please select your dose of " << drugName << ":" << newLine;
        for (int x = 0;x < doses.size() ; ++x) {
            char i = 'a' + x;
            cout << "[" << i << "] " << doses[x] << " mg" << endl;
        }
    };
    bool isValidDose(int e){
        int result = 0;
        for (int i = 0; i < doses.size(); i++) {
            //  If e is in doses[] return true
            result = e == doses[i] ? 1 : result;
        }
        return result;
    }
    void isOther(){
        cout << "Please type the drug name:" << endl;
        cin.ignore();
        getline(cin, drugName);
        cout << "Please type the dose taken:" << endl;
        cin >> dose;

    }
    //  Constructor
    void addToDoses(int a){
        doses.push_back(a);
    }
    void setDrugName(string nameString){
        static char ID = 'a';
        drugName = nameString;
        //  drugID = ID unless ID is beyond 'z' (97 d; 7a h) in which case we remove 49 to get '0' (48 d; 30 h)
        drugID = ID < 'z' ? ID : ID - 49 ;
        ID++;
    }

};

/*
 *                            –––––––––––––––––––––––––––––––––––––
 *                            |   Function:           MAIN        |
 *                            –––––––––––––––––––––––––––––––––––––
 */
int main(int argc, const char * argv[]) {
    //  Set time string value
    time_t  timeResult  =   time(nullptr);
    string  theTime     =   ctime(&timeResult);
    //  Using pop_back(); to remove the annoying '\n' in ctime();
    theTime.pop_back();

    //  Set variables
    char    choice;           /*  User input:         Choice of the drug from the list. a, b or c                         */
    string  drugUsed;         /*  Output:             Name of the drug used.                                              */
    int     dosage            /*  User input:         Choice of the drug from the list. Int from 1 to size (4)            */
            ,doseUsed   =   0 /*  Output:             Dose used in mg                                                     */
            ,tries      =   0;/*  Error handling:     Is incremented if user inputs an incorrect value for dosage         */
    bool    idiot       =   1 /*  Error handling:     Is set to false if choice is correct                                */
            ,canCount   =   0;/*  Error handling:     Is set to true if the user inputs a correct value for dosage        */

    //  Set Objects
    drug    concerta
            ,effexor
            ,ritalin
            ,other;

    //  Set values for objects

    //  Ritalin
    intvect ritDoses {5,10,15,20};              /*  Vector:  Contains all the values for ritalin.doses[]                */
    for(int d = 0; d < ritDoses.size(); d++){   /*  Set values from ritDoses[] to the object variable ritalin.doses[]   */
        ritalin.addToDoses(ritDoses[d]);
    }
    ritalin.setDrugName("Ritalin");             /*  Set object variable drugName for Ritalin                            */

    //  Effexor
    effexor.dose = 225;                         /*  Set object variable dose for Effexor                                */
    effexor.setDrugName("Effexor");             /*  Set object variable drugName for Effexor                            */

    //  Concerta
    concerta.dose = 72;                         /*  Set object variable dose for Concerta                               */
    concerta.setDrugName("Concerta");           /*  Set object variable drugName for Concerta                           */

    //  Other
    other.setDrugName("other");

    //  Print the drugs

    ritalin.printName();
    effexor.printName();
    concerta.printName();
    other.printName();

    //  Ask for choice
    choice = ask();                             /*  User input: Setting value for choice using function ask();          */


    //  Switch as long as idiot is true. If the input is correct idiot is set to false.
    do{
        //  Pretty self explanatory. Set local variables (drugUsed, doseUsed) for choice
        switch (choice) {
            default:
                cout << "try again" << endl;
                choice = ask();
                break;
            case 'a' :
                //  Concerta
                drugUsed = concerta.drugName;
                doseUsed = concerta.dose;
                idiot = 0;
                break;
            case 'b' :
                //  Effexor
                drugUsed = effexor.drugName;
                doseUsed = effexor.dose;
                idiot = 0;
                break;
            case 'c' :
                //  Ritalin
                ritalin.isRit();
                do{
                    //  Is it the first try? If not, try again
                    if ( tries > 0 ){
                        cout << "Try again:" << endl;
                        ritalin.isRit();
                    }
                    cin >> dosage;

                    //  canCount is true if isValidDose is also true
                    canCount = ritalin.isValidDose(ritDoses[dosage -1]);

                    tries++;

                }while (canCount == 0);
                //  Only set the dose if the user can count
                ritalin.dose = ritDoses[dosage -1];

                drugUsed = ritalin.drugName;
                doseUsed = ritalin.dose;

                idiot = 0;
                break;
            case 'd' :

                other.isOther();
                drugUsed = other.drugName;
                doseUsed = other.dose;
                idiot = 0;
                break;
        }
    }while (idiot == 1);

    //  Print the result (this is mainly for debug but it might stay in prod)
    cout << theTime << drugUsed << " " << doseUsed << "mg" << endl;

    //  Almost done! Now we just need to put it in a file.
    
    return 0;
}

