#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string.h>


using namespace std ;


int n;
void conv_bin(unsigned int **M,unsigned int *N, int m)
{
	int i,j,k,x,y,z,w,count ;
	j = (int)pow(2,n) ;
	w = (int)pow(2,m) ;
	for ( i = 0; i < j; i++)
	{
		k = w / 2 ;
		x = N[i] ;
		z = m ;
		count = 0 ;
		while ( z > 0)
		{
			y = x / k;
			if (y > 0) 
				x = x - k ;
			M[i][count] = y ; 
			k /= 2 ;
			z -- ;
			count++ ;
		}
	}
}


int main(){

	bool inputParity, outputParity;
	int m, g, p ;
	unsigned int i,j,k,x,y,z,QC,max, maxY ;
	unsigned int **A,**B ;
	unsigned int *X,*Y ;
	int *match,*mismatch,*count ;

	cin >> n;
	x = (int)pow (2,n) ;

	A = new unsigned int *[x] ;
	B = new unsigned int *[x] ;
	X = new unsigned int[x] ;
	Y = new unsigned int[x] ;
	match = new int[x] ;
	mismatch = new int[x] ;
	count = new int[x] ;

	maxY = 0;
	for (i = 0; i < x; i++)
	{
		A[i] = new unsigned int[n] ;
		//B[i] = new unsigned int[m] ;
		X[i] = i ;
		cin >> Y[i] ;
		if (Y[i] > maxY)
			maxY = Y[i];
	}
	m = log2 (maxY) + 1;

	for (i = 0; i < x; i++)
		B[i] = new unsigned int[m] ;

	conv_bin(A,X,n) ;
	conv_bin(B,Y,m) ;
	/*
	for (i = 0; i < x; i++){
		cout << i << " " ;
		for (j = 0; j < n; j++)
			cout << A[i][j];
		cout << " ";
		for (j = 0; j < m; j++)
			cout << B[i][j];
		cout << endl;
	}*/

	//Algorithm implementation
	max = 0;
	for (i = 0; i < x; i++){
		match[i]=0; mismatch[i]=0; count[i]=0;
	}
	for (i = 0; i < x; i++){
		inputParity = 0;
		for (j = 0; j < n; j++)
			inputParity = inputParity ^ A[i][j] ;
		outputParity = 0;
		for (j = 0; j < m; j++)
			outputParity = outputParity ^ B[i][j] ;
		
		if (inputParity == outputParity){
			//cout << "match" << endl ;
			match[Y[i]]++;
			count[i] = match[Y[i]];
			if (max <= match[Y[i]])
				max = match[Y[i]];
		}
		else{
			//cout << "mismatch" << endl ;
			mismatch[Y[i]]--;
			count[i] = abs(mismatch[Y[i]]);
			if (max <= abs(mismatch[Y[i]]))
				max = abs(mismatch[Y[i]]);
		}
	}
	g = log2 (max) + 1;
	cout << "No. of garbage bits : " << g << endl;
	for (i = 0; i < x; i++){
		if (count[i] != 0)
			count[i]--;
		//cout << count[i] << endl ;
	}

	cout << "Input    ||  Output\n";
	for (i = 0; i < x; i++){
		inputParity = 0;
		outputParity = 0;
		for (j = 0; j < n; j++){
			inputParity = inputParity ^ A[i][j] ;
			cout << A[i][j];
		}

		z = g;
		cout << "  ";
		while (z > 0){
			cout << "0";
			z--;
		} 
		cout << "  ||  ";
		for (j = 0; j < m; j++){
			cout << B[i][j];
			outputParity = outputParity ^ B[i][j] ;
		}
		cout << " ";
		z = g;
		k = count[i];
		p = (int)pow (2,z-1) ;

		while (z > 0){
			outputParity = outputParity ^ (k / p) ;
			cout << k / p;
			k = k % p;
			p = p / 2;			
			z--;
		}
		if (inputParity == outputParity)
			cout << "  0";
		else
			cout << "  1";
		cout << endl;
	}
//*/
	return 0;
}
