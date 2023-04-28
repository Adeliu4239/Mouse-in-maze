//---------------------------------------------------------------------------

#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "HW3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


int **maze;
int **mark;
int **g_maze;
int g_Height=0;
int g_Width=0;
int g_Size=40;
int Height,Width;
bool found = false;
bool b1 = false;
bool b2 = false;
int gx=1;
int gy=0;

#define possible_direction 8

struct offset
{
	int dx, dy;
};

enum directions {N, NE, E, SE, S, SW, W, NW};  // N=0, NE=1, ... , NW=7; Using integers 0-7 would be just fine (No need to enumerate them)

struct offset move[possible_direction];

struct position
{
	int x,y;
	directions dir;   // Or int dir;
};
int m,p;
int top=-1;
struct position * stack;

int ** generatemaze(int ** maze, int x, int y);
void push (struct position data);
struct position pop();
void path(int m, int p);

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Clear();

        move[N].dx = -1;   move[N].dy = 0;//Define offset
        move[NE].dx = -1;  move[NE].dy = 1;
        move[E].dx = 0;    move[E].dy = 1;
        move[SE].dx = 1;   move[SE].dy = 1;
        move[S].dx = 1;    move[S].dy = 0;
        move[SW].dx = 1;   move[SW].dy = -1;
        move[W].dx = 0;    move[W].dy = -1;
        move[NW].dx = -1;  move[NW].dy = -1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        top=-1;
        found=false;
        b1=false;
        if (g_maze) // delete the previous maze
	{
        	for (int i=0; i<g_Height; i++)
                	delete(g_maze[i]);
        	delete(g_maze);
        }
        if (maze) // delete the previous maze
        {
        	for (int i=0; i<Height; i++)
                	delete(maze[i]);
                delete(maze);
        }
        if(Form1->Edit1->Text.IsEmpty()||Form1->Edit2->Text.IsEmpty())
        {
                //ShowMessage("請輸入數字！！！");
                MessageBox(Application->Handle,L"請在 Height 或 Width 輸入數字！！！",L"Error",MB_OK|MB_ICONSTOP);

        }
        else if(Form1->Edit1->Text[1]<48||Form1->Edit1->Text[1]>57||Form1->Edit2->Text[1]<48||Form1->Edit2->Text[1]>57)
        {
                MessageBox(Application->Handle,L"請在 Height 或 Width 輸入數字！！！",L"Error",MB_OK|MB_ICONSTOP);

        }
        else
        {
                Memo1->Lines->Clear();
                g_Height=StrToInt(Form1->Edit1->Text);
		g_Width=Form1->Edit2->Text.ToInt();
                if(Form1->Edit3->Text.IsEmpty())
                {
                        g_Size=40;
                }
                else if(Form1->Edit3->Text[1]<48||Form1->Edit3->Text[1]>57)
                {
                        //ShowMessage("請輸入數字！！！");
                        MessageBox(Application->Handle,L"請別在 Size 輸入數字以外的東西！！！",L"Error",MB_OK|MB_ICONSTOP);

                }
                else
                {
               		g_Size=Form1->Edit3->Text.ToInt();
                }
                g_maze = new int *[g_Height];
                for(int i=0;i<g_Height;i++)
                {
                        g_maze[i] = new int [g_Width];
                }
                int Start_i=1, Start_j=1, End_i=g_Height-2, End_j=g_Width-2;
                String s;
		int x, y;
		srand(time(NULL));
                for (x=0; x<g_Height; x++)
                {
                	for (y=0; y<g_Width; y++)
                        {
                        	if (x==0 || y==0 || x==g_Height-1 || y==g_Width-1 )
                                	g_maze[x][y] = 2; // 設定外牆

				else
                                	g_maze[x][y] = 1; // 初始迷宮內部

                        }

                }
                g_maze = generatemaze(g_maze, End_i, End_j); // 產生迷宮
		g_maze[Start_i][Start_j-1] =0; // 拆掉入口左牆
                g_maze[End_i][End_j+1] =0; // 拆掉出口右牆
                if(g_Height%2==0 || g_Width%2==0)
                {
                        g_maze[Start_i+1][Start_j] =0;
                        g_maze[Start_i][Start_j] =0;
                }
                StringGrid1->RowCount = g_Height;
		StringGrid1->ColCount = g_Width;
                StringGrid2->RowCount = g_Height;
		StringGrid2->ColCount = g_Width;
                StringGrid3->RowCount = g_Height;
		StringGrid3->ColCount = g_Width;
                for (int i=0; i<g_Width; i++)
                {
                        StringGrid1->ColWidths[i] = g_Size;
                        StringGrid2->ColWidths[i] = g_Size;
                        StringGrid3->ColWidths[i] = g_Size;
                }
		for (int i=0; i<g_Height; i++)
                {
                        StringGrid1->RowHeights[i] = g_Size;
                        StringGrid2->RowHeights[i] = g_Size;
                        StringGrid3->RowHeights[i] = g_Size;
                }
                Memo1->Lines->Add("(H,W)="+IntToStr(g_Height)+", "+IntToStr(g_Width));
                for (int i=0; i<g_Height; i++)
                {
                        s="";
                	for (int j=0; j<g_Width; j++)
                        {
                                s=s+IntToStr(g_maze[i][j])+" ";
                		StringGrid1->Cells[j][i] = g_maze[i][j];
                                StringGrid2->Cells[j][i] = g_maze[i][j];
                                StringGrid3->Cells[j][i] = g_maze[i][j];
                        }
                       	Memo1->Lines->Add(s);
                }
                StringGrid2->DefaultDrawing = false;
                PageControl1->ActivePage = TabSheet3;
                StringGrid2->Refresh();
                if (CheckBox1->Checked)
                {
                        TrackBar1->Enabled=True;
                	for (int i=0; i<g_Height; i++)
                        {
                        	for (int j=0; j<g_Width; j++)
                            	{
                                	Sleep(TrackBar1->Position);
                                 	StringGrid2->Refresh();
				}
                        }
                }
                Button3->Enabled=true;
                Button4->Enabled=true;
                Button5->Enabled=true;
                TrackBar1->Enabled=true;
                //if (CheckBox2->Checked)
                	//Form1->DoubleBuffered = true;
		//else
                	//Form1->DoubleBuffered = false;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
/*
    int m, n, i, j;
    freopen("in.txt", "r", stdin);
    // read data in "in.txt" as standard input 將in.txt當成stdin
    freopen("out.txt", "w", stdout);  // write into file "out.txt"
    cin >> m >> n;  // get the matrix size m*n from in.txt (stdin)
    int ** maze;
    maze = new int * [m];
    for (int i=0; i<m; i++)
    {    maze[i] = new int [n];
	 for (int j=0; j<n; j++)
	     cin >> maze[i][j];  // 自in.txt (stdin) 讀資料
    }
    fclose(stdin);
     cin.clear();  // clear the possible errors from cin
    String s="";  // write data onto Form1
    for (int i=0; i<m; i++)
    {   for (int j=0; j<n; j++)
         s = s + IntToStr(maze[i][j]) + " ";
        Form1->Memo1->Lines->Add(s);
    }
    // write data into file "out.txt"
    cout << m << " " << n << endl;
    for (i=0; i<m; i++)
    {   for (j=0; j<n; j++)
             cout << maze[i][j] <<" ";
	cout << endl;
    }
     fclose(stdout);
*/
	FILE *fp; // Define fp as a pointer pointing to some file (with data type FILE) in HD
        String out;
        AnsiString infile;   // Use builder's string (AnsiString) to ease the conversion (into const char *)
        if (OpenDialog1->Execute())
        {
                top=-1;
                found=false;
                b1=false;
                if (maze) // delete the previous maze
                {
                        for (int i=0; i<Height; i++)
                                delete(maze[i]);
                        delete(maze);
                }
                if (g_maze) // delete the previous maze
                {
                        for (int i=0; i<g_Height; i++)
                                delete(g_maze[i]);
                        delete(g_maze);
                }
                Height=0;
		Width=0;
        	infile = OpenDialog1->FileName;
		fp = fopen(infile.c_str(), "r+");
		//c_str函数的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用
          	fscanf(fp, "%d %d", &Height, &Width);    // Read in two integers m & n
		Memo1->Lines->Add("(H,W)="+IntToStr(Height)+", "+IntToStr(Width));
                g_Height=Height;
		g_Width=Width;
                maze = new int *[Height];
                for(int i=0;i<Height;i++)
                {
                        maze[i] = new int [Width];
                }
		for (int i=0; i<Height; i++)// Reda in m*n 0/1/2's into maze[][]
                {
        		for (int j=0; j<Width; j++)
                	{
                                fscanf(fp,"%d",&maze[i][j]);
                        }
                }
		fclose(fp);
          	for (int i=0; i<Height; i++)      // Print out maze[][] in Memo1
		{
          		out = "";
			for (int j=0; j<Width; j++) out += "  "+IntToStr(maze[i][j]);
			Memo1->Lines->Add(out);
           	}
		// Print out maze[][] in StringGrid1
                g_maze = maze;
		StringGrid1->RowCount = Height;
		StringGrid1->ColCount = Width;
                StringGrid2->RowCount = Height;
		StringGrid2->ColCount = Width;
                for (int i=0; i<Width; i++)
                {
                        StringGrid1->ColWidths[i] = g_Size;
                        StringGrid2->ColWidths[i] = g_Size;
                }
		for (int i=0; i<Height; i++)
                {
                        StringGrid1->RowHeights[i] = g_Size;
                        StringGrid2->RowHeights[i] = g_Size;
                }
		for (int i=0; i<Height; i++)
                {
                	for (int j=0; j<Width; j++)
                        {
                        	StringGrid1->Cells[j][i] = maze[i][j];
                                StringGrid2->Cells[j][i] = maze[i][j];
                        }
                }
                StringGrid1->Refresh();
		StringGrid2->Refresh();
                Button3->Enabled=true;
                Button4->Enabled=true;
                Button5->Enabled=true;
        }
        else
        {
                MessageBox(Application->Handle,L"什麼事...都沒發生過！！！",L"Error",MB_OK|MB_ICONSTOP);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if (SaveDialog1->Execute())     //確認SaveDialog1讀取檔案成功
	{ // 取SaveDialog1所開啟的檔案名稱, 將檔案名稱轉為char格式後用fopen開啟此檔案
	AnsiString file_name = SaveDialog1->FileName;
	FILE *fp = fopen(file_name.c_str(),"w");  // "w" 表示開以寫檔的方式開啟
	//利用fprintf將g_matrix中的元素寫入fp, 當需要換行時使用putc將'\n'加入fp中
        	if (fp)
                {
			fprintf(fp, "%d %d", g_Height, g_Width);
                        putc('\n', fp);
                        for  (int i=0 ; i<g_Height ; i++)
                        {
                                for (int j=0 ; j<g_Width ; j++)
                                {
                                        fprintf(fp, "%d ",g_maze[i][j]);
                                }
                                putc('\n', fp);
                        }
                        fclose(fp);   // 寫完檔後請關檔

                }

	}
        else
        {
                MessageBox(Application->Handle,L"什麼事...都沒發生過！！！",L"Error",MB_OK|MB_ICONSTOP);
        }
}
//---------------------------------------------------------------------------

int ** generatemaze(int ** maze, int x, int y)

{
	int direction;
        maze[x][y] =0; // 標示此格已設定
        //Form1->Memo2->Lines->Add("(x,y,dir)="+IntToStr(x)+","+IntToStr(y)+","+IntToStr(direction));
        while ((y+2 < g_Width && maze[x][y+2]==1) || (x+2 < g_Height && maze[x+2][y]==1) || (y-2 > 0 && maze[x][y-2]==1) || (x-2 > 0 && maze[x-2][y]==1)) // 如果不是外牆
        {
        	direction = rand()%4+1; // 決定下一個位置
		if (direction==1 && maze[x][y+2]==1 && y+2<g_Width) // 向右走
                {
                	maze[x][y+1] =0; // 拆掉右牆
                        maze = generatemaze(maze, x,y+2);

                }
               else if (direction==2 && maze[x-2][y]==1 && x-2>0) // 向上走
               {
               		maze[x-1][y] =0; // 拆掉上牆
                        maze = generatemaze(maze, x-2,y);

               }
               else if (direction==3 && maze[x][y-2]==1 && y-2>0) // 向左走
               {
               		maze[x][y-1] =0; // 拆掉右牆
                        maze = generatemaze(maze, x,y-2);
               }
               else if (direction==4 && x+2 < g_Height && maze[x+2][y]==1) // 向下走
               {
               		maze[x+1][y] =0; // 拆掉上牆
			maze = generatemaze(maze, x+2,y);
               }
	}
	return maze;

}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	//RadioButton1->Enabled=true;
        //RadioButton2->Enabled=true;
        //Button5->Enabled=false;
        //RadioButton1->Checked=true;
        //TrackBar1->Enabled=true;
        b1=false;
        m = g_Height-2;
	p = g_Width-2;
        mark = new int *[g_Height];
        for(int i=0;i<g_Height;i++)
        {
        	mark[i] = new int [g_Width];
        }
	for(int i=0; i<=m+1; i++)
	{
        	for (int j=0; j<=p+1; j++)
		{
                	mark[i][j] = g_maze[i][j];
		}
	}
        position step;
        stack = new struct position [m*p];
        int npx,npy,fx,fy;
        mark[1][0]=5;//5代表走到
        StringGrid1->Cells[0][1] = ">>>";
        StringGrid2->Cells[0][1] = "5";
        Sleep(50+((TrackBar1->Position)*10));
        step.x = 1;
        step.y = 0;
        step.dir = 2;// E

	push(step);
        while(top!=-1&& (!found))
        {
            step=pop();
            npx=step.x;
            npy=step.y;
            while(step.dir<=7&&(!found))
            {
            	fx=npx+move[step.dir].dx;
                fy=npy+move[step.dir].dy;
                if((!g_maze[fx][fy])&&(!mark[fx][fy]))
                {
                        step.x = npx;
                        step.y = npy;
                        step.dir=step.dir+2;
                        push(step);
                        mark[fx][fy]+=5;
                        StringGrid1->Cells[fy][fx] = "^";
                        StringGrid1->Refresh();
			StringGrid2->Cells[fy][fx]= mark[fx][fy];
                        StringGrid2->Refresh();
  			Sleep(50+((TrackBar1->Position)*10));
                        Memo1->Lines->Add("Onway:("+IntToStr(npx)+","+IntToStr(npy)+")"+"["+IntToStr(mark[npx][npy])+"]");
                        if(fx==m&&fy==p)
                        {
                                found = true;//成功找到出口
                                step.x = fx;
                                step.y = fy+1;
                                step.dir = 2;
                                StringGrid1->Cells[fy+1][fx] = ">>>";
                                StringGrid2->Cells[fy+1][fx] = "5";
                                StringGrid1->Refresh();
                                StringGrid2->Refresh();
                                break;
                        }
                       	npx = fx;
                       	npy = fy;
                       	step.dir = 0;
                }
                else
		{       /*
                	if(RadioButton1->Checked==true)
                        {
                                step.dir = step.dir+2;
                        }
                        if(RadioButton2->Checked==true)
                        {
                                step.dir = step.dir+1;
                        }*/
                        step.dir = step.dir+2;
                }
            }
            if(step.dir>7)
            {
                mark[npx][npy]+=5;
                StringGrid1->Cells[npy][npx]= "-";
                StringGrid1->Refresh();
            	StringGrid2->Cells[npy][npx]= mark[npx][npy];
            	StringGrid2->Refresh();
                Sleep(50+((TrackBar1->Position)*10));
            	Memo1->Lines->Add("pop:("+IntToStr(npx)+","+IntToStr(npy)+")"+"["+IntToStr(mark[npx][npy])+"]");
            	//Memo1->Lines->Add("("+IntToStr(npx)+","+IntToStr(npy)+")");
            }
            /*
            if(found==true)
            {
                StringGrid1->Cells[npy][npx]= "^";
                StringGrid1->Refresh();
                StringGrid2->Cells[npy][npx]= "5";
            	StringGrid2->Refresh();
            }
            else
            {
               	mark[npx][npy]+=5;
                StringGrid1->Cells[npy][npx]= "-";
                StringGrid1->Refresh();
                StringGrid2->Cells[npy][npx]= mark[npx][npy];
            	StringGrid2->Refresh();
            	Sleep(50+((TrackBar1->Position)*10));
                Memo1->Lines->Add("pop:("+IntToStr(npx)+","+IntToStr(npy)+")"+"["+IntToStr(mark[npx][npy])+"]");
            	//Memo1->Lines->Add("("+IntToStr(npx)+","+IntToStr(npy)+")");
            }
             */

        }
        if(found==true)
        {
                MessageBox(Application->Handle,L"已找到出口！",L"尋找結果",MB_OK|MB_ICONINFORMATION);
        }
        else
        {
                MessageBox(Application->Handle,L"找不到出口！",L"尋找結果",MB_OK|MB_ICONINFORMATION);
        }
	for (int i=0; i<g_Height; i++)
        	delete(mark[i]);
        delete(mark);
        delete []stack;
        if(g_maze)
        {
        	for (int i=0; i<g_Height; i++)
                        delete(g_maze[i]);
                delete(g_maze);
        }
        if(maze)
        {
                for (int i=0; i<Height; i++)
                        delete(maze[i]);
                delete(maze);
        }
        Button4->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,TGridDrawState State)
{
        AnsiString text = StringGrid2->Cells[ACol][ARow];
        int x1,x2,x3;
        int y1,y2,y3;
        x1=rand()%256;
        x2=rand()%256;
        x3=rand()%256;
        y1=rand()%256;
        y2=rand()%256;
        y3=rand()%256;
        if(Form1->CheckBox3->Checked==true)
        {
            if (text == "0")
        	StringGrid2->Canvas->Brush->Color = TColor RGB(243, 245, 249) ;
            else if(text == "1")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(155, 178, 205) ;
            else if(text=="2")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(58, 67, 77);
            else if(text == "5")
            {
                if(found==false)
                {
                	StringGrid2->Canvas->Brush->Color = TColor RGB(x1, x2, x3) ;
                }
                else
                {
                        StringGrid2->Canvas->Brush->Color = TColor RGB(155, 205, 157) ;
                }
            }
            else
            {
                if(found==false)
                {
                	StringGrid2->Canvas->Brush->Color = TColor RGB(y1, y2, y3) ;
                }
                else
                {
                        StringGrid2->Canvas->Brush->Color = TColor RGB(205, 182, 155) ;
                }
            }

            StringGrid2->Canvas->FillRect(Rect);
        }
        else
        {
            if (text == "0")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(243, 245, 249) ;
            else if(text == "1")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(155, 178, 205) ;
            else if(text=="2")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(58, 67, 77);
            //else if(StrToInt(text)>5)
                    //StringGrid2->Canvas->Brush->Color = TColor RGB(205, 182, 155) ;
            else if(text == "5")
                    StringGrid2->Canvas->Brush->Color = TColor RGB(155, 205, 157) ;
            else
                    StringGrid2->Canvas->Brush->Color = TColor RGB(205, 182, 155) ;
            StringGrid2->Canvas->FillRect(Rect);

        }
}
//---------------------------------------------------------------------------

void push (struct position data)
{
	if (top == (m*p-1))//StackFull();
        {
                MessageBox(Application->Handle,L"發生錯誤！！！\n堆疊已滿！！！",L"Error",MB_OK|MB_ICONSTOP);
        }
	else stack[++top] = data;
}
struct position pop()
{
        if (top == -1)
        	MessageBox(Application->Handle,L"發生錯誤！！！\n堆疊為空！！！",L"Error",MB_OK|MB_ICONSTOP);
	else
        	return stack[top--];
}
/*
void path(int m, int p)
{

	stack = new struct position [m*p]; // if allocated dynamically
	struct position step;
	int i,j,u,v;
	directions d;
	step.x = step.y = 1; step.dir = 2;  // E
	push(step);
	while (top != -1) // while stack NOT empty
	{
        	step = pop();
        	i=step.x; j=step.y; d=step.dir;
        	while (d<=7)
        	{
                    u = i+move[d].dx; v = j+move[d].dy;
                    if ((!g_maze[u][v]) && (!mark[u][v]))
                    {
                            step.x = i; step.y = j;
                            step.dir = step.dir+1;
                            push(step);
                            if ((u==m) && (v==p))
                            {
                                    return;
                            }
                            mark [u][v]=1;
                            i=u; j=v; d=N;
                    }
                    else
                    	d = (directions) d+1;
                }
  	}
	delete [] stack;

}
 */

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        //Button4->Enabled=false;
        PageControl1->ActivePage = TabSheet4;
        MessageBox(Application->Handle,L"切換到英文輸入法按一下表格後按下t開始！",L"提示",MB_OK|MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
        int y1,y2,y3;
        AnsiString text = StringGrid3->Cells[ACol][ARow];
        if (text == "0")
        	StringGrid3->Canvas->Brush->Color = TColor RGB(243, 245, 249) ;
        else if(text == "1")
                StringGrid3->Canvas->Brush->Color = TColor RGB(155, 178, 205) ;
	else if(text=="2")
		StringGrid3->Canvas->Brush->Color = TColor RGB(58, 67, 77);
        else if(text == "5")
        {
		if(Form1->CheckBox3->Checked==true)
                {
                    y1=rand()%256;
                    y2=rand()%256;
                    y3=rand()%256;
                    StringGrid3->Canvas->Brush->Color = TColor RGB(y1,y2,y3) ;
                }
                else
                {
                    StringGrid3->Canvas->Brush->Color = TColor RGB(205,155,178) ;
                }
        }
        else
                StringGrid3->Canvas->Brush->Color = TColor RGB(205, 182, 155) ;
	StringGrid3->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3KeyPress(TObject *Sender, System::WideChar &Key)

{
        switch(Key)
        {
            case't':
                if(b1==false)
                {
                    Memo1->Lines->Add("===Begin play!!!===");
                    MessageBox(Application->Handle,L"開始遊戲！！！\n w->上 a->左 d->右 s->下 e->exit",L"提示",MB_OK|MB_ICONINFORMATION);
                    mark = new int *[g_Height];
                    for(int i=0;i<g_Height;i++)
                    {
                            mark[i] = new int [g_Width];
                    }
                    for(int i=0; i<=m+1; i++)
                    {
                            for (int j=0; j<=p+1; j++)
                            {
                                    mark[i][j] = g_maze[i][j];
                            }
                    }
                    b1=true;
                }
                mark[gx][gy]=0;
                StringGrid3->Cells[gy][gx]= mark[gx][gy];
                gx=1;
                gy=0;
                mark[gx][gy]=5;
                StringGrid3->Cells[gy][gx]= mark[gx][gy];
                StringGrid3->Refresh();
                break;
            case'w':
                if(g_maze[gx-1][gy]==0&&gx-1>=0)
                {
                        mark[gx-1][gy]=5;
                        mark[gx][gy]=0;
                        StringGrid3->Cells[gy][gx-1]= mark[gx-1][gy];
                        StringGrid3->Cells[gy][gx]= mark[gx][gy];
                        gx-=1;
                	StringGrid3->Refresh();
                }
                break;
            case'a':
                if(g_maze[gx][gy-1]==0&&gy-1>=0)
                {
                        mark[gx][gy-1]=5;
                        mark[gx][gy]=0;
                        StringGrid3->Cells[gy-1][gx]= mark[gx][gy-1];
                        StringGrid3->Cells[gy][gx]= mark[gx][gy];
                        gy-=1;
                	StringGrid3->Refresh();
                }
                break;
            case's':
                if(g_maze[gx+1][gy]==0 && gx+1<g_Height)
                {
                        mark[gx+1][gy]=5;
                        mark[gx][gy]=0;
                        StringGrid3->Cells[gy][gx+1]= mark[gx+1][gy];
                        StringGrid3->Cells[gy][gx]= mark[gx][gy];
                        gx+=1;
                	StringGrid3->Refresh();
                }
                break;
            case'd':
                if(g_maze[gx][gy+1]==0&&gy+1<g_Width)
                {
                        mark[gx][gy+1]=5;
                        mark[gx][gy]=0;
                        StringGrid3->Cells[gy+1][gx]= mark[gx][gy+1];
                        StringGrid3->Cells[gy][gx]= mark[gx][gy];
                        gy+=1;
                	StringGrid3->Refresh();
                }
                if(gx==g_Height-2&&gy==g_Width-1)
                {
                        int Start_i=1, Start_j=1, End_i=g_Height-2, End_j=g_Width-2;
                        int x, y;
                        srand(time(NULL));
                        for (x=0; x<g_Height; x++)
                        {
                                for (y=0; y<g_Width; y++)
                                {
                                        if (x==0 || y==0 || x==g_Height-1 || y==g_Width-1 )
                                                g_maze[x][y] = 2; // 設定外牆

                                        else
                                                g_maze[x][y] = 1; // 初始迷宮內部

                                }

                        }
                        g_maze = generatemaze(g_maze, End_i, End_j); // 產生迷宮
                        g_maze[Start_i][Start_j-1] =0; // 拆掉入口左牆
                        g_maze[End_i][End_j+1] =0; // 拆掉出口右牆
                        if(g_Height%2==0 || g_Width%2==0)
                        {
                                g_maze[Start_i+1][Start_j] =0;
                                g_maze[Start_i][Start_j] =0;
                        }
                        for (x=0; x<g_Height; x++)
                        {
                                for (y=0; y<g_Width; y++)
                                {
                                        StringGrid1->Cells[y][x]=g_maze[x][y];
                                        StringGrid2->Cells[y][x]=g_maze[x][y];
                                        StringGrid3->Cells[y][x]=g_maze[x][y];
                                }

                        }
                        for(int i=0; i<=m+1; i++)
                        {
                                for (int j=0; j<=p+1; j++)
                                {
                                        mark[i][j] = g_maze[i][j];
                                }
                        }
                        gx=1;
                        gy=0;
                        mark[gx][gy]=5;
                        StringGrid3->Cells[gy][gx]= mark[gx][gy];
                        StringGrid1->Refresh();
                        StringGrid2->Refresh();
                        StringGrid3->Refresh();
                }
                break;
            case 'e':
                PageControl1->ActivePage = TabSheet3;
                for (int i=0; i<g_Height; i++)
                        delete(mark[i]);
                delete(mark);
                b1=false;
                mark[gx][gy]=0;
                StringGrid3->Cells[gy][gx]= mark[gx][gy];
                StringGrid3->Refresh();
                gx=1;
                gy=0;
                MessageBox(Application->Handle,L"已離開！！如要繼續請回至play",L"提示",MB_OK|MB_ICONINFORMATION);
                break;
        }
}
//---------------------------------------------------------------------------

