#include <iostream>
using namespace std;

int partition(int *a,int start,int end){
    int pivot=a[end];int i=start-1;

    for(int j=start;j<end;j++){
        if(a[j]<pivot){
            swap(a[++i],a[j]);
        }
    }
    swap(a[++i],a[end]);
    return i;
}


void quickSort(int* a,int start,int end){
    if(start<end){
        int p=partition(a,start,end);

        quickSort(a,start,p-1);
        quickSort(a,p+1,end);
    }
}




void merge(int*a,int start,int middle,int end){
    int n1=middle-start+1,n2=end-middle;
    int L[n1],R[n2];
    for(int i=0;i<n1;i++)
        L[i]=a[start+i];
    for(int i=0;i<n1;i++)
        R[i]=a[middle+1+i];

    int i=0,j=0,k=start;
    while(i<n1 && j<n2){
        a[k++]=(L[i]<R[j])?L[i++]:R[j++];
    }
    while(i<n1){
        a[k++]=L[i++];
    }
    while(i<n2){
        a[k++]=R[j++];
    }
}
void mergeSort(int*a,int start,int end){
    if(start<end) {
        int middle = start + (end - start) / 2;
        mergeSort(a,start,middle);
        mergeSort(a,middle+1,end);
        merge(a,start,middle,end);

    }
}



int main(){
    int n=6;
    int a[]={5,7, 2, 3, 4, 1};

    quickSort(a,0,n-1);

    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }


    return 0;
}
