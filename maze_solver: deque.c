#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// declaring point structure to store x and y cordinates together as one pair
struct point
{
    int x;
    int y;
};

// creating deque data structure 
#define N 1000
#define MAX_COLS 100
#define MAX_ROWS 100
struct point deque[N];
int front=-1;
int rear=-1;

void add_first(int a,int b){
    
    if( (front==0 && rear==N-1) || (front==rear+1) ){
        printf("Overflow");
    }
    else if(front==-1 && rear==-1){
        front=rear=0;
        deque[front].x=a;
        deque[front].y=b;
    }
    else if(front==0){
        front=N-1;
        deque[front].x=a;
        deque[front].y=b;
    }
    else{
        front--;
        deque[front].x=a;
        deque[front].y=b;
    }
}


void add_last(int a,int b){
    
    if( (front==0 && rear==N-1) || (front==rear+1) ){
        printf("Overflow");
    }
    else if(front==-1 && rear==-1){
        front=rear=0;
        deque[rear].x=a;
        deque[rear].y=b;
    }
    else if(rear==N-1){
        rear=0;
        deque[rear].x=a;
        deque[rear].y=b;
    }
    else{
        rear++;
        deque[rear].x=a;
        deque[rear].y=b;
    }
}


void remove_first(){
    if(front==-1 && rear==-1){
        printf("Underflow");
    }
    else if(front==rear){
        front=rear=-1;
    }
    else if(front==N-1){
        front=0;
    }
    else{
        front++;
    }
}


void remove_last(){
    if(front==-1 && rear==-1){
        printf("Underflow");
    }
    else if(front==rear){
        front=rear=-1;
    }
    else if(rear==0){
        rear=N-1;
    }
    else{
        rear--;
    }
}

int main()
{
    char arr[1000][1000];
   FILE *file;
   file=fopen("maze1.txt","r");
   //change the file name "maze1.txt" to other files so as to read other mazes
   //eg. "maze2.txt","maze3.txt"
   if (file == NULL) {
        printf("Error opening file \n");
        return;
    }
   char line[MAX_COLS];
   int row=0,col=0;
   while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(arr[row],line);
        col = strlen(line);
        row++;
    }
    // finding index of S and E
    int E1,E2,S1,S2;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(arr[i][j]=='E')
            {
                E1=i,E2=j;
            }
            else if(arr[i][j]=='S')
            {
                S1=i,S2=j;
            }
        }
    }
    add_first(S1,S2);
    int k=0;
    while(rear!=-1||front!=-1)
    {
        int i=deque[front].x;
        int j=deque[front].y;
        remove_first();
        if(arr[i][j]=='E'){
            k=1;
            break;
        }
        else if(arr[i][j]=='#'||arr[i][j]=='.')
            continue;
        else if(arr[i][j]==' '||arr[i][j]=='S')
        {
            arr[i][j]='.';
            // to decide wheather to push front or rear we calculate distance of l and compare each
            int l_distance=abs(E1-i)+abs(E2-j);
            if(j+1<col)
            {
                if(abs(E1-i)+abs(E2-j-1)<l_distance)
                    add_first(i,j+1);
                else
                    add_last(i,j+1);
            }
            if(j-1>=0)
            {
                if(abs(E1-i)+abs(E2-j+1)<l_distance)
                    add_first(i,j-1);
                else
                    add_last(i,j-1);
            }
            if(i+1<row)
            {
                if(abs(E1-i-1)+abs(E2-j)<l_distance)
                    add_first(i+1,j);
                else
                    add_last(i+1,j);
            }
            if(i-1>=0)
            {
                if(abs(E1-i+1)+abs(E2-j)<l_distance)
                    add_first(i-1,j);
                else
                    add_last(i-1,j);
            }
        }
    }
    // since i changed S to . now i convert it back
    arr[S1][S2]='S';
    // to print the final array i.e answer
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%c", arr[i][j]);
        }
        puts("");
    }
    if(k==1) printf("maze is solvable\n");
    else printf("maze is not solvable");
    return 0;
}
