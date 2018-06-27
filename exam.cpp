#include<cstdio>
#include<cstring>
#include "stdops.h"
#include<ctime>
#include<unistd.h>
const int sz1=28;
FILE *flab,*fimg,*fpar;
unsigned char a[100001][28][28],b[100001];
unsigned n;
Tensor input[100001],w1({},{sz1,28*28+1}),w2({},{10,sz1}),ans[100001];
float eps1,eps2;
unsigned flip(unsigned t){return (t>>24)|((t>>8)&0xff00)|((t<<8)&0xff0000)|(t<<24);}
void getdata()
{
	int i,j,k;
	flab=fopen("t10k-labels.idx1-ubyte","rb");
	fimg=fopen("t10k-images.idx3-ubyte","rb");
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
	std::cerr<<"ok\n";
	fpar=fopen("train.tmp","r");
	if(fpar!=nullptr)
	{
#ifndef float
		for(i=0;i<sz1;i++)
		for(j=0;j<28*28+1;j++)fscanf(fpar,"%f",&w1.at({i,j}));
		for(i=0;i<10;i++)
		for(j=0;j<sz1;j++)fscanf(fpar,"%f",&w2.at({i,j}));
#else
		for(i=0;i<sz1;i++)
		for(j=0;j<28*28+1;j++)fscanf(fpar,"%lf",&w1.at({i,j}));
		for(i=0;i<10;i++)
		for(j=0;j<sz1;j++)fscanf(fpar,"%lf",&w2.at({i,j}));
#endif
		//fscanf(fpar,"%f%f",&eps1,&eps2);
		fclose(fpar);
	}
	else
	{
		std::cerr<<"train.tmp not found.\n";
		exit(0);
	}
	std::cerr<<"ok\n";
	for(i=0;i<n;i++)
	{
		input[i]=Tensor({},{28*28+1,1});
		for(j=0;j<28;j++)
		for(k=0;k<28;k++)input[i].at({j*28+k,0})=a[i][j][k]/4096.0;
		input[i].at({28*28,0})=1;
	}
	std::cerr<<"ok\n";
	for(i=0;i<n;i++)
	{
		ans[i]=Tensor({},{10,1});
		for(j=0;j<10;j++)if(b[i]==j)ans[i].at({j,0})=1;else ans[i].at({j,0})=0;
	}
	std::cerr<<"ok\n";
	fclose(flab);fclose(fimg);
}
int main()
{
	int i,j,k;
	getdata();
	std::cerr<<"ok\n";
	auto pi=placeholder(),po=placeholder();
	auto p1=parameter(w1),p2=parameter(w2),pe1=parameter(eps1),pe2=parameter(eps2);
	//std::cout<<ans[0]<<'\n';
	auto mout1=/*print(*/matmul(p1,pi)/*,"mout1=")*/;
	auto out1=/*print(*/sigmoid(mout1)/*,"out1=")*/;
	auto out=/*print(*/matmul(p2,out1)/*,"out=")*/;
	auto soft=/*print(*/softmax(out)/*,"soft=")*/;
	std::cerr<<"ok\n";
	int okgs=0;
	for(int T=0;T<n;T++)
	{
		std::cout<<Run({{pi,input[T]},{po,ans[T]}},*soft);
		for(i=0,j=1;j<10;j++)if(soft->getvalue().at({j})>soft->getvalue().at({i}))i=j;
		std::cout<<"test "<<T<<": out="<<i<<" ans="<<(int)b[T]<<((i==b[T])?" ok\n":" ng\n");
		if(i==b[T])okgs++;
	}
	std::cout<<"correct:"<<okgs<<"/"<<n<<'\n';
	std::cerr<<"correct:"<<okgs<<"/"<<n<<'\n';
	return 0;
}
	
	
