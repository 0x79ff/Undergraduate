#include <bits/stdc++.h>
using namespace std;
//ŷ��һ�ʻ����� ����ͼ �ڽӾ���洢 dfs ���Ϊ����1

int n;
const int maxn = 100+10;
int g[maxn][maxn];
int degree[maxn];
int odd_degree_num,arc_num;

//ͼ�Ľ���
void Build()
{     
    //�����Լ�������
    for (;;){
        printf("������ͼ�Ķ�����Ŀn (1<=n<=100)\n");
        int ret = scanf("%d", &n);
        if (ret == 1 && (n >= 1 && n <= 100)) break;
        else if (ret == 1 && (n < 1 || n > 100)) continue;
        else
            while (getchar() != '\n') ;
    }
    printf("������%d x %d���ڽӾ�������ʾ��ͼ\n",n,n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&g[i][j]);
            if(g[i][j] == 1){
                degree[i]++;
                if(i<j) arc_num++;//����һ�����ظ�����
            }
        }
    }
}

//�ж��ܷ�һ�ʻ� ���򷵻�1 ����0
int judge()
{
    for(int i=1;i<=n;i++)
        if(degree[i]%2==1) 
            odd_degree_num++;
    if((degree[1]%2==1 && odd_degree_num == 2) || odd_degree_num == 0) return 1;
    return 0;
}

int ans[maxn];//������洢��ǰ�Ľ��
int len_ans;

//dfs ���õݹ�ķ�ʽʵ��
void dfs(int pos)
{
    //��ֹ���� ���б߱���һ��
    //��ʱ����Ķ������ĿӦ��Ϊͼ�бߵ�����+1
    if(len_ans == arc_num + 1){
        for(int i=0;i<len_ans;i++) printf("%d ",ans[i]);
        printf("\n");
    }
 
    //ѭ������������ ѭ��˳������������ж���˳�����
    for(int i=1;i<=n;i++){
        if(g[pos][i] == 1){
            g[pos][i] = g[i][pos] = 0;//�ݹ� 
            ans[len_ans++] = i;//����״̬
            dfs(i);
            g[pos][i] = g[i][pos] = 1;//����
            len_ans--;//����״̬
        }
    }
}

int main()
{
    Build();
    if(judge() == 0){
        printf("��ͼ�Ӷ���1��ʼ����һ�ʻ�!\n");
        return 0;
    }
    else{
        printf("��ͼ�Ӷ���1��ʼ�ܹ�ʵ��һ�ʻ�!\n");
        printf("����һ�ʻ���������(���ն������˳������):\n");
        ans[len_ans++] = 1;
        dfs(1);//���������������
    }
    return 0;
}