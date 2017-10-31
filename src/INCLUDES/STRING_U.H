

//======================Ucs================================================
class Ucs
 {
	private:
		int len;
		char* p;
	public :
		Ucs();
		Ucs(const char*);
		Ucs(const Ucs&);
		~Ucs();
		int   PosL(char*);
		int   PosR(char*);
		int   Len();
		void  Show();
		char* sout();
		Ucs   Copy(int,int);
		Ucs     operator+ (Ucs&);
		Ucs&    operator= (Ucs&);
		Ucs&    operator= (char*  );
		void       operator+=(Ucs&);
		friend int operator==(Ucs&,Ucs&);
		friend int operator!=(Ucs&,Ucs&);
		friend int operator> (Ucs&,Ucs&);
		friend int operator< (Ucs&,Ucs&);
		friend ostream& operator<<(ostream&,Ucs&);
 };
//Functions-------------------------------------------------------------------
Ucs::Ucs()
 {len=0; p=new char[len+1]; p[0]=0;}
Ucs::Ucs(const char* s)
 {len=strlen(s); p=new char[len+1]; strcpy(p,s);}
Ucs::Ucs(const Ucs& s)
 {len=s.len; p=new char[len+1]; strcpy(p,s.p);}
Ucs::~Ucs()
 {delete []p;}
int  Ucs::PosL(char* s)
 {
	int rp=0,i=0,j=0;
	while(p[i] && !rp)
	 {
		if (p[i]==s[j])
		 {
			rp=i+1;
			while(p[i]==s[j] && j<strlen(s)) {i++; j++;}
		 }
		 else i++;
		if (j!=strlen(s)) {rp=0; j=0;}
	 }
	return rp;
 }
int  Ucs::PosR(char* s)
 {
	int rp=0,i=len-1,j=strlen(s)-1;
	while(p[i] && !rp)
	 {
		if (p[i]==s[j])
		 {
			rp=i+1;
			while(p[i]==s[j] && j>0) {i--; j--;}
		 }
		 else i--;
		if (j>0) {rp=0; j=0;}
	 }
	return rp;
 }
int  Ucs::Len()
 {return len;}
void Ucs::Show()
 {cout<<p;}
char* Ucs::sout()
 {return p;}
Ucs Ucs::Copy(int pt,int k)
 {
	char* str=new char[k+1]; int i,j;
	for (i=pt,j=0; i<pt+k && i<len; i++,j++)
	 str[j]=p[i]; str[j]=0;
	Ucs temp(str); delete[] str; return temp;
 }
//Operators-------------------------------------------------------------------
Ucs Ucs::operator+ (Ucs& s)
 {
	Ucs temp; temp.len=len+s.len;
	temp.p=new char[temp.len+1];
	strcpy(temp.p,s.p); strcat(temp.p,p);
	return temp;
 }
void   Ucs::operator+=(Ucs& s)
 {
	Ucs temp(*this);
	delete[] p; len+=s.len;
	p=new char[len+1]; strcpy(p,temp.p);
	strcat(p,s.p);
 }
ostream& operator<<(ostream& os,Ucs& s)
 {os<<s.p; return os;}
Ucs& Ucs::operator=(Ucs& s)
 {
	if(this==&s)return *this;
	delete [] p; len=s.len;
	p=new char[len+1]; strcpy(p,s.p);
	/*p=s.p; len=s.len;*/ return *this;
 }
Ucs& Ucs::operator=(char* s)
 {len=strlen(s); p=new char[len+1]; strcpy(p,s); return *this;}
int operator==(Ucs& s1,Ucs& s2)
 {return !(strcmp(s1.p,s2.p));}
int operator!=(Ucs& s1,Ucs& s2)
 {return !(s1==s2);}
int operator> (Ucs& s1,Ucs& s2)
 {return strcmp(s1.p,s2.p)>0;}
int operator< (Ucs& s1,Ucs& s2)
 {return strcmp(s1.p,s2.p)<0;}
//End-------------------------------------------------------------------------