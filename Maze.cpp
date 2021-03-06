#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
using namespace std;
#define MaxSize 99
int M,N;//定义全局变量，减少形参
//用二维数组定义8个方向,从北，逆时针开始
int step[8][2]=
{
    {-1,0},
    {-1,1},
    {0,1},
    {1,1},
    {1,0},
    {1,-1},
    {0,-1},
    {-1,-1}
};

//第二个问题，先简单点，默认左上角为入口，右下角为出口，有8个方向可走，怎么表示呢？
typedef struct
{
    short int row;
    short int col;
    short int dir=0;//8个数值代表了8个方向,一开始默认为0
} Point;
//定义栈
typedef struct
{
    Point Data[MaxSize];    // 存储元素的数组
    int Top; //栈顶指针

} SeqStack;

void InitStack(SeqStack *s) //创建一个栈
{
    s->Top=-1; //表示栈空
}

bool Push(SeqStack *s, Point x)//进栈操作
{
    if(s->Top==MaxSize-1)
        return false;
    else
    {
        s->Top++;
        s->Data[s->Top]=x;
        return true;
    }
}

bool Pop(SeqStack *s)  //出栈操作
{
    if(s->Top==-1)
        return false;
    else
    {
        s->Top--;
        return true;
    }
}

bool GetAllElem(SeqStack *s) //迭代栈
{
    if(s->Top==-1) return false;
    else
    {
        for(int i=s->Top; i>-1; i--)
        {
            printf("(%d,%d)->",s->Data[i].col,s->Data[i].row);
        }
        return true;

    }

}
//问题三，dfs算法

int path(Point p,SeqStack s,int **Maze,int **Maze_sy)  //难道是s和&的区别？？？？
{
    if (Maze[p.row][p.col]==1)   //
    {
        //Pop(&s); 不用删除，应该退回到上一个元素，继续访问没访问过的结点
       // printf("***(%d,%d)无效***\n",p.col,p.row);
        //printf("(A-,%d)->",s.Data[s.Top-1].dir);
        // if(p.col&&p.row==0) return 0; //不能在此退出调用函数
    } //无效起点
    else
    {
        if(p.col==N-2&&p.row==M-2)
        {
            Push(&s,p);
            printf("\n恭喜到达终点！路径如下:\n\n");
            GetAllElem(&s);
            return 1;
        }
        else
        {
            if
            (Maze_sy[p.row][p.col]==0)
            {
                Push(&s,p);//入栈（根节点）
                Maze_sy[p.row][p.col]=1;// 标志已给访问过
               // printf("压入点:(%d,%d)->",s.Data[s.Top].col,s.Data[s.Top].row);//输出节点坐标
            }
        }

    }

    //int len=sizeof(s.Data)/sizeof(int);//不该数组长度 应该用栈顶指针！
    short int dir=p.dir;
    Point next_p;
    // printf("****%d***",s.Data[s.Top].dir);  测试当前是否dir可达到7的语句
    if(s.Data[s.Top].dir==7)   //判断该栈顶元素是否搜索完成，
    {
        Pop(&s);    //完成则弹出
        //printf("弹无效点->");
        if( s.Top==-1 )//栈是否为空，空则没有路径
        {
            printf("\n\n很遗憾!没有路径走出迷宫！\n\n");
            return 0;
        }
        else
        {
            //printf("***hello2->"); 测试代码可否运行到此处
            //printf("回溯到: (%d,%d)->",s.Data[s.Top].col,s.Data[s.Top].row); //回到栈顶元素
            //Maze_sy[s.Data[s.Top].col][s.Data[s.Top].row]=0;//栈顶重新设置为未访问
            path(s.Data[s.Top],s,Maze,Maze_sy);  //返回栈顶

        }
    }
    else   //搜索没有完成，取未被搜索的根节点，并回到第2步
    {


        for(; dir<=7;)  //界限应该是0到6还是0到7？？
        {
            next_p.row=p.row+step[dir][1]; //问题，下一个点的位置计算
            next_p.col=p.col+step[dir][0];
            if ((Maze[next_p.row][next_p.col]!=1)&&(Maze_sy[next_p.row][next_p.col]!=1)) break;//此处注意一下，下一个点不是1，和一个点标志不为1，
            else dir++;
        }
        if(dir==8) dir--; //dir最终会加到8。。。只能这种老方法了
        //p.dir=dir;//为什么这种方法不行？
        s.Data[s.Top].dir=dir;// 记录走的方向
        // printf("(s.top.dir)->%d->",s.Data[s.Top].dir); 测试dir是否成功赋值给p点
        //printf("  预计下一个:(%d,%d)\n",next_p.col,next_p.row);
        path(next_p,s,Maze,Maze_sy);
    }
}

int main()
{

    SeqStack s;
    InitStack(&s);
    Point startpoint;  //定义开始起点
    startpoint.row=1,startpoint.col=1; //起点为（1,1)


    int m,n;  // m 是行，n是列
    cout<<"请输入行和列，通过空格分开"<<endl;
    cin>>m>>n;
    m=m+2;
    n=n+2;
    M=m;
    N=n;
    //endpoint.row=N-2,endpoint.col=M-2;//终点为(M,N)

    int **Maze =  new int*[m];   //分配一个指针数组，将其首地址保存在Maze中
    int **Maze_sy= new int*[m];
    for(int i = 0; i < m; i++)   //为指针数组的每个元素分配一个数组,相当于产生了一个二维数组 a[m][n]了
    {
        Maze[i] = new int [n];
        Maze_sy[i]=new int [n]; //定义辅助数组；
    }
    int choose=1;
    while(choose)
    {
        cout<<endl<<"*************************************************************"<<endl;
        cout<<"1.自动生成迷宫。    2.输出生成的迷宫。   3.手动输入迷宫"<<endl;
        cout<<endl<<"4.DFS算法查找路径。 5.更改入口     6.更改出口     "<<endl;
        cout<<"*******************************************************************"<<endl;
        cout<<"请输入你的选择";
        cin>>choose;
        switch(choose)
        {
        case 1:
            cout<<endl<<">>自动生成迷宫成功！"<<endl;
            for (int i=0; i<m; i++)   //给辅助数组赋值全为0
            {
                for( int j=0; j<n; j++)
                {
                    Maze_sy[i][j]=0;

                }
            }
            int i,j;
            srand((unsigned)time(NULL)); ///srand()就是给rand()提供种子seed
            for (i=0; i<m; i++)
            {

                for(j=0; j<n; j++)
                {

                    int num = (rand()+1)%2;            //对2取余得到就是0或者1
                    Maze[i][j] = num ;

                    if(i==0||j==0||i==m-1||j==n-1) Maze[i][j]=1;

                }
            }
            Maze[1][1]=0,Maze[m-2][n-2]=0;
            cout<<">>生成的迷宫如下："<<endl;
            for (i=0; i<m; i++)
            {
                printf("\n");
                for(j=0; j<n; j++)
                {
                    if(i==0||j==0||i==m-1||j==n-1) continue; //不输出墙壁
                    else
                    {
                        printf(" ");
                        cout<<Maze[i][j];
                    }
                }
            }

            break;
        case 2:
            cout<<">>生成的迷宫如下："<<endl;
            for (i=0; i<m; i++)
            {
                printf("\n");
                for(j=0; j<n; j++)
                {
                    if(i==0||j==0||i==m-1||j==n-1) continue; //不输出墙壁
                    else
                    {
                        printf(" ");
                        cout<<Maze[i][j];
                    }
                }
            }

            break;
        case 3:
            int num;
            for (i=0; i<m; i++)
            {

                for(j=0; j<n; j++)
                {
                    if(i==0||j==0||i==m-1||j==n-1) Maze[i][j]=1;
                    else
                    {
                        cin>>num;
                        Maze[i][j] = num ;
                    }

                }
            }
            break;
        case 4:
            cout<<"深度优先算法查找迷宫如下："<<endl;
             for (int i=0; i<m; i++)   //给辅助数组赋值全为0
            {
                for( int j=0; j<n; j++)
                {
                    Maze_sy[i][j]=0;

                }
            }
            path(startpoint,s,Maze,Maze_sy);
            break;
        case 5:
            cout<<"请输入开始起点"<<endl;
            cin>>startpoint.col>>startpoint.row;
            for (int i=0; i<m; i++)   //给辅助数组赋值全为0
            {
                for( int j=0; j<n; j++)
                {
                    Maze_sy[i][j]=0;

                }
            }
            break;
        case 6:
            cout<<"请输入终点："<<endl;
            cin>>N>>M;
            M=M+2;N=N+2;
             for (int i=0; i<m; i++)   //给辅助数组赋值全为0
            {
                for( int j=0; j<n; j++)
                {
                    Maze_sy[i][j]=0;

                }
            }
            break;
        }
    }

}
