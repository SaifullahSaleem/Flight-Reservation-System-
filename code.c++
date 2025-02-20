#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define MAXCITY 30
#define MAXFLIGHT 200
#define MINLAYOVER 30

// Flight structure
struct FlightType {
    int FlightNo;
    string startCity;
    int timeDepart;
    string endCity;
    int timeArrival;
    int noOfPassengers;
    FlightType* nextDeparture;
    FlightType* nextArrival;
};

// Reservation route structure
struct RouteType {
    int Day;
    int nHops;
    int FlightNo1;
    int FlightNo2;
};

#define ROUNDTRIP 0
#define ONEWAY 1

// Reservation structure
struct ReservationType {
    string firstName;
    string lastName;
    int tripType;
    RouteType route1;
    RouteType route2;
    ReservationType* nextReserve;
};

// Merged City structure
struct CityType {
    string cityName;
    FlightType* nextDeparture;
    FlightType* nextArrival;
    vector< pair<string, int> > adjCities; // Adjacent cities and their weights
    int distance;
    string previous;
};

// Flight number list structure
struct FlightNumberListType {
    int FlightNo;
    FlightType* flight;
};

// Global Variables
unordered_map <string, CityType> cityMap;
FlightNumberListType flightList[MAXFLIGHT];
int flightCount = 0;
ReservationType* reserveHead = nullptr;
ReservationType* reserveTail = nullptr;

// Function to create and initialize a flight node
FlightType* MakeFlightNode(int flightNo, const string& startCity, int timeDepart,
                            const string& endCity, int timeArrival, int noOfPassengers) {
    FlightType* newFlight = new FlightType;
    newFlight->FlightNo = flightNo;
    newFlight->startCity = startCity;
    newFlight->timeDepart = timeDepart;
    newFlight->endCity = endCity;
    newFlight->timeArrival = timeArrival;
    newFlight->noOfPassengers = noOfPassengers;
    newFlight->nextDeparture = nullptr;
    newFlight->nextArrival = nullptr;
    return newFlight;
}

// Initialize the city list
void InitializeCityList() {
    cityMap.clear();
}

// Add flight to the city list
void AddFlightToCityList(FlightType* flight) {
    // If start city is not in the map, add it
    if (cityMap.find(flight->startCity) == cityMap.end()) {
        CityType newCity;
        newCity.cityName = flight->startCity;
        cityMap[flight->startCity] = newCity;
    }

    // Add the flight to the departure city list
    flight->nextDeparture = cityMap[flight->startCity].nextDeparture;
    cityMap[flight->startCity].nextDeparture = flight;

    // Repeat the process for the arrival city
    if (cityMap.find(flight->endCity) == cityMap.end()) {
        CityType newCity;
        newCity.cityName = flight->endCity;
        cityMap[flight->endCity] = newCity;
    }
    flight->nextArrival = cityMap[flight->endCity].nextArrival;
    cityMap[flight->endCity].nextArrival = flight;
}

// Add flight to the flight list
void AddFlightToFlightList(FlightType* flight) {
    flightList[flightCount].FlightNo = flight->FlightNo;
    flightList[flightCount].flight = flight;

    sort(flightList, flightList + flightCount + 1, [](const FlightNumberListType& a, const FlightNumberListType& b) {
        return a.FlightNo < b.FlightNo;
    });

    ++flightCount;
}

// Function to create and initialize a reservation node
ReservationType* MakeReserveNode(const string& firstName, const string& lastName,
                                int tripType, int day, int nHops,
                                int flightNo1, int flightNo2) {
    ReservationType* newReservation = new ReservationType;
    newReservation->firstName = firstName;
    newReservation->lastName = lastName;
    newReservation->tripType = tripType;
    newReservation->route1.Day = day;
    newReservation->route1.nHops = nHops;
    newReservation->route1.FlightNo1 = flightNo1;
    newReservation->route1.FlightNo2 = flightNo2;
    newReservation->nextReserve = nullptr;
    return newReservation;
}

// Add reservation to the reservation list
void AddReservation(ReservationType* newReservation) {
    if (reserveHead == nullptr) {
        reserveHead = newReservation;
        reserveTail = newReservation;
    } else {
        ReservationType* current = reserveHead;
        ReservationType* prev = nullptr;

        // Traverse the list to find the appropriate position for the new reservation
        while (current != nullptr &&
            (newReservation->lastName > current->lastName ||
            (newReservation->lastName == current->lastName &&
            newReservation->firstName > current->firstName))) {
            prev = current;
            current = current->nextReserve;
        }

        // Insert the new reservation into the list
        if (prev == nullptr) {
            newReservation->nextReserve = reserveHead;
            reserveHead = newReservation;
        } else {
            prev->nextReserve = newReservation;
            newReservation->nextReserve = current;
            if (current == nullptr) {
                reserveTail = newReservation;
            }
        }
    }
}

// Function to display information of a flight
void DisplayFlightInfo(FlightType* flight) {
    cout << "Flight No: " << flight->FlightNo << ", From: " << flight->startCity
        << ", To: " << flight->endCity << ", Departure Time: " << flight->timeDepart
        << ", Arrival Time: " << flight->timeArrival << ", Passengers: "
        << flight->noOfPassengers << endl;
}

// Function to display all flights' information
void DisplayAllFlightsData() {
    cout << "Flights Information:" << endl;
    for (int i = 0; i < flightCount; ++i) {
        DisplayFlightInfo(flightList[i].flight);
    }
}

// Function to display all cities serviced by the airline
void DisplayAllCities() {
    cout << "\nCities Serviced by the Airline:" << endl;
    for (const auto& city : cityMap) {
        cout << city.first << endl;
    }
    cout << endl;
}

// Function to display a list of cities reachable from a specific city
void DisplayCitiesFromCity(const string& cityName) {
    cout << "Cities reachable from " << cityName << ":" << endl;

    // Find the departure list for the given city
    if (cityMap.find(cityName) == cityMap.end() || cityMap[cityName].nextDeparture == nullptr) {
        cout << "No cities reachable." << endl;
        return;
    }

    FlightType* departureList = cityMap[cityName].nextDeparture;
    set<string> reachableCities;

    while (departureList != nullptr) {
        reachableCities.insert(departureList->endCity);
        departureList = departureList->nextDeparture;
    }

    if (reachableCities.empty()) {
        cout << "No cities reachable." << endl;
        return;
    }

    for (const string& city : reachableCities) {
        cout << city << endl;
    }

    cout << endl;
}


int FindCityIndex(const string& cityName, unordered_map<string, CityType>& cityMap) {
    auto it = cityMap.find(cityName);
    if (it != cityMap.end()) {
        return distance(cityMap.begin(), it);
    }
    return -1; // City not found
}


void DijkstraShortestPath(const string& startCity, const string& endCity, unordered_map<string, CityType>& cityMap) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    for (auto& entry : cityMap) {
        entry.second.distance = INT_MAX;
    }

    int startIndex = FindCityIndex(startCity, cityMap);
    int endIndex = FindCityIndex(endCity, cityMap);

    if (startIndex == -1 || endIndex == -1) {
        cout << "Invalid start or end city." << endl;
        return;
    }

    cityMap[startCity].distance = 0;
    pq.push({0, startCity});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for (auto& adjCity : cityMap[u].adjCities) {
            string v = adjCity.first;
            int weight = adjCity.second;

            if (cityMap[u].distance != INT_MAX && cityMap[u].distance + weight < cityMap[v].distance) {
                cityMap[v].distance = cityMap[u].distance + weight;
                cityMap[v].previous = u;
                pq.push({cityMap[v].distance, v});
            }
        }
    }

    // Extract and display the shortest path
    if (cityMap[endCity].distance == INT_MAX) {
        cout << "\nNo path found between " << startCity << " and " << endCity << "." << endl;
        return;
    }

    cout << "\nShortest path between " << startCity << " and " << endCity << " is: ";
    string currentNode = endCity;
    vector<string> shortestPath;

    while (currentNode != startCity) {
        shortestPath.push_back(currentNode);
        currentNode = cityMap[currentNode].previous;
    }

    shortestPath.push_back(startCity);

    for (auto it = shortestPath.rbegin(); it != shortestPath.rend(); ++it) {
        cout << *it;
        if (it != shortestPath.rend() - 1) {
            cout << " -> ";
        }
    }

    cout << endl;
}

// Function to perform Depth-First Search (DFS) to find all possible routes
void DFSFindAllRoutes(const string& startCity, const string& endCity, unordered_map<string, CityType>& cityMap, vector<string>& currentRoute, vector<vector<string>>& allRoutes, unordered_set<string>& visited) {
    visited.insert(startCity);
    currentRoute.push_back(startCity);

    if (startCity == endCity) {
        allRoutes.push_back(currentRoute);
    } else {
        for (const auto& adjCity : cityMap[startCity].adjCities) {
            const string& nextCity = adjCity.first;
            if (visited.find(nextCity) == visited.end()) {
                DFSFindAllRoutes(nextCity, endCity, cityMap, currentRoute, allRoutes, visited);
            }
        }
    }

    visited.erase(startCity);
    currentRoute.pop_back();
}

// Function to find all possible routes between two cities using DFS
vector<vector<string>> DFSFindAllRoutes(const string& startCity, const string& endCity, unordered_map<string, CityType>& cityMap) {
    vector<vector<string>> allRoutes;
    vector<string> currentRoute;
    unordered_set <string> visited;

    DFSFindAllRoutes(startCity, endCity, cityMap, currentRoute, allRoutes, visited);

    return allRoutes;
}

// Function to print a list of passengers of a particular flight (in order of last name)
void PrintPassengersOfFlight(int flightNo, ReservationType* reserveHead) {
    cout << "Passengers of Flight " << flightNo << " (in order of last name):" << endl;

    vector<pair<string, string>> passengers; // Store pairs of (last name, full name)

    // Traverse the reservation list and collect passengers of the specified flight
    ReservationType* currentReservation = reserveHead;
    while (currentReservation != nullptr) {
        if (currentReservation->route1.FlightNo1 == flightNo || currentReservation->route1.FlightNo2 == flightNo) {
            // Collect last name and full name of the passenger
            string lastName = currentReservation->lastName;
            string fullName = currentReservation->firstName + " " + lastName;
            passengers.push_back({lastName, fullName});
        }
        currentReservation = currentReservation->nextReserve;
    }

    // Sort passengers in order of last name
    sort(passengers.begin(), passengers.end());

    // Display passengers in order of last name
    for (const auto& passenger : passengers) {
        cout << passenger.second << endl;
    }
}

// Function to show a list of flight departures for a city, sorted by time of departure
void ShowDeparturesForCity(const string& cityName, unordered_map<string, CityType>& cityMap) {
    cout << "\nFlight departures from " << cityName << ", sorted by time of departure:" << endl;

    if (cityMap.find(cityName) == cityMap.end() || cityMap[cityName].nextDeparture == nullptr) {
        cout << "No departures found for " << cityName << "." << endl;
        return;
    }

    vector<FlightType*> departures;

    // Traverse the departure list for the given city and collect flights
    FlightType* departureList = cityMap[cityName].nextDeparture;
    while (departureList != nullptr) {
        departures.push_back(departureList);
        departureList = departureList->nextDeparture;
    }

    // Sort departures by time of departure
    sort(departures.begin(), departures.end(), [](const FlightType* a, const FlightType* b) {
        return a->timeDepart < b->timeDepart;
    });

    // Display sorted departure flights
    for (const auto& departure : departures) {
        cout << "Flight No: " << departure->FlightNo << ", Departure Time: " << departure->timeDepart
            << ", To: " << departure->endCity << endl;
    }
}

// Function to show a list of flight arrivals for a city, sorted by time of arrival
void ShowArrivalsForCity(const string& cityName, unordered_map<string, CityType>& cityMap) {
    cout << "\nFlight arrivals at " << cityName << ", sorted by time of arrival:" << endl;

    if (cityMap.find(cityName) == cityMap.end() || cityMap[cityName].nextArrival == nullptr) {
        cout << "No arrivals found for " << cityName << "." << endl;
        return;
    }

    vector<FlightType*> arrivals;

    // Traverse the arrival list for the given city and collect flights
    FlightType* arrivalList = cityMap[cityName].nextArrival;
    while (arrivalList != nullptr) {
        arrivals.push_back(arrivalList);
        arrivalList = arrivalList->nextArrival;
    }

    // Sort arrivals by time of arrival
    sort(arrivals.begin(), arrivals.end(), [](const FlightType* a, const FlightType* b) {
        return a->timeArrival < b->timeArrival;
    });

    // Display sorted arrival flights
    for (const auto& arrival : arrivals) {
        cout << "Flight No: " << arrival->FlightNo << ", Arrival Time: " << arrival->timeArrival
            << ", From: " << arrival->startCity << endl;
    }
}


// Main function
int main() {
    InitializeCityList();

    FlightType* flight1 = MakeFlightNode(1, "CityA", 830, "CityB", 950, 100);
    FlightType* flight2 = MakeFlightNode(2, "CityB", 1200, "CityC", 1400, 150);
    FlightType* flight3 = MakeFlightNode(3, "CityC", 1200, "CityD", 2000, 190);
    FlightType* flight4 = MakeFlightNode(4, "CityD", 1400, "CityE", 1700, 150);
    FlightType* flight5 = MakeFlightNode(5, "CityB", 1800, "CityE", 2200, 150);

    // Add edges between cities (connections/flights)
    cityMap["CityA"].adjCities.push_back({"CityB", 2});
    cityMap["CityB"].adjCities.push_back({"CityA", 3});
    cityMap["CityB"].adjCities.push_back({"CityC", 4});
    cityMap["CityC"].adjCities.push_back({"CityB", 1});
    cityMap["CityC"].adjCities.push_back({"CityD", 7});
    cityMap["CityD"].adjCities.push_back({"CityC", 3});
    cityMap["CityD"].adjCities.push_back({"CityE", 4});
    cityMap["CityE"].adjCities.push_back({"CityD", 5});
    cityMap["CityB"].adjCities.push_back({"CityE", 7});
    cityMap["CityE"].adjCities.push_back({"CityB", 1});

    AddFlightToCityList(flight1);
    AddFlightToFlightList(flight1);
    AddFlightToCityList(flight2);
    AddFlightToFlightList(flight2);
    AddFlightToCityList(flight3);
    AddFlightToFlightList(flight3);
    AddFlightToCityList(flight4);
    AddFlightToFlightList(flight4);
    AddFlightToCityList(flight5);
    AddFlightToFlightList(flight5);

    ReservationType* reservation1 = MakeReserveNode("John", "Doe", ROUNDTRIP, 1215, 2, 1, 2);
    ReservationType* reservation2 = MakeReserveNode("Alice", "Smith", ONEWAY, 1220, 1, 3, 0);
    ReservationType* reservation3 = MakeReserveNode("Emily", "Johnson", ROUNDTRIP, 1217, 1, 2, 0);
    ReservationType* reservation4 = MakeReserveNode("Michael", "Williams", ONEWAY, 1218, 2, 3, 4);
    ReservationType* reservation5 = MakeReserveNode("Sophia", "Brown", ROUNDTRIP, 1220, 2, 1, 4);
    
    AddReservation(reservation1);
    AddReservation(reservation2);
    AddReservation(reservation3);
    AddReservation(reservation4);
    AddReservation(reservation5);

    DisplayAllFlightsData();

    cout << "\nReservations Information:" << endl;
    ReservationType* currentReservation = reserveHead;
    while (currentReservation != nullptr) {
        cout << "Name: " << currentReservation->firstName << " " << currentReservation->lastName << endl;
        cout << "Trip Type: " << (currentReservation->tripType == ROUNDTRIP ? "Round Trip" : "One Way") << endl;
        cout << "Day: " << currentReservation->route1.Day << endl;
        if (currentReservation->route1.nHops == 1) {
            cout << "Flight 1: " << currentReservation->route1.FlightNo1 << endl;
        } else {
            cout << "Flight 1: " << currentReservation->route1.FlightNo1 << ", Flight 2: "
                << currentReservation->route1.FlightNo2 << endl;
        }
        cout << endl;

        currentReservation = currentReservation->nextReserve;
    }

    // Print passengers of Flight No. 1
    PrintPassengersOfFlight(1, reserveHead);

    // Assuming you want to display departures and arrivals for "CityA"
    ShowDeparturesForCity("CityA", cityMap);
    ShowArrivalsForCity("CityA", cityMap);

    DisplayAllCities();
    DisplayCitiesFromCity("CityA");
    DisplayCitiesFromCity("CityB");
    DisplayCitiesFromCity("CityC");
    DisplayCitiesFromCity("CityD");
    DisplayCitiesFromCity("CityE");

    DijkstraShortestPath("CityA", "CityE", cityMap);

  // Finding all possible routes between two cities using DFS
    cout << "\nAll possible routes between CityA and CityE (DFS):" << endl;
    vector<vector<string>> allRoutesDFS = DFSFindAllRoutes("CityA", "CityE", cityMap);

    if (allRoutesDFS.empty()) {
        cout << "\nNo routes found between CityA and CityE using DFS." << endl;
    } else {
        int routeNumber = 1;
        for (const auto& route : allRoutesDFS) {
            cout << "Route " << routeNumber << ": ";
            for (size_t i = 0; i < route.size(); ++i) {
                cout << route[i];
                if (i != route.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
            routeNumber++;
        }
    }

    // Free allocated memory or delete the reservations
    for (int i = 0; i < flightCount; ++i) {
        delete flightList[i].flight;
    }

    delete reservation1;
    delete reservation2;
    delete reservation3;
    delete reservation4;
    delete reservation5;

    return 0;
}
