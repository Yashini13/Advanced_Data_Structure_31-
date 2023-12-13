#include <iostream>
using namespace std;
int cookies(int k , int *a,int size)
{
  int cnt = 0; // Flag to check the level of sweetness in cookies
  while(true)
  {
    int corr_sweetness=1;
    int min=INT16_MAX;
    int min2 = INT16_MAX;

     for(int i=0; i< size ;i++){
        if(corr_sweetness && a[i]< k)
        { corr_sweetness=0;  }

         if(a[i]<min)    
        {
        min2 = min;
        min = a[i];  //finding the last element 
        }
        else if(a[i]<min2)
        {
            min2=a[i];  //finding the second last element 
        }   
     }

    
     if(corr_sweetness)
     {
          return cnt;  //if sweetness is upto the mark
     }
     int total= 1*min+2*min2;  //calculation part

     if(total<min2) //if negative value
     {
        return -1;
     }
     for(int i=0; i<size;i++)
     {
        if(a[i]==min||a[i]==min2)
         a[i]=total;   // replacing the array
     }
     cout<<"updated array:\n";
     for(int i=0;i<size;i++)
     {    
         cout<<a[i]<<endl;  
     }
     cnt++;
  }

  return cnt; 
}
int main() {
    int k = 10; // desired sweetness amount
    int a[] = {2,6,8,5, 20, 12}; 
    int size = sizeof(a) / sizeof(a[0]); 
    int ans = cookies(k, a,size);
    for (int i=0;i<size;i++)
    {
      cout<<a[i]<<endl;
    }
   
    printf("\n No.of Iterations : %d", ans); 
   
    return 0;
}