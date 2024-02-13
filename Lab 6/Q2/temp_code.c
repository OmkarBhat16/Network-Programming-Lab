/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <math.h>
int parityBitCount(int arr[],int size){
    int parity = 0;
    while(!(pow(2,parity)>=(parity+size+1))){
        parity++;
    }
    return parity;
}

int[] parityGenerator(int arr[], int n , int parity[] , int p){
    for(int i=0;i<p;i++){
        int val = pow(2,i);
        for(int j=val;j<n;j+=val){
            
        }
    }
}
int main()
{
    printf("Enter size of array : ");
    int n = 0;
    scanf("%d",&n);
    int arr[n];
    
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);

        if(arr[i]!=0 && arr[i]!=1)
            arr[i]%=2;
    }
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    
    printf("\n%d",parityBitCount(arr,n));
    
    
    return 0;
}
