#!/bin/bash                                                                                                                                                                                                                                                                                                                                                                            

CWD=`pwd`
echo $CWD

# For each problem size, we'll run the experiment with                                                                                                                                                                                                                                                                                                                                 
# 1, 2, 4, 8, 16, and 32 processes on 1 and 2 nodes                                                                                                                                                                                                                                                                                                                                    
for NODES in 8 16
do
    for N in 16384
    do
            STUDY_NAME=$(printf 'n%d' ${N})

            for NPERNODE in 1 2 4 8 16 32
            do
                DIR_NAME=$(printf '%s/n%02dppn%02d' ${STUDY_NAME} ${NODES} ${NPERNODE})
                cd $DIR_NAME
                sbatch run.slurm

                cd $CWD
            done
        done
    done
done








