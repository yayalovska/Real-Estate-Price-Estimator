#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const double MAX_AREA = 1000.0;
const double MIN_AREA = 30.0;
const int MAX_NUMBER_OF_BEDROOMS = 10;
const int MIN_NUMBER_OF_BEDROOMS = 1;
const int MAX_NUMBER_OF_TOILETS = 5;
const int MIN_NUMBER_OF_TOILETS = 1;
const int MAX_DISTANCE_TO_SUBWAY = 60;
const int MIN_DISTANCE_TO_SUBWAY = 1;
const double MAX_COST = 10000000.0;
const double MIN_COST = 20000.0;


struct RealtyFeatures {
    double area;
    int number_of_bedrooms;
    int number_of_toilets;
    int distance_to_subway;
    bool is_commercial;
    double cost;
};

RealtyFeatures read_real_estate_data(bool need_to_read_cost);
vector <RealtyFeatures> read_training_data();
double predict(const vector<RealtyFeatures>& realty_list, const RealtyFeatures& target_real_estate);


bool is_number(const string& str);
int read_integer_value();
double read_double_value();
double read_area_value();
int read_number_of_bedrooms();
int read_number_of_toilets();
int read_distance_to_subway();
int read_real_estate_type();
double read_cost_value();

bool is_valid_area(double area);
bool is_valid_number_of_bedrooms(int number_of_bedrooms);
bool is_valid_number_of_toilet(int number_of_toilet);
bool is_valid_distance_to_subway(int distance_to_subway);
bool is_valid_type(int commercial_or_residential);
bool is_valid_cost(double cost);

int main() {

    cout.precision(10);
    vector<RealtyFeatures> training_realty = read_training_data();

    bool need_to_read_data = true;
    do
    {
        cout << "Please enter the specified data about the house to determine the approximate price of the apartments. "<< endl ;
        cout << "Enter '0' as value for area parameter to finish input data." << endl << endl;


        RealtyFeatures target_realty = read_real_estate_data(false);
        if (target_realty.area > 0.0) {
            double target_cost = predict(training_realty, target_realty);
            cout << "The calculated cost is: " << target_cost << endl << endl;
        }
        else
            need_to_read_data = false;

    } while (need_to_read_data);
}

RealtyFeatures read_real_estate_data(bool need_to_read_cost) {
    RealtyFeatures real_estate;

    real_estate.area = read_area_value();
    if (real_estate.area == 0.0)
        return real_estate;

    real_estate.number_of_bedrooms = read_number_of_bedrooms();
    real_estate.number_of_toilets = read_number_of_toilets();
    real_estate.distance_to_subway = read_distance_to_subway();
    real_estate.is_commercial = read_real_estate_type();

    if (need_to_read_cost)
        real_estate.cost = read_cost_value();

    return real_estate;
}

vector<RealtyFeatures> read_training_data() {
    vector<RealtyFeatures> realty;
    bool read_data_to_analize = true;
    do
    {
        cout << "Please enter the training data about the house to evaluate price of the apartments in next step. " << endl;
        cout << "Enter '0' as value for area parameter to finish input data." << endl << endl;

        RealtyFeatures real_estate = read_real_estate_data(true);
        if (real_estate.area > 0.0)
            realty.push_back(real_estate);
        else if (realty.empty())
            cout << "You have entered insufficient amount of real estate units. Please enter data about at least one real estate." << endl << endl;
        else
            read_data_to_analize = false;

    } while (read_data_to_analize);

    cout << "Process inputting training data is finished!" << endl << endl;

    return realty;
}
//
double predict(const vector<RealtyFeatures>& realty_list, const RealtyFeatures& target_real_estate) {
    double target_cost = 0.0;


    auto nearest_real_estate = min_element(realty_list.begin(), realty_list.end(),
                                           [target_real_estate](const RealtyFeatures& first_realty, const RealtyFeatures& second_realty) {
                                               return abs(first_realty.area - target_real_estate.area) < abs(second_realty.area - target_real_estate.area);
                                           });


    if (nearest_real_estate != realty_list.end()) {

        double area_coefficient = target_real_estate.area / nearest_real_estate->area;

        target_cost = nearest_real_estate->cost * area_coefficient;
    }

    return target_cost;
}

bool is_number(const string& str) {
    return !str.empty() && std::find_if(str.begin(),
                                        str.end(), [](char c) { return !(isdigit(c) || c == '.'); }) == str.end();
}

int read_integer_value() {
    int int_value = -1;
    string str_value;
    if (!(cin >> str_value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (is_number(str_value)) {
        int_value = atoi(str_value.c_str());
    }

    return int_value;
}

double read_double_value() {
    double double_value = -1.0;
    string str_value;
    if (!(cin >> str_value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (is_number(str_value)) {
        double_value = atof(str_value.c_str());
    }

    return double_value;
}

double read_area_value() {
    double area;
    cout << "Please enter area of apartment: (values from " << MIN_AREA << " to " << MAX_AREA << ")." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        area = read_double_value();
        if (area != 0.0 && !is_valid_area(area)) {
            cout << "The area of the apartment is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return area;
}

int read_number_of_bedrooms() {
    int number_of_bedrooms;
    cout << "Please, enter the number of bedrooms: (values from " << MIN_NUMBER_OF_BEDROOMS
         << " to " << MAX_NUMBER_OF_BEDROOMS << ")." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        number_of_bedrooms = read_integer_value();
        if (!is_valid_number_of_bedrooms(number_of_bedrooms)) {
            cout << "The number of bedrooms of the apartment is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return number_of_bedrooms;
}

int read_number_of_toilets() {
    int number_of_toilets;
    cout << "Please, enter the number of toilets: (values from " << MIN_NUMBER_OF_TOILETS
         << " to " << MAX_NUMBER_OF_TOILETS << ")." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        number_of_toilets = read_integer_value();
        if (!is_valid_number_of_toilet(number_of_toilets)) {
            cout << "The number of toilet of the apartment is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return number_of_toilets;
}

int read_distance_to_subway() {
    int distance_to_subway;
    cout << "Please, enter the distance to the subway in minute on foot: (values from " << MIN_DISTANCE_TO_SUBWAY
         << " to " << MAX_DISTANCE_TO_SUBWAY << ")." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        distance_to_subway = read_integer_value();
        if (!is_valid_distance_to_subway(distance_to_subway)) {
            cout << "The number distance to subway of the apartment is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return distance_to_subway;
}

int read_real_estate_type() {
    int real_estate_type;
    cout << "Specify the type of real estate. If it's commercial write '0' and if it's residential write '1'." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        real_estate_type = read_integer_value();
        if (!is_valid_type(real_estate_type)) {
            cout << "The entered value is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return real_estate_type;
}

double read_cost_value() {
    double cost;
    cout << "Please, enter the cost of real estate. Pay attention that the target should be in the range between "
         << MIN_COST << " and " << MAX_COST << "." << endl;

    bool is_valid_input_data;
    do {
        is_valid_input_data = true;
        cost = read_double_value();
        if (!is_valid_cost(cost)) {
            cout << "The cost of the apartment is incorrect. Please, enter again." << endl;
            is_valid_input_data = false;
        }
    } while (!is_valid_input_data);

    return cost;
}

bool is_valid_area(double area) {
    return area >= MIN_AREA && area <= MAX_AREA;
}

bool is_valid_number_of_bedrooms(int number_of_bedrooms) {
    return number_of_bedrooms >= MIN_NUMBER_OF_BEDROOMS && number_of_bedrooms <= MAX_NUMBER_OF_BEDROOMS;
}

bool is_valid_number_of_toilet(int number_of_toilet) {
    return number_of_toilet >= MIN_NUMBER_OF_TOILETS && number_of_toilet <= MAX_NUMBER_OF_TOILETS;
}

bool is_valid_distance_to_subway(int distance_to_subway) {
    return distance_to_subway >= MIN_DISTANCE_TO_SUBWAY && distance_to_subway <= MAX_DISTANCE_TO_SUBWAY;
}

bool is_valid_type(int commercial_or_residential) {
    return commercial_or_residential == 0 || commercial_or_residential == 1;
}

bool is_valid_cost(double cost) {
    return cost >= MIN_COST && cost <= MAX_COST;
}
