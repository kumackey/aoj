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

int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Segment s = Segment{Point(x1, y1), Point(x2, y2)};

    int q;
    int x, y;

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        Point p = project(s, Point(x, y));
        cout << fixed << setprecision(10) << p.x << " " << p.y << endl;
    }

    return 0;
}
