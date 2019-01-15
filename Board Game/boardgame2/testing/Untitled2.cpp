// EWQ6 3/8/2017
// Dynamic Memory allocation
#include <iostream>
#include <new>
using namespace std;
void displayArr(const int *, int);

int main()
{

  const int SIZE=100;
  long int num;
  // Read in size of the array during execution
  cout << "Enter array size ";
  cin >> num;
  cout << "You entered " << num << endl;

  try {
  	int *ip = new int[num];
 	 // check if allocation worked
  	int numelts=3;
  	for (int i=0;i<numelts;i++) {
	  	cout << "Enter a number for loc " << i << ":";
	  	cin >> ip[i]; // same as *(ip+i) 
  	}
  	displayArr(ip, numelts);
  }
  catch(bad_alloc){
	  // you can do whatever you want here to handle exception 
	  cout << "Memory was not allocated! Pgm is terminating." << endl;
  }

  // int arr[num]; ILLEGAL C++, do not do this
  //int arr2[10000000]; 10M caused a segmentation fault


  //
  delete[] ip; // frees up the array that ip points to on the heap
  return 0;
}

// you can use array notation or pointer notation and they
// are completely equivalent
//void displayArr(const int arr[], int size)
void displayArr(const int *arr, int size)
{
	cout << "in function displayArr: " << endl;
	for (int i=0;i<size;i++)
		cout << arr[i] << endl;
}

