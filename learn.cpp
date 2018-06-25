#include<cstdio>
#include<cstring>
#include "stdops.h"
#include<ctime>
const int cs0=28*28+1,cs1=10,cs2=10,ns=2;
FILE *flab,*fimg,*fpar;

unsigned n;
float input[100001][28*28],w1[cs1][cs0],w2[10][cs1+1],ans[100001][10],eps;
Placeholder *pin[ns][cs0],*pout[ns][10];
Parameter *pw1[cs1][cs0],*pw2[10][cs1+1],*peps;
Node *out1[ns][cs1+1],*out2[ns][10],*loss;
Assign *ch1[cs1][cs0],*ch2[10][cs1+1];
Node *fin;
std::map<Node*,Tensor> initlist;
std::vector<Node*> v;
int tttt;
unsigned flip(unsigned t){return (t>>24)|((t>>8)&0xff00)|((t<<8)&0xff0000)|(t<<24);}
void getdata()
{
	int i,j,k;
	unsigned char a[100001][28][28],b[100001];
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
		for(i=0;i<cs1;i++)
		for(j=0;j<cs0;j++)fscanf(fpar,"%f",&w1[i][j]);
		for(i=0;i<10;i++)
		for(j=0;j<cs1+1;j++)fscanf(fpar,"%f",&w2[i][j]);
		fscanf(fpar,"%f",&eps);
		fclose(fpar);
	}
	else
	{
		srand(time(0));
		for(i=0;i<cs1;i++)
		for(j=0;j<cs0;j++)w1[i][j]=(rand()/(float)RAND_MAX-0.5);
		for(i=0;i<10;i++)
		for(j=0;j<cs1+1;j++)w2[i][j]=(rand()/(float)RAND_MAX-0.5);
		eps=1;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<28;j++)
		for(k=0;k<28;k++)input[i][j*28+k]=a[i][j][k]/256.0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<10;j++)if(b[i]==j)ans[i][j]=1;else ans[i][j]=0;
	}
	std::cerr<<"ok\n";
	for(j=0;j<ns;j++)
	for(i=0;i<cs0;i++)pin[j][i]=placeholder();
	for(j=0;j<ns;j++)
	for(i=0;i<10;i++)pout[j][i]=placeholder();
	for(i=0;i<cs1;i++)
	for(j=0;j<cs0;j++)pw1[i][j]=parameter(w1[i][j]);
	for(i=0;i<10;i++)
	for(j=0;j<cs1+1;j++)pw2[i][j]=parameter(w2[i][j]);
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
	for(k=0;k<ns;k++)
	{
		for(i=0;i<cs1;i++)
		{
			v.clear();
			for(j=0;j<cs0;j++)v.push_back(mul(pw1[i][j],pin[k][j]));
			out1[k][i]=exp(print(addn(v),"out1:"));
		}
		v.clear();
		for(i=0;i<cs1;i++)v.push_back(out1[k][i]);
		auto sum=addn(v);
		for(i=0;i<cs1;i++)out1[k][i]=div(out1[k][i],sum);
	}
	/*out1[cs1]=One;
	
	for(i=0;i<10;i++)
	{
		v.clear();
		for(j=0;j<cs1+1;j++)v.push_back(mul(pw2[i][j],out1[j]));
		out2[i]=sigmoid(print(addn(v),"out2:"));
	}
	v.clear();
	for(i=0;i<10;i++)v.push_back(sqr(sub(out2[i],pout[i])));*/
	v.clear();
	for(k=0;k<ns;k++)
	for(i=0;i<10;i++)v.push_back(/*print(*/mul(log(out1[k][i]),pout[k][i])/*,"log:")*/);
	loss=sub(Zero,addn(v));
	loss=print(loss,"loss:");
	std::cerr<<"ok\n";
	for(i=0;i<cs1;i++)
	for(j=0;j<cs0;j++)ch1[i][j]=assign(pw1[i][j],print(sub(pw1[i][j],mul(peps,/*print(*/loss->grad(pw1[i][j])/*,"grad of loss:")*/)),"ch1["+std::to_string(i)+"]["+std::to_string(j)+"]:"));
	std::cerr<<"ok\n";
	
	//for(i=0;i<10;i++)
	//for(j=0;j<cs1+1;j++)ch2[i][j]=assign(pw2[i][j],print(sub(pw2[i][j],mul(peps,loss->grad(pw2[i][j]))),"ch2:"));
	//fin=Zero;
	v.clear();
	v.push_back(loss);
	for(i=0;i<cs1;i++)
	for(j=0;j<cs0;j++)v.push_back(ch1[i][j]);
	/*for(i=0;i<10;i++)
	for(j=0;j<cs1+1;j++)v.push_back(ch2[i][j]);*/
	fin=bindn(v);
	int T=1;
	std::cerr<<"ok\n";
	while(peps->getfloat()>1e-9)
	{
		for(k=0;k<ns;k++)
		{
			for(j=0;j<cs0-1;j++)
			{
				initlist[pin[k][j]]=input[k+T][j];
				//std::cerr<<"T="<<T<<" j="<<j<<" input[T][j]="<<input[T][j]<<" initlist[pin[j]]="<<initlist[pin[j]]<<'\n';
			
			}
		
			initlist[pin[k][cs0-1]]=1;
			for(j=0;j<10;j++)initlist[pout[k][j]]=ans[k+T][j];
			std::cerr<<"k="<<k<<"ok\n";
			/*for(j=0;j<cs0-1;j++)
			{
				std::cerr<<"T="<<T<<" j="<<j<<" input[T][j]="<<input[T][j]<<" initlist[pin[j]]="<<initlist[pin[j]]<<'\n';
			
			}*/
		}
		tttt=clock();
		std::cout<<Run(initlist,*fin)<<'\n';
		std::cerr<<"time="<<clock()-tttt<<'\n';
		fpar=fopen("train.tmp","w");
		for(i=0;i<cs1;i++)
		{for(j=0;j<cs0;j++)fprintf(fpar,"%f ",pw1[i][j]->getvalue());fputc('\n',fpar);}
		for(i=0;i<10;i++)
		{for(j=0;j<cs1+1;j++)fprintf(fpar,"%f ",pw2[i][j]->getvalue());fputc('\n',fpar);}
		fprintf(fpar,"%f\n",peps->getvalue());
		fclose(fpar);
		std::cerr<<"eps="<<peps->getvalue()<<'\n';
		T=rand()%(n-ns+1);
	}
	return 0;
}
	
	
	
	
