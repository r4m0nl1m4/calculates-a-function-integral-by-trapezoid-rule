
//Main for "integral-by-trapezoid-rule-serial" C++ application
//Created by r4m0nl1m4 14/10/2020

#include "./integral.h"
#include "./report.h"

int main(int argc, char** argv){

    int problemSize;
    double a, b, h, areaTotal, executeTime;
    struct timeval start, end;
    
    problemSize = atoi(argv[1]);
    a = 1;
    b = 2;
    h = (b-a)/problemSize;

    gettimeofday(&start, 0);

    areaTotal = getTrapezoidRuleBySerie(problemSize, a, h);

    gettimeofday(&end, 0);

    executeTime = getExecuteTime(start, end);  

    saveResultReportOnFile("result_report-serie-runtime.txt", executeTime);

    return 0;
}