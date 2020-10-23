#!/bin/bash

# To run on terminal: ./shellscript_start.sh

#remove temp. files
rm cpu_report.txt
rm result_report-serie.txt
rm result_report-parallel.txt
rm integral-by-trapezoid-rule-serial
rm integral-by-trapezoid-rule-parallel

#parallel compilation
g++ -O0 -g -W -ansi -pedantic -std=c++11 -o integral-by-trapezoid-rule-serial integral-by-trapezoid-rule-serial.c
mpicc -g -Wall integral-by-trapezoid-rule-parallel.c -o integral-by-trapezoid-rule-parallel -lm

#cpu_report.txt
echo -e "\n/* \n * CPU Report \n */" >> "cpu_report.txt"
echo -e "\n /* CPU */ \n">> "cpu_report.txt"
cat /proc/cpuinfo | grep 'model name' | uniq >> "cpu_report.txt"
cat /proc/cpuinfo | grep 'vendor' | uniq >> "cpu_report.txt"
cat /proc/cpuinfo | grep 'cpu cores' | uniq >> "cpu_report.txt"
cat /proc/cpuinfo | grep 'siblings' | uniq >> "cpu_report.txt"
cat /proc/cpuinfo | grep 'cache size' | uniq >> "cpu_report.txt"
echo -e "\n /* Calculation Reports */ " >> "cpu_report.txt"

#result_report.txt
echo -e "\n/* \n * Result Report Serie \n */" >> "result_report-serie.txt"
echo -e "\n/* \n * Result Report Parallel \n */" >> "result_report-parallel.txt"

#attempts by number of cores and size
attempts=5
for cores in 2 4 6 8
do 
	for sizeProblem in 100 200
	do 
		echo -e "\n\t$cores\t$sizeProblem\c" >> "result_report-serie.txt"
		echo -e "\n\t$cores\t$sizeProblem\c" >> "result_report-parallel.txt"
	    echo -e "\n $cores Cores CPU - Size Problem $sizeProblem \n" >> "cpu_report.txt"
		for attempt in $(seq $attempts)
		do
			echo -e "  Try $attempt" >> "cpu_report.txt"
			#execute
			./integral-by-trapezoid-rule-serial $sizeProblem
			mpirun -np  $cores --oversubscribe ./integral-by-trapezoid-rule-parallel $sizeProblem
		done 
	done
done
exit