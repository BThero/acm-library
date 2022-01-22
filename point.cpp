typedef long double ld;

struct Point {
    ld x, y;

    Point() : x(0), y(0) {}
    Point(ld x, ld y) : x(x), y(y) {}

    ld abs() {
        return sqrtl(x * x + y * y);
    }

    Point unit() {
        ld len = abs();
        return Point(x / len, y / len);
    }
};

Point operator + (Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator * (Point a, ld b) {
    return Point(a.x * b, a.y * b);
}

ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool operator == (Point a, Point b) {
    return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS;
}

bool operator != (Point a, Point b) {
    return !(a == b);
}

bool operator < (Point a, Point b) {
    if (a.x + EPS < b.x) {
        return true;
    }

    if (b.x + EPS < a.x) {
        return false;
    }

    return a.y + EPS < b.y;
}

ld dist(Point a, Point b) {
    return (b - a).abs();
}

int sgn(ld x) {
    if (x < -EPS) {
        return -1;
    }

    if (x > EPS) {
        return 1;
    }

    return 0;
}
