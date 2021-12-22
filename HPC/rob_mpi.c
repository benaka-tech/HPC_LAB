#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  
  int rank, size, threshold=15,break_point, prob[100],value[100],from,to,num=0;
  for (int i = 0; i < 100; ++i)
  {
    /* code */
    num = rand() % 2;
    prob[i]=num;
  }
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /*MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)*/

  //from = rank*100/size;
  //to= (rank+1)*100/size;

  MPI_Scatter(prob, 100/size,MPI_INT,value,100/size,MPI_INT,0,MPI_COMM_WORLD);

  int failure,sum;
  
  for(int i=0; i<100/size;i++)
  {
    if(value[i]==1)
      failure++;
  }
  printf("process %d has %d failures\n", rank, failure);

  MPI_Reduce(&failure,&break_point,1,MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(break_point>=threshold)
  {
    printf("Maximum failures reached (%d). Terminating process.\n", break_point);
    MPI_Finalize();
  }
  else{
    MPI_Finalize();
  }

  return 0;
}
