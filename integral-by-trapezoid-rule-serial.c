
//Main for "integral-by-trapezoid-rule-serial" C application
//Created by r4m0nl1m4 14/10/2020

//library(ies)
#include <stdlib.h>
#include <unistd.h> //use sleep

//new library(ies)
#include "./integral.h"
#include "./report.h"

int main(int argc, char** argv){

    /* Allocate serie environment variables */
    int problemSize;
    double a, b, h, areaTotal, executeTime;
    struct timeval start, end;
    
    /* Set serie environment variables */
    problemSize = atoi(argv[1]);
    a = 1;
    b = 2;
    h = (b-a)/problemSize;

    gettimeofday(&start, 0);

    areaTotal = getTrapezoidRuleBySerie(problemSize, a, h);

    gettimeofday(&end, 0);

    executeTime = getExecuteTime(start, end);  

    saveResultReportOnFile("result_report-serie.txt", executeTime);

    return 0;
}