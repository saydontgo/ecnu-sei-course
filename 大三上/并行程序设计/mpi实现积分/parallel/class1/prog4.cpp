#include <iostream>
#include <mpi.h>


using namespace std;
 
int main(int argc, char *argv[])
{
    int numprocessors, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);
  
    int receive_buffer[5];

    if ( rank == 0 )
    {
	int * array=new int[10];
	for(int i=0;i<10;i++)array[i]=i;
        MPI_Scatter(array, 2, MPI_INT, receive_buffer, 2, MPI_INT, 0, MPI_COMM_WORLD);
    	cout <<"the master process 0 has scattered the values\n";
	cout << "slave  (" << rank << "/" << numprocessors << ") received values: "<<receive_buffer[0]<<" and "<<receive_buffer[1]<<endl;
	delete[] array;
    } else {
	MPI_Scatter(NULL, 2, MPI_INT, receive_buffer, 2, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "slave  (" << rank << "/" << numprocessors << ") received values: "<<receive_buffer[0]<<" and "<<receive_buffer[1]<<endl;
   }
   MPI_Finalize();
   return 0;
}
