#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class CountryCityManager {
private:
    map<string, vector<string>> data;

public:
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string country, city;
        while (file >> country >> city) {
            data[country].push_back(city);
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& entry : data) {
            const string& country = entry.first;
            const vector<string>& cities = entry.second;
            for (const auto& city : cities) {
                file << country << " " << city << endl;
            }
        }
    }

    void showCountries() {
        for (const auto& entry : data) {
            const string& country = entry.first;
            cout << country << endl;
        }
    }

    void showCities(const string& country) {
        if (data.count(country)) {
            for (const auto& city : data[country]) {
                cout << city << " ";
            }
            cout << endl;
        }
    }

    void addCity(const string& country, const string& city) {
        data[country].push_back(city);
    }

    void removeCity(const string& country, const string& city) {
        auto& cities = data[country];
        cities.erase(remove(cities.begin(), cities.end(), city), cities.end());
    }

    void removeCountry(const string& country) {
        data.erase(country);
    }

    int countCities() {
        int count = 0;
        for (const auto& entry : data) {
            const vector<string>& cities = entry.second;
            count += cities.size();
        }
        return count;
    }
};

int main() {
    CountryCityManager manager;
    manager.loadFromFile("data.txt");
    manager.addCity("France", "Lyon");
    manager.showCities("France");
    cout << "Total cities: " << manager.countCities() << endl;
    manager.saveToFile("data.txt");
    return 0;
}
