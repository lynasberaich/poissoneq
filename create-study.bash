#!/bin/bash                                                                                                                                                                                                                                                                                                                                                                            

# This function writes a SLURM script. We can call it with different parameter                                                                                                                                                                                                                                                                                                         
# settings to create different experiments                                                                                                                                                                                                                                                                                                                                             
function write_script
{
    STUDY_NAME=$(printf 'n%d' ${N})
    DIR_NAME=$(printf '%s/n%02dppn%02d' ${STUDY_NAME} ${NODES} ${NPERNODE})

    echo $DIR_NAME
    mkdir -p $DIR_NAME

    cat <<_EOF_ > ${DIR_NAME}/run.slurm                                                                                                                                                                                                                                                                                                                                                
#!/bin/bash                                                                                                                                                                                                                                                                                                                                                                            
#SBATCH --job-name=poisson                                                                                                                                                                                                                                                                                                                                                             
#SBATCH --output=slurm.out                                                                                                                                                                                                                                                                                                                                                             
#SBATCH --error=slurm.err                                                                                                                                                                                                                                                                                                                                                              
#SBATCH --partition=high_mem                                                                                                                                                                                                                                                                                                                                                           
#SBATCH --qos=short+                                                                                                                                                                                                                                                                                                                                                                   
#SBATCH --constraint=hpcf2018                                                                                                                                                                                                                                                                                                                                                          
#SBATCH --nodes=${NODES}                                                                                                                                                                                                                                                                                                                                                               
#SBATCH --ntasks-per-node=${NPERNODE}                                                                                                                                                                                                                                                                                                                                                  
#SBATCH --time=00:55:00                                                                                                                                                                                                                                                                                                                                                                
#SBATCH --mem=10G                                                                                                                                                                                                                                                                                                                                                                      
#SBATCH --exclusive                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                       
mpirun ../../poisson ${N} 1.0e-6 50000                                                                                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                                                                       
_EOF_                                                                                                                                                                                                                                                                                                                                                                                  
}

# For each problem size, we'll set up the experiment with                                                                                                                                                                                                                                                                                                                              
# 1, 2, 4, 8, 16, and 32 processes on 1 and 2 nodes                                                                                                                                                                                                                                                                                                                                    

for N in 16384
do
    for NPERNODE in 1 2 4 8 16 32
    do
        for NODES in 8 16
        do
            write_script
        done
    done
done

