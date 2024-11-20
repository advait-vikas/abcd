#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <chrono>
using namespace std;

struct Point {
    int x, y;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(vector<Point>& points, int l, int r) {
    double minDist = DBL_MAX;
    for (int i = l; i < r; ++i)
        for (int j = i + 1; j <= r; ++j)
            minDist = min(minDist, distance(points[i], points[j]));
    return minDist;
}

double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    sort(strip.begin(), strip.end(), compareY);

    for (int i = 0; i < strip.size(); ++i)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j)
            minDist = min(minDist, distance(strip[i], strip[j]));

    return minDist;
}

double closestUtil(vector<Point>& points, int l, int r) {
    if (r - l <= 3)
        return bruteForce(points, l, r);

    int mid = l + (r - l) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, l, mid);
    double dr = closestUtil(points, mid + 1, r);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = l; i <= r; i++)
        if (abs(points[i].x - midPoint.x) < d)
            strip.push_back(points[i]);

    return min(d, stripClosest(strip, d));
}

double closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size() - 1);
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    cout << "The smallest distance is: " << closestPair(points) << endl;
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    cout << "Time taken: " << duration.count() << " seconds" << endl;
    return 0;
}
