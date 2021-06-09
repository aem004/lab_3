#ifndef LAB3_TESTTIME_H
#define LAB3_TESTTIME_H

#include <chrono>
#include <fstream>

int f(int k) {
    return 2 * k;
}

int fr(int a, int b) {
    return a + b;
}

bool fw(int a) {
    return a > 300;
}

struct cmpInt {
    bool operator()(const int &a, const int &b) const {
        return (a > b);
    }
};

struct cmpComplex {
    bool operator()(const std::complex<int> &a, const std::complex<int> &b) const {
        return (sqrt(pow(a.real(), 2) + pow(a.imag(), 2)) >
                sqrt(pow(b.real(), 2) + pow(b.imag(), 2)));
    }
};


struct cmpDouble {
    bool operator()(const double &a, const double &b) const {
        return (a > b);
    }
};

TPQueue<int, cmpInt> *TP = new TPQueue<int, cmpInt>[20];

long *calculateInitializing() {
    long *result = new long[20];
    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int k = 0; k < 1e4 + i * 500; ++k) {
            TP[i].push(rand() % 10000);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        result[i] = ms;
    }
    return result;
}

long *calculateReduce() {
    long *result = new long[20];
    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        TP[i].reduce(&fr);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        result[i] = ms;
    }
    return result;
}

long *calculateWhere() {
    long *result = new long[20];
    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        TP[i].where(&fw);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        result[i] = ms;
    }
    return result;
}


long *calculateMap() {
    long *result = new long[20];
    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        TP[i].map(&f);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        result[i] = ms;
    }
    return result;
}

void writeResultsOfAllMethods() {
    auto res1 = calculateInitializing();
    auto res2 = calculateReduce();
    auto res3 = calculateWhere();
    auto res4 = calculateMap();
    ofstream out("../output.txt");
    for (int i = 0; i < 20; ++i)
        out << to_string(res1[i]) << ", ";
    out << std::endl;
    for (int i = 0; i < 20; ++i)
        out << to_string(res2[i]) << ", ";
    out << std::endl;
    for (int i = 0; i < 20; ++i)
        out << to_string(res3[i]) << ", ";
    out << std::endl;
    for (int i = 0; i < 20; ++i)
        out << to_string(res4[i]) << ", ";
    out << std::endl;
    out.close();
}


#endif //LAB3_TESTTIME_H
