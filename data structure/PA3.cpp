#include <bits/stdc++.h>
using namespace std;

#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

/*线性表相关操作开始*/
typedef int Status;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
 
typedef char ElemType;
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
 
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(LOVERFLOW);
    L.length=0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length+1)   
        return ERROR;
    
    if (L.length >= L.listsize) {
    ElemType *newbase;
    newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
    if (!newbase)
        return LOVERFLOW;
 
    L.elem = newbase;
    L.listsize += LISTINCREMENT;
    }
 
    q = &(L.elem[i-1]);  
 
    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p=&(L.elem[L.length-1]); p>=q; --p) *(p+1)=*(p);
 
    *q = e;
    L.length++;
    return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length+1)   
        return ERROR;
 
    p = &(L.elem[i-1]);         //指向第i个元素
    e=*p;
    q = L.elem + L.length -1;
 
    for(++p;p <= q;++p) *(p-1)=*(p);
    --L.length;
    return OK;
}

Status Destroy_Sq(SqList &L)
{
    free(L.elem);
    return OK;
}

/*线性表相关操作结束*/

//用数组来构造huffman tree
int weight[256];//存储每个字母的权值
char code[256][256];//存储每个字符的huffman编码
int bytenum,lastbit;

struct Node{
    int leftChild;
    int rightChild;
} tree[256];

//解压huffman tree
struct NodeV{
    int leftChild;
    int rightChild;
    char c;
} tree2[256];


//读文件并统计字符出现的频率
int count_weight(char *orifile)
{
    FILE *ori_file;
    ori_file = fopen(orifile,"rb");
    if(ori_file == NULL)return FALSE;
    char ch;
    while ((ch = fgetc(ori_file)) != EOF) {
        weight[(int)(ch)]++;
    }
    fclose(ori_file);
    return TRUE;
}

const int INF = 0x7fffffff;
//选出两个range中权值最小的节点
void select_node(int range,int &s1,int &s2)
{
    int ret1 = 0,ret2 = 0;
    weight[0]=INF;
    for(int i=1;i<range;i++){
        if(weight[i] != 0){
            if(weight[i] < weight[ret1]){
                ret2 = ret1;
                ret1 = i;
            }
            else if(weight[i] < weight[ret2]){
                ret2 = i;
            }
            else
                ;
        }
    }
    weight[0]=0;
    
    s1 = ret1;
    s2 = ret2;
}

char a[256];
void Huffmancode(int pos)
{
    //终止条件
    if(tree[pos].leftChild == 0 && tree[pos].rightChild == 0){
        strcpy(code[pos],a);
        return ;
    }
    //递归条件的转移和回溯
    strcat(a,"0");
    Huffmancode(tree[pos].leftChild);
    a[strlen(a)-1]='\0';
    strcat(a,"1");
    Huffmancode(tree[pos].rightChild);
    a[strlen(a)-1]='\0';
}

void build_Huffmamtree(int &root)
{
    //建立huffman tree
    int ch_num = 0;
    for(int i=1;i<=127;i++){
        if(weight[i]!=0) ch_num++;
    }
    for(int i=128;i<128+ch_num-1;i++){
        int s1,s2;
        select_node(i,s1,s2);//选择parent为0(即权值不为0)且权值最小的两个节点
        tree[i].leftChild = s1;
        tree[i].rightChild = s2; 
        weight[i] = weight[s1] + weight[s2];
        weight[s1] = weight[s2] = 0;
    }
    if(ch_num == 1){
        for(int i=1;i<=127;i++){
            if(weight[i]!=0){
                root=i;
                break;
            }
        }
        tree[128].leftChild = root;
        tree[128].rightChild = root;
        strcpy(code[root],"1");
        root = 128;
    }
    //求每个结点的huffman编码，从根节点开始遍历
    //寻找根节点
    else root = 128+ch_num -2;
    Huffmancode(root);
}

void output_Huffmancode()
{
    printf("下面是字符压缩后的编码:\n");
    for(int i=1;i<=127;i++){
        if(strcmp(code[i],"\0")!=0){
            printf("字符:%c ASCII值:%d 压缩后的编码:%s\n",(char)(i),i,code[i]);
        }
    }
}

/*创建压缩后的文件*/
int write_compressedfile(char *orifile)
{
    char compressedfile[256];
    sprintf(compressedfile,"%s.huffman",orifile);

    FILE *compress_file,*ori_file;
    compress_file = fopen(compressedfile,"wb");
    if(compress_file == NULL) return FALSE;
    ori_file = fopen(orifile,"rb");
    
    //维护每8个输出一次,记录结束的值和最后一个字节中有效比特位的个数
    SqList s;
    InitList_Sq(s);
    int ch;
    while ((ch = fgetc(ori_file) )!= EOF) {
        for(int i=0;i<strlen(code[ch]);i++) ListInsert_Sq(s,s.length+1,code[ch][i]);
    }
    bytenum = (s.length%8 == 0 ? s.length/8:s.length/8+1);
    lastbit = s.length - s.length / 8 *8;
    if(lastbit!=0){
        for(int i=1;i<=8 - lastbit;i++) ListInsert_Sq(s,s.length+1,'0');
    }
    int loop = 8,num = 0;
    for(int i=0;i<s.length;i++){
        num += pow(2,loop-1)*(s.elem[i]-'0');    
        loop--;
        if(loop == 0){
            fprintf(compress_file,"%c",(char)(num));
            num=0;
            loop = 8;
        }
    }
    
    Destroy_Sq(s);
    fclose(compress_file);
    fclose(ori_file);
    return TRUE;
}



/*解压压缩后的文件*/
int write_decompressedfile(char *orifile,int root)
{
    char compressedfile[256];
    sprintf(compressedfile,"%s.huffman",orifile);
    char decompressedfile[256];
    sprintf(decompressedfile,"%s.unpress",orifile);

    FILE *decompress_file,*compress_file;
    decompress_file = fopen(decompressedfile,"wb");
    if(decompress_file == NULL) return FALSE;
    compress_file = fopen(compressedfile,"rb");
  
    SqList s;
    InitList_Sq(s);

    int ch;
    while ((ch = fgetc(compress_file)) != EOF) {
        for(int i=7;i>=0;i--){
            if((ch & (1<<i))!=0) ListInsert_Sq(s,s.length+1,'1');
            else ListInsert_Sq(s,s.length+1,'0');   
        }
    }
    if(lastbit!=0){
        for(int i=1;i<=8 - lastbit;i++){
            char ch2;ListDelete_Sq(s,s.length,ch2);
        }
    }

    int pos = root;
    for (int i=0;i<s.length;i++) {
        if(s.elem[i] == '0'){
            if(tree[pos].leftChild == 0 && tree[pos].rightChild == 0);
            else pos = tree[pos].leftChild;
        }
        if(s.elem[i] == '1'){
            if(tree[pos].leftChild == 0 && tree[pos].rightChild == 0);
            else pos = tree[pos].rightChild;    
        }
        if(tree[pos].leftChild == 0 && tree[pos].rightChild == 0){
            char ch = (char)(pos);
            fprintf(decompress_file,"%c",ch);
            pos = root;
        }
    }
    Destroy_Sq(s);
    fclose(compress_file);
    fclose(decompress_file);

    return TRUE;
}

int main()
{
    char filename[256];
    printf("请输入原始文件名:\n");
    scanf("%s",filename);

    //写压缩文件
    if(count_weight(filename)==FALSE){
        printf("原始文件打开失败.程序已退出.\n");
        return 0;
    }
    int root = 0;
    build_Huffmamtree(root);
    output_Huffmancode();
    
    //huffman 压缩
    if(write_compressedfile(filename)==FALSE){
        printf("压缩文件创建失败.程序已退出.\n");
        return 0;
    }

    //解压压缩文件
    if(write_decompressedfile(filename,root)==FALSE){
        printf("解压文件创建失败.程序已退出.\n");
        return 0;
    }

    printf("压缩文件和解压文件创建完毕,请查看文件.\n");
    return 0;
}