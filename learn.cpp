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
	std::cerr<<"ok\n";
	fpar=fopen("train.tmp","r");
	if(fpar!=nullptr)
	{
		for(i=0;i<sz1;i++)
		for(j=0;j<28*28+1;j++)fscanf(fpar,"%f",&w1.at({i,j}));
		for(i=0;i<10;i++)
		for(j=0;j<sz1;j++)fscanf(fpar,"%f",&w2.at({i,j}));
		fclose(fpar);
	}
	else
	{
		srand(time(0));
		for(i=0;i<sz1;i++)
		for(j=0;j<28*28+1;j++)w1.at({i,j})=rand()/(float)RAND_MAX/10;
		for(i=0;i<10;i++)
		for(j=0;j<sz1;j++)w2.at({i,j})=rand()/(float)RAND_MAX;
	}
	fpar=fopen("train_eps.tmp","r");
	if(fpar!=nullptr)
	{
		fscanf(fpar,"%f%f",&eps1,&eps2);
		fclose(fpar);
	}
	else
	{
		eps1=1e-2;eps2=1e-2;
	}
	
	std::cerr<<"ok\n";
	n=1000;
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
	auto out=print(matmul(p2,out1),"out=");
	auto soft=print(softmax(out),"soft=");
	auto loss=print(sub(Zero,matmul(transpose(po),log(soft))),"loss=");
	auto dw2=print(matmul(sub(soft,po),transpose(out1)),"dw2");
	auto dw1=/*print(*/matmul(mul(matmul(transpose(p2),sub(soft,po)),mul(out1,sub(One,out1))),transpose(pi))/*,"dw1")*/;
	//auto ch1=assign(p1,sub(p1,mul(pe1,dw1)));
	//auto ch2=assign(p2,sub(p2,mul(pe2,dw2)));
	auto fin=bind(loss,bind(dw1,dw2));
	int T=0;
	int tmp_size=10;
	Tensor sdw1({},{sz1,28*28+1}),sdw2({},{10,sz1});
	std::cerr<<"ok\n";
	std::cout<<"p2="<<p2<<'\n';
	while(1)
	{
		std::cout<<"T="<<T<<'\n';
		std::cout<<Run({{pi,input[T]},{po,ans[T]}},*fin);
		std::cout<<"po="<<po<<'\n';
		sdw1=sdw1+dw1->getvalue();sdw2=sdw2+dw2->getvalue();
		std::cout<<"eps1="<<pe1->getvalue()<<'\n';
		std::cout<<"eps2="<<pe2->getvalue()<<'\n';
		T++;if(T%tmp_size==0)
		{
			T=0;
			//if(T>=n)T=0;
			p1->minus(sdw1*eps1/tmp_size);p2->minus(sdw2*eps2/tmp_size);
			sdw1=0;sdw2=0;
			w1=p1->getvalue();w2=p2->getvalue();
			fpar=fopen("train.tmp","w");
			for(i=0;i<sz1;i++)
			{for(j=0;j<28*28+1;j++)fprintf(fpar,"%f ",w1.at({i,j}));fputc('\n',fpar);}
			for(i=0;i<10;i++)
			{for(j=0;j<sz1;j++)fprintf(fpar,"%f ",w2.at({i,j}));fputc('\n',fpar);}
			freopen("train_eps.tmp","w",fpar);
			fprintf(fpar,"%f %f\n",eps1,eps2);
			fclose(fpar);
			usleep(500000);
		}
		
		//getchar();
		
		//T++;
		//if(T>=tmp_size){T-=tmp_size;}
		//eps*=0.8;pe->set(eps);
		
	}
	return 0;
}
	
	
