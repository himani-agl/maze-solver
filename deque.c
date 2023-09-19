#include<stdio.h>
int n; // n defines the size of deque 
int first=-1,last=0;

//function to add elment at begining of deque
void add_first(int dq[n],int x){
    //checking if deque is full
    if ((first==0 && last==n-1)|| first==last+1){
        printf("overflow\n");
        return;
    }
    //if deque is initially empty
    if (first==-1){
        first=0;
        last=0;
    }
    else if(first==0)
        first=n-1;
    else
        first--;
    dq[first]=x;
}

// function to insert element at end of deque
void add_last(int dq[n],int x){
    //checking if deque is full
    if ((first==0 && last==n-1)|| first==last+1){
        printf("overflow\n");
        return;
    }
    //if deque is intitially empty
    if (first==-1){
        first=0;
        last=0;
    }
    else if(last==n-1)
        last=0;
    else
        last++;
    dq[last]=x;
}

//function to remove first element of deque
void remove_first(){
    //checking if deque is empty
    if(first==-1){
        printf("underflow\n");
        return;
    }
    // checking if deque has only one element
    if(first==last){
        first=-1;
        last=-1;
    }
    else if(first==n-1)
        first=0;
    else
        first++;
}

//function to remove last element of deque
void remove_last(){
    //checking if deque is empty
    if(first==-1){
        printf("underflow\n");
        return;
    }
    //checking if deque has only one element
    if(first==last){
        first=-1;
        last=-1;
    }
    else if(last==0)
        last=n-1;
    else
        last--;
}

//function to print elements of deque
void print_deque(int dq[n]){
    //checking if deque is empty
    if(first==-1)
       printf("list is empty");
    else{
       int i=first;
       do{
           printf("%d\n",dq[i]);
           if(i==last)
              break;
           i=(i+1)%n;
       }while(i!=first);
    }
}
int main(){
    printf("enter the size of deque:\n");
    scanf("%d",&n);
    int x;
    int value;
      int dq[n]; // here dq is represents deque
    while(1){
    printf("enter 1 to add_first\n 2 to add_last\n 3 to remove first\n 4 to remove last\n 5 to print deque\n 0 to stop the function");
    scanf("%d",&x);
    if(x==0) break; //terminate the while loop
    switch(x){
        case 1 :
           printf("enter value to be added\n");
           scanf("%d",&value);
           add_first(dq,value);
           break;
        case 2 :
           printf("enter value to be added\n");
           scanf("%d",&value);
           add_last(dq,value);
           break;
        case 3 :
           remove_first(dq);
           break;
        case 4 :
           remove_last(dq);
           break;
        case 5 :
           print_deque(dq);
           break;
        default:
           printf("invalid");
           break;
    }
    }
   return 0;
}