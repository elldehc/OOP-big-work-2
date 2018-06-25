#include<cstdio>
#include<cstring>
#include "stdops.h"
#include<ctime>
#include<cstdlib>
const int cs0=28*28+1,cs1=10,cs2=10;
FILE *flab,*fimg,*fpar;
unsigned n;
unsigned char a[100001][28][28],b[100001];
float input[100001][28*28],w1[cs1][cs0],w2[10][cs1+1],ans[100001][10],eps;
Placeholder *pin[cs0],*pout[10];
Parameter *pw1[cs1][cs0],*pw2[10][cs1+1],*peps;
Node *out1[cs1+1],*out2[10],*loss;
Assign *ch1[cs1][cs0],*ch2[10][cs1+1];
Node *fin;
std::map<Node*,Tensor> initlist;
std::vector<Node*> v;
int tttt;
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
		std::cerr<<"train.tmp not found!\n";
		exit(0);
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
	for(i=0;i<cs0;i++)pin[i]=placeholder();
	for(i=0;i<10;i++)pout[i]=placeholder();
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
	srand(time(0));
	getdata();
	for(i=0;i<cs1;i++)
	{
		v.clear();
		for(j=0;j<cs0;j++)v.push_back(mul(pw1[i][j],pin[j]));
		out1[i]=exp(addn(v));
	}
	v.clear();
	for(i=0;i<cs1;i++)v.push_back(out1[i]);
	auto sum=addn(v);
	for(i=0;i<cs1;i++)out1[i]=div(out1[i],sum);
	v.clear();
	for(i=0;i<cs1;i++)v.push_back(out1[i]);
	auto fin=addn(v);
	int s=0,ttt1=0,ttt2=0;
	for(int T=0;T<n;T++)
	{
		for(j=0;j<cs0-1;j++)
		{
			initlist[pin[j]]=input[T][j];
		}
		initlist[pin[cs0-1]]=1;
		int tttt=clock();
		cout<<Run(initlist,*fin)<<'\n';
		ttt1+=clock()-tttt;
		//for(i=0;i<10;i++)std::cout<<out1[i]->getvalue()<<' ';cout<<'\n';
		tttt=clock();
		float t=rand()/(float)RAND_MAX;
		for(i=0;i<10&&t>=out1[i]->getvalue();i++)t-=out1[i]->getvalue();
		ttt2+=clock()-tttt;
		std::cout<<"test "<<T<<":out="<<i<<" ans="<<(int)b[T]<<(i==b[T]?" ok\n":" ng\n");
		if(i==b[T])s++;
		std::cout<<"ttt1="<<ttt1<<" ttt2="<<ttt2<<'\n';
	}
	std::cout<<s<<" corrects in "<<n<<" tests.\n";
	return 0;
}
		
		
