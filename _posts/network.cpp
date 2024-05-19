// 2151216 �޳��� �˳�ѧ-������� 
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<fstream>
using namespace std;

#define N 24
#define M 76
struct edge{
	int id,o,d;
	float len,cap;
}e[M+1];

//���·�е���ض��� 
int bian[N+1][N+1];//ָ��i-j�ߵ�id�� 
float avg_dis[N+1];//�����������ƽ�����·���� 
float dis[N+1][N+1]; //��������·���� 
int pre[N+1][N+1];//��¼i-j���·��j��ǰ����� 
int cnt[N+1][M+1]; //ÿ����Դ�����·����ÿ����ʹ�ô���  

// MST�е���ض��� 
float path[N+1][N+1]; //MST����������·���� 
int fa[N+1];//MST��¼���ڵ� 
float tot; //MST������ֵ 

// ���5��������ض��� 
bool flag[M+1];// �ж�ÿ�����Ƿ����MST�� 
int index[16];// 15����û��ѡ�У�������ǵ�index 
int best5[6];//����õ�5���ߵ�id 
int add_i[6];//��Ҫ�ӵ�5���ߵ�id��
float original,current,best;// originalΪMST�����·������ֵ
       // currentΪ����߸��º�ǰ��ֵ bestΪ��ǰ����ֵ 
int num; //����������ѡ5���ߵ�ʱ�����ϴ����� 
float newpath[N+1][N+1]; //������ѡ5���ߵ�ʱ������·���� 

inline int find_pre(int source,int x){ //��sourceΪԴͷ�����·��Դ��� 
	int PRE=pre[source][x];
	if(PRE==0) return source;
	else{
		int BIAN=bian[PRE][x];
		cnt[source][BIAN]=1;  //���1�����ظ�,Ϊ+=1   ���2���ظ�,Ϊ=1�� 
		find_pre(source,pre[source][x]);
	}
} 

inline void Floyd(){ 
	for(int k=1;k<=N;k++)
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++){
		if((i!=j)&&(i!=k)&&(j!=k))
		if(dis[i][j]>dis[i][k]+dis[k][j])
		{
			dis[i][j]=dis[i][k]+dis[k][j];
			pre[i][j]=pre[k][j];//��i��j�����·������Ϊi��k��j��
			                   //��ôi��j���·��j��ǰ������k��j���·��j��ǰ����ͬ
		}
	} 
	for(int i=1;i<=N;i++){//��ƽ�����·���� 
        float tmp=0;  	
		for(int j=1;j<=N;j++){
			tmp+=dis[i][j];
		}
		avg_dis[i]=tmp/(N-1); //�״�㣺����N-1����N�������R������mean�Ļ�Ҫ*N/(N-1) 
	}	
	for(int i=1;i<=N;i++){ //ͳ��ÿ����Դ�����·����ÿ����ʹ�ô��� 
		 for(int j=1;j<=N;j++)
		 if(i!=j)
		 find_pre(i,j); 
	}
}

int father(int x){ //Ѱ����߲�εĸ��ڵ� 
	if (fa[x]!=x) fa[x]=father(fa[x]);
	return fa[x];
} 
void union_father(int x,int y){ //���ڵ�ϲ� 
	int Fa=father(x);
	int Fb=father(y);
	if(Fa!=Fb) fa[Fa]=Fb;
}
int cmp(const edge&a,const edge&b){ // ����sort����������Զ��巽�� 
	if(a.len<b.len) return 1;
	else return 0;
}

inline void kruskal(){
	for(int i=1;i<=N;i++) fa[i]=i;
	sort(e+1,e+1+M,cmp); 
	int k=0;
	cout<<"��MSTѡ�еı�id���Լ������Ľ��"<<endl;
	for(int i=1;i<=M;i++){
		if(father(e[i].o)!=father(e[i].d)){
			union_father(e[i].o,e[i].d);
			path[e[i].o][e[i].d]=e[i].len;
			path[e[i].d][e[i].o]=e[i].len;//��ʼ��MST���·���� 
			cout<<"��"<<e[i].id<<": ��"<<e[i].o<<" �͵�"<<e[i].d<<" ����һ���ˣ�ȨֵΪ"<<e[i].len<<endl; 
		 	flag[e[i].id]=1;
		 	int BIAN=0;
			 BIAN=bian[e[i].d][e[i].o];
			 flag[BIAN]=1;//˫��߶�Ҫ��ǣ� 
				tot+=e[i].len;
				k++;
		}
		if(k==N-1) break;  
	}
	cout<<endl;
	cout<<"MST:  ";
	cout<<tot<<endl;
	cout<<endl;
	
	cout<<"��kruskal��ľ���" <<endl;
	for(int i=1;i<=N;i++){
		cout<<i<<": ";
		for(int j=1;j<=N;j++){
			if(path[i][j]<9999)
			cout<<path[i][j]<<"  ";	 
			else cout<<'M'<<"  "; 
		}cout<<endl;
		}
	
	for(int k=1;k<=N;k++)
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++){
		if((i!=j)&&(i!=k)&&(j!=k))
		if(path[i][j]>path[i][k]+path[k][j])
		{
			path[i][j]=path[i][k]+path[k][j];
		}
	} 
	cout<<"MST�����·����"<<endl;
	cout<<"   ";
	for(int i=1;i<=N;i++)
	cout<<i<<"  "; 
	cout<<endl;
	for(int i=1;i<=N;i++){
		cout<<i<<": ";
		for(int j=1;j<=N;j++){
			cout<<path[i][j]<<"  ";	 
			original+=path[i][j]; //˳������ԭMST���·������ֵ�� 
		}cout<<endl;
		}
		best=original; // Ϊbest����ʼֵ
		printf("original: %.2f ", original); 
	cout<<endl;
	ofstream outputFile("MST_path.csv"); 
	    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            outputFile<<path[i][j]; // д�����Ԫ��
            if (j != N) {
                outputFile << ","; // �ö��ŷָ�ÿ��Ԫ��
            }
        }
        outputFile << endl; // д�뻻�з�
    }
    outputFile.close(); // �ر��ļ�
    cout << "�����ѳɹ����浽 MST_path.csv �ļ���" <<endl;
}

inline void add_edge(){ //����� 
	for(int i=1;i<=N;i++){   //Ϊ�˲�Ӱ��ԭ����path�����ȸ���һ�� 
		for(int j=1;j<=N;j++)
		newpath[i][j]=path[i][j];
	} 
	for(int i=1;i<=5;i++)
	{
		int tmp=0,tmp_o=0,tmp_d=0,tmp_len;
		tmp=add_i[i];
		tmp_o=e[tmp].o;
		tmp_d=e[tmp].d;
		tmp_len=e[tmp].len;
		if(newpath[tmp_o][tmp_d]>tmp_len){
			newpath[tmp_o][tmp_d]=tmp_len;  //�ö���߸����� 
			newpath[tmp_d][tmp_o]=tmp_len;  //�״�ǧ��ע�⣬��Ϊ�������!!! 
		}
	}
     //��Floyd����º�����·����  
	for(int k=1;k<=N;k++)
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++){
		if((i!=j)&&(i!=k)&&(j!=k))
		if(newpath[i][j]>newpath[i][k]+newpath[k][j])
		{
			newpath[i][j]=newpath[i][k]+newpath[k][j];
		}
	}  
	current=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			current+=newpath[i][j]; 
	if(best>current){
		for(int i=1;i<=5;i++)
		best5[i]=add_i[i];
		best=current;
		cout<<"���������� "<<num<<"  ����ֵ��";
		printf("%.2f ", best);
		cout<<endl;
	}
}

inline void choose() {
	int tmp_cnt=0;
	best=original;
		printf("��ʼ %.2f",best); 
		cout<<endl; 
	for(int i=1;i<=M;i++){
		if(!flag[e[i].id])
		index[++tmp_cnt]=e[i].id;
	}
	int ai=0,bi=0,ci=0,di=0,ei=0;
	for(int a=1;a<=30;a++){  //����c��5,30������ϣ������� 
		add_i[1]=index[a];
		for(int b=a+1;b<=30;b++){
			add_i[2]=index[b];
			for(int c=b+1;c<=30;c++ ){
				add_i[3]=index[c];
				for(int d=c+1;d<=30;d++){
					add_i[4]=index[d];
					for(int k=d+1;k<=30;k++){
					    add_i[5]=index[k];
					    num++; 
						add_edge();
					   
					}
				}
			}
		}
	}
	cout<<endl; 
	cout<<"��õ�5����ѡ��Ϊ��";
	for(int i=1;i<=5;i++){
		cout<<best5[i]<<' ';
		add_i[i]=best5[i];
	}
	cout<<endl; 
		printf("���� %.2f" ,best);
	cout<<endl;
	cout<<"ѡ��֮������·����" <<endl;
	add_edge();
	ofstream outputFile("add_path.csv"); 
	    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            outputFile<<newpath[i][j]; // д�����Ԫ��
            if (j != N) {
                outputFile << ","; // �ö��ŷָ�ÿ��Ԫ��
            }
        }
        outputFile << endl; // д�뻻�з�
    }
    outputFile.close(); // �ر��ļ�
    cout << "�����ѳɹ����浽 add_path.csv �ļ���" <<endl;
	
}

inline void getdata(){
	//��ʼ��dis,path����
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(i!=j) 
		{
		 path[i][j]=99999;
		 dis[i][j]=99999; 
		}	
		}
	}
    cout<<"�����"<<endl;
	for(int i=1;i<=76;i++){
		int id,o,d;
		float len,cap;
		cin>>id>>o>>d;
  		scanf("%f%f",&len,&cap);
		dis[o][d]=len;  
		bian[o][d]=i; //ָ��o-d�ߵ�id 
		pre[o][d]=o;  // d��ǰ�����Ϊo 
		e[i].id=id;e[i].o=o;e[i].d=d;
		e[i].len=len;e[i].cap=cap; 
	} 
		cout<<"�������"<<endl;
}

inline void output1(){
	cout<<"���·����"<<endl;
	cout<<"   ";
	for(int i=1;i<=N;i++)
	cout<<i<<"  "; 
	cout<<endl;
	for(int i=1;i<=N;i++){
		cout<<i<<": ";
		for(int j=1;j<=N;j++){
			if(dis[i][j]<9999)
			cout<<dis[i][j]<<"  ";
			else cout<<'M'<<"  "; 
		}
	cout<<endl;
	}	
	cout<<"���·ƽ��ֵ  �ӽ���������"<<endl;
	for(int i=1;i<=N;i++)
	{
		printf("%d : %.2f  %.2f",i,avg_dis[i],1/avg_dis[i]);
		cout<<" ";
		if(N%8==0) cout<<endl;
	}
	cout<<endl;
	cout<<"ԭʼ�������·�е�ʹ�ô��������ظ���max=24��"<<endl;
	for(int j=1;j<=M;j++)	
	{
		int tmp=0;
		for(int i=1;i<=N;i++)
		tmp+=cnt[i][j];
		cout<<"��"<<j<<": "<<tmp<<"  ";
		if(j%10==0) cout<<endl;  
	}
	cout<<endl;
	//����ֱ��������ļ��� 
	ofstream outputFile("cnt.csv"); 
	outputFile<<"id��count" <<endl;
	for(int j=1;j<=M;j++)	
	{
		int tmp=0;
		for(int i=1;i<=N;i++)
		tmp+=cnt[i][j];
		outputFile<<j<<","<<tmp<<endl; 
	}
    outputFile.close(); // �ر��ļ�
    cout << "�����ѳɹ����浽 cnt.csv �ļ���" <<endl;
}

int main(){
	getdata();//���� 
	Floyd();//��Դ�����Ǵӵ�������Ҫ�ѱ���ϵ������
	//bellman-ford(); ��Ȼ�ǵ�Դ������ֱ�Ӵ���� ,�Ϸ��� 
	//dijkstra()
	//spfa
	output1();//������·����dis�����·����ƽ��ֵ;
	         //������·��ʹ�ô������������ 
	kruskal();//�����С��������mst�����·����path
	choose();//ѡ5���� 
	return 0; 
}


