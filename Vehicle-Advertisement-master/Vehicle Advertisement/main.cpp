#include "ads.h"
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    list list;
    string p, tp;

    while (true) {

        showmenu();

        cin >> p; // Reads user input
        cout << endl;
        if (p == "1") {

            cout << "What type of Vehicle would you like to add (car/motorbike/boat): ";
            cin >> tp;
            if (tp == "car") {
                string ma, mo, c, t, f;
                // int y, mi, fi;
                int y, mi, oC, oW;
                float pr;

                getinfo(&ma, &mo, &c, &y, &mi, &pr, &oC, &oW);

                f = fueltype();

                Car* v = new Car("Car", ma, mo, c, y, mi, pr, oC, oW, f);
                // v->read(cin);
                list.push(v);

            }
            else if (tp == "motorbike") {

                string ma, mo, c, b, t;
                int y, mi, oC, oW;
                float pr;

                getinfo(&ma, &mo, &c, &y, &mi, &pr, &oC, &oW);

                b = biketype();

                Motorbike* v = new Motorbike("Motorbike", ma, mo, c, y, mi, pr, oC, oW, b);
                list.push(v);

            }
            else if (tp == "boat") {

                string ma, mo, c, t;
                int y, mi, n, oC, oW;
                float pr;

                getinfo(&ma, &mo, &c, &y, &mi, &pr, &oC, &oW);
                n = numberofengines();

                Boat* v = new Boat("Boat", ma, mo, c, y, mi, pr, oC, oW, n);
                list.push(v);

            }
            else {
                cout << "Invalid input. Please try again." << endl;
            }

        }
        else if (p == "2") {
            list.write(cout);
        }
        else if (p == "3") {
            cout << "Total number of listings: " << list.size() << endl << endl;
        }
        else if (p == "4") {
            list.pop();
        }
        else if (p == "5") {
            list.delete_list();
        }
        else if (p == "q") {
            cout << "Bye :)";
            break;
        }
        else if (p == "6") {
            list.searchbymake();
        }
        else if (p == "7") {
            list.sortbyprice();

        }


    }

    return 0;
}