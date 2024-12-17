#include "ads.h"

engOil::engOil(int oC, int oW) {
    oc = oC;
    ow = oW;
}

void engOil::write(ostream& out) const {
    out << ", Engine Oil: SAE " << oc << "W-" << ow << " ";
}

// Implementation of Vehicle class
Vehicle::Vehicle(string t, string ma, string mo, string c, int y, int mi,
    float p, int oC, int oW)
    : oil(oC, oW) {
    type = t;
    make = ma;
    model = mo;
    condition = c;
    year = y;
    mileage = mi;
    price = p;
}

void Vehicle::read(istream& in) {
    string ma, mo, t, f;
    int y, mi, fi, oC, oW;
    float pr;
    string c;
    char discard;

    cout << "Enter Make: ";
    cin >> ma;
    cout << "Enter Model: ";
    cin >> mo;
    cout << "Enter Condition: ";
    cin >> c;
    cout << "Enter Year: ";
    cin >> y;
    cout << "Enter Mileage: ";
    cin >> mi;
    cout << "Enter Price: ";
    cin >> pr;
    cout << "Enter Engine Oil (SEC ## W- ##): ";
    cin >> oC >> discard >> discard >> oW;
    Vehicle(t, ma, mo, c, y, mi, pr, oC, oW);
}

void Vehicle::write(ostream& out) const {
    out << "Type: " << type;
    out << ", Make: " << make;
    out << ", Model: " << model;
    out << ", Condition: " << condition;
    out << ", Year: " << year;
    out << ", Mileage: " << mileage;
    out << ", Price: " << price;
    oil.write(out);
}

// Implementation of Car class
Car::Car(string t, string ma, string mo, string c, int y, int mi, float p,
    int oC, int oW, string f)
    : Vehicle("car", ma, mo, c, y, mi, p, oC, oW) {
    fuelType = f;
}

void Car::read(istream& in) {
    string ma, mo, c, t, f;
    int y, mi, fi;
    float pr;

    fuelType = f;

    Vehicle::read(in);
    cout << "Enter fuel type (enter 1 for Gas, 2 for Hybrid or 3 for Electric): ";
    cin >> fi;
    if (fi == 1) {
        f = "Gas";
    }
    else if (fi == 2) {
        f = "Hybrid";
    }
    else if (fi == 3) {
        f = "Electric";
    }
}

void Car::write(std::ostream& out) const {
    Vehicle::write(out);
    out << ", Fuel Type: " << fuelType << endl << endl;
}

// Implementation of Motorbike class
Motorbike::Motorbike(string t, string ma, string mo, string c, int y, int mi,
    float p, int oC, int oW, string b)
    : Vehicle("mototrbike", ma, mo, c, y, mi, p, oC, oW) {
    bikeType = b;
}

void Motorbike::read(istream& in) {
    string ma, mo, t, f, b;
    int y, mi;
    int oC, oW;
    float pr;
    string c;
    bikeType = b;

    cout << "Enter bike type: ";
    cin >> b;
    // Motorbike *v = new Motorbike(t, ma, mo, c, y, mi, pr, oC, oW, b);
}

void Motorbike::write(ostream& out) const {
    Vehicle::write(out);
    out << ", Bike Type: " << bikeType << endl << endl;
}

// Implementation of Boat class
Boat::Boat(string t, string ma, string mo, string c, int y, int mi, float p,
    int oC, int oW, int n)
    : Vehicle("boat", ma, mo, c, y, mi, p, oC, oW) /*numEngines(n)*/ {
    numEngines = n;
}

void Boat::read(istream& in) {
    string ma, mo, t;
    int y, mi, n;
    float pr;
    string c;
    numEngines = n;

    cout << "Enter number of engines: ";
    cin >> n;
}
void Boat::write(ostream& out) const {
    Vehicle::write(out);
    out << ", Number of Engines: " << numEngines << endl << endl;
}

// Implementation of Node class
node::node(Vehicle* v) {
    data = v;
    next = NULL;
}

// Implementation of List class
list::list(void) {
    start = NULL;
    count = 0;
}

void list::push(Vehicle* v) {
    node* ptr = new node(v);
    ptr->next = start;
    start = ptr;
    count++;
}

void list::pop(void) {
    if (start == NULL) {
        cout << "No listings available" << endl << endl;
    }
    else {
        node* ptr = start;
        start = start->next;
        delete ptr;
        count--;
    }
}

int list::size(void) const { return count; }

void list::write(ostream& out) const {
    node* ptr = start;

    if (start == NULL) {
        out << "No vehicles listed" << endl << endl;
    }
    else {
        while (ptr != NULL) {
            Vehicle* v = ptr->data;
            // out << "Type: " << v->type;
            v->write(
                out); // call the write function of the corresponding derived class
            ptr = ptr->next;
        }
    }
}

void list::delete_list() {
    while (start != NULL) {
        node* temp = start;
        start = start->next;
        delete temp;
    }
    count = 0;
    cout << "All vehicles deleted." << endl;
}

void list::sortbyprice() {
    if (start == NULL || start->next == NULL) {
        cout << "Not enough data listed to sort." << endl << endl;
        return;
    }

    bool swapped = true;
    while (swapped) {
        swapped = false;
        node* curr = start;

        while (curr->next != NULL) {
            if (curr->data->price > curr->next->data->price) {
                // Swap data in two nodes
                Vehicle* temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = true;

                curr = curr->next;
            }
            else {
                curr = curr->next;
            }
        }
    }
    Vehicle* v;
    cout << "Vehicles sorted by price." << endl << endl;
}




void list::searchbymake() {
    string make;
    cout << "Enter the make you want to search for: ";
    cin >> make;
    cout << endl;

    node* curr = start;
    bool found = false;
    while (curr != NULL) {
        if (curr->data->make == make) {
            found = true;
            curr->data->write(cout);
        }
        curr = curr->next;
    }
    if (!found) {
        cout << endl << "Vehicle not found." << endl << endl;
    }
}


void showmenu() {
    cout << endl;
    cout << "Please choose prompts from the following options: " << endl;
    cout << endl;
    cout << "Add listing = 1" << endl;
    cout << "View all listings = 2" << endl;
    cout << "View total number of listings = 3" << endl;
    cout << "Remove most recent listing = 4" << endl;
    cout << "Clear list = 5" << endl;
    cout << "Search by make = 6" << endl;
    cout << "Sort by price = 7" << endl;

    cout << "quit = q" << endl;
    cout << endl;
    return;
}

string fueltype() {
    int fi;
    string f;

    cout << "Enter Fuel Type (enter 1 = Gas, 2 = Hybrid or 3 = Electric): ";
    cin >> fi;
    if (fi == 1) {
        f = "Gas";
    }
    else if (fi == 2) {
        f = "Hybrid";
    }
    else if (fi == 3) {
        f = "Electric";
    }
    return f;
}

void getinfo(string* ma, string* mo, string* c, int* y, int* mi, float* pr,
    int* oC, int* oW) {

    string lma, lmo, lc;
    int ly, lmi;
    int loc, low;
    float lpr;

    cout << "Enter Make: ";
    cin >> lma;
    cout << "Enter Model: ";
    cin >> lmo;
    cout << "Enter Condition: ";
    cin >> lc;
    cout << "Enter Year: ";
    cin >> ly;
    cout << "Enter Mileage: ";
    cin >> lmi;
    cout << "Enter Price: ";
    cin >> lpr;
    cout << "Enter idle oil Viscocity Rating: ";
    cin >> loc;
    cout << "Enter Operating oil Viscocity Rating: ";
    cin >> low;
    cout << endl;

    *ma = lma;
    *mo = lmo;
    *c = lc;
    *y = ly;
    *mi = lmi;
    *pr = lpr;
    *oC = loc;
    *oW = low;
}

string biketype() {
    string biketype;
    int choice;
    cout << "Enter bike type(1 for Sport, 2 for Touring, 3 for Dirt, 4 for "
        "Scooter): ";
    cin >> choice;

    if (choice == 1) {
        biketype = "Sport";
    }
    else if (choice == 2) {
        biketype = "Touring";
    }
    else if (choice == 3) {
        biketype = "Dirt";
    }
    else if (choice == 4) {
        biketype = "Scooter";
    }
    else {
        cout << "wrong input" << endl;
    }

    return biketype;
}

int numberofengines() {
    int n, check;

    cout << "Enter number of engines(2, 4, 5 or 6): ";
    cin >> n;

    if (n == 2 || n == 4 || n == 5 || n == 6) {
        check = n;
    }
    else {
        cout << "invalid number of engines, please restart program. ";
    }
    return check;
}
