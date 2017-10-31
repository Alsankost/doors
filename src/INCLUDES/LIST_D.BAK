//=====================FILE TYPE STRUCTURE====================================
const int TFS=5;
struct FType
 {char s[TFS]; int type;};
FType MFT[]={{".TXT",1},{".CPP",1},{".PAS",1},{".H"  ,1},
		 {".EXE",2},{".COM",2},{".BAT",2},{".BAK",1},{"\0",0}};
//=====================DFI====================================================
class DFI
 {
	private:
		Ucs name; int type; long size;
	public :
		void Init(Ucs&,long);
		Ucs& GetN();
		int  GetT();
		long GetS();
		DFI&            operator= (DFI&);
		friend int      operator==(DFI&,DFI&);
		friend int      operator> (DFI&,DFI&);
		friend int      operator< (DFI&,DFI&);
		friend ostream& operator<<(ostream&,DFI&);
		friend void     Draw_DF(int,int,int,DFI&);
 };
//Function:-------------------------------------------------------------------
void DFI::Init(Ucs& nt,long st)
 {
	name=nt; int i;
	if (name.PosL("."))
	 {
		type=0;
		for (i=0; MFT[i].s[0]; i++)
		if (strlen(MFT[i].s)==name.Len()-name.PosL(".")+1 &&
		    name.PosL(MFT[i].s)) {type=MFT[i].type; break;};
	 }
	 else type=3;
	size=st;
 }
Ucs& DFI::GetN()
 {return name;}
int  DFI::GetT()
 {return type;}
long DFI::GetS()
 {return size;}
//Operators:------------------------------------------------------------------
DFI& DFI::operator=(DFI& df)
 {name=df.name; type=df.type; size=df.size; return *this;}
int operator==(DFI& df1,DFI& df2)
 {return df1.name==df2.name;}
int operator> (DFI& df1,DFI& df2)
 {return df1.name> df2.name;}
int operator< (DFI& df1,DFI& df2)
 {return df1.name< df2.name;}
ostream& operator<<(ostream& os,DFI& df)
 {os<<df.name; return os;}
//end=========================================================================

//======================LIST==================================================
typedef DFI item;
const int index = 5;
struct Node
{Node*pred; item data; Node*next;};
class List
 {
	private:
		Node *start, *end; int kol;
	public:
		List();
		~List();
		void AddFront(item);
		void AddBack(item);
		void delFront();
		void delBack();
		void del_elem(item);
		void del_number(int);
		int  kol_element();
		void Sort();
		void insert(item);
		/*void insert(int,item);
		int find(item); */
		void Show(char);
		int  lout(int,item&);
		void DelAll();
 };
//Function--------------------------------------------------------------------
List::List():start(0),end(0),kol(0){}
void List::AddFront(item x)
 {
	Node* temp=new Node; temp->data=x; temp->next=0; temp->pred=0;
	if (start==0) {start=end=temp; kol++; return;}
	temp->next=start; start=temp; kol++;
 }
void List::AddBack(item x)
 {
	Node* temp=new Node; temp->data=x; temp->next=0; temp->pred=0;
	if (start==0) {start=temp; end=temp; kol=1; return;}
	end->next=temp; end=temp; kol++;
 }
void List::delFront()
 {
	if (start==0) return; if(start==end)
	 {delete start; start=end=0; kol--; return;}
	Node* temp=start; start=start->next; delete temp; kol--;
 }
void List::delBack()
 {
	if (start==0) return; if(start==end)
	 {delete start; start=end=0; kol--; return;}
	Node*temp=start; while(temp->next!=end) {temp=temp->next;}
	delete end; end=temp; end->next=0; kol--;
 }
void List::del_elem(item x)
 {
	if(start==0) return; if(start->data==x)
	 {delFront(); kol--; return;} Node *current=start;
	Node *temp=0; while(current->next!=end)
	 {
		if(current->next->data==x)
		 {
			temp=current->next; current->next=current->next->next;
			delete temp; kol--; return;
		 }
		current=current->next;
	 }
	if (end->data==x) {delete end; end=current; end->next=0;}
	temp=current->next; kol--;
 }
void List::del_number(int n)
 {
	if (n<=0 && n>kol) {cout<<"Error"<<endl; return;}
	if(start==0) return; if(n==1) {delFront(); kol--; return;}
	int kol=1; Node *current=start; Node*temp=0;
	while(current->next!=end && kol<n-1)
	 {
		kol++; cout<<"        "<<kol<<"      "<<current->data<<endl;
		current=current->next;
	 }
	if(current->next!=end)
	 {
		temp=current->next; current->next=current->next->next;
		delete temp; kol--; return;
	 } kol++;
	if(kol==n) {delete end; kol--; end=current; end->next=0; return;}
	cout<<"Error num";
 }
int List::lout(int n,item& d)
 {
	if (n<=0 || n>kol) {cout<<(n<=0)<<" "<<(n>kol)<<endl; return 0;}
	if (start==0) return 0;// if (n==1) {d=start->data; return 1;}
	int k=1; Node *current=start;
	while (k<n)
	 {k++; current=current->next;}
	if(current!=end)
	 {d=current->data	; return 1;} k++;
	if(kol==n) {d=end->data; return 1;}
	cout<<"Error 2"; return 0;
 }
int List::kol_element()
 {return kol;}
void List::insert(item x)
 {
	if (start==0) return; if(start==end) {AddFront(x); return;}
	Node *current=start; Node *max=new Node; max->data=x;
	max->next=0; while (current->next!=end)
	 {
		if (current->next->data>max->data)
		 {current->next=max; max->next=current->next->next; kol--; return;}
		current=current->next;
	 }
	if(end->data>max->data)
	 {current->next=max; max->next=end; kol--; return;} AddBack(x);
 }
void List::Show(char ch)
 {
	if(start==0) {cout<<"γαβ®"<<endl; return;} Node *current=start;
	while(current!=0) {cout<<current->data<<ch; current=current->next;}
 }
void List::DelAll()
 {
	Node*current=start; Node*temp=0;
	while (current) {temp=current; current=current->next; delete temp;}
	start=0; end=0; kol=0;
 }
List::~List()
 {
	Node*current=start; Node*temp=0;
	while (current) {temp=current; current=current->next; delete temp;}
 }
//Other functions:------------------------------------------------------------
//End-------------------------------------------------------------------------