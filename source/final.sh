#!/bin/bash

printf "\nExecution System Start...\n\n===============================\n\n"

printf "Step 1: Generate date.txt file.\n\n"
./1date.out
printf "\nStep 1 Completed!\n\n-------------------------------\n\n"

printf "Step 2: FPP stock file.\n\n"
./2FPP-stock.out
printf "\nStep 2 Completed!\n\n-------------------------------\n\n"

printf "Step 3: FPP index file.\n\n"
./3FPP-index.out
printf "\nStep 3 Completed!\n\n-------------------------------\n\n"

printf "Step 4: add EPS data.\n\n"
python3 addEPS-final.py
printf "\nStep 4 Completed!\n\n-------------------------------\n\n"

printf "Step 5: Filename and Benchmark (deleted) Generation.\n\n"

ulimit -n 4096
printf "ulimit changed...\n\n"

./5fbgen.out
printf "\nStep 5 Completed!\n\n-------------------------------\n\n"

printf "Step 6: Binary files generation.\n\n"
./6binary.out
printf "\nStep 6 Completed!\n\n-------------------------------\n\n"

printf "Step 7: Filename and Benchmark (deleted) Generation - Binary.\n\n"
./7fbgen-binary.out
printf "\nStep 7 Completed!\n\n-------------------------------\n\n"

printf "Step 8: Execution...\n\n"
./8exe.out
printf "\nStep 8 Completed!\n\n-------------------------------\n\n"