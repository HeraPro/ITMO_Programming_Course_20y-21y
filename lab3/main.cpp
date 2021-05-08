#include <iostream>
#include <vector>
#include <string>
#include "src/pugixml.hpp"
#include <unordered_map>
#include <cmath>
#include <climits>

using std::string, std::vector, std::pair, std::cout, std::endl, std::unordered_map;

struct Transport_station {
    //string the_official_name;
    vector<string> locations;
    vector<string> routes;
    pair<double, double> coordinates;
};

bool cmp(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second < b.second;
}

void RouteWithTheMostStations(vector<Transport_station>& stations_of_one_type_of_transport) {
    unordered_map<string, int> Routes;
    for (const auto& one_station : stations_of_one_type_of_transport) {
        for (const auto &route : one_station.routes) {
            Routes.try_emplace(route, 0);
            ++Routes[route];
        }
    }
    auto max_route = max_element(Routes.begin(), Routes.end(), cmp);
    cout << "Route with the most stations " << max_route->first << "." << '\n' <<
         "Route length - " << max_route->second << " stations." << '\n';
}
double ToRadians (double &degree) {
    return degree * M_PI / 180;
}
double DistanceBetween2stations(pair<double, double> &first_co, pair<double, double> &second_co) {
    double lat1 = ToRadians(first_co.first);
    double long1 = ToRadians(first_co.second);
    double lat2 = ToRadians(second_co.first);
    double long2 = ToRadians(second_co.second);
    double dlong = long2 - long1;
    double dlat = lat2 - lat1;
    double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    return ans * 6371;
}
double LengthOfTheRouteFromTheGivenPosition(pair<double, double> &given_position,
                                            vector<pair<double, double>> &all_coordinates) {
    vector<bool> check(all_coordinates.size(), false);
    int index = find(all_coordinates.begin(), all_coordinates.end(), given_position) - all_coordinates.begin();
    check[index] = true;
    double result = 0;
    for (int j = 0; j < all_coordinates.size() - 1; ++j){
        double min_length = LONG_LONG_MAX;
        int index_of_new_given_position;
        for (int i = 0; i < all_coordinates.size(); ++i) {
            if (!check[i]) {
                double distance = DistanceBetween2stations(given_position, all_coordinates[i]);
                if (distance < min_length) {
                    min_length = distance;
                    index_of_new_given_position = i;
                }
            }
        }
        result += min_length;
        given_position = all_coordinates[index_of_new_given_position];
        check[index_of_new_given_position] = true;
    }
    return result;
}
void TheLongestRoute(vector<Transport_station> &stations_of_one_type_of_transport) {
    unordered_map <string, vector<pair<double, double>>> RouteAndCoordinatesOfStationsOfThisRoute;
    for (const auto &one_station : stations_of_one_type_of_transport) {
        auto one_coordinate = one_station.coordinates;
        for (const auto &route : one_station.routes) {
            RouteAndCoordinatesOfStationsOfThisRoute[route].emplace_back(one_coordinate);
        }
    }
    double TheLongestRoute = -1;
    for (auto one_route : RouteAndCoordinatesOfStationsOfThisRoute) {
        double length = INT_MAX;
        for (auto start_position : one_route.second) {
            length = fmin(length, LengthOfTheRouteFromTheGivenPosition(start_position, one_route.second));
        }
        TheLongestRoute = fmax(TheLongestRoute, length);
    }
    cout << "The longest route " << TheLongestRoute << " km" << '\n';
}

void StreetWithTheMostStations(vector<Transport_station>& stations_of_one_type_of_transport1,
                               vector<Transport_station>& stations_of_one_type_of_transport2,
                               vector<Transport_station>& stations_of_one_type_of_transport3
) {
    unordered_map<string, int> Streets;
    for (const auto& one_station : stations_of_one_type_of_transport1) {
        for (const auto& one_location : one_station.locations) {
            if (!one_location.empty()) {
                Streets.try_emplace(one_location, 0);
                ++Streets[one_location];
            }
        }
    }
    for (const auto& one_station : stations_of_one_type_of_transport2) {
        for (const auto& one_location : one_station.locations) {
            if (!one_location.empty()) {
                Streets.try_emplace(one_location, 0);
                ++Streets[one_location];
            }
        }
    }
    for (const auto& one_station : stations_of_one_type_of_transport3) {
        for (const auto& one_location : one_station.locations) {
            if (!one_location.empty()) {
                Streets.try_emplace(one_location, 0);
                ++Streets[one_location];
            }
        }
    }
    auto street_with_max_number = max_element(Streets.begin(), Streets.end(), cmp);
    cout << "Street with the most stations - " << street_with_max_number->first << '\n' <<
         "Number of stations - " << street_with_max_number->second << '\n';
}

void GetInformationFromXmlFile (vector<Transport_station>& stations_BUS,
                                vector<Transport_station>& stations_TROLLEY,
                                vector<Transport_station>& stations_TRAM) {
    pugi::xml_document doc;
    doc.load_file("data.xml");
    for (auto station : doc.first_child().children()) {

        unsigned count = 1;
        Transport_station station_in_question;
        vector<Transport_station>* kind_of_transport;

        for (auto specification : station.children()) {
//            if (count == 1 || count == 3 || count == 4) continue;
            if (count == 2){
                string type_of_vehicle = specification.child_value();
                if (type_of_vehicle == "Автобус")
                    kind_of_transport = &stations_BUS;
                else if (type_of_vehicle == "Троллейбус")
                    kind_of_transport = &stations_TROLLEY;
                else if (type_of_vehicle == "Трамвай")
                    kind_of_transport = &stations_TRAM;
            }
            /*else if (count == 5){
                station_in_question.the_official_name = specification.child_value();
            } */
            else if (count == 6){
                string one_location = specification.child_value();
                while (one_location.find(',') != one_location.find('g')) {
                    station_in_question.locations.push_back(one_location.substr(0, one_location.find(',')));
                    one_location = one_location.substr(one_location.find(',') + 2);
                }
                station_in_question.locations.push_back(one_location);
            }
            else if (count == 7){
                string one_route = specification.child_value();
                while (one_route.find('.') != one_route.find('g') || one_route.find(',') != one_route.find('g')) {
                    if (one_route.find('.') != one_route.find('g')) {
                        station_in_question.routes.push_back(one_route.substr(0, one_route.find('.')));
                        one_route = one_route.substr(one_route.find('.') + 1);
                    }
                    else {
                        station_in_question.routes.push_back(one_route.substr(0, one_route.find(',')));
                        one_route = one_route.substr(one_route.find(',') + 1);
                    }
                }
                station_in_question.routes.push_back(one_route);
            }
            else if (count == 8) {
                string coordinates = specification.child_value();
                size_t sz;
                double first_coordinate = std::stod(coordinates, &sz);
                double  second_coordinate = std::stod(coordinates.substr(sz + 1));
                station_in_question.coordinates = {first_coordinate, second_coordinate};
            }
            ++count;
        }
        kind_of_transport->push_back(station_in_question);
    }
}

int main() {

    vector<Transport_station> stations_BUS;
    vector<Transport_station> stations_TROLLEY;
    vector<Transport_station> stations_TRAM;

    GetInformationFromXmlFile(stations_BUS, stations_TROLLEY, stations_TRAM);

    cout << "#1" << '\n';
    cout << "BUS" << '\n';
    RouteWithTheMostStations(stations_BUS);
    cout << "TROLLEY" << '\n';
    RouteWithTheMostStations(stations_TROLLEY);
    cout << "TRAM" << '\n';
    RouteWithTheMostStations(stations_TRAM);

    cout << "#2" << '\n';
    cout << "BUS" << '\n';
    TheLongestRoute(stations_BUS);
    cout << "TROLLEY" << '\n';
    TheLongestRoute(stations_TROLLEY);
    cout << "TRAM" << '\n';
    TheLongestRoute(stations_TRAM);
    cout << "#3" << '\n';
    StreetWithTheMostStations(stations_BUS, stations_TROLLEY, stations_TRAM);
    return 0;
}