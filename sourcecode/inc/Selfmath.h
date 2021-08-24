#ifndef Selfmath
#define Selfmath

int mathmin03(double* arr,int size)
{double min= arr[0];
int index=0;
for(int i=0;i<size;++i)
	if(min>arr[i]){
		min=arr[i];
		index=i;
	}
return index;
}

int* InsertionSort(int *a, int* seq,int len) 
{   
	for (int j=1; j<len; j++)  
    {  
        int key = a[j];  
        int i = j-1;  
        while (i>=0 && a[i]>key)  
        {  
            a[i+1] = a[i];
			int temp=seq[i+1];
			seq[i+1]=seq[i];
			seq[i]=temp;
            i--;  
        }  
        a[i+1] = key;  
    }  
	return seq;
} 

#endif