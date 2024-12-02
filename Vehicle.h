#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Vehicle {
private:
    string vin;
    string county;
    string city;
    string state;
    string postalCode;
    int modelYear;
    string make;
    string model;
    string evType;
    bool cafvEligible;
    double electricRange;
    double baseMsrp;
    int legislativeDistrict;
    string dolVehicleId;
    string vehicleLocation;
    string electricUtility;
    string censusTract;

public:
    // Constructor
    Vehicle();

    // Helper functions
    int strToInt(const string& str, int defaultVal = 0);
    double strToDouble(const string& str, double defaultVal = 0.0);

    // Setters
    void setVin(const string& v);
    void setCounty(const string& c);
    void setCity(const string& c);
    void setState(const string& s);
    void setPostalCode(const string& p);
    void setModelYear(int year);
    void setMake(const string& m);
    void setModel(const string& m);
    void setEvType(const string& t);
    void setCafvEligible(bool eligible);
    void setElectricRange(double range);
    void setBaseMsrp(double msrp);
    void setLegislativeDistrict(int district);
    void setDolVehicleId(const string& id);
    void setVehicleLocation(const string& loc);
    void setElectricUtility(const string& util);
    void setCensusTract(const string& tract);

    // Getters
    string getVin() const;
    string getCounty() const;
    string getCity() const;
    string getState() const;
    string getPostalCode() const;
    int getModelYear() const;
    string getMake() const;
    string getModel() const;
    string getEvType() const;
    bool isCafvEligible() const;
    double getElectricRange() const;
    double getBaseMsrp() const;
    int getLegislativeDistrict() const;
    string getDolVehicleId() const;
    string getVehicleLocation() const;
    string getElectricUtility() const;
    string getCensusTract() const;

    // Other methods
    void printDetails() const;
    bool parseFromCsv(const string& line);
};