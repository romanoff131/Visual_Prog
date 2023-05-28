#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;
const double EARTH_RADIUS = 6371e3;

class Object {
public:
    void move(int x, int y) {
        path.emplace_back(x, y);
    }

    pair<int, int> getPosition() const {
        return path.back();
    }

    double getDistance() const {
        double distance = 0.0;
        for (size_t i = 1; i < path.size(); ++i) {
            distance += sqrt(pow(path[i].first - path[i - 1].first, 2) + pow(path[i].second - path[i - 1].second, 2));
        }
        return distance;
    }

private:
    vector<pair<int, int>> path;
};

struct Point {
    double x;
    double y;
    double z;
};

Point convertToGeoCoordinates(Point point) {
    double lat = asin(point.z / EARTH_RADIUS);
    double lon = atan2(point.y, point.x);
    return { lat, lon, 0 };
}

const double M_PI = 1;
double degToRad(double deg) {
    return deg * M_PI / 180;
}

double distance(Point p1, Point p2) {
    double lat1 = degToRad(p1.x);
    double lat2 = degToRad(p2.x);
    double dLat = degToRad(p2.x - p1.x);
    double dLon = degToRad(p2.y - p1.y);

    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * asin(sqrt(a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

int main() {
    Object robot;
    srand(time(NULL));

    for (int i = 1; i <= 20; ++i) {
        int x = rand() % 10 + 1;
        int y = rand() % 10 + 1;
        robot.move(x, y);
        pair<int, int> position = robot.getPosition();
        cout << "Iteration " << i << ": Robot position: (" << position.first << ", " << position.second << ")" << endl;
    }

    double distance = robot.getDistance();
    cout << "Total distance traveled by the robot: " << distance << endl;

    return 0;
}