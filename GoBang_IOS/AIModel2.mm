//
//  AIModel.m
//  GoBang_IOS
//
//  Created by su xinde on 13-1-22.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import "AIModel2.h"

@implementation AIModel

- (id)init
{
    if(self = [super init])
    {
        m_list = [[NSMutableArray alloc] initWithCapacity:0];
    }
    return self;
}

- (void)initBoard
{
    if(!m_list.count==0)
       [m_list removeAllObjects];
    for (int i=0;i<BOARDSIZE+2*OUTSIDE;i++)
        for (int j=0;j<BOARDSIZE+2*OUTSIDE;j++)
        {
            m_board[i][j]=INAVAILABLE;
            m_temp[i][j]=INAVAILABLE;
        }
    for (int i=OUTSIDE;i<OUTSIDE+BOARDSIZE;i++)
        for (int j=OUTSIDE;j<OUTSIDE+BOARDSIZE;j++)
        {m_board[i][j]=EMPTY;
            m_temp[i][j]=EMPTY;
            m_level[i-OUTSIDE][j-OUTSIDE]=0;
        }
    [self initLevel];
}

- (void)initLevel
{
    for (int i=BOARDSIZE/2-2;i<=BOARDSIZE/2+1;i++)
        for (int j=BOARDSIZE/2-2;j<=BOARDSIZE/2+1;j++)
            m_level[i][j]=1;
}

- (int)Catalog:(int)sx sy:(int)sy px:(int)px py:(int)py  color:(int)color type:(int)type
{
    int cat=0;
    int pos=0;
    int num=5;
    for (pos=0;pos<5;pos++)
    {
        int t=m_temp[sx+pos*px][sy+pos*py];
        int e=(color==BLACK)?WHITE:BLACK;
        if (t==INAVAILABLE||t==e) {cat=-1;num--;}
        if (t==EMPTY) {if (cat!=-1) cat=cat*10+pos+1;num--;}
    }
    type=num; // type &
    return cat;
}

- (int)evalLevel:(int)x y:(int)y color:(int)color count:(int)count
{
	int me=color;
	int num=0;
	int enemy=(color==BLACK)?WHITE:BLACK;
    int	levelmax=1;
	int level;
    //	int level_temp[BOARDSIZE][BOARDSIZE];
    for (int i=OUTSIDE;i<OUTSIDE+BOARDSIZE;i++)
        for (int j=OUTSIDE;j<OUTSIDE+BOARDSIZE;j++)
        { level=0;
            if(m_temp[i][j]==EMPTY)
            {  	unsigned melevel=0;
                unsigned helevel=0;
                int metype = [self pointLevel:i y:j color:me level:melevel];
                int hetype= [self pointLevel:i y:j color:enemy level:helevel];
                level=1;
                if (metype==5*1) level=10000;
                else if (hetype==5*1) level=9000;
                else if (metype==4*4||metype==4*3) level=8000;
                else if (metype==3*3&&melevel==0) level=0;
                else if (hetype==4*4||hetype==4*3) level=5000;
                else if (metype==3*3&&melevel==9600) level=5000;
                else if (hetype==3*3&&helevel==9600) level=5000;
                else
                {
                    if (metype==3*2) level=5000;
                    if (metype==4*1) level=5000;
                    if (metype==2&&hetype==3*2) level=2000;
                    if (metype==2&&hetype==2) level=1000;
                    if (metype==2&&hetype==1) level=500;
                    if (metype==1&&hetype>1) level=100;
                    if (metype==1&&hetype==1) level=1;
                }
                
                if (level>levelmax&&levelmax>=1)
                {	levelmax=level;
                    num=0;
                }
                if (levelmax>1&&level==levelmax)
                    num++;
            }
            m_level[i-OUTSIDE][j-OUTSIDE]=level;
        }
    if (levelmax<9000&&num>0)
    {int sub;
        num=0;
        switch(levelmax)
        {
            case 8000: sub=2000;break;
            case 5000: sub=5000;break;
            case 2000: sub=8000;break;
            case 1000: sub=9000;break;
            default:sub=10000;
        }
        int t=levelmax;
        levelmax=0;
        for (int i=OUTSIDE;i<OUTSIDE+BOARDSIZE;i++)
            for (int j=OUTSIDE;j<OUTSIDE+BOARDSIZE;j++)
            {int n;
                int l;
                l=m_level[i-OUTSIDE][j-OUTSIDE];
                if (l==t)
                {
                    l+=sub-EvalBoard(i,j,me,n,enemy);//+EvalBoard(i,j,me,n,me);
                    l-=n;
                    if (l>levelmax) {levelmax=l;num=0;}
                    if (l==levelmax) num++;
                }
                else l=0;
                m_level[i-OUTSIDE][j-OUTSIDE]=l;
            }
    }
    count=num;
    return levelmax;
}

- (int)pointLevel:(int) x y:(int) y color:(int) color level:(unsigned int &)level
{
    unsigned t[4];
    unsigned l[4];
    unsigned temp[6]={0,0,0,0,0,0};
    unsigned cat[6]={0,0,0,0,0,0};
    int type=-1;
    unsigned factor[6]={0,1,10,100,1000,10000};
    m_temp[x][y]=color;
    t[0]=PointLineLevel(x-5,y,1,0,color,l[0]);
    t[1]=PointLineLevel(x-5,y-5,1,1,color,l[1]);
    t[2]=PointLineLevel(x,y-5,0,1,color,l[2]);
    t[3]=PointLineLevel(x-5,y+5,1,-1,color,l[3]);
    m_temp[x][y]=EMPTY;
    unsigned sumt=factor[t[0]]*l[0]+l[1]*factor[t[1]]+l[2]*factor[t[2]]+l[3]*factor[t[3]];
    temp[t[0]]+=factor[l[0]];
    temp[t[1]]+=factor[l[1]];
    temp[t[2]]+=factor[l[2]];
    temp[t[3]]+=factor[l[3]];
    if (temp[5]>=1)  cat[5]=5*1;//成五
    if (temp[4]>=2) cat[4]=4*4;//双四
    else if (temp[4]>=1) cat[4]=4*1;//单四
    if (temp[3]>=110) cat[3]=3*3;//双三
    else if (temp[3]>=100) cat[3]=3*2;//
    else if (temp[3]>=20) cat[3]=3*3;//双三
    else if (temp[3]>=10) cat[3]=3*2;//活三
    else if (temp[3]>=1) cat[3]=3*1;//单三
    if (temp[2]>=10) cat[2]=2*1;//活二
    else if (temp[2]>=1) cat[2]=1*1;//单二
    else if (temp[1]) cat[1]=1*1;//孤子
    if (color==BLACK)
    {
        if (cat[3]==3*3) {level=0;return 3*3;}//9
    }
    if (cat[5]==5*1) {level=9900;return 5*1;}//5
    if (cat[4]==4*4) {level=9800;return 4*4;}//16
    if (cat[4]==4*1&&cat[3]>3*1) {level=9700;return 4*3;}//12
    if (color==WHITE)
    {
        if (cat[3]==3*3) {level=9600;return 3*3;}//9
    }
    if (cat[4]==4*1&&cat[2]==2){level=5000;return 4*1;}//4
    if (cat[4]==4*1&&cat[2]==1){level=4900;return 4*1;}
    if (cat[4]==4*1){level=4800;return 4*1;}
    if (cat[3]==3*2&&cat[2]==2){level=5000;return 3*2;}//6
    if (cat[3]==3*2&&cat[2]==1){level=4900;return 3*2;}//6
    if (cat[3]==3*2) {level=4800;return 3*2;}//6
    if (cat[3]==3*1||cat[2]==2){level=1000;return 2;}
    if (cat[2]==1) {level=1;return 1;}
    level=1;
    
    return 1;
}

#pragma mark - 

int IsSuccess()
{QiZhi *temp=(QiZhi *) m_list.GetHead();
    if (temp==NULL) return 0;
    int posX=temp->x+OUTSIDE;
    int posY=temp->y+OUTSIDE;
    int color=temp->color;
    unsigned level;
    int result=PointLevel(posX,posY,color,level);
    if (result==5*1) result=1;
    if (color==BLACK&&result==3*3&&level==0) result=1;
    else result=0;
    return result;
}

int AddChess(int x, int y, int color)
{
    int posX=x+OUTSIDE;
    int posY=y+OUTSIDE;
    if (!IsEmpty(posX,posY))
    {
        char str[20];
        sprintf(str,"%d,%d,%d",x,y,color);
        return SQUAREFULL;
    }
    QiZhi *temp=new QiZhi(x,y,color);
    if (temp==NULL) return MEMORYFAIL;
    m_list.AddHead(temp);
    m_board[posX][posY]=color;
    unsigned int level;
    if (PointLevel(posX,posY,color,level)==5*1) return CHESSWIN;
    if (PointLevel(posX,posY,color,level)==3*3&&color==BLACK) return CHESSFAIL;
    m_temp[posX][posY]=color;
    // int count;
    // EvalLevel(posX,posY,color,count);
    m_level[x][y]=-1;
    return 0;
}

int IsEmpty(int x, int y)
{
    if (m_board[x][y]>=2) return 1;
    else return 0;
}

int RemoveChess(int &cx, int &cy, int &color)
{//AfxMessageBox("hello");
    if (!m_list.IsEmpty())
    {
        QiZhi *temp=(QiZhi *) m_list.GetHead();
        if (temp==NULL) return 0;
        cx=temp->x;
        cy=temp->y;
        color=temp->color;
        m_board[temp->x+OUTSIDE][temp->y+OUTSIDE]=EMPTY;
        m_temp[temp->x+OUTSIDE][temp->y+OUTSIDE]=EMPTY;
        m_level[temp->x][temp->y]=0;
        m_list.RemoveHead();
        delete temp;
        return 1;
    }
    else return 0;
}



ChessMan *GetChess(POSITION &index)
{
    ChessMan *temp;
    if (m_list.IsEmpty()) return NULL;
    if (index!=m_list.GetTailPosition()) temp=(QiZhi *) m_list.GetNext(index);
    else temp=NULL;
    return temp;
}

QiZhi* GetHead(POSITION &index)
{
    if (m_list.IsEmpty()) return NULL;
    QiZhi *temp=(QiZhi *)m_list.GetHead();
    index=m_list.GetHeadPosition();
    return temp;
}

void GetBoard(int board[14][14])
{int i,j;
    for (i=0;i<14;i++)
        for (j=0;j<14;j++)
            board[i][j]=m_level[i][j];
}

void InitLevel()
{
    for (int i=BOARDSIZE/2-2;i<=BOARDSIZE/2+1;i++)
        for (int j=BOARDSIZE/2-2;j<=BOARDSIZE/2+1;j++)
            m_level[i][j]=1;
}


int Catalog(int sx, int sy, int px, int py, int color,int &type)
{
    int cat=0;
    int pos=0;
    int num=5;
    for (pos=0;pos<5;pos++)
    {
        int t=m_temp[sx+pos*px][sy+pos*py];
        int e=(color==BLACK)?WHITE:BLACK;
        if (t==INAVAILABLE||t==e) {cat=-1;num--;}
        if (t==EMPTY) {if (cat!=-1) cat=cat*10+pos+1;num--;}
    }
    type=num;
    return cat;
}




unsigned PointLineLevel(int sx, int sy, int px, int py, int color, unsigned &level)
{
    int count=7;
    unsigned type=-1;
    int num=0;
    int startx=sx;
    int starty=sy;
    int cat[7];
    int list[7];
    int match[5];
    for (int i=0;i<5;i++) match[i]=0;
    int e=(color==BLACK)?WHITE:BLACK;
    while (count>0)
    {int s;
        int n;
        s=Catalog(startx,starty,px,py,color,n);
        cat[7-count]=s;
        list[7-count]=n;
        count--;
        startx+=px;
        starty+=py;
    }
    for (i=1;i<6;i++)
    { int c=cat[i];
        switch(c)
        {
            case 0:if(list[i-1]==4&&list[i+1]==4)
            {
                match[4]=1;
                break;
            }
            case 1:if (cat[i+1]==5&&list[i+2]==3&&list[i-1]==3)
            {match[3]=2;
            }
            else if (cat[i+1]==-1)
            {
                if (match[3]<1) match[3]=1;
            }
                break;
            case 5:if (cat[i-1]==1&&list[i-2]==3&&list[i+1]==3)
            {
                match[3]=2;
            }
            else if (cat[i-1]==-1)
            {
                if (match[3]<1)match[3]=1;
            }
                break;
            case 4:
            case 3:
            case 2:if (list[i-1]==3&&list[i+1]==3)
            {
                if (match[3]<1)match[3]=1;break;
            }
                break;
            case 12:if (cat[i+1]==15) break;
            else if (list[i+1]==3&&list[i-1]==2)
            {
                if (match[2]<1)match[2]=1;break;
            }
            case 45:if (cat[i-1]==15) break;
            else if (list[i-1]==3&&list[i+1]==2)
            {
                if (match[2]<1)match[2]=1;break;
            }
            case 15:if (cat[i-1]==12&&cat[i+1]==45&&list[i-2]==2&&list[i+2]==2)
            {
                match[2]=3;
                break;
            }
                if (cat[i-1]==12)
                {
                    if (list[i-2]==2&&list[i+1]==3)
                    {
                        if (match[2]<2)match[2]=2;
                    }
                    break;
                }
                if (cat[i+1]==45)
                {
                    if (list[i-1]==3&&list[i+2]==2)
                    {
                        if (match[2]<2)match[2]=2;
                    }
                    break;
                }
                if (list[i-1]==3&&list[i+1]==3)
                {
                    if (match[2]<1)match[2]=1;
                    break;
                }
                break;
            case 13:if (cat[i+1]==25) break;
            else
            {
                if (cat[i-1]!=24&&cat[i+1]!=2)
                    if (match[2]<1) match[2]=1;
                break;
            }
            case 25:if (cat[i-1]==13&&list[i-2]==2&&list[i+1]==2)
            {
                if (match[2]<2) match[2]=2;
                break;
            }
                if (list[i-1]==3&&list[i+1]==2)
                {
                    if (match[2]<1) match[2]=1;
                    break;
                }
            case 14:if(cat[i+1]==35) break;
            else
            {
                if (list[i+1]==3&&list[i-1]==2)
                    if (match[2]<1)match[2]=1;
                break;
            }
            case 35:if (cat[i-1]==14&&list[i-2]==2&&list[i+1]==2)
            { if (match[2]<2)
                match[2]=2;
                break;
            }
                if (list[i-1]==3&&list[i+1]==2)
                { if (match[2]<1)
                    match[2]=1;
                    break;
                }
            case 23:
            case 34:
            case 24:if (list[i-1]==2&&list[i+1]==2)  if (match[2]<1)match[2]=1;
                break;
            case 123:if (cat[i+1]==125||cat[i+2]==145||cat[i+3]==345) match[1]=2;else if (match[1]<1) match[1]=1;break;
            case 145:if (cat[i-2]==123||cat[i-1]==125||cat[i+1]==345) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 125:if (cat[i-1]==123||cat[i+1]==145||cat[i+2]==345) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 345:if (cat[i-3]==123||cat[i-2]==125||cat[i-1]==145) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 245:if (cat[i-2]==124||cat[i-1]==135) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 135:if (cat[i-1]==124||cat[i+1]==245) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 124:if (cat[i+1]==135||cat[i+2]==245) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 235:if (cat[i-1]==134) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 134:if (cat[i+1]==235) match[1]=2;else if (match[1]<1)match[1]=1;break;
            case 234:if (match[1]<1)match[1]=1;
            case -1:break;
            default:match[0]=1;break;
        }
    }
    type=0;level=0;
    if (match[0]) {type=1;level=match[0];}
    if (match[1]) {type=2;level=match[1];}
    if (match[2]) {type=3;level=match[2];}
    if (match[3]) {type=4;level=match[3];}
    if (match[4]) {type=5;level=match[4];}
    return type;
}

void GetNextPace(int &x, int &y, int color)
{
    int count;
    CObArray pList;
    int levelmax=EvalLevel(x,y,color,count);
    for (int i=0;i<BOARDSIZE;i++)
        for (int j=0;j<BOARDSIZE;j++)
        {
            if (levelmax==m_level[i][j]) pList.Add(new QiZhi(i,j,color));
        }
    SYSTEMTIME systime;
    ::GetSystemTime(&systime);
    srand(systime.wSecond);
    if (count>1)
    {
        int index=rand()%count;
        QiZhi *temp=(QiZhi*) pList.GetAt(index);
        x=temp->x;
        y=temp->y;
    }
    else
    {
        QiZhi *temp=(QiZhi*) pList.GetAt(0);
        x=temp->x;
        y=temp->y;
    }
}

int EvalBoard(int x,int y,int mecolor,int &count,int color)
{
	int me=color;
	unsigned level=1;
	unsigned levelmax=0;
	int num=0;
	m_temp[x][y]=mecolor;
    for (int i=OUTSIDE;i<OUTSIDE+BOARDSIZE;i++)
        for (int j=OUTSIDE;j<OUTSIDE+BOARDSIZE;j++)
        {   level=0;
            if(m_temp[i][j]==EMPTY)
            {
                PointLevel(i,j,me,level);
                if (level>levelmax) {levelmax=level;num=0;}
                if (level==levelmax) num++;
            }
        }
    count=num;
    m_temp[x][y]=EMPTY;
    return levelmax;
}

//QiZhi * GetTail()
//{
//    QiZhi *temp;
//    if (m_list.IsEmpty()) return NULL;
//    temp=(QiZhi *) m_list.GetTail();
//    return temp;
//}

@end










