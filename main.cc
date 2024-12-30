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

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2; // p2, p0, p1
static const int ONLINE_FRONT = -2; // p0, p1, p2
static const int ON_SEGMENT = 0; // p0, p2, p1

int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
    if (cross(a, b) < -EPS) return CLOCKWISE;
    if (dot(a, b) < -EPS) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}

bool intersect(Segment s1, Segment s2) {
   return (ccw(s1.p1, s1.p2, s2.p1) * ccw(s1.p1, s1.p2, s2.p2) <= 0 &&
        ccw(s2.p1, s2.p2, s1.p1) * ccw(s2.p1, s2.p2, s1.p2) <= 0);
}

double getDistanceSS(Segment s1, Segment s2) {
    if (intersect(s1, s2)) return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)), min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

Point getCrossPoint(Segment s1, Segment s2) {
    Vector base = s2.p2 - s2.p1;
    double d1 = fabs(cross(base, s1.p1 - s2.p1));
    double d2 = fabs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}

class Circle {
    public:
        Point c;
        double r;

        Circle(Point c = Point(), double r = 0.0): c(c), r(r) {}
};

pair<Point, Point> getCrossPointCL(Circle c, Line l) {
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
    double base = sqrt(c.r * c.r - (pr-c.c).norm());
    return make_pair(pr + e * base, pr - e * base);
}

int main() {
    int cx, cy, r, q;
    int x1, y1, x2, y2;

    cin >> cx >> cy >> r >> q;
    Circle c = {Point(cx, cy), static_cast<double>(r)};

    for (int i = 0; i < q; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        Line l = {Point(x1, y1), Point(x2, y2)};
        pair<Point, Point> points = getCrossPointCL(c, l);
        if (points.first < points.second) {
            cout << fixed << setprecision(10) << points.first.x << " " << points.first.y << " " << points.second.x << " " << points.second.y << endl;
        } else {
            cout << fixed << setprecision(10) << points.second.x << " " << points.second.y << " " << points.first.x << " " << points.first.y << endl;
        }
    }

    return 0;
}
