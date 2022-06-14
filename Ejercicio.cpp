//One-dimensional Steady Conduction Problem
#include<iostream>

#include<stdlib.h>
#include<time.h>
#include<math.h>

using namespace std;
int main(){
float c,e=1,l;
int vc,n=10,m, j=0;
float sx[100],p[100],dx[100],ap[100],T[100],Ta[100],ae[100],aw[100],b[100];
vc=n-2;
m=floor(n/2);

//Geometry
l=1;//length [m]
for(int i=0;i<n-1;i++){//defining sx
	if(i==0){sx[i]=l/(2*vc);//first sx
	}
	else if(i==n-2){sx[i]=l/(2*vc);;//last sx
	}
	else{sx[i]=l/vc;//Remaining sx
	}
}
for(int i=0;i<n;i++){//defining dx
dx[i]=0;
if((i!=0)&&(i!=n-1))
{dx[i]=l/vc;}//dx for the nodes with a C.V.;
}

// Properties
c=200;//conductivity(W/m*K)
for(int i=0;i<n;i++){
T[i]=0;//Fist iteration of Temperatures by filling it with 0
if(i==0){//fist node
ae[i]=c/sx[i];
aw[i]=0;
b[i]=0;
ap[i]=ae[i]+aw[i];
	}
	else if(i==n-1){//Last node
ae[i]=0;
aw[i]=c/sx[i-1];// is i-1 because the gemoetry is = to #nodes-1
b[i]=0;
ap[i]=ae[i]+aw[i];
	}
	else{
ae[i]=c/sx[i];
aw[i]=c/sx[i-1];// is i-1 the gemoetry is = to #nodes-1
b[i]=0*dx[i];//it is defined so it has a value
ap[i]=ae[i]+aw[i];
	}
}	

// Dirichlet Boundary  Condition left T=37[K]
ap[0]=1;//
ae[0]=0;
aw[0]=0;
b[0]=37;//[K]
//Mixed Boundary  Condition rigth Convection
ae[n-1]=0;
aw[n-1]=c/sx[n-2];
ap[n-1]=aw[n-1]+9;
b[n-1]=9*25;//(W/m^2)

//Solver
do{
for(int i=0;i<n;i++){
    Ta[i]=T[i];//memory of the previous temperatures
	if(i==0){T[i]=(ae[i]*T[i+1]+b[i])/ap[i];//First node
	}
	else if(i==n-1){T[i]=(aw[i]*T[i-1]+b[i])/ap[i];//Last node
	}
	else{
	b[i]=64*T[i]*dx[i];//GENERATION
	T[i]=(ae[i]*T[i+1]+aw[i]*T[i-1]+b[i])/ap[i];
	}
	}
e=(abs(Ta[m]-T[m])+abs(Ta[n-1]-T[n-1]))/2;
j++;
}
while((j<100000)&&(e>0.000001));//conditions 

//Print Results and end. 
	cout<<"X-Coordinate    "<<"T[K]\n";
	p[0]=0;
for(int i=0;i<n;i++){
	cout<<p[i]<<"         "<<T[i]<<"\n";
	p[i+1]=p[i]+sx[i];}
cout<<"l/2   #"<<m+1<<"  x="<<p[m]<<"     T[m]    "<<T[m]<<"\n";
	
	return 0;
}