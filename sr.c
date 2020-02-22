
// Copyright www.computing.llnl.gov
#include "mpi.h"
#include <stdio.h>


void clean(int arr[10][10]){
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			arr[i][j] = 99;
		}
	}
}
int main(int argc, char *argv[]) {
int numtasks, rank, dest, source, rc, count, tag=1;
int inmsg[10][10], outmsg[10][10];

for (int i = 0; i < 10; i++)
{
	for (int j = 0; j < 10; j++)
	{
		outmsg[i][j] = 10*i+j;
	}
}

MPI_Status Stat;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (rank == 0) {
	dest = 1;
	source = 1;
	rc = MPI_Send(&outmsg[5], 50, MPI_INT, dest, tag, MPI_COMM_WORLD);
	rc = MPI_Recv(&inmsg[5], 50, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d\n", inmsg[i][j]);
		}
	}
}
else if (rank == 1) {
	dest = 0;
	source = 0;
	rc = MPI_Recv(&inmsg[5], 50, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	printf("%s\n", "pass");
	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d\n", inmsg[i][j]);
		}
	}
	clean(inmsg);
	rc = MPI_Send(&inmsg[5], 50, MPI_INT, dest, tag, MPI_COMM_WORLD);
}
rc = MPI_Get_count(&Stat, MPI_INT, &count);
printf("Task %d: Received %d char(s) from task %d with tag %d \n",
rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
MPI_Finalize();
}
