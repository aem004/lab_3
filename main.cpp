#include <iostream>
#include <cassert>
#include <limits>
#include <complex>
#include "PriorityQueue.h"
#include "TestTime.h"
#include "OtherClasses.h"

void TestMapInt() {
    TPQueue<int, cmpInt> pq;
    TPQueue<int, cmpInt> pq1;
    TPQueue<int, cmpInt> pq2;

    for (int i = 0; i < 30; ++i)
        pq.push(rand() % 400);
    for (int i = 0; i < 30; ++i) {
        pq1.push(pq.top());
        pq2.push(pq.top() * 2);
        pq.pop();
    }
    pq1.map(&f);
    std::cout << pq1;
    std::cout << pq2;
    assert(pq1 == pq2);
    std::cout << "TEST MAP INT OK" << std::endl;
}

void TestReduceInt() {
    TPQueue<int, cmpInt> pq;
    int result = 0;
    for (int i = 0; i < 30; ++i) {
        int temp = rand() % 400;
        pq.push(temp);
        result += temp;
    }
    std::cout << result<< std::endl;
    std::cout << pq.reduce(&fr)<< std::endl;
    assert(pq.reduce(&fr) == result);
    std::cout << "TEST REDUCE INT OK" << std::endl;
}

void TestWhereInt() {
    TPQueue<int, cmpInt> pq;
    TPQueue<int, cmpInt> pq1;
    TPQueue<int, cmpInt> pq2;

    for (int i = 0; i < 30; ++i)
        pq.push(rand() % 400);
    for (int i = 0; i < 30; ++i) {
        pq1.push(pq.top());
        if (fw(pq.top()))
            pq2.push(pq.top());
        pq.pop();
    }
    pq1.where(&fw);
    std::cout << pq1;
    std::cout << pq2;
    assert(pq1 == pq2);
    cout << "TEST WHERE INT OK " << std::endl;
}

void TestCheckSizeInt() {
    TPQueue<int, cmpInt> pq;
    for (int i = 0; i < 30; ++i)
        pq.push(rand() % 400);
    std::cout << 30 << std::endl;
    std::cout << pq.size() << std::endl;
    assert(pq.size() == 30);
    std::cout << "TEST CHECK SIZE INT OK" << std::endl;
}

void TestChekTopInt() {
    int max = INT32_MIN;
    TPQueue<int, cmpInt> pq;
    for (int i = 0; i < 30; ++i) {
        int temp = rand() % 400;
        pq.push(temp);
        if (temp > max)
            max = temp;
    }
    std::cout << max;
    std::cout << pq.top();
    assert(pq.top() == max);
    std::cout << "TEST CHECK TOP ELEMENT INT OK" << std::endl;
}

void TestGetRangeInt() {
    TPQueue<int, cmpInt> pq1;
    TPQueue<int, cmpInt> pq2;
    TPQueue<int, cmpInt> cur;
    for (int i = 0; i < 30; ++i) {
        int temp = rand() % 400;
        pq1.push(temp);
        pq2.push(temp);
    };
    int k = 0;
    while (!pq1.empty()) {
        if (k >= 3 && k <= 13) {
            cur.push(pq1.top());
        }
        k++;
        pq1.pop();
    }
    auto pq = pq2.getRange(3, 13);
    std::cout << cur;
    std::cout << pq;
    assert(pq == cur);
    std::cout << "TEST GET RANGE INT OK" << std::endl;
}

void TestMergeInt() {
    TPQueue<int, cmpInt> pq;
    TPQueue<int, cmpInt> pq1;
    TPQueue<int, cmpInt> pq2;

    for (int i = 0; i < 30; ++i) {
        int temp1 = rand() % 400;
        int temp2 = rand() % 400;
        pq.push(temp1);
        pq.push(temp2);
        pq1.push(temp1);
        pq2.push(temp2);
    }
    pq1.merge(pq2);
    std::cout << pq1;
    std::cout << pq;
    assert(pq1 == pq);
    std::cout << "TEST MERGE INT OK" << std::endl;

}

void menu() {
    std::cout << "1. Automatic queue creation." <<
              std::endl << "0. exit" << std::endl;
}

int type_menu() {
    std::cout << "1. integer" <<
              std::endl << "2. Real numbers." <<
              std::endl << "3. Complex numbers" << std::endl;
    int n;
    std::cin >> n;
    if (std::cin.fail()) {
        std::cin.clear();
        size_t maxValue_ = std::numeric_limits<size_t>::max();
        std::cin.ignore(maxValue_, '\n');
        std::cout << "only numbers!" << std::endl;
    } else if (n < 1 || n > 3) {
        std::cout << "Invalid input" << std::endl;
        n = type_menu();
    }
    return n;
}


void generateIntPriority(long size) {
    TPQueue<int, cmpInt> pq;
    for (int i = 0; i < size; ++i) {
        pq.push(rand() % size);
        if (i % 5 == 0 && size < 100)
            std::cout << pq;
        if (i % 50 == 0 && size > 100)
            std::cout << pq;
    }
    std::cout << pq;
    std::cout << "Finished" << std::endl;
}

double fRand(double fMin, double fMax) {
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void generateDoublePriority(long size) {
    TPQueue<double, cmpDouble> pq;
    for (int i = 0; i < size; ++i) {
        pq.push(fRand(0, size));
        if (i % 5 == 0 && size < 100)
            std::cout << pq;
        if (i % 50 == 0 && size > 100)
            std::cout << pq;
    }
    std::cout << pq;
    std::cout << "Finished" << std::endl;
}

void generateComplexPriority(long size) {
    TPQueue<std::complex<int>, cmpComplex> pq;
    for (int i = 0; i < size; ++i) {
        std::complex<int> z(rand() % size, rand() % size);
        pq.push(z);
        if (i % 5 == 0 && size < 100)
            std::cout << pq;
        if (i % 50 == 0 && size > 100)
            std::cout << pq;
    }
    std::cout << pq;
    std::cout << "Finished" << std::endl;
}

long generatedNumber() {
    long n;
    std::cin >> n;
    if (std::cin.fail()) {
        std::cin.clear();
        size_t maxValue_ = std::numeric_limits<size_t>::max();
        std::cin.ignore(maxValue_, '\n');
        std::cout << "only numbers!" << std::endl;
    } else if (n <= 0) {
        std::cout << "Positive numbers" << std::endl;
        n = generatedNumber();
    }
    return n;
}


void switch_menu() {
    int n;
    std::cin >> n;
    if (std::cin.fail()) {
        std::cin.clear();
        size_t maxValue_ = std::numeric_limits<size_t>::max();
        std::cin.ignore(maxValue_, '\n');
        std::cout << "only numbers!" << std::endl;
        switch_menu();
    } else if (n < 0 || n > 1) {
        std::cout << "Invalid input" << std::endl;
        menu();
        switch_menu();
    } else {
        switch (n) {
            case 1: {
                std::cout << "Enter the type of the array:" << std::endl;
                int type = type_menu();
                std::cout << "Enter the size of the array:" << std::endl;
                long generateNumber = generatedNumber();
                if (type == 1) {
                    generateIntPriority(generateNumber);
                } else if (type == 2) {
                    generateDoublePriority(generateNumber);
                } else {
                    generateComplexPriority(generateNumber);
                }
                menu();
                switch_menu();
                break;
            }
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));
    TestMapInt();
    TestReduceInt();
    TestWhereInt();
    TestCheckSizeInt();
    TestChekTopInt();
    TestMergeInt();
    TestGetRangeInt();
    std::cout << "ALL TEST PASSED" << std::endl;
    writeResultsOfAllMethods();
    menu();
    switch_menu();

    return 0;
}
