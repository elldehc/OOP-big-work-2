#include<cstdio>
#include<cstring>
#include "stdops.h"
#include<ctime>
FILE *flab,*fimg,*fpar;
unsigned char a[100001][28][28],b[100001];
unsigned n;
Tensor input[100001],w1({},{28*28+1,28*28+1}),w2({},{28*28+2,10}),ans[100001];
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
		for(i=0;i<28*28+1;i++)
		for(j=0;j<28*28+1;j++)fscanf(fpar,"%f",&w1.at({i,j}));
		for(i=0;i<28*28+2;i++)
		for(j=0;j<10;j++)fscanf(fpar,"%f",&w2.at({i,j}));
		fclose(fpar);
	}
	else
	{
		srand(time(0));
		for(i=0;i<28*28+1;i++)
		for(j=0;j<28*28+1;j++)w1.at({i,j})=rand()/(float)RAND_MAX;
		for(i=0;i<28*28+2;i++)
		for(j=0;j<10;j++)w2.at({i,j})=rand()/(float)RAND_MAX;
	}
	for(i=0;i<n;i++)
	{
		input[i]._reshape({1,28*28});
		for(j=0;j<28;j++)
		for(k=0;k<28;k++)input[i].at({1,j*28+k})=a[i][j][k];
	}
	for(i=0;i<n;i++)
	{
		ans[i]._reshape({n,10});
		for(j=0;j<10;j++)if(b[i]==j)ans[i].at({1,j})=1;else ans[i].at({1,j})=0;
	}
	fclose(flab);fclose(fimg);
}
int main()
{
	int i,j,k;
	getdata();
	auto pi=placeholder(),po=placeholder();
	auto p1=parameter(w1),p2=parameter(w2),pe=parameter(100);
	auto out1=sigmoid(matmul(p1,concat(pi,constant({{1},{1,1}}),1)));
	auto out=matmul(p2,concat(out1,constant({{1},{1,1}}),1));
	auto loss=print(matmul(sub(out,po),transpose(sub(out,po))));
	auto ch1=assign(p1,sub(p1,mul(pe,loss->grad(p1))));
	auto ch2=assign(p2,sub(p2,mul(pe,loss->grad(p2))));
	auto fin=bind(ch1,ch2);
	i=0;
	int tmp_size=n;
	while(pe->getfloat()>1e-5)
	{
		std::cout<<Run({{pi,input[i]},{po,ans[i]}},*fin);
		w1=p1->getvalue();w2=p2->getvalue();
		fpar=fopen("train.tmp","w");
		for(i=0;i<28*28+1;i++)
		{for(j=0;j<28*28+1;j++)fprintf(fpar,"%f ",w1.at({i,j}));fputs("",fpar);}
		for(i=0;i<28*28+2;i++)
		{for(j=0;j<10;j++)fprintf(fpar,"%f ",w2.at({i,j}));fputs("",fpar);}
		fclose(fpar);
		std::cout<<"eps="<<pe->getvalue()<<'\n';
		pe->multiply(0.9);i++;if(i>=tmp_size)i-=tmp_size;
	}
	return 0;
}
	
	
