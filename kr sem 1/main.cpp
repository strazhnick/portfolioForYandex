#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

//ПРИМЕЧАНИЕ. МНОГИЕ ВЕЩИ В ПРОГРАММЕ РЕАЛИЗОВАНЫ НЕ ОПТИМАЛЬНО, НО СОГЛАСНО ТРЕБОВАНИЯМ ПРЕПОДАВАТЕЛЯ.
//МНЕ НУЖНО БЫЛО ПО МИНИМУМУ ИСПОЛЬЗОВАТЬ СТАНДАРТНЫЕ БИБЛИОТЕКИ И ПО ВОЗМОЖНОСТИ РЕАЛИЗОВЫВАТЬ ВСЕ С НУЛЯ.

using namespace std;

const double PI = 3.14159265358979323846264338327950288419716939937510, EPS = 0.000001;

double dotPr(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

struct Triangle {
    double x1, y1, x2, y2, x3, y3, s;

    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        s = abs(det(x1-x3, y1-y3, x2-x3, y2-y3) / 2);
    }
};

void sortVertexes(double *a, int n) {
    double *phi = new double[n];
    double centX = 0, centY = 0;
    for (int i = 0; i < n; i++) {
        centX += a[2 * i];
        centY += a[2 * i + 1];
    }
    centX /= n;
    centY /= n;
    for (int i = 0; i < n; i++) {
        phi[i] = atan2(a[2 * i + 1] - centY, a[2 * i] - centX);
        if (phi[i] < 0) {
            phi[i] += 2 * PI;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (phi[i] > phi[j]) {
                swap(phi[i], phi[j]);
                swap(a[2 * i], a[2 * j]);
                swap(a[2 * i + 1], a[2 * j + 1]);
            }
        }
    }
    delete[] phi;
}

bool isd(int x) {
    return x > 47 && x < 58 || x == 45;
}

bool isw(int x) {
    return x == 0 || x == 32;
}


int sizeOfElements(string s) {
    int size = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isw(s[i]) && isw(s[i + 1])) {
            size++;
        }
    }
    return size;
}


double *toDoubleArray(string s, int size) {
    double *a = new double[size]{};
    int j = 0, l = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isw(s[i]) && !isw(s[i + 1])) {
            l = i + 1;
        }
        if (!isw(s[i]) && isw(s[i + 1])) {
            a[j++] = stod(s.substr(l, i + 1));
        }
        if (j == size) {
            break;
        }
    }
    return a;
}


bool inTriangle(Triangle t, double pointX, double pointY) {
    double k = det(t.x1 - pointX, t.y1 - pointY, t.x2 - t.x1, t.y2 - t.y1);
    double m = det(t.x2 - pointX, t.y2 - pointY, t.x3 - t.x2, t.y3 - t.y2);
    double n = det(t.x3 - pointX, t.y3 - pointY, t.x1 - t.x3, t.y1 - t.y3);
    /*
    bool b = (k >= 0 && m >= 0 && n >= 0) || (k <= 0 && m <= 0 && n <= 0);
    if (b) {
        cout << "точка принадлежит треугольнику " << pointX << " " << pointY << "\n";
    } else {
        cout << "точка НЕ принадлежит треугольнику " << pointX << " " << pointY << "\n";
    }
    */
    return (k >= 0 && m >= 0 && n >= 0) || (k <= 0 && m <= 0 && n <= 0);
}

bool intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double &xr,
               double &yr) {
    if (abs(det(x2 - x1, y2 - y1, x4 - x3, y4 - y3)) < EPS) {
        //cout << "отрезки параллельны\n";
        return false;
    }
    xr = ((x2 - x1) * det(x3, y3, x4, y4) - (x4 - x3) * det(x1, y1, x2, y2)) / det(x2 - x1, y2 - y1, x4 - x3, y4 - y3);
    yr = ((y2 - y1) * det(x3, y3, x4, y4) - (y4 - y3) * det(x1, y1, x2, y2)) / det(x2 - x1, y2 - y1, x4 - x3, y4 - y3);
    if (dotPr(xr - x1, yr - y1, xr - x2, yr - y2) > 0 || dotPr(xr - x3, yr - y3, xr - x4, yr - y4) > 0) {
        //cout << "отрезки не пересекаются\n";
        return false;
    }
    //cout << "отрезки пересекаются: " << xr << " " << yr << "\n";
    return true;
}

double square(Triangle t1, Triangle t2) {
    //ptc << "вызов функции square\n";
    double v[30];//в реале 6, но случаев 15. * 2 за счет x, y.
    int n = 0;
    if (inTriangle(t1, t2.x1, t2.y1)) {
        v[n++] = t2.x1;
        v[n++] = t2.y1;
    }
    if (inTriangle(t1, t2.x2, t2.y2)) {
        v[n++] = t2.x2;
        v[n++] = t2.y2;
    }
    if (inTriangle(t1, t2.x3, t2.y3)) {
        v[n++] = t2.x3;
        v[n++] = t2.y3;
    }
    if (inTriangle(t2, t1.x1, t1.y1)) {
        v[n++] = t1.x1;
        v[n++] = t1.y1;
    }
    if (inTriangle(t2, t1.x2, t1.y2)) {
        v[n++] = t1.x2;
        v[n++] = t1.y2;
    }
    if (inTriangle(t2, t1.x3, t1.y3)) {
        v[n++] = t1.x3;
        v[n++] = t1.y3;
    }
    double ix, iy, cx = 0, cy = 0, s = 0;
    if (intersect(t1.x1, t1.y1, t1.x2, t1.y2, t2.x1, t2.y1, t2.x2, t2.y2, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x1, t1.y1, t1.x2, t1.y2, t2.x2, t2.y2, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x1, t1.y1, t1.x2, t1.y2, t2.x1, t2.y1, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x2, t1.y2, t1.x3, t1.y3, t2.x1, t2.y1, t2.x2, t2.y2, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x2, t1.y2, t1.x3, t1.y3, t2.x2, t2.y2, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x2, t1.y2, t1.x3, t1.y3, t2.x1, t2.y1, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x1, t1.y1, t1.x3, t1.y3, t2.x1, t2.y1, t2.x2, t2.y2, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x1, t1.y1, t1.x3, t1.y3, t2.x2, t2.y2, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }
    if (intersect(t1.x1, t1.y1, t1.x3, t1.y3, t2.x1, t2.y1, t2.x3, t2.y3, ix, iy)) {
        v[n++] = ix;
        v[n++] = iy;
    }

    sortVertexes(v, n / 2);
    for (int i = 0; i < n / 2; i++) {
        cx += v[2 * i];
        cy += v[2 * i + 1];
    }
    cx /= n / 2;
    cy /= n / 2;

    for (int i = 0; i < n / 2; i++) {
        s += det(v[i * 2] - cx, v[i * 2 + 1] - cy, v[(i * 2 + 2) % n] - cx, v[(i * 2 + 3) % n] - cy) / 2;

    }
    return s;
}

struct Pair {
    Triangle *t1, *t2;
    double s;

    Pair(Triangle *t1, Triangle *t2) {
        this->t1 = t1;
        this->t2 = t2;
        s = square(*t1, *t2);
        if (s < EPS && s > -EPS) {
            s = 0;
        }
    }

    ~Pair() {
        delete t1;
        delete t2;
    }

};

int main() {
    setlocale(LC_ALL, "ru.utf-8");
    fstream ptc;
    fstream fout;
    fstream fin;
    ptc.open("protocol.txt", ios::out);
    fout.open("out.txt", ios::out);
    fin.open("in.txt", ios::in);
    int n = 0;
    string s;
    while (!fin.eof()) {
        getline(fin, s);
        if (sizeOfElements(s) >= 2) {
            n++;
        }
    }
    fin.close();
    double **a = new double *[n];
    int iv = 0, it = 0, ip = 0, nt = n * (n - 1) * (n - 2) / 6, np = nt * (nt - 1) / 2;
    double maxSquare = 0;
    fin.open("in.txt", ios::in);
    ptc << "выбранные точки\n";
    while (!fin.eof()) {
        getline(fin, s);
        if (sizeOfElements(s) >= 2) {
            //ptc << s << "\n";
            a[iv++] = toDoubleArray(s, 2);
            ptc << a[iv - 1][0] << " " << a[iv - 1][1] << "\n";
        }
    }
    fin.close();
    Triangle **trs = new Triangle *[nt];
    Pair **pairs = new Pair *[np];
    ptc << "\nвыбранные треугольники\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                trs[it++] = new Triangle(a[i][0], a[i][1], a[j][0], a[j][1], a[k][0], a[k][1]);
                if (trs[it - 1]->s > EPS) {
                    ptc << "t" << it - 1 << ": ( " << trs[it - 1]->x1 << "; " << trs[it - 1]->y1 << " ) " << "( "
                        << trs[it - 1]->x2 << "; " << trs[it - 1]->y2 << " ) " << "( " << trs[it - 1]->x3 << "; "
                        << trs[it - 1]->y3 << " ) s=" << trs[it - 1]->s << "\n";
                }
            }
        }
    }
    ptc << "\nпары треугольников и площадь\n";
    for (int i = 0; i < nt; i++) {
        for (int j = i + 1; j < nt; j++) {
            pairs[ip] = new Pair(trs[i], trs[j]);
            if (pairs[ip]->t1->s > EPS && pairs[ip]->t2->s > EPS) {
                ptc << "t" << i << ", t" << j << ". S=" << pairs[ip]->s << "\n";
            }
            maxSquare = max(maxSquare, pairs[ip]->s);
            ip++;
        }
    }
    if (maxSquare > EPS) {
        fout << "максимальная площадь: " << maxSquare << "\nпары треугольников с такой площадью:\n";
        for (int i = 0; i < np; i++) {
            if (pairs[i]->s > maxSquare - EPS) {
                fout << "t1: ";
                fout << "( " << pairs[i]->t1->x1 << "; " << pairs[i]->t1->y1 << " ) " << "( " << pairs[i]->t1->x2
                     << "; "
                     << pairs[i]->t1->y2 << " ) " << "( " << pairs[i]->t1->x3 << "; " << pairs[i]->t1->y3 << " ) ";
                fout << "   t2: ";
                fout << "( " << pairs[i]->t2->x1 << "; " << pairs[i]->t2->y1 << " ) " << "( " << pairs[i]->t2->x2
                     << "; "
                     << pairs[i]->t2->y2 << " ) " << "( " << pairs[i]->t2->x3 << "; " << pairs[i]->t2->y3 << " ) ";
                fout << "\n";
            }
        }
    } else {
        fout << "таких пересекающихся пар треугольников не существует\n";
    }
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    for (int i = 0; i < nt; i++) {
        delete trs[i];
    }
    delete[] pairs;
    ptc.close();
    fout.close();
    fin.close();
}