#include<cstdio>
#include<cstring>
#include "stdops.h"
#include<ctime>
FILE *flab,*fimg,*fpar;
unsigned char a[100001][28][28],b[100001];
unsigned n;
float input[100001][28*28],w1[28+1][28*28+1],w2[10][28+2],ans[100001][10],eps;
Placeholder *pin[28*28+1],*pout[10];
Parameter *pw1[28+1][28*28+1],*pw2[10][28+2],*peps;
Node *out1[28+2],*out2[10],*loss;
Assign *ch1[28+1][28*28+1],*ch2[10][28+2];
Node *fin;
std::map<Node*,Tensor> initlist;
std::vector<Node*> v;
unsigned flip(unsigned t){return (t>>24)|((t>>8)&0xff00)|((t<<8)&0xff0000)|(t<<24);}
void getdata()
{
	int i,j,k;
	flab=fopen("train-labels.idx1-ubyte","rb");
	fimg=fopen("train-images.idx3-ubyte","rb");
	unsigned t;
	fread(&t,4,1,flab);
	t=flip(t);
	//printf("%u\n",t);
	fread(&n,4,1,flab);
	n=flip(n);
	//printf("%u\n",n);
	fread(b,1,n,flab);
	fseek(fimg,16,SEEK_SET);
	fread(a,1,n*28*28,fimg);
	fpar=fopen("train.tmp","r");
	if(fpar!=nullptr)
	{
		for(i=0;i<28+1;i++)
		for(j=0;j<28*28+1;j++)fscanf(fpar,"%f",&w1[i][j]);
		for(i=0;i<10;i++)
		for(j=0;j<28+2;j++)fscanf(fpar,"%f",&w2[i][j]);
		fscanf(fpar,"%f",&eps);
		fclose(fpar);
	}
	else
	{
		srand(time(0));
		for(i=0;i<28+1;i++)
		for(j=0;j<28*28+1;j++)w1[i][j]=rand()/(float)RAND_MAX;
		for(i=0;i<10;i++)
		for(j=0;j<28+2;j++)w2[i][j]=rand()/(float)RAND_MAX;
		eps=100;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<28;j++)
		for(k=0;k<28;k++)input[i][j*28+k]=a[i][j][k];
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<10;j++)if(b[i]==j)ans[i][j]=1;else ans[i][j]=0;
	}
	std::cerr<<"ok\n";
	for(i=0;i<28*28+1;i++)pin[i]=placeholder();
	for(i=0;i<10;i++)pout[i]=placeholder();
	for(i=0;i<28+1;i++)
	for(j=0;j<28*28+1;j++)pw1[i][j]=parameter(w1[i][j]);
	for(i=0;i<10;i++)
	for(j=0;j<28+2;j++)pw2[i][j]=parameter(w2[i][j]);
	peps=parameter(eps);
	std::cerr<<"ok\n";
	
	
	fclose(flab);fclose(fimg);
}
int main()
{
	int i,j,k;
	std::cerr<<"ok\n";
	getdata();
	std::cerr<<"ok\n";
	for(i=0;i<28+1;i++)
	{
		v.clear();
		for(j=0;j<28*28+1;j++)v.push_back(mul(pw1[i][j],pin[j]));
		out1[i]=print(sigmoid(addn(v)),"out1:");
	}
	out1[28+1]=One;
	
	for(i=0;i<10;i++)
	{
		v.clear();
		for(j=0;j<28+2;j++)v.push_back(mul(pw2[i][j],out1[j]));
		out2[i]=print(addn(v),"out2:");
	}
	v.clear();
	for(i=0;i<10;i++)v.push_back(sqr(sub(out2[i],pout[i])));
	loss=addn(v);
	loss=print(loss,"loss:");
	std::cerr<<"ok\n";
	for(i=0;i<28+1;i++)
	for(j=0;j<28*28+1;j++)ch1[i][j]=assign(pw1[i][j],print(sub(pw1[i][j],mul(peps,loss->grad(pw1[i][j]))),"ch1:"));
	std::cerr<<"ok\n";
	
	for(i=0;i<10;i++)
	for(j=0;j<28+2;j++)ch2[i][j]=assign(pw2[i][j],print(sub(pw2[i][j],mul(peps,loss->grad(pw2[i][j]))),"ch2:"));
	fin=Zero;
	v.clear();
	for(i=0;i<28+1;i++)
	for(j=0;j<28*28+1;j++)v.push_back(ch1[i][j]);
	for(i=0;i<10;i++)
	for(j=0;j<28+2;j++)v.push_back(ch2[i][j]);
	fin=bindn(v);
	i=0;
	std::cerr<<"ok\n";
	while(peps->getfloat()>1e-5)
	{
		
		for(j=0;j<28*28;j++)initlist[pin[j]]=input[i][j];
		initlist[pin[28*28]]=1;
		for(j=0;j<10;j++)initlist[pout[j]]=ans[i][j];
		std::cerr<<"i="<<i<<"ok\n";
		std::cout<<Run(initlist,*fin)<<'\n';
		fpar=fopen("train.tmp","w");
		for(i=0;i<28+1;i++)
		for(j=0;j<28*28+1;j++)fprintf(fpar,"%f",pw1[i][j]->getvalue());
		for(i=0;i<10;i++)
		for(j=0;j<28+2;j++)fprintf(fpar,"%f",pw2[i][j]->getvalue());
		fprintf(fpar,"%f",peps->getvalue());
		fclose(fpar);
		i++;if(i>=n)i-=n;peps->multiply(0.9);
	}
	return 0;
}
	
	
	
	
