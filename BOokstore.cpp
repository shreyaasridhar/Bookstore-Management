#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class book
{
	char title[50],auth[50],genre[20];
	int year;
	protected:
		int quantity,price,sno,totprice;
	public:
		book()
		{	
			totprice=0;
		}
		void changeq()
		{
			--quantity;
		}
		void buy();
		class badno{};
		class Noauth{};
		class Nogen{};
		void view();
		void display();
		void copy();
		int retprice()
		{
			return price;
		}
}t;


void book::copy()
{		
	book a;
	int k=2;
	fstream f,g,h,e;
	f.open("inventory.dat",ios::out|ios::in|ios::binary);
	e.open("title.txt",ios::out|ios::in);
	g.open("auth.txt",ios::out|ios::in);
	h.open("genre.txt",ios::out|ios::in);
	int z=1;
	while(!e.eof()&&!g.eof())
	{
		a.sno=z++;
		k++;
		if(k>10)
		{
			k=4;
		}
		e.getline(a.title,50);
		g.getline(a.auth,50);
		h.getline(a.genre,20);
		a.year=2000+k;
		a.price=300+k*20;
		a.quantity=k;
		f.write(reinterpret_cast<char*>(&a),sizeof(a));
	}

	e.close();
	f.close();
	g.close();
	h.close();
}


void book::display()
{
	cout<<endl<<endl<<sno<<".\n";
	cout<<"\nTitle: "<<title;
	cout<<"\nAuthor: "<<auth;
	cout<<"\nGenre: "<<genre;
	cout<<"\nPrice: Rs."<<price;
	cout<<"\nYear: "<<year;
	cout<<"\nQuantity available: "<<quantity;
}


void book::view()
{
	ifstream data("inventory.dat",ios::binary|ios::in);
	cout<<"\n1.View all Titles\nView by:\n2.Author Name (by letter)\n3.Genre\nEnter Choice: ";
	int n;
	cin>>n;
	if(n==1)
	{
		int i=1;
		cout<<"\nDisplaying Title:";
		book s;
		data.read(reinterpret_cast<char*>(&s),sizeof(s));
		while(!data.eof())
		{
			cout<<"\n"<<i++<<"."<<s.title;
			data.read(reinterpret_cast<char*>(&s),sizeof(s));
		}
	}
	else if(n==2)
	{
		char c;
		int flag=0;
		cout<<"\nEnter Author's first letter: ";
		cin>>c;
		book s;
		data.read(reinterpret_cast<char*>(&s),sizeof(s));
		while(!data.eof())
		{
			if(c==s.auth[0])
			{
				flag=1;
				s.display();
			}
			data.read(reinterpret_cast<char*>(&s),sizeof(s));
		}
		if(flag==0)
		{
			throw Noauth();
		}
	}		
	else if(n==3)
	{
		int flag=0;
		char str[50];
		cout<<"\nEnter Genre: ";
		cin>>str;
		while(data)
		{
			book s;
			data.read(reinterpret_cast<char*>(&s),sizeof(s));
			if(strcmp(s.genre,str)==0)
			{
				flag=1;
				s.display();
			}
		}
		if(flag==0)
		{
			throw Nogen();
		}
	}
	else 
		throw badno();
	data.close();
}


void book::buy()
{
	int n,i=0,x;
	char y;	
	book s1;
	view();
	cont:
	cout<<"\n\n\nEnter book code(1/2/..): ";
	cin>>n;
	fstream ifile("inventory.dat",ios::binary|ios::in|ios::out);
	ifile.seekg(((n-1)*sizeof(s1)),ios::beg);
	ifile.read(reinterpret_cast<char*>(&s1),sizeof(s1));
	s1.display();
	totprice+=s1.retprice();
	s1.changeq();
	ifile.seekp(((n-1)*sizeof(s1)),ios::beg);	
	ifile.write(reinterpret_cast<char*>(&s1),sizeof(s1));
	cout<<"\n\nTotal price till now: Rs."<<totprice;
	ifile.close();
	i++;
	cout<<"\nContinue?";
	cin>>y;
	if(y=='Y'||y=='y')
	goto cont;
	else
	{
		if(i=1) badno();
		cout<<"\nTotal price of all books: Rs."<<totprice<<"\n\n********Have a GREAT DAY!!!********";	
	}
}

int main()
{
	cout<<"\n\n*****************WELCOME TO THE BOOK STORE*********************\n\n";
	t.copy();
	book t1;
	
	try
	{
		t1.buy();	
	}
	catch(book::badno)
	{
		cout<<"\n Number out of bounds!!Exiting...";
	}
		catch(book::Noauth)
	{
		cout<<"\nNo authors found for this letter!";
	}	catch(book::Nogen)
	{
		cout<<"\nNo books in this genre!";
	}
	return 0;
}
