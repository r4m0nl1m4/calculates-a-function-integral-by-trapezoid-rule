
//Main for "integral-by-trapezoid-rule-parallel" C application
//Created by r4m0nl1m4 14/10/2020

//library(ies)
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h> //use sleep

//new library(ies)
#include "./integral.h"
#include "./report.h"

MPI_Status status;

int main(int argc, char** argv){

	/* Allocate serie environment variables */
	int numtasks, taskid, problemSize;
	double a, b;
	struct timeval start, end;

    /* Set serie environment variables */
	problemSize = atoi(argv[1]);
	a = 1;
	b = 2;

	/* Start parallel computing */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    /* To each core's process */
	//printf("\n\ttaskid=\t%d\n",taskid);

	/* Allocate parallel environment variables */
	bool isMaster;
	double localVector[numtasks], totalVector[numtasks];

	/* Allocate and set problem environment variables */
	double h, nLocal, aLocal, integralLocal; 
	h = (b-a)/problemSize;
	nLocal = problemSize/numtasks;
	aLocal = a + taskid*nLocal*h;
	integralLocal = getTrapezoidRuleBySerie(nLocal, aLocal, h);

	/* Set parallel environment variables */
    double local = integralLocal;	
    double total, executeTime;

	isMaster = (taskid == 0);
	if (isMaster) {

		gettimeofday(&start, 0);

        int master = 0;
		localVector[master] = local;
		totalVector[master] = localVector[master];

		total = local;
		for( int worker=1; worker<numtasks; worker++ ){
	        MPI_Recv(&local, 1, MPI_DOUBLE, worker, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	        total += local;
		    
		    localVector[worker] = local;
		    totalVector[worker] = total;
		}

		gettimeofday(&end, 0);

		executeTime = getExecuteTime(start, end);

		saveCPUReportOnFile("result_report-parallel-cpu.txt", numtasks, problemSize, localVector, totalVector, executeTime);

		saveResultReportOnFile("result_report-parallel.txt", executeTime);
	}
	else /* Send  local to process 0 */
	    MPI_Send(&local, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

  	MPI_Finalize(); 

  	return 0;
}
