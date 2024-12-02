#include "Vehicle.h"

Vehicle::Vehicle() {
    this->modelYear = 0;
    this->cafvEligible = false;
    this->electricRange = 0.0f;
    this->baseMsrp = 0.0f;
    this->legislativeDistrict = 0;
}

int Vehicle::strToInt(const string& str, int defaultVal) {
    if (str.empty())
        return defaultVal;
    else
        return stoi(str);
}

double Vehicle::strToDouble(const string& str, double defaultVal) {
    if (str.empty())
        return defaultVal;
    else
        return stod(str);
}

// Setters
void Vehicle::setVin(const string& v) {
    vin = v;
}
void Vehicle::setCounty(const string& c) {
    county = c;
}
void Vehicle::setCity(const string& c) {
    city = c;
}
void Vehicle::setState(const string& s) {
    state = s;
}
void Vehicle::setPostalCode(const string& p) {
    postalCode = p;
}
void Vehicle::setModelYear(int year) {
    modelYear = year;
}
void Vehicle::setMake(const string& m) {
    make = m;
}
void Vehicle::setModel(const string& m) {
    model = m;
}
void Vehicle::setEvType(const string& t) {
    evType = t;
}
void Vehicle::setCafvEligible(bool eligible) {
    cafvEligible = eligible;
}
void Vehicle::setElectricRange(double range) {
    electricRange = range;
}
void Vehicle::setBaseMsrp(double msrp) {
    baseMsrp = msrp;
}
void Vehicle::setLegislativeDistrict(int district) {
    legislativeDistrict = district;
}
void Vehicle::setDolVehicleId(const string& id) {
    dolVehicleId = id;
}
void Vehicle::setVehicleLocation(const string& loc) {
    vehicleLocation = loc;
}
void Vehicle::setElectricUtility(const string& util) {
    electricUtility = util;
}
void Vehicle::setCensusTract(const string& tract) {
    censusTract = tract;
}

// Getters
string Vehicle::getVin() const {
    return vin;
}
string Vehicle::getCounty() const {
    return county;
}
string Vehicle::getCity() const {
    return city;
}
string Vehicle::getState() const {
    return state;
}
string Vehicle::getPostalCode() const {
    return postalCode;
}
int Vehicle::getModelYear() const {
    return modelYear;
}
string Vehicle::getMake() const {
    return make;
}
string Vehicle::getModel() const {
    return model;
}
string Vehicle::getEvType() const {
    return evType;
}
bool Vehicle::isCafvEligible() const {
    return cafvEligible;
}
double Vehicle::getElectricRange() const {
    return electricRange;
}
double Vehicle::getBaseMsrp() const {
    return baseMsrp;
}
int Vehicle::getLegislativeDistrict() const {
    return legislativeDistrict;
}
string Vehicle::getDolVehicleId() const {
    return dolVehicleId;
}
string Vehicle::getVehicleLocation() const {
    return vehicleLocation;
}
string Vehicle::getElectricUtility() const {
    return electricUtility;
}
string Vehicle::getCensusTract() const {
    return censusTract;
}

void Vehicle::printDetails() const {
    cout << "VIN: " << vin << "\n"
         << "Make: " << make << "\n"
         << "Model: " << model << " (" << modelYear << ")\n"
         << "Location: " << city << ", " << state << " " << postalCode << "\n"
         << "EV Type: " << evType << "\n"
         << "Electric Range: " << electricRange << " miles\n"
         << "Base MSRP: $" << baseMsrp << "\n";
}

bool Vehicle::parseFromCsv(const string& line) {
    istringstream ss(line);
    string token;

    try {
        getline(ss, token, ',');
        setVin(token);

        getline(ss, token, ',');
        setCounty(token);

        getline(ss, token, ',');
        setCity(token);

        getline(ss, token, ',');
        setState(token);

        getline(ss, token, ',');
        setPostalCode(token);

        getline(ss, token, ',');
        setModelYear(strToInt(token));

        getline(ss, token, ',');
        setMake(token);

        getline(ss, token, ',');
        setModel(token);

        getline(ss, token, ',');
        setEvType(token);

        getline(ss, token, ',');
        setCafvEligible(token == "Clean Alternative Fuel Vehicle Eligible");

        getline(ss, token, ',');
        setElectricRange(strToDouble(token));

        getline(ss, token, ',');
        setBaseMsrp(strToDouble(token));

        getline(ss, token, ',');
        setLegislativeDistrict(strToInt(token));

        getline(ss, token, ',');
        setDolVehicleId(token);

        getline(ss, token, ',');
        setVehicleLocation(token);

        getline(ss, token, ',');
        setElectricUtility(token);

        getline(ss, token, '\n');
        setCensusTract(token);

        return true;
    } catch (...) {
        return false;
    }
}