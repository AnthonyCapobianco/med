//
//  main.cpp
//  med.cpp
//
//  Created by Anthony Capobianco on 11/11/2017.
//  Copyright © 2017 Anthony Capobianco. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>

#define newLine "\n"
using namespace std;

//  String length function
int arrLength(int *p){
    int result = (sizeof(p)/sizeof(*p))+1;
    return result;
}
//  Ask for choice function
char ask(){
    char e;
    cout << "Please insert the letter of the drug you took" << endl;
    cin >> e;
    return e;

};
//  Array size for ritalin (avoiding pain in the ass if the number changes)
const int ritArraySize = 4;

//  Class definition
class drug{
public:
    int      doses[ritArraySize]
            ,dose;
    string   drugName;

    void printName(){
        static char i = 'a';
        cout << "[" << i << "] " << drugName << endl;
        i++;
    };

    void isRit(){
        static int i = 1;
        cout << "Please select your dose of " << drugName << ":" << newLine;
        for (int x = 0;x <= arrLength(doses) ; ++x) {
            cout << "[" << i << "] " << doses[x] << newLine;
            i++;
        }
    };
    bool isValidDose(int e){
        int result = 0;
        for (int i = 0; i <= arrLength(doses); ++i) {
            //  If e is in doses[] return true
            result = e == doses[i] ? 1 : 0;
        }
        return result;
    }

};

/***********************************************************************************************************************
 *                              Function:           MAIN                                                               *
 ***********************************************************************************************************************/
int main(int argc, const char * argv[]) {
    //  Set variables
    char    choice;         /*  User input:         Choice of the drug from the list. a, b or c                         */
    string  drugUsed;       /*  Output:             Name of the drug used.                                              */
    int     dosage          /*  User input:         Choice of the drug from the list. Int from 1 to ritArraySize (4)    */
            ,doseUsed = 0   /*  Output:             Dose used in mg                                                     */
            ,tries = 0;     /*  Error handling:     Is incremented if user inputs an incorrect value for dosage         */
    bool    idiot = 1       /*  Error handling:     Is set to false if choice is 'a', 'b' or 'c'                        */
            ,canCount = 0;  /*  Error handling:     Is set to true if the user inputs a correct value for dosage        */

    //  Set Objects
    drug    concerta
            ,effexor
            ,ritalin;

    //  Set values for objects

    //  Ritalin
    int ritDoses[ritArraySize] {5,10,15,20};    /*  Array:  Contains all the values for ritalin.doses[]                 */
    for(int d = 0; d <= ritArraySize; d++){     /*  Set values from ritDoses[] to the object variable ritalin.doses[]   */
        ritalin.doses[d] = ritDoses[d];
    }
    ritalin.drugName = "Ritalin";               /*  Set object variable drugName for Ritalin                            */

    //  Effexor
    effexor.dose = 225;                         /*  Set object variable dose for Effexor                                */
    effexor.drugName = "Effexor";               /*  Set object variable drugName for Effexor                            */

    //  Concerta
    concerta.dose = 72;                         /*  Set object variable dose for Concerta                               */
    concerta.drugName = "Concerta";             /*  Set object variable drugName for Concerta                           */

    //  Print the drugs
    concerta.printName();
    effexor.printName();
    ritalin.printName();

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
                        cout    << "The selection must be between 1 and 4. EI: Type 1 for 5mg, 2 for 10mg…"
                                << newLine << "Try again:" << endl;
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
        }
    }while (idiot == 1);

    //  Print the result (this is mainly for debug but it might stay in prod)
    cout << /*time goes here <<*/ drugUsed << " " << doseUsed << "mg" << endl;

    return 0;
}

