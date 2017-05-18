#include <iostream>
#include <algorithm>

 
using namespace std;

int n = 0;
long long int A[100001];
long long int B[100001];
long long int C[200002];

// simply print the array
void printarr(long long int *arr, int len){
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
 
// Add the two part to get the middle part of each arr
void addTwoPart(long long int* a, long long int* b, long long int* tar, int lena, int lenb)
{
 
    // Add tow part together
    for (int i = 0; i < lena; ++i)
    {
    	tar[i] = a[i] +b[i];
    }
 
    // if the second part is greater than the first part
    if (lena != lenb)  
    	tar[lena] = b[lena];
 
    return;
}
 
// the base case of multiply tow number
void multiplyBase(long long int* a, long long int* b, long long int* c){  
	c[0] = a[0] * b[0];
	return;
}
 
// The multiply two array
void multiply(long long int* a, long long int* b, long long int* tar, int len)
{
 
    // Base cases  
    if (len == 1) {
    	multiplyBase(a, b, tar);
    	return; 
    }
 
    // First half of array, floor(len/2)
    int fh = len/2;  
    // Second half of array, ceil(len/2)
    int sh = len-fh; 

    // seperate the first arr into left mid and right three part
    long long int* aleft = new long long int [fh];
    long long int* aright = new long long int [sh];
    long long int* amid = new long long int [sh];

    //copy the parts into corresponding arr
    copy(a, a+fh, aleft);
    copy(a+fh, a+len, aright);
    addTwoPart(aleft, aright, amid, fh, sh);
 
    // seperate the first arr into left mid and right three part
    long long int* bleft = new long long int [fh];
    long long int* bright = new long long int [sh];
    long long int* bmid = new long long int [sh];

	// copy the parts into corresponding arr 
    copy(b, b+fh, bleft);
    copy(b+fh, b+len, bright);
    addTwoPart(bleft, bright, bmid, fh, sh);
 
    // create 3 new result arr
    long long int* rleft = new long long int [2*fh-1];
    long long int* rright = new long long int [2*sh-1];
    long long int* rmid = new long long int [2*sh-1];

    //recursively multiply until hit the base case
    multiply(aleft, bleft, rleft, fh);
    multiply(aright, bright, rright, sh);
    multiply(amid, bmid, rmid, sh);

    // substract the mid part with left and right
    for (int i = 0; i < fh*2-1; ++i)
    {
    	rmid[i] = rmid[i] - rleft[i] - rright[i];
    }

    // if right part is greater than left then substract the rest
    if (sh > fh){
    	for (int i = fh*2-1; i < sh*2-1; ++i)
    	{
    		rmid[i] = rmid[i] - rright[i];
    	}
    }

    // clear the target arr
 	for (int i = 0; i < 2*len-1; ++i)
 	{
 		tar[i] = 0;
 	}

 	// insert the left part to target arr
    for (int i = 0; i < 2*fh-1; ++i)
    {
    	tar[i] = tar[i] + rleft[i];
    }
    // insert the mid part to target arr
    for (int i = 0; i < 2*sh-1; ++i)
    {
    	tar[fh+i] = tar[fh+i] + rmid[i];
    }
    // insert the right part to target arr
    int t = 2*len-1;
    for (int i = 2*sh-2; i >= 0; --i)
    {
    	--t;
    	tar[t] = tar[t] + rright[i];
    }

    // delete the used array
    delete[] aleft;
    delete[] amid; 
    delete[] aright;
    delete[] bleft;
    delete[] bmid; 
    delete[] bright;
    delete[] rleft;
    delete[] rmid; 
    delete[] rright;
    return;
}

int main(int argc, char const *argv[])
{
	// get the # n
	cin >> n;

	// input arr A
	for (int i = 0; i < n+1; ++i)
	{
        long long int c = 0;
        cin >> c;
		A[i] = c ;
	}

	// input arr B
	for (int i = 0; i < n+1; ++i)
	{
		long long int c = 0;
        cin >> c;
        B[i] = c ;
	}

	// do the multiple therom
	multiply(A, B, C, n+1);

	// print
	printarr(C, 2*n+1);
	return 0;
}