/*
 * Author: Tyler Griffith
 * Date: 9/25/16
 * Class: CSC-2710
 * File Location: ~/CSC2710/proj3/p3.cpp
 *
 * This program uses floyd's algorithm to determine
 * whether or not a collection of relationships are
 * connected or disconnected.
 */

#include <iostream>
#include <iomanip>

using namespace std;

//function prototypes
void load(string [], int &, int &, int **);
int searchAndInsert(string [], int &, string);
void createGraph(int **);
void fillGraph(int **, int, int);
void floyds(int **, int &);
void print(int **, int &);

//defining the maximum amount of relationships
#define MAX 64

//driver
int main(){
   int m, n, size;
   string friends[MAX];
   int **graph;
   graph = new int* [MAX]; //dynamic array (size MAX) of pointers to int

   //specifies the number of collections
   cin >> n;
   //loops the functions for the certain number of collections
   for(int i=0; i<n; i++){
      size = 0;
      createGraph(graph);
      load(friends, m, size, graph);
      floyds(graph, size);
      print(graph, size);
   }
   return 0;
}

/* load function: 
 *     Read from standard input to load the people
 *     into an array. Then use that array to fill
 *     the relationships of the matrix.
 *                 
 *  precondition: 
 *     friends[] is an array of strings. 
 *     m is the number of friend relationships.
 *     size is the size of friends.
 *     graph is the final matrix.
 *     friends[] is empty.
 *     size is empty.
 *
 *  postcondition: 
 *     friends[] will be loaded with people.
 *     size will contain the size of friends.
 *     graph will be filled with the correct values.
 */
void load(string friends[], int &m, int &size, int **graph){
   string temp;
   string person, person2;
   int sub=0, sub2=0;

   //specifies the number of friend relationships in a collection
   cin >> m;
   for(int i=0; i<m; i++){
      //reading in people
      cin >> person >> temp >> person2;

      sub = searchAndInsert(friends, size, person);
      sub2 = searchAndInsert(friends, size, person2);

      fillGraph(graph, sub, sub2);
   }
}

/* searchAndInsert function: 
 *     Search the array to see if the current
 *     search item is already located within
 *     friends.
 *                 
 *  precondition: 
 *     friends[] is an array of strings.
 *     size is the size of friends.
 *     searchKey is the string being searched for.
 *     size is empty.
 *
 *  postcondition: 
 *     size will incriment to the the size of friends.
 *     the function will return the index of the string found.
 */
int searchAndInsert(string friends[], int &size, string searchKey) { 
   int index = 0;
      while(index < size){
         if(friends[index] == searchKey){
            return index;
         }
         index++;
      }
      friends[size] = searchKey;
      size++;
      return size-1;
}

/* createGraph function: 
 *     Create a matrix filled with 0's
 *     that is MAX x MAX large or 64x64.
 *                 
 *  precondition: 
 *     graph is the final matrix.
 *     graph is empty.
 *
 *  postcondition: 
 *     graph will be a MAX x MAX array
 *     filled with 0's
 */
void createGraph(int **graph){
   for(int i=0; i<MAX; i++){
      graph[i] = new int[MAX];
      //each i-th pointer is now pointing to dynamic array (size MAX) of actual int values
   }
   for(int r=0; r<MAX; r++){    //for each row
      for(int c=0; c<MAX; c++){ //for each column
         graph[r][c] = 0;
      }
   }
}

/* fillGraph function: 
 *     The matrix graph will set the
 *     friends that are connected to 1.
 *                 
 *  precondition: 
 *     graph is the final matrix.
 *     sp1 is the location of person 1.
 *     sp2 is the location of person 2.
 *
 *  postcondition: 
 *     graph will have 1 where the
 *     relationship is connected and 0
 *     where it is not.
 */
void fillGraph(int **graph, int sp1, int sp2){
   graph[sp1][sp2] = 1;
}

/* floyds function: 
 *     Uses floyd's algorithm to create Dn,
 *     checks all values except for diagonals.
 *                 
 *  precondition: 
 *     graph is the final matrix.
 *     size is the size of the arrray.
 *     graph is currently at D0
 *
 *  postcondition: 
 *     graph will fill up to Dn
 */
void floyds(int **graph, int &size){
   int i,j,k;
   for(k=0; k<size; k++){
      for(i=0; i<size; i++){
         for(j=0; j<size; j++){
            if(i == j)
               graph[i][j] = 0;
            else
               graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
         }
      }
   }
}

/* print function: 
 *     checks the final matrix to
 *     see if it is connected or disconnected
 *     and prints "connected" or "disconnected"
 *     respectively.
 *                 
 *  precondition: 
 *     graph is the final matrix.
 *     size is the size of the array.
 *
 *  postcondition: 
 *     prints 'connected' if connected
 *     prints 'disconnected' if disconnected
 */
void print(int **graph, int &size){
   int connected = -1, row, col;
   for(row = 0; row<size; row++){
      for(col = 0; col<size; col++){
         if(row != col){
            if(graph[row][col] == 0){
               connected = 0;
               break;
            }
            else
               connected = 1;
         }
         else
            break;
      }
   }
   if(connected == 1)
      cout << "connected" << endl;
   else
      cout << "disconnected" << endl;
}