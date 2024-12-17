#pragma once
// ads.h
#ifndef ADS_H
#define ADS_H

#include <iostream>
#include <string>

using namespace std;

class engOil {
public:
    int oc;
    int ow;
    engOil(int oC, int oW);

    void write(ostream& out) const;
};

class Vehicle {
public:
    Vehicle(string t, string ma, string mo, string c, int y, int mi, float p, int oc, int ow);

    virtual void write(ostream& out) const;
    virtual void read(istream& in);

    string type;
    string make;
    string model;
    string condition;
    int year;
    int mileage;
    float price;
    engOil oil;
};

class Car : public Vehicle {
public:
    Car(string t, string ma, string mo, string c, int y, int mi, float p, int oC, int oW, string f);
    void read(istream& in);
    void write(ostream& out) const;

    string fuelType;
};

class Motorbike : public Vehicle {
public:
    Motorbike(string t, string ma, string mo, string c, int y, int mi, float p, int oC, int oW, string b);
    void read(istream& in);
    void write(ostream& out) const;

    string bikeType;
};

class Boat : public Vehicle {
public:
    Boat(string t, string ma, string mo, string c, int y, int mi, float p, int oc, int ow, int n);
    void read(istream& in);
    void write(ostream& out) const;

    int numEngines;
};

class node {
public:
    node(Vehicle* v);

    Vehicle* data;
    node* next;

};

class list {
public:
    list(void);

    void push(Vehicle* v);

    void pop(void);

    int size(void) const;

    void write(ostream& out) const;

    void delete_list(void);

    void sortbyprice(void);

    void searchbymake(void);

private:
    node* start;
    int count;
    // vector<Vehicle *> inventory;
};

void showmenu(void);

string fueltype(void);

void getinfo(string* ma, string* mo, string* c, int* y, int* mi, float* pr, int* oC, int* oW);

string biketype();

int numberofengines();

#endif