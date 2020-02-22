ls
lscpu
htop
exit
top
exit
top
nano
nano mpi_hostfile
ls
nano hellompi.c
mpicc hellompi.c -o a
nano share
ls
nano share
chmod +x share
mv a asd
ls
./share
ls
scp asd 13517109@167.205.35.151
rm -rf 13517109@167.205.35.151
ls
rm -rf 13517109@167.205.35.152
rm -rf 13517109@167.205.35.153
rm -rf 13517109@167.205.35.154
rm -rf 13517109@167.205.35.155
nano share
./share
ls
mpirun -np 6 --hostfile mpi_hostfile asd
top
ls
nano run
chmod +x run
./run
nano run
./run
ls
top
./run
ls
top
ls
nano copas.c
mpicc copas.c -o asd
./share
./run
nano copas.c
rm copas.c 
nano c.c
nano comp
chmod +x comp
./comp
./share
./run
nano all
chmod +x all
./all
ls
exit
ls
rm share.save 
ls
exit
./all
exit
./all
ls
cd /.ssh
cd ~/.ssh
ls
cd 
~ls
ls
ssh-keygen -t ed25519 -C "13517109@std.stei.itb.ac.id"
exit
ls
git
ls
mpicc
ls
nano comp
./all
ls
nano comp
mpicc c.c
./all
mpicc c.c -o asd 10
ls
nano comp
nano run
./all
mpirun -np 1 asd 10
nano run
./all
nano run
./run 1
./run 10
nano all
./all 10
nano cop
chmod +x cop
./cop
./all 10
./cop
./all
nano run
nano all
ls
./cop
./all 1 10
./comp
ls
./comp
./run 1
./run 1 10
top
htop
ks
ls
./cop
./all 5
./all 5 10
ls
mpirun -np 6 asd 1 10 10
mpirun -np 6 asd 10 10
mpirun -np 6 asd 10000000 1000000
mpirun -np 6 asd 1000 1000
top
./cop
./run 6 100
./all 6 100
./run 6 100
mpirun -np 5 asd 100
mpirun -np 5 asd 10000
mpirun -np 5 asd 100000
nano run
./run 4 10
./run 4 10000
./run 2 10000
ls
./cop
./all 6 100
./all 6 1000
./cop
./all
./all 1
./all 5
./all 3
./cop
./all 1
./all 1 10
nano all
./cop
ls
./comp
./cop
./all
./all 1
./cop
./all
./all 1
./cop
./all 1
./cop
nano all
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./cop
./all
./run 6
./share
./run 6
./run 1
nano all
./cop
./all
./run
./run 6
ls
./cop
./all
./run 2
./run 3
./run 2
./cop
./all 2 x
./run 2
./run 2 x
./run 2 'x'
./run 2 "X"
./cop
./comp
./cop
./comp
./cop
./comp
./share
./run 2
./cop
./COP
./cop
./all 2
nano all
./all
./all 2
./run 2
./cop
./all 2
./cop
./all 2
./cop
./all 2
./COP
./cop
./all 2
./cop
./all 2
./cop
./comp
./cop
./comp
./all 2
// Copyright www.computing.llnl.gov
#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
int numtasks, rank, dest, source, rc, count, tag=1;
int inmsg[10], outmsg[10][10];
for (int i = 0; i < 10; ++i)
{ for (int j = 0; j < 10; ++i)
{ it(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (rank == 0) {
dest = 1;
source = 1;
rc = MPI_Send(&outmsg, 100, MPI_INT, dest, tag, MPI_COMM_WORLD);
rc = MPI_Recv(&inmsg, 100, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
for (int i = 0; i < 10; ++i)
{ t j = 0; j < 10; ++i)
{ tf("%d\n", inmsg[i][j]);
outmsg[i][j] = 10*i+j;
}
else if (rank == 1) {
dest = 0;
./co[
./cop
./all 2
./cop
./all 2
./cop
./all 2
./cop
./all
./all 2
./cop
./all 2
./cop
./all 2
./cop
./comp
./all 2
./cop
./all 1
./cop
./comp
./share
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./COP
./cop
./COP
./cop
./comp
././cop
./comp
./run 1
./cop
./comp
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./cmp
./comp
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./COP
./cop
./comp
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
././cop
./comp
./cop
./comp
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./run1
./run 1
./cop
./comp
./run 1
./cop
./comp
./run 1
./cop
./comp
./cop
./comp
./cop
./comp
./cop
./com
./comp
./run 6
./cop
./comp
./run 6
./all 6
./cop
./all 6
./cop
./comp
./all 6
nano run
nano all
./cop
./all 6 100
./all 6 10
./all 6 100
./all 6 50
./all 6 10
./run 6 10
./run 6 20
./run 6 10
./run 2 10
./run 2 9
./run 4 9
./run 6 100
./run 5 100
./cop
#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
int N = 100;
int getmin_index(int graph[N][N], bool pickedVertices[N], int sourceVertex) {
./cop
./all 6 100
./cop
./comp
./share
./run 6 100
./run 6 9
./cop
./comp
./share
./cop
./comp
./share
./run 6 1000
./cop
./comp
./share
./run 6 100
./cop
./comp
./share
./run 6 100
./run 6 1000
./run 6 500
./run 6 1000
./cop
./all 6 100
./all 6 500
./run 6 1000
./cop
./all 6 100
./cop
./comp
./cop
./comp
./share
./run 6 100
./run 6 10
./cop
./comp
./share
./run 6 10
./cop
./all 6 100
./cop
./all 6 100
./run 6 100
./run 6 500
./cop
./all 6 100
./run 6 100
./run 6 500
./run 6 1000
nano run
#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
int N = 100;
int getmin_index(long graph[N][N], bool pickedVertices[N], int sourceVertex) {
mpirun -np 6 --hostfile mpi_hostfile asd 1000
mpirun -np 6 --hostfile mpi_hostfile asd 1000 --bind-to core:overload-allowed
mpirun -np 6 --hostfile mpi_hostfile asd 1000 --verbose
./cop
./all 6 100
./run 6 500
./cop
./all 6 10
./cop
./all 6 9
./share
./run 4 9
./cop
./comp
./share
./run 4 9
./cop
./comp
./cop
./comp
./share
./run 4 9
./run 2 9
./cop
./comp
./share
./run 2 9
./cop
./comp
./share
./run 2 9
./cop
./comp
./share
./run 2 9
./run 4 9
nano c.c
./all 6 100
./run 2 9
./cop
./comp
./share
./run 6 100
./cop
./comp
./share
./run 2 9
./cop
./comp
./share
./run 2 9
./run 4 9
./cop
./comp
./share
./run 2 9
./run 4 9
./cop
./comp
./share
./run 6 0
./run 6 100
./run 6 1000
./cop
./comp
./cop
./comp
./cop
./comp
./cop
./comp
./share
./run 2 9
./run 4 9
./run 6 1000
./run 6 5000
./cop
./comp
./cop
./comp
./share
./run 6 100
./run 6 1000
./cop
./comp
./share
./run 6 100
./run 6 1000
./cop
./comp
./share
./run 6 100
./run 6 1000
./cop
./share
./run 6 100
./run 6 1000
./run 6 5000
./run 6 1000
./run 6 3000
./run 2 1000
./cop
./comp
./run 1 9
./cop
top
./cop
./comp
./run 1 9
exit
ulimit -a
exit
ulimit -s 40000
ulimit -a
ulimit -s 400000
ulimit -s 80000
ulimit -a
ulimit -s 60000
ulimit -s 50000
ulimit -s 40000
./cop
./comp
./run 1 10
./run 1 100
./run 1 1000
./run 1 3000
./run 1 5000
./cop
./comp
./run 1 5000
./cop
./comp
./cop
./comp
./cop
./comp
./cop
./comp
./cop
./comp
./run 1
top
htop
./cop
./comp
./run 1
./run 1 1000
./run 2 1000
./run 6 1000
./cop
./comp
./share
./run 6 1000
./cop
./comp
./share
./run 6 5000
./cop
./comp
./share
./run 6 5000
nano mpi_hostfile 
./cop
./comp
./cop
./comp
./share
./run 5 5000
nano mpi_hostfile 
./cop
./comp
./share
./run 6 5000
ls
cd ..
ls
cd josal
cd 13517115
ls -ola
ls
cd 13517109
ls ..
exit
