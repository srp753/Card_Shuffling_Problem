
/* This is a C program to compute the number of rounds
required to get the same sequence of cards after following the
4 steps described in Problem 1.

>>This program takes one command line input which is the number of 
cards and outputs the number of rounds required.

**Important data structure for this problem: Queue

****Basic Requirements and Functions*****

1) Let N be the number of cards. We first create:
    a) An array orig
    b) A queue 
    having elements ranging from 1 to N. If there are 3 cards,
    the orig array and queue will have elements 1,2,3. 

    We want the same sequence 1,2,3 after following the 4 steps in 
    Problem 1.

    Queue is implemented using a structure called Node whose members
    are an int type data variable and pointer pointing to the next struct 
    Node type variable.

    Functions Enqueue, Dequeue and Front are crucial operations for 
    insertion & deletion in a queue and obtaining the front element of the queue
    respectively. 

    I have taken reference of the Queue structure from the link below:
    https://gist.github.com/mycodeschool/7510222

    Since we have the requirement of only one queue here, the front and rear
    pointers have been made global.

2) Some other functions like reverseArray and compareArrays are crucial 
    for achieving the required solution.

    Their reference is as follows:
    https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
    https://stackoverflow.com/questions/24153883/comparing-two-arrays-in-c-element-by-element
    
    The reference was taken to save time in coding redundant operations
    
****Method of Implementation****

1) Firstly, the queue and array orig is loaded with original card sequence.

2) Thenafter, the first element is drawn from the front of the queue
and stored in an array. This operation resembles placing the top card 
on the table.

3) We dequeue the queue(remove the front element) and again extract 
the front element of the queue. We enqueue this extracted value at
the end of the queue and remove it from the front. This operation 
resembles placing the card at the bottom of the deck.

4) Step 2 and 3 above are repeated till the queue is empty.

5) Now we have a new sequence in the temporary array arr.
However, we need to reverse this sequence since the first
card drawn in 2nd round will be the one which was put last 
on the table.

6) We repeat steps 2 to 5 till the new sequence is not equal
to the original card sequence 1 2 3... N. We also increment
a counter till the equality between arr and orig is established.

7) Count now gives us the number of rounds which is the
solution of Problem 1.

*/


#include <stdlib.h>  
#include <stdio.h>   

//Implementation of Queue data structure
struct Node {
   int data;
   struct Node* next;
};
// Two global variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;

// To Enqueue an integer
void Enqueue(int x) {
   struct Node* temp = 
      (struct Node*)malloc(sizeof(struct Node));
   temp->data =x; 
   temp->next = NULL;
   if(front == NULL && rear == NULL){
      front = rear = temp;
      return;
   }
   rear->next = temp;
   rear = temp;
}

// To Dequeue an integer.
void Dequeue() {
   struct Node* temp = front;
   if(front == NULL) {
      printf("Queue is Empty\n");
      return;
   }
   if(front == rear) {
      front = rear = NULL;
   }
   else {
      front = front->next;
   }
   free(temp);
}

int Front() {
   if(front == NULL) {
      printf("Queue is empty\n");
      return 0;
   }
   return front->data;
}

//Function to reverse an array
void reverseArray(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}     

//Function to compare 2 same-sized arrays
int compareArrays(int a[], int b[], int n) {
  int i;
  for(i = 0; i < n; i++) {
    if (a[i] != b[i]) return 0;
  }
  return 1;
}

//Takes one argument which is number of cards.
int main(int argc, char *argv[]) {
   
       
      if( argc == 2 ) {
         printf("The argument supplied is %s\n", argv[1]);
         }
       else if( argc > 2 ) {
            printf("Too many arguments supplied.\n");
         }
      else {
           printf("One argument expected.\n");
         }

       int num_cards;
       num_cards = atoi(argv[1]);
       
       int orig[num_cards],arr[num_cards];
   
      printf("No of cards: %d \n", num_cards);
      
   //Loading the queue and array orig with original card sequence.
    for (int i = 0; i < num_cards; i++) {
        
        Enqueue(i+1);
        orig[i] = i + 1;
    }
     
    
     int count = 0;
     //Flag to indicate when arr equal to orig
     int flag = 0;
     while(flag == 0)
     {
         //Resetting k for the new iteration
         int k = 0;
        
         while(front!=NULL)
         {
             //When top card is put on the table
             arr[k++] = Front();
             Dequeue();
             //When top card is put at the bottom of the deck
             if(front!=NULL)
             {
                 int g = Front();
                 Dequeue();
                 Enqueue(g);
             }
         }
         //Reversing arr since the first card drawn again will be 
         //the one which was put last on the table.

         reverseArray(arr,0,num_cards-1);
         
         //If the deck is equal to original then flag 1 & last count
         // increment
         if(compareArrays(orig,arr,num_cards))
         {
            count = count + 1;
            flag = 1;
         }
        //Else keep counting and enqueue the new sequence in the queue
         else
            {
                count = count + 1;
                
                //printf("\narr: ");
                for(int j = 0; j < num_cards; j++)
                {
                    Enqueue(arr[j]);
                    /*To see the new card sequences uncomment the below
                    and printf("\narr: ") above;*/
                    //printf("%d ",arr[j]); 
                }
            }
        
        
     }
    printf("No. of rounds needed: %d\n",count);
    
    //Freeing front and rear to avoid memory leaks
     
   free(front);
   free(rear);
   return 0;
}