/*11.A school has five sections for each grade and they have three grades (PreKG, LKG and
UKG). They send a teacher to each section to get the information about the age of each child in
the section. Assume that there are ten students in each section. Assuming each teacher is
simulated as a thread use the MPI-Reduction function to determine the Minimum age, the
Maximum age and the Average age for each section, each grade and for the whole school. Use
random numbers for generating the age of the children.
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
// Creates an array of random numbers. Each number has a value from 0 - 1
int min_arr(int arr[], int n)
{
    int i;
    
    // Initialize maximum element
    int min = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
 
    return min;
}
int largest(int arr[], int n)
{
    int i;
    
    // Initialize maximum element
    int max = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}
int *create_rand_nums_PreKG(int num_elements) {
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() % (4 - 2 + 1) + 2);
    printf("val=%d\t",rand_nums[i]);
  }
  
  return rand_nums;
}

int *create_rand_nums_LKG(int num_elements) {
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() % (5 - 3 + 1) + 3);
    printf("val=%d\t",rand_nums[i]);
  }
  
  return rand_nums;
}

int *create_rand_nums_UKG(int num_elements) {
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() % (6 - 4 + 1) + 4);
    printf("val=%d\t",rand_nums[i]);
  }
  
  return rand_nums;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }

  int num_elements_per_proc = atoi(argv[1]);
  int new_id, new_nodes;

 /* MPI_Init(int* argc,
             char*** argv);
1.argc
  The number of arguments passed through main, or NULL.

2.argv
  The argument values passed through main, or NULL.*/
  
  MPI_Init(NULL, NULL);

  int world_rank;
  /*MPI_Comm_rank(MPI_Comm communicator,
                  int* rank);
1.communicator
     The MPI communicator to explore.
2.rank
    A pointer on the variable in which write the rank of the calling MPI process in the MPI communicator given.*/
    
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  /*MPI_Comm_size(MPI_Comm communicator,
                  int* size);
1.communicator
   The MPI communicator to explore.

2.size
   A pointer on the variable in which write the size of the MPI communicator given.*/
  
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm New_Comm;
  int color;
  color = world_rank/5;
  
  /*MPI_Comm_split(MPI_Comm old_communicator,
                   int colour,
                   int key,
                   MPI_Comm* new_communicator);
  1.old_communicator
    The communicator in which the calling MPI process belongs and is the one to split.

  2.colour
    The value determining in which group the calling MPI process will be; MPI processes providing the same colour value will be put in the same subgroup. If MPI_UNDEFINED is passed as the colour value, the subgroup in which the calling MPI process will be placed is MPI_COMM_NULL.

  3.key
     The value determining the rank that the calling MPI process will be assigned in the subgroup in which it will be placed. For each subgroup, MPI processes will be assigned ranks in the order of their key value, with ties being broken according to their rank in the old communicator.

 4.new_communicator
   The communicator created, made of the group containing all MPI processes having provided the same colour value. If MPI_UNDEFINED was provided as the colour value, MPI_COMM_NULL is returned.*/
   
  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &New_Comm);
  MPI_Comm_rank(New_Comm, &new_id);
  MPI_Comm_size(New_Comm, &new_nodes);
  

  // Create a random array of elements on all processes.
  srand(time(NULL)*world_rank);   // Seed the random number generator to get different results each time for each processor
  int *rand_nums = NULL;
if(world_rank<=4){
  
  
  rand_nums = create_rand_nums_PreKG(num_elements_per_proc);
}


if(world_rank>=5 && world_rank<=9 ){
  rand_nums = create_rand_nums_LKG(num_elements_per_proc);


} if(world_rank>=10 && world_rank<=14){
  rand_nums = create_rand_nums_UKG(num_elements_per_proc);

}

//local min
  int local_min=min_arr(rand_nums,num_elements_per_proc);
  printf("min=%d\t",local_min);
  
  int local_max=largest(rand_nums,num_elements_per_proc);
  printf("max=%d\t",local_max);
  

  // Sum the numbers locally
  int local_sum = 0;
  int i;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sum += rand_nums[i];
  }

  // Print the random numbers on each process
  float avg=(float)local_sum / (float)num_elements_per_proc;
  printf("\nLocal sum for process %d - sum = %d, avg = %f\n",world_rank,local_sum,avg);

  // Reduce all of the local sums into the global sum
      /*MPI_Reduce(const void* send_buffer,
                   void* receive_buffer,
                   int count,
                   MPI_Datatype datatype,
                   MPI_Op operation,
                   int root,
                   MPI_Comm communicator);
                   
1.send_buffer
 A pointer on the buffer to send for reduction.

2.receive_buffer
  A pointer on the buffer in which store the result of the reduction. Only the MPI process with the specified as root will receive the reduction result.

3.count
   The number of elements in the send buffer, which is identical to that in the receive buffer as well.

4.datatype
    The type of a buffer element.

5.operation
    The operation to apply to combine messages received in the reduction. This operation must be associative, and commutative for predefined operations while user-defined operations may be non-commutative.

6.root
    The rank of the MPI process that will collect the reduction result.

7.communicator
    The communicator in which the reduction takes place.*/
  
  int global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0,
             MPI_COMM_WORLD);
  
  int global_min;
  MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0,
             MPI_COMM_WORLD);
 int global_max;
  MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0,
             MPI_COMM_WORLD);
  
 int grade_sum;
  MPI_Reduce(&local_sum, &grade_sum, 1, MPI_INT, MPI_SUM, 0,
             New_Comm);
 int grade_max;
  MPI_Reduce(&local_max, &grade_max, 1, MPI_INT, MPI_MAX, 0,
             New_Comm);
  int grade_min;
  MPI_Reduce(&local_min, &grade_min, 1, MPI_INT, MPI_MIN, 0,
             New_Comm);
  // Print the result
   if (new_id == 0){
   
    float avg2= (float)grade_sum / (float)(new_nodes * num_elements_per_proc);
    printf("\nTotal grade sum = %d , avg=%f\n", grade_sum,avg2);
    printf("\nTotal grade max = %d\n", grade_max);
    printf("\nTotal grade min = %d\n", grade_min);
    
  }
  if (world_rank == 0) {
   
   float avg1= (float)global_sum / (float)(world_size * num_elements_per_proc);
    printf("\nTotal sum = %d, avg = %f\n", global_sum,avg1);
    printf("\nTotal min = %d\n", global_min);
   printf("\nTotal max = %d\n", global_max); 
       
  }
 

  // Clean up
  //free(rand_nums_UKG);
  //free(rand_nums_LKG);
  //free(rand_nums);
  MPI_Barrier(New_Comm);
  MPI_Barrier(MPI_COMM_WORLD);
 
 
  MPI_Finalize();
}
