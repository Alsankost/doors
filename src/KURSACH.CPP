	# include <iostream.h>
# include <graphics.h>
# include <process.h>
# include <iomanip.h>
# include <fstream.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <ctype.h>
# include <conio.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <dos.h>
# include <dir.h>
# include <io.h>
# include "C:/KURS/INCLUDES/MOUSE.H"
# include "C:/KURS/INCLUDES/STRING_U.H"
# include "C:/KURS/INCLUDES/INTF.H"
# include "C:/KURS/INCLUDES/LIST_D.H"

//OPOTIONS
int O_ws=1,O_b=1,FD=0;

int operator==(struct time& t1,struct time& t2)
 {return  t1.ti_hour==t2.ti_hour &&
		 t1.ti_min ==t2.ti_min  && t1.ti_sec==t2.ti_sec;}
int operator!=(struct time& t1,struct time& t2)
 {return !(t1==t2);}

char SO[40],*DISK;  Ucs SU("");

void LoadScreen()
 {
	int i=0,r=340/100*i,d=360/100*i;
	for (i=0; i<=100; i++)
	 {
		setcolor(16); DrawSquare(r,d);
		r=340/100.0*(i-1); d=360/100.0*i;
		setcolor(15); DrawSquare(r,d); delay(30);
	 }
	settextjustify(1,1); settextstyle(0,0,20);
	for (i=20; i>10; i--)
	 {
		setcolor(11); outtextxy(322,242,"DOORS");
		settextstyle(0,0,i);
		setcolor(4); outtextxy(320,240,"DOORS"); delay(20);
	 }

 }

struct time T,Tt;
void TimeShow(int x,int y)
 {
	gettime(&T); char stm[3];
	if (T!=Tt)
	 {
		setfillstyle(1,0); bar(x,y,x+71,y+8); setcolor(4);
		itoa(T.ti_hour,stm,10); strcpy(SO,stm); strcat(SO,":");
		itoa(T.ti_min ,stm,10); strcat(SO,stm); strcat(SO,":");
		itoa(T.ti_sec ,stm,10); strcat(SO,stm);
		outtextxy(x+6,y+1,SO); Tt=T;
	 }
 }

int Menu()
 {
	Button B_exit("< EXIT" ,10 ,438,50,20),
		 B_fmop("FILES"  ,575,5  ,60,60),
		 B_info("INFO"   ,510,5  ,60,60),
		 B_opts("OPTIONS",445,5  ,60,60),
		 B_wson("ON"     ,445,80 ,30,14),
		 B_wsof("OFF"    ,475,80 ,30,14),
		 B_bkon("ON"     ,445,109,30,14),
		 B_bkof("OFF"    ,475,109,30,14); B_opts.ofn(FD);
	B_wsof.ofn(O_ws); B_wson.ofn(!O_ws);
	B_bkof.ofn(O_b);  B_bkon.ofn(!O_b);
	char ch=0,mxy[4]; mousestate m={0,0,0},mt={0,0,1}; int opt=0;
	settextjustify(1,1); setfillstyle(1,8); bar(0,0,640,480);
	settextstyle(0,0,14);
	if (O_b)
	 {
		setcolor(0); outtextxy(322,242,"DOORS");
		setcolor(4); outtextxy(320,240,"DOORS");
	 }
	setfillstyle(1,8); settextjustify(0,2); settextstyle(0,0,1);
	MoveMouseCursor(320,240); setcolor(15); rectangle(1,468,639,480);
	setfillstyle(1,7); floodfill(2,469,15); setfillstyle(1,0);
	bar(577,7,637 ,67); bar(512,7,572,67);  bar(447,7,507,67);
	while (ch!=27)
	 {
		do
		 {
			if (kbhit()) ch=getch(); else ch=0;
			switch (ch)
			 {
				case 27: return 0;
			 }
			if (m.x!=mt.x || m.y!=mt.y)
			 {
				MHide(); setfillstyle(1,0); bar(10,470,122,478);
				setcolor(4); itoa(m.x,mxy,10); strcpy(SO,"x:");
				strcat(SO,mxy); outtextxy(15,471,SO);
				itoa(m.y,mxy,10); strcpy(SO,"y:"); strcat(SO,mxy);
				outtextxy(80,471,SO); mt.x=m.x; mt.y=m.y; MShow();
			 }
			TimeShow(559,470);
			getmousestate(m);
			//drawing button
			if (m.b!=mt.b)
			 {
				MHide(); B_exit.Draw(m); B_fmop.Draw(m);
					   B_opts.Draw(m); B_info.Draw(m);
				if (opt)
				 {
					B_wson.Draw(m); B_wsof.Draw(m);
					B_bkon.Draw(m); B_bkof.Draw(m);
				 }
				settextjustify(0,2); delay(100);
				mt=m; MShow();
			 }
		 }
		while (m.b!=1);
		if (B_exit.Get(m)) return 0;
		if (B_fmop.Get(m)) return 1;
		if (B_opts.Get(m))
		 {
			if (opt)
			 {opt=0; setfillstyle(1,8); bar(435,68,517,133);}
			 else
			  {
				opt=1; setfillstyle(1,0); settextjustify(1,1);
				setcolor(4); outtextxy(475,73,"load screen");
				outtextxy(475,102,"background"); bar(447,82,507,96);
				bar(447,111,507,125); settextjustify(0,2);
			  }
			 delay(100);
		 }
		if (B_wson.Get(m) && opt)
		 {O_ws=1; B_wson.ofn(0); B_wsof.ofn(1);}
		if (B_wsof.Get(m) && opt)
		 {O_ws=0; B_wsof.ofn(0); B_wson.ofn(1);}
		if (B_bkon.Get(m) && opt)
		 {O_b=1; B_bkon.ofn(0); B_bkof.ofn(1);}
		if (B_bkof.Get(m) && opt)
		 {O_b=0; B_bkof.ofn(0); B_bkon.ofn(1);}
	 }
 }

void SDisk()
 {
	delete []DISK; char c; int i=0,kol=0; DIR* d;
	for (c='A'; c<='Z'; c++) {SO[0]=c; SO[1]=0; strcat(SO,":/");
	d=opendir(SO); if (d) kol++; closedir(d);}  DISK=new char[kol];
	for (c='A'; c<='Z'; c++) {SO[0]=c; SO[1]=0; strcat(SO,":/");
	d=opendir(SO); if (d) {DISK[i]=c; i++;} closedir(d);} DISK[i]=0;
 }

void WindInfoF(int,int,DFI&);
void WindError(int,int);
int  WindQuest(int,int,char*);
char WindMakeD(int,int);
Ucs  WindInput(int,int,char*);

void Draw_DF(int x,int y,int r,DFI& df)
 {
	Draw_Icon(x,y,r,df.type); setcolor(7);
	Draw_Str(x+r*2,y+r/2,r/10,df.name);
 }
void ReadDirL(Ucs& dir,List& lfd)
 {
	struct ffblk f; int flag; DFI df; Ucs s;
	flag=findfirst(dir.sout(),&f,FA_DIREC|FA_RDONLY|FA_ARCH|FA_HIDDEN|FA_SYSTEM);
	while (!flag)
	 {s=f.ff_name; df.Init(s,f.ff_fsize); lfd.AddBack(df); flag=findnext(&f);}
 }/*
int  DelDir(Ucs& dir)
 {
	if (rmdir(dir.sout()))
	 {
		List f; ReadDirL(Ucs("/*.*")+dir,f);
		int i,k=f.kol_element(); DFI buf;
		for (i=4; i<=k; i++)
		 {
			f.lout(i,buf);
			if (remove((buf.GetN()+Ucs("/")+dir).sout())) return 1;
		 }
		rmdir(dir.sout());
		 } else return 0;
	return 1;
 }*/
int CopyFile(Ucs& fp1,Ucs& fp2,long size)
 {
	ofstream fout(fp2.sout(),ios::binary);
	ifstream fin (fp1.sout(),ios::binary); char buf;
	if (!fin || !fout) return 0;
	Matrix Mt; Mt.Get(268,200,106,150); char ch=0; long r=0;
	setfillstyle(1,7); bar(268,200,374,250);
	setcolor(0); rectangle(268,200,374,250);
			 rectangle(270,210,372,238);
	outtextxy(288,202,"Copying..");
	outtextxy(283,240,"[Esc]=Stop");
	setfillstyle(5,14);
	while (fin.read((char*)&buf,sizeof(buf)) && ch!=27)
	 {
		fout.write((char*)&buf,sizeof(buf));
		bar(271,211,100.0*r/size+271,237);
		if (kbhit()) ch=getch(); r++;
	 }
	fin.close(); fout.close();
	if (ch!=27) {Mt.Put(268,200); return 1;}
	 remove(fp2.sout()); Mt.Put(268,200); return 0;
 }
int ReFile(Ucs& path)
 {ifstream fin(path.sout()); if (!fin) return 0; else return 1;}
int PFileManager(Ucs& dir1,Ucs& dir2)
 {
	Ucs BUF_F(""); long SBF=0;
	List files1,files2; mousestate m={0,0,0},mt={0,0,1};
	Button B_exit ("X",630,0,10,10),
		 B_down1("",309,459,9,9),     B_up1("",309,69,9,9),
		 B_down2("",629,459,9,9),     B_up2("",629,69,9,9),
		 B_open1("OPEN",10 ,20,40,20), B_back1("<<",55 ,20,20,20),
		 B_open2("OPEN",330,20,40,20), B_back2("<<",375,20,20,20),
		 B_info1("i",120,20,20,20),    B_info2("i" ,440,20,20,20),
		 B_cdir1("NEW",145,20,30,20),  B_cdir2("NEW",465,20,30,20),
		 B_delt1("X",180,20,20,20),    B_delt2("X",500,20,20,20),
		 B_cutf1(">",215,20,10,20),    B_cutf2("<",535,20,10,20),
		 B_copy1("C",225,20,10,20),    B_copy2("C",545,20,10,20),
		 B_past1("P",235,20,10,20),    B_past2("P",555,20,10,20),
		 B_disk1(dir1.Copy(0,dir1.PosL("/")-1),80 ,20,20,20),
		 B_disk2(dir2.Copy(0,dir2.PosL("/")-1),400,20,20,20),
		 B_clrbuf("CLEAR",302,4,42,10); MoveMouseCursor(320,240);
	int lc1=1,lct1=-1,lc2=1,lct2=-1,i,j,k1,k2,tp=9,cp=1,E1=1,E2=1,fr1=0,fr2=0;
	char ch=0,mxy[4]; DFI buf;      setcolor(15);
	rectangle(0,68,319,468);      rectangle(319,68,639,468);
	line(308,68,308,468);         line(628,68,628,468);
	setfillstyle(2,8);
	floodfill(309,69,15);         floodfill(629,69,15);
	setfillstyle(tp,cp);
	floodfill(307,69,15);         floodfill(627,69,15);
	rectangle(0,0,639,68);        rectangle(0,468,639,480);
	setfillstyle(1,7);
	floodfill(10,10,15);          floodfill(10,469,15);
	setfillstyle(1,0);
	bar(10,57,300,65);            bar(330,57,620,65);
	bar(10, 5,300,13);		setcolor(4);
	outtextxy(12 ,58,     (dir1.Copy(0,35)).sout());
	outtextxy(332,58,     (dir2.Copy(0,35)).sout());
	outtextxy( 12, 6,(BUF_F.Copy(0,35)).sout());
	ReadDirL(dir1,files1); ReadDirL(dir2,files2);
	k1=files1.kol_element(); k2=files2.kol_element();
	//Main while:
	while (ch!=27)
	 {
		//Activated button:
		B_open1.ofn(E1>=0); B_open2.ofn(E2>=0);
		B_info1.ofn(E1>=0); B_info2.ofn(E2>=0);
		B_back1.ofn(dir1.PosL("/")!=dir1.PosR("/"));
		B_back2.ofn(dir2.PosL("/")!=dir2.PosR("/"));
		files1.lout(E1,buf);
		B_copy1.ofn(E1>=0 && buf.GetT()!=3);
		B_cutf1.ofn(dir1!=dir2 && E1>=0 && buf.GetT()!=3);
		files2.lout(E2,buf);
		B_copy2.ofn(E2>=0 && buf.GetT()!=3);
		B_cutf2.ofn(dir1!=dir2 && E2>=0 && buf.GetT()!=3);
		B_past1.ofn(BUF_F.Copy(0,BUF_F.PosR("/"))!=dir1.Copy(0,dir1.PosR("/")) && BUF_F.Len()>0);
		B_past2.ofn(BUF_F.Copy(0,BUF_F.PosR("/"))!=dir2.Copy(0,dir2.PosR("/")) && BUF_F.Len()>0);
		//reversion file in buffer:
		if (!ReFile(BUF_F)) BUF_F="";
		//restarting window 1:
		settextjustify(0,2);
		if (lc1!=lct1) {setfillstyle(tp,cp); bar(2,69,307,468);}
		if (lc1!=lct1 && k1>0)
		 {
			setfillstyle(2,8);
			if (k1>20)
			 {
				bar(309,((long(lct1)*100)/k1)*3.8+80,
				    318,((long(lct1)*100)/k1)*3.8+((2000)/k1)*3.8+81);
				setfillstyle(5,14);
				bar(309,((long(lc1 )*100)/k1)*3.8+80,
				    318,((long(lc1 )*100)/k1)*3.8+((2000)/k1)*3.8+81);
			 }
			 else bar(309,80,318,458);
			for (i=lc1; (k1<=20 && i<=k1) ||
			    (k1>20 && i<lc1+20); i++)
			 {files1.lout(i,buf); Draw_DF(10,70+20*(i-lc1),15,buf);}
			lct1=lc1;
		 }
		//restarting window 2:
		if (lc2!=lct2) {setfillstyle(tp,cp); bar(321,69,627,468);}
		if (lc2!=lct2 && k2>0)
		 {
			setfillstyle(2,8);
			if (k2>20)
			 {
				bar(629,((long(lct2)*100)/k2)*3.8+80,
				    638,((long(lct2)*100)/k2)*3.8+((2000)/k2)*3.8+81);
				setfillstyle(5,14);
				bar(629,((long(lc2 )*100)/k2)*3.8+80,
				    638,((long(lc2 )*100)/k2)*3.8+((2000)/k2)*3.8+81);
			 }
			 else bar(629,80,638,458);
			for (i=lc2; (k2<=20 && i<=k2) ||
			    (k2>20 && i<lc2+20); i++)
			 {files2.lout(i,buf); Draw_DF(330,70+20*(i-lc2),15,buf);}
			lct2=lc2;
		 }
		//control part:
		MShow();
		do
		 {
			if (kbhit()) ch=getch();
			 else ch=0;
			switch (ch)
			 {
				case 27: return 0;
			 }
			if (m!=mt)
			 {
				MHide(); setfillstyle(1,0); bar(10,470,122,478);
				setcolor(4); itoa(m.x,mxy,10); strcpy(SO,"x:");
				strcat(SO,mxy); outtextxy(15,471,SO);
				itoa(m.y,mxy,10); strcpy(SO,"y:"); strcat(SO,mxy);
				outtextxy(80,471,SO); mt=m; MShow();
			 }
			TimeShow(559,470);
			getmousestate(m);
			//drawing button
			if (m.b!=mt.b)
			 {
				MHide(); B_exit.Draw(m);
				B_down1.Draw(m);   B_up1.Draw(m);
				B_down2.Draw(m);   B_up2.Draw(m);
				B_open1.Draw(m); B_open2.Draw(m);
				B_back1.Draw(m); B_back2.Draw(m);
				B_info1.Draw(m); B_info2.Draw(m);
				B_disk1.Draw(m); B_disk2.Draw(m);
				B_cdir1.Draw(m); B_cdir2.Draw(m);
				B_delt1.Draw(m); B_delt2.Draw(m);
				B_cutf1.Draw(m); B_cutf2.Draw(m);
				B_copy1.Draw(m); B_copy2.Draw(m);
				B_past1.Draw(m); B_past2.Draw(m);
				B_clrbuf.Draw(m);
				settextjustify(0,2);
				delay(100); mt=m; MShow();
			 }
		 }
		while (m.b!=1);
		//reaction button:
		if (B_exit.Get(m) ) {return 0;}
		if (B_down1.Get(m)) if (lc1<k1-20) lc1++;
		if (B_down2.Get(m)) if (lc2<k2-20) lc2++;
		if (B_up1.Get(m)  ) if (lc1>1)     lc1--;
		if (B_up2.Get(m)  ) if (lc2>1)     lc2--;
		if (B_open1.Get(m))
		 {
			files1.lout(E1,buf);
			switch (buf.GetT())
			 {
				case 3: dir1=dir1.Copy(0,dir1.Len()-3);
					  dir1+=Ucs("/*.*")+buf.GetN();
					  setfillstyle(1,0); bar(10,57,300,65);
					  setcolor(4); fr1=1;
					  outtextxy(12,58,(dir1.Copy(0,35)).sout());
					 break;
				case 1: SU=buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1);
					  return 1;
				case 2: SU=buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1);
					  return 2;
			 }
			delay(200);
		 }
		if (B_open2.Get(m))
		 {
			files2.lout(E2,buf);
			if (buf.GetT()==3)
			switch (buf.GetT())
			 {
				case 3: dir2=dir2.Copy(0,dir2.Len()-3);
					  dir2+=Ucs("/*.*")+buf.GetN();
					  setfillstyle(1,0); bar(10,57,300,65);
					  setcolor(4); fr2=1;
					  outtextxy(12,58,(dir1.Copy(0,35)).sout());
					 break;
				case 1: SU=buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1);
					  return 1;
				case 2: SU=buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1);
					  return 2;
			 }
			delay(200);
		 }
		if (B_back1.Get(m))
		 {
			for (i=0; i<2; i++) dir1=dir1.Copy(0,dir1.PosR("/")-1);
			dir1+=Ucs("/*.*"); fr1=1; setfillstyle(1,0);
			bar(10,57,300,65); setcolor(4);
			outtextxy(12 ,58,(dir1.Copy(0,35)).sout()); delay(200);
		 }
		if (B_back2.Get(m))
		 {
			for (i=0; i<2; i++) dir2=dir2.Copy(0,dir2.PosR("/")-1);
			dir2+=Ucs("/*.*"); fr2=1; setfillstyle(1,0);
			bar(330,57,620,65); setcolor(4);
			outtextxy(332,58,(dir2.Copy(0,35)).sout()); delay(200);
		 }
		if (B_info1.Get(m))
		 {files1.lout(E1,buf); WindInfoF(100,100,buf);}
		if (B_info2.Get(m))
		 {files2.lout(E2,buf); WindInfoF(420,100,buf);}
		if (B_disk1.Get(m))
		 {
			SO[0]=WindMakeD(100,100);
			if (SO[0])
			 {
				SO[1]=0; strcat(SO,":/*.*"); dir1=SO;
				setfillstyle(1,0); bar(10,57,300,65); setcolor(4);
				outtextxy(12 ,58,(dir1.Copy(0,35)).sout());
				B_disk1.Put(dir1.Copy(0,dir1.PosL("/")-1));
				fr1=1; delay(200);
			 }
		 }
		if (B_disk2.Get(m))
		 {
			SO[0]=WindMakeD(440,100);
			if (SO[0])
			 {
				SO[1]=0; strcat(SO,":/*.*"); dir2=SO;
				setfillstyle(1,0); bar(330,57,620,65); setcolor(4);
				outtextxy(332,58,(dir2.Copy(0,35)).sout());
				B_disk2.Put(dir2.Copy(0,dir2.PosL("/")-1));
				fr2=2; delay(200);
			 }
		 }
		if (B_cdir1.Get(m))
		 {
			SU=WindInput(100,100,"NAME:");
			if ((SU.sout())[0])
			 if (mkdir((SU+dir1.Copy(0,dir1.PosL("*")-1)).sout()))
			  WindError(270,100); else
			   {fr1=1; if (dir2==dir1) fr2=1;}
		 }
		if (B_cdir2.Get(m))
		 {
			SU=WindInput(390,100,"NAME:");
			if ((SU.sout())[0])
			 if (mkdir((SU+dir2.Copy(0,dir2.PosL("*")-1)).sout()))
			  WindError(270,100); else
			   {fr2=1; if (dir1==dir2) fr1=1;}
		 }
		if (B_delt1.Get(m))
		 {
			files1.lout(E1,buf); if (E1>k1-1) E1--;
			SU=buf.GetN()+dir1.Copy(0,dir1.PosR("/"));
			if (E1>=0 && WindQuest(245,100,"CONFIRM REMOVAL"))
			 if (remove(SU.sout()) && rmdir(SU.sout()))
			  WindError(270,100);
			else {fr1=1; if (dir2==dir1) fr2=1;}
		 }
		if (B_delt2.Get(m))
		 {
			files2.lout(E2,buf); if (E2>k2-2) E2--;
			SU=buf.GetN()+dir2.Copy(0,dir2.PosR("/"));
			if (E1>=0 && WindQuest(245,100,"CONFIRM REMOVAL"))
			 if (remove(SU.sout()) && rmdir(SU.sout()))
			  WindError(270,100);
			else {fr2=1; if (dir1==dir2) fr1=1;}
		 }
		if (B_copy1.Get(m))
		 {
			files1.lout(E1,buf);
			BUF_F=buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1);
			SBF=buf.GetS();
			setfillstyle(1,0); bar(10,5,300,13); setcolor(4);
			outtextxy(12,6,(BUF_F.Copy(0,35)).sout());
		 }
		if (B_copy2.Get(m))
		 {
			files2.lout(E2,buf);
			BUF_F=buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1);
			SBF=buf.GetS();
			setfillstyle(1,0); bar(10,5,300,13); setcolor(4);
			outtextxy(12,6,(BUF_F.Copy(0,35)).sout());
		 }
		if (B_past1.Get(m))
		 {
			SU=BUF_F.Copy(BUF_F.PosR("/"),BUF_F.Len()-BUF_F.PosR("/")+1);
			if (BUF_F.Len()>0)
			 {
				if (CopyFile(BUF_F,SU+dir1.Copy(0,dir1.PosL("*")-1),SBF))
				 {fr1=1; fr2=1;} else WindError(270,100);
			 }
		 }
		if (B_past2.Get(m))
		 {
			SU=BUF_F.Copy(BUF_F.PosR("/"),BUF_F.Len()-BUF_F.PosR("/")+1);
			if (BUF_F.Len()>0)
			 {
				if (CopyFile(BUF_F,SU+dir2.Copy(0,dir2.PosL("*")-1),SBF))
				 {fr1=1; fr2=1;} else WindError(270,100);
			 }
		 }
		if (B_cutf1.Get(m))
		 {
			files1.lout(E1,buf);
			if (CopyFile(buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1),
			     buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1),buf.GetS()))
			 {
				if (E1>k1-1) E1--;
				remove((buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1)).sout());
				fr1=1; fr2=1;
			 }
		 }
		if (B_cutf2.Get(m))
		 {
			files2.lout(E2,buf);
			if (CopyFile(buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1),
			     buf.GetN()+dir1.Copy(0,dir1.PosL("*")-1),buf.GetS()))
			 {
				if (E2>k2-1) E2--;
				remove((buf.GetN()+dir2.Copy(0,dir2.PosL("*")-1)).sout());
				fr2=1; fr1=1;
			 }
		 }
		if (B_clrbuf.Get(m))
		 {
			BUF_F="";
			setfillstyle(1,0); bar(10,5,300,13); setcolor(4);
			outtextxy(12,6,(BUF_F.Copy(0,35)).sout());
		 }
		MHide();
		//restarting of list files:
		if (fr1)
		 {
			files1.DelAll(); ReadDirL(dir1,files1); lct1=-1;
			lc1=1; fr1=0; k1=files1.kol_element(); E1=1;
		 }
		if (fr2)
		 {
			files2.DelAll(); ReadDirL(dir2,files2); lct2=-1;
			lc2=1; fr2=0; k2=files2.kol_element(); E2=1;
		 }
		//reaction of list files:
		if (m.x>=0   && m.x<=309 && m.y>=68 &&
		   ((k1<=20 && m.y<=k1*20+68) || (k1>20 && m.y<=468)))
		 {
			if (E1>=0)
			 {
				setfillstyle(tp,cp);
				bar(8,69+20*(E1-lc1),306,87+20*(E1-lc1));
				files1.lout(E1,buf);
				Draw_DF(10,70+20*(E1-lc1),15,buf);
			 }
			E1=float(m.y-70)/20+lc1; files1.lout(E1,buf);
			Draw_DF(10,70+20*(E1-lc1),15,buf); setcolor(10);
			rectangle(8,69+20*(E1-lc1),306,87+20*(E1-lc1));
		 }
		if (m.x>=319 && m.x<=629 && m.y>=68 &&
		   ((k2<=20 && m.y<=k2*20+68) || (k2>20 && m.y<=468)))
		 {
			if (E2>=0)
			 {
				setfillstyle(tp,cp);
				bar(328,69+20*(E2-lc2),626,87+20*(E2-lc2)+1);
				files2.lout(E2,buf);
				Draw_DF(330,70+20*(E2-lc2),15,buf);
			 }
			E2=float(m.y-70)/20+lc2; files2.lout(E2,buf);
			Draw_DF(330,70+20*(E2-lc2),15,buf); setcolor(10);
			rectangle(328,69+20*(E2-lc2),626,87+20*(E2-lc2));
		 }
	 }
 }

void TextReader(Ucs file)
 {
	ifstream fin(file.sout(),ios::binary); int y=0,st=0,i=0,flag=1;
	if (!fin) {return;}
	mousestate m={0,0,0},mt={-1,-1,-1};
	Button B_exit("X",630,2,10,10),
		 B_down("",30 ,2,10,10),
		 B_up  ("",20 ,2,10,10);
	char ch=0,mxy[6],buf=0,wr[101];
	setcolor(15);
	rectangle(1,1,639,12);  rectangle(1,468,639,480);
	setfillstyle(1,7);
	floodfill(2,2,15);      floodfill(2,469,15);
	setcolor(4); settextjustify(2,2);
	SU=file.Copy(file.PosR("/"),file.Len()-file.PosR("/"));
	outtextxy(320,3,SU.sout()); settextjustify(0,2);
	while (ch!=27)
	 {
		i=0; y=0; setcolor(15); setfillstyle(1,0);
		MHide(); if (flag) bar(1,13,638,468);
		while (y<56 && flag)
		 {
			while (i<100 && fin.read((char*)&buf,sizeof(buf)))
			 wr[i++]=buf;
			wr[i]=0; outtextxy(4,y*8+18,wr); y++; i=0;
			if (fin.eof()) {flag=0; B_down.ofn(0);}
		 }
		B_up.ofn(st); if (flag) flag=0; MShow();
		do
		 {
			if (kbhit()) ch=getch(); else ch=0;
			switch (ch)
			 {
				case 27: return;
			 }
			if (m.x!=mt.x || m.y!=mt.y)
			 {
				MHide(); setfillstyle(1,0); bar(10,470,122,478);
				setcolor(4); itoa(m.x,mxy,10); strcpy(SO,"x:");
				strcat(SO,	mxy); outtextxy(15,471,SO);
				itoa(m.y,mxy,10); strcpy(SO,"y:"); strcat(SO,mxy);
				outtextxy(80,471,SO); mt.x=m.x; mt.y=m.y; MShow();
			 }
			TimeShow(559,470);
			getmousestate(m);
			//drawing button
			if (m.b!=mt.b)
			 {
				MHide(); B_exit.Draw(m); setcolor(16);
				B_up.Draw(m); B_down.Draw(m);
				settextjustify(0,2); delay(100); mt=m; MShow();
			 }
		 }
		while (m.b!=1);
		if (fin.eof())
		 {
			fin.close(); fin.open(file.sout(),0,ios::binary);
			fin.seekg(st);
		 }
		if (B_exit.Get(m)) return;
		if (B_up  .Get(m))
		 {st-=100; fin.seekg(st); flag=1; B_down.ofn(flag);}
		if (B_down.Get(m))
		 {st+=100; fin.seekg(st); flag=1;}
	 }
 }
//================MAIN!=======================================================
void main()
 {
	clrscr();// DFI hj; List file; Ucs dir("H:/*.*");
	ofstream TEST("TEMP.T");
	if (TEST) {FD=1; TEST.close(); remove("TEMP.T");} else FD=0;
	ifstream OPTS("OPTIONS.BIN",::ios::binary);
	if (OPTS)
	 {
		OPTS.read((char*)&O_ws,sizeof(O_ws));
		OPTS.read((char*)&O_b ,sizeof(O_b ));
		OPTS.close();
	 }
	int d=DETECT,rg=0,C=-1,Ct=-1; initgraph(&d,&rg,"C:/TurboC3/BGI");
	if (O_ws) LoadScreen(); Ucs path1,path2; SDisk(); SO[1]=0;
	SO[0]=DISK[0]; strcat(SO,":/*.*"); path1=SO; path2=SO;
	while (Ct)
	 {
		Ct=Menu();
		if (Ct==1) while (C)
		 {
			cleardevice(); MHide();
			C=PFileManager(path1,path2); MHide(); cleardevice();
			switch (C)
			 {
				case 1: TextReader(SU); break;
				case 2: spawnl(P_WAIT,SU.sout(),NULL);
					  if (errno==ENOMEM) WindError(270,100);
					  cout<<'\n'<<" <<Press any key>> "; getch();
					break;
			 }
		 }
		C=-1;
	 }
	//line(320,0,320,480); line(0,240,640,240);
	closegraph();
	if (FD)
	 {
		ofstream OPTS_R("OPTIONS.BIN",ios::binary);
		OPTS_R.write((char*)&O_ws,sizeof(O_ws));
		OPTS_R.write((char*)&O_b ,sizeof(O_b ));
	 }
	clrscr(); cout<<"DOORS v0.0.1a ||  ALeX"<<'\n'
			  <<"EXIT <=> [any key]"; getch();
	//cout<<DelDir("c:/ops");
	//SDisk(); cout<<DISK; getch();
 }
//================END=========================================================
void WindInfoF(int x,int y,DFI& f)
 {
	MHide();
	Matrix Mt; Mt.Get(x,y,100,100);
	mousestate m,mt; m.b=-1; Button B_ok("OK",x+30,y+78,40,20);
	setfillstyle(1,7); bar(x,y,x+99,y+99);
	setcolor(8); rectangle(x,y,x+99,y+99); setcolor(0);
	settextjustify(1,1); outtextxy(x+50,y+10,"INFO:");
	settextjustify(0,2); Draw_Str (x+10,y+20,1,Ucs("Name: "));
	Draw_Str(x+3,y+30,1,f.GetN()); outtextxy(x+10,y+50,"SIZE (B):");
	itoa(f.GetS(),SO,10); outtextxy(x+3,y+60,SO);
	MShow();
	do
	 {if (m.b!=mt.b) {B_ok.Draw(m); mt=m;} getmousestate(m);}
	while (!B_ok.Get(m));
	MHide(); Mt.Put(x,y); MShow();
 }

void WindError(int x,int y)
 {
	MHide();
	Matrix Mt; Mt.Get(x,y,100,100);
	mousestate m,mt; m.b=-1; Button B_ok("OK",x+30,y+75,40,20);
	setfillstyle(1,7); bar(x,y,x+99,y+99); setcolor(8);
	rectangle(x,y,x+99,y+99); setcolor(0); settextjustify(1,1);
	setcolor(4); outtextxy(x+50,y+10,"ERROR!");
	MShow();
	do
	 {if (m.b!=mt.b) {B_ok.Draw(m); mt=m;} getmousestate(m);}
	while (!B_ok.Get(m));
	MHide(); Mt.Put(x,y); MShow();
 }

int WindQuest(int x,int y,char* q)
 {
	Matrix Mt; char ch; Mt.Get(x,y,200,50); mousestate m,mt; mt.b=-1;
	Button B_ok("OK",x+5,y+25,40,20),B_no("NO",x+155,y+25,40,20);
	setfillstyle(1,7); bar(x,y,x+199,y+49); setcolor(8);
	rectangle(x,y,x+199,y+49); setcolor(0); settextjustify(1,1);
	outtextxy(x+100,y+15,q);
	do
	 {
		getmousestate(m); if (kbhit()) ch=getch(); else ch=0;
		if (m.b!=mt.b)
		 {
			MHide(); B_ok.Draw(m); B_no.Draw(m);
			mt=m; MShow();
		 }
		if (B_ok.Get(m) || ch==13) {MHide(); Mt.Put(x,y); return 1;}
		if (B_no.Get(m) || ch==27) {MHide(); Mt.Put(x,y); return 0;}
	 }
	while (1);
 }
Ucs WindInput(int x,int y,char* ots)
 {
	Matrix Mt; char ch,str[14]={0}; Mt.Get(x,y,150,55); Ucs s("");
	mousestate m,mt; mt.b=-1; Button B_ok("OK",x+55,y+30,40,20);
	int i=0,flag=1; setfillstyle(1,7); bar(x,y,x+149,y+54);
	setcolor(8); rectangle(x,y,x+149,y+54); settextjustify(1,1);
	setcolor(0); outtextxy(x+75,y+10,ots);
	do
	 {
		getmousestate(m);
		if (m.b!=mt.b) {MHide(); B_ok.Draw(m); MShow(); mt=m;}
		if (kbhit())
		 {
			ch=getch();
			if (ch!=' ' && ch!=13 && ch!=27 && ch!=8 && i<13)
			 {str[i]=ch; str[i+1]=0; i++; flag=1;}
			if (ch==8   && i>0) {str[--i]=0; flag=1;}
		 } else ch=0;
		if (flag)
		 {
			MHide(); setfillstyle(1,0); bar(x+10,y+15,x+140,y+25);
			setcolor(4); outtextxy(x+75,y+20,str); flag=0; MShow();
		 }
	 }
	while (!B_ok.Get(m) && ch!=13 && ch!=27); if (ch!=27) s=str;
	MHide(); Mt.Put(x,y); MShow(); return s;
 }
char WindMakeD(int x,int y)
 {
	MHide(); SDisk(); int i=0, k=strlen(DISK)-1; SO[0]=DISK[i]; SO[1]=0;
	Matrix M; M.Get(x,y,101,71); mousestate m,mt; mt.b=-1; setcolor(8);
	Button B_back("<", x+10,y+10,20,20), B_next(">",x+70,y+10,20,20),
		 B_ok  ("OK",x+30,y+40,40,20);
	setfillstyle(1,7); bar(x,y,x+100,y+70); rectangle(x,y,x+100,y+70);
	setfillstyle(1,0); bar(x+40,y+10,x+60,y+30); settextjustify(1,1);
	setcolor(4); outtextxy(x+50,y+22,SO); char ch;
	do
	 {
		MShow(); B_back.ofn(i>0); B_next.ofn(i<k);
		do
		 {
			getmousestate(m);
			if (kbhit()) ch=getch(); else ch=0;
			if (ch==27) return 0;
			if (m.b!=mt.b)
			 {
				MHide(); B_ok.Draw(m); B_back.Draw(m);
				B_next.Draw(m); MShow(); mt=m;
			 }
		 }
		while (m.b!=1 && ch!=13);
		if (B_back.Get(m)) if (i>0) i--;
		if (B_next.Get(m)) if (i<k) i++;
		MHide(); SO[0]=DISK[i]; SO[1]=0; setfillstyle(1,0); delay(200);
		bar(x+40,y+10,x+60,y+30); setcolor(4); outtextxy(x+50,y+22,SO);
	 }
	while (!B_ok.Get(m));
	M.Put(x,y); MShow(); settextjustify(0,2); return DISK[i];
 }