#include<stdio.h>
#include<mpi.h>
#include<fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

	int rank,proces;
	int rango
	int ct1 =0;
	int ct= -1; // se inicia en -1 puesto que se le debe restar la primera linea  
	ifstream fichero("utem.csv", ifstream::in);//se abre fichero

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proces); //Cantidad de procesadores
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //proce actual

	while(fichero.good()){ //ciclo que recorre fichero hasta el final
		if(fichero.get()=='\n'){ // busca salto de linea 
			ct1 ++;
		}
 	}
	ct1= ct1-1;
	rango= ct1 / proces;

	if(rank==0){ // cuando el procesador actual es 0
	 while(fichero.good()){ //ciclo que recorre fichero hasta el final
	    for(int i=0;i<proces;i++){
		    if(fichero.get()=='\n'){ //busca salto de linea
		    	ct++;
		        MPI_Send(&ct, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		        MPI_Recv(&ct, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	        }
	    }
	 }
	cout<<"total = "<< ct <<endl;
	}
	else { // para los demas procesadores
	 while(fichero.good()){ //ciclo que recorre fichero hasta el final
	    for(int i=0;i<proces;i++){
		    if(fichero.get()=='\n'){ //busca salto de linea
		    	ct++;
		        MPI_Send(&ct, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		        MPI_Recv(&ct, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	        }
	    }
	 }
	cout<<"total = "<< ct <<endl;
	}

	fichero.close() ;
    	MPI_Finalize();
}
