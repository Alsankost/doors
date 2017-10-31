void Draw_Str(int x,int y,int r,Ucs s,int sp=0,int d=0)
 {settextstyle(sp,d,r); outtextxy(x,y,s.sout());}

void DrawSquare(int r,int d)
 {
	line(320+cos((d+45 )*M_PI/180)*r,240-sin((d+45 )*M_PI/180)*r,
	     320+cos((d+135)*M_PI/180)*r,240-sin((d+135)*M_PI/180)*r);
	line(320+cos((d+135)*M_PI/180)*r,240-sin((d+135)*M_PI/180)*r,
	     320+cos((d+225)*M_PI/180)*r,240-sin((d+225)*M_PI/180)*r);
	line(320+cos((d+225)*M_PI/180)*r,240-sin((d+225)*M_PI/180)*r,
	     320+cos((d+315)*M_PI/180)*r,240-sin((d+315)*M_PI/180)*r);
	line(320+cos((d+315)*M_PI/180)*r,240-sin((d+315)*M_PI/180)*r,
	     320+cos((d+45 )*M_PI/180)*r,240-sin((d+45 )*M_PI/180)*r);
 }


void Draw_Icon(int x,int y,int r,int in=0)
 {
	if (in==3)
	 {
		setcolor(6); setfillstyle(1,14);
		bar(x,y+r/4,x+r+r/4,y+r);
		setfillstyle(1,6 );
		bar(x+r/20,y,x+r/2,y+r/4);
		return;
	 }
	else
	 {
		setcolor(15);  setfillstyle(1,15);
		bar(x,y,x+r/2+r/4,y+r/4);
		bar(x,y+r/4,x+r,y+r);
		line(x+r/2+r/4,y,x+r,y+r/4);
		floodfill(x+r/2+r/4+1,y+r/4-1,15);
		setcolor(7);
		line(x+r/2+r/4,y,x+r/2+r/4,y+r/4);
		line(x+r/2+r/4,y+r/4,x+r,y+r/4);
	 }
	if (in==1)
	 {
		int i;setcolor(0);
		for (i=1; i<4; i++) line(x+r/4,y+r/4*i,x+r-r/4,y+r/4*i);
		return;
	 }
	if (in==2)
	 {Draw_Str(x+r/4,y+r/4,r/10,"P"); return;}
 }
class Matrix
 {
	private:
		void*m;
	public :
		Matrix();
		void Get(int,int,int,int);
		void Put(int,int);
		void Del();
		~Matrix();
 };
Matrix::Matrix():m(0){}
void Matrix::Get(int x,int y,int w,int h)
 {
	unsigned size=imagesize(x,y,x+w,y+h);
	if (size!=0xffff) m=malloc(size);
	 else {cout<<"Error of memory!!!"; m=0; return;}
	getimage(x,y,x+w,y+h,m);
 }
void Matrix::Put(int x,int y)
 {if (m) putimage(x,y,m,COPY_PUT);}
void Matrix::Del()
 {if (m) free(m);}
Matrix::~Matrix()
 {Del();}

class Button
 {
	private:
		char str[25]; int x,y,w,h,state;
	public :
		void DrawON(int);
		void DrawOFF();
		Button(char*,int,int,int,int,int=1);
		Button(Ucs &,int,int,int,int,int=1);
		int  Get(mousestate&);
			void Put(int,int,int,int,int=1);
		void Put(char*);
		void Put(Ucs &);
		void Draw (mousestate&);
		void ofn(int);
 };

void Button::DrawOFF()
 {
	setcolor(7); rectangle(x,y,x+w,y+h);
	setfillstyle(1,8); bar(x+1,y+1,x+w-1,y+h-1);
	settextjustify(1,1); outtextxy(x+w/2,y+h/2,str);
 }
void Button::DrawON(int flag)
 {
	int c1=15,c2=8; if (flag) {c1=8; c2=15;}
	setfillstyle(1,7); bar(x+1,y+1,x+w-1,y+h-1);
	setcolor(c1);  line(x,y,x+w,y);     line(x,y,x,y+h);
	setcolor(c2);  line(x+w,y+h,x,y+h); line(x+w,y+h,x+w,y);
	settextjustify(1,1); setcolor(0); outtextxy(x+w/2,y+h/2,str);
 }

Button::Button(char* st,int xt,int yt,int wt,int ht,int s):
x(xt),y(yt),w(wt),h(ht),state(s)
 {strcpy(str,st);}
Button::Button(Ucs & st,int xt,int yt,int wt,int ht,int s):
x(xt),y(yt),w(wt),h(ht),state(s)
 {strcpy(str,st.sout());}
int  Button::Get(mousestate& m)
 {return m.x>=x && m.x<=x+w && m.y>=y && m.y<=y+h && m.b==1 && state;}
void Button::Put(int xt,int yt,int wt,int ht,int s)
 {x=xt; y=yt; w=wt; h=ht; state=s;}
void Button::Put(char* st)
 {strcpy(str,st);}
void Button::Put(Ucs&  st)
 {strcpy(str,st.sout());}
void Button::Draw(mousestate& m)
 {
	if (!state) {DrawOFF(); return;}
	DrawON(m.x>=x && m.x<=x+w && m.y>=y && m.y<=y+h && m.b==1);
 }
void Button::ofn(int flag)
 {state=flag;}