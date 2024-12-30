#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAX 100000

#define EPS 1e-10
#define equals(a, b) (fabs((a) - (b)) < EPS)

class Point {
    public:
        double x, y;
        Point(double x = 0, double y = 0): x(x), y(y) {}

        Point operator + (Point p) { return Point(x + p.x, y + p.y); }
        Point operator - (Point p) { return Point(x - p.x, y - p.y); }
        Point operator * (double a) { return Point(a*x, a*y); }
        Point operator / (double a) { return Point(x/a, y/a); }

        double abs() { return sqrt(norm()); }
        double norm() { return x*x + y*y; }

        bool operator < (const Point &p) const {
            return x != p.x ? x < p.x : y < p.y;
        }

        bool operator == (const Point &p) const {
            return fabs(x - p.x) < EPS && fabs(y-p.y) < EPS;
        }
};

typedef Point Vector;

double dot(Vector a, Vector b) {
    return a.x*b.x + a.y*b.y;
}

double cross(Vector a, Vector b) {
    return a.x*b.y - a.y*b.x;
}

struct Segment {
    Point p1, p2;
};

typedef Segment Line;

Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / base.norm();
    return s.p1 + base * r;
}

Point refect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2.0;
}

double getDistancePP(Point a, Point b) {
    return (a - b).abs();
}

double getDistanceLP(Line l, Point p) {
    return fabs(cross(l.p2 - l.p1, p - l.p1)) / (l.p2 - l.p1).abs();
}

double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return getDistancePP(p, s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return getDistancePP(p, s.p2);
    return getDistanceLP(s, p);
}

bool intersect(Segment s1, Segment s2) {
    return (cross(s1.p2 - s1.p1, s2.p1 - s1.p1) * cross(s1.p2 - s1.p1, s2.p2 - s1.p1) < 0) &&
           (cross(s2.p2 - s2.p1, s1.p1 - s2.p1) * cross(s2.p2 - s2.p1, s1.p2 - s2.p1) < 0);
}

double getDistanceSS(Segment s1, Segment s2) {
    if (intersect(s1, s2)) return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)), min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

int main() {
    int n;
    int x0, y0, x1, y1, x2, y2, x3, y3;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Segment s1 = {Point(x0, y0), Point(x1, y1)};
        Segment s2 = {Point(x2, y2), Point(x3, y3)};
        cout << fixed << setprecision(10) << getDistanceSS(s1, s2) << endl;
    }

    return 0;
}
