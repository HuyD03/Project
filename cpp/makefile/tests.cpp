#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <typeinfo>
using namespace std;

#include "cs150check.h"

#include "h38.h"


void runTests()
{
    ///////////// Begin a set of tests
    beginTests(); // test heading

    /////// Tests for //////////////////////
    beginFunctionTest("Checking the Worker class.");
    struct x { string n; double r; virtual ~x(){}};
    int xSz = sizeof(x); // makes testing easier
    int wSz = sizeof(Worker);
    assertEqualsMsg("Checking size of Worker", xSz, wSz);

    ofstream out("temp.cpp");
    out << "#include \"h38.h\"\n#include <iostream>\nint main()\n";
    out << "{ Worker w(\"Sam\", 2.5); return 0; }\n";
    out.close();
    if (! system("g++ -std=c++17 -c temp.cpp 2>/dev/null"))
        failMsg("Worker class is not abstract", 5);
    else
        passMsg("Worker class is abstract", 5);
    system("rm -rf temp.cpp 2>/dev/null");

    endFunctionTest(); // end

    beginFunctionTest("Checking the SalariedWorker classes.");

    int sSz = sizeof(SalariedWorker);
    assertEqualsMsg("Checking for extra fields in SalariedWorker", wSz, sSz);

    Worker * p = new SalariedWorker("Sam", 19.50);
    assertEqualsMsg("Checking inherited getName() method.", "Sam", p->getName());
    assertDoubleEqualsMsg("Checking inherited getRate() method.", 19.50, p->getRate(), .001);

    // Now, let's test the virtual function
    assertEqualsMsg("Checking less than 40 hours.", "Sam(Salaried, $ 19.50) worked 20 hours. Pay: $ 780.00", p->payInfo(20));
    assertEqualsMsg("Checking more than 40 hours.", "Sam(Salaried, $ 19.50) worked 50 hours. Pay: $ 780.00", p->payInfo(50));
    assertEqualsMsg("Checking 40 hours.", "Sam(Salaried, $ 19.50) worked 40 hours. Pay: $ 780.00", p->payInfo(40));

    delete p;

    endFunctionTest(); // end

    /////// Tests for //////////////////////
    beginFunctionTest("Checking the HourlyWorker classes.");

    int hSz = sizeof(HourlyWorker);
    assertEqualsMsg("Checking for extra fields in HourlyWorker", wSz, hSz);

    p = new HourlyWorker("Sally", 18.50);
    assertEqualsMsg("Checking inherited getName() method.", "Sally", p->getName());
    assertDoubleEqualsMsg("Checking inherited getRate() method.", 18.50, p->getRate(), .001);

    // Now, let's test the virtual function
    assertEqualsMsg("Checking less than 40 hours.", "Sally(Hourly, $ 18.50) worked 20 hours. Pay: $ 370.00", p->payInfo(20));
    assertEqualsMsg("Checking more than 40 hours.", "Sally(Hourly, $ 18.50) worked 50 hours. Pay: $ 1017.50", p->payInfo(50));
    assertEqualsMsg("Checking 40 hours.", "Sally(Hourly, $ 18.50) worked 40 hours. Pay: $ 740.00", p->payInfo(40));

    delete p;

    endFunctionTest(); // end

    endTests();
}

