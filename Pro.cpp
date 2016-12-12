#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string.h>
#include<fstream>
using namespace std;

class dictionary;

int content()
{
	int choice;
	cout<<"\n\n\t\t\t? Binary Search Tree - DICTIONARY ?\a\n\n\t\t"
		<<"1:Enter Word.\t\t\t2.Search Meaning.\n\t\t3.Delete Word.\t\t\t4:Display Dictionary\n\t\t5.Delete Dictionary.\t\t6:Exit\n\n"
		<<"Enter Your Choice(1-6):";
	cin>>choice;
	return choice;
}

class node
{
	char word[1000],mean[4][3000];
	node *prev,*next;
	int cnt;
	friend dictionary;
};


class dictionary
{
	node *headnd;
	public:
	dictionary()
	{
		headnd=NULL;
	}
	void insertword();
	void displayword();
	void deleteword();
	void displaydictionary();
	void deletedictionary();
};

int main()
{
	dictionary d;
	int choice;
			//clrscr();
			system("cls");
	while(1)
	{
		choice=content();
		switch(choice)
		{
			case 1:d.insertword();
			break;
			case 2:d.displayword();
			break;
			case 3:d.deleteword();
			break;
			case 4:d.displaydictionary();
			break;
			case 5:d.deletedictionary();
			break;
			case 6:exit(0);
			getch();
			
			default:cout<<"\nInvalid Choice!";
		}//switch
	}//while
	return 0;
}//main


void dictionary :: insertword()
{
	node *newnd,*current;
	newnd=new node;
	int i;
	cout<<"Enter the word:";
	cin>>newnd->word;
	cout<<"How many meanings you want to insert (<5):\t";
	cin>>newnd->cnt;
	if(newnd->cnt>4)
	{
		cout<<"\nIt cannot store "<<newnd->cnt<<" meanings.";
		delete newnd;
		return;
	}
	for(i=0;i<newnd->cnt;i++)
	{
		cout<<"Enter the meaning "<<i+1<<"\t";
		cin>>newnd->mean[i];
	}
	// now this node should be placed in the DLL
	if(headnd==NULL)	// It is first node
	{
		headnd=newnd;
		headnd->next=NULL;
		headnd->prev=NULL;
		return;
	}
	if(strcmp(newnd->word,headnd->word)<0)
	{
		// place at the beginning
		newnd->next=headnd;
		newnd->prev=NULL;
		headnd->prev=newnd;
		headnd=newnd;
	return;
	}
	// now find position where node should be placed such that list is sorted
	for(current=headnd;current->next!=NULL;current=current->next)
	{
		if(strcmp(newnd->word,current->next->word)<0)
		{
			break; //to be placed after current
		}
	}
	if(current->next==NULL) // place at the end
	{
		current->next=newnd;
		newnd->prev=current;
		newnd->next=NULL;
	}
	else	//place in between
	{
		newnd->next=current->next;
		current->next=newnd;
		newnd->prev=current;
		newnd->next->prev=newnd;
	}
}


void dictionary :: displayword()
{
	node *current;
	int i,flag,c,j;
	char target[1000];
	if(headnd!=NULL)
	{
		cout<<"\nEnter the target you want to know?\t";
		cin>>target;
		for(current=headnd,flag=0,c=0;current!=NULL;current=current->next)
		{
			j=strcmp(target,current->word);
			c++;	//count the number of comparisons
			if(j==0)	// target found
			{
				cout<<"\nWORD\t";     for(i=1;i<=current->cnt;i++){cout<<"\tMEANING"<<i;}
				cout<<"\n"<<current->word<<" :";
				for(i=0;i<current->cnt;i++)
				{
					cout<<"\t\t"<<current->mean[i];
				}//for
				flag=1;
				break;
			}//if
		}//for
		if(flag==0)
		cout<<"\n\nWord not available in this Dictionary";
		cout<<"\n\nNumber of comparisons are "<<c;
	}//if
	else
	cout<<"\nDictionary is Empty";
}


void dictionary :: deleteword()
{
	node *current;
	char target[1000],opt;
	int flag=0;
	
	if(headnd!=NULL)
	{
		cout<<"\nEnter the word you want to delete\t";
		cin>>target;
		current=headnd;
		// check at beginning
		if(strcmp(target,headnd->word)==0)// first node contains target
		{
			headnd=headnd->next;
			delete headnd->prev;
			headnd->prev=NULL;
			cout<<"\nThe word is deleted....";
			return;
		}
		//search elsewhere
		for(current=headnd->next;current!=NULL;current=current->next)
		{
			if(strcmp(target,current->word)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			cout<<"\nThe word not found....";
			return;
		}
		//current points to node to be deleted
		if(current->next==NULL)	// last node
		{
			current->prev->next=NULL;
			delete current;
		}
		else	// in between
		{
			current->prev->next=current->next;
			current->next->prev=current->prev;
			delete current;
		}
		cout<<"\nThe word is deleted....";
		
	}//outer if
	else
	cout<<"\nDictionary is Empty";
}


void dictionary :: displaydictionary()
{
	node *current;
	int i;
				
	string filename="Dictionary.txt";
	ofstream outFile;
	outFile.open(filename.c_str());
	if(outFile.fail())
	{
		cout<<"The file was not opened"<<endl;
		exit(1);		
	}
	
	if(headnd==NULL)
	{
		cout<<"\nDictionary is Empty";
		return ;	
	}
	outFile<<"WORD \t\tMEANING-1\tMEANING-2\tMEANING-3\tMEANING-4\n";
	cout<<"\nWORD\t";     for(i=1;i<=current->cnt;i++){cout<<"\tMEANING"<<i;}
	for(current=headnd;current!=NULL;current=current->next)
	{
		cout<<"\n"<<current->word<<":";
		for(i=0;i<current->cnt;i++)
		{
		cout<<"\t\t"<<current->mean[i];
		}//for
		     {
				
				
				outFile<<current->word;
				for(i=0;i<current->cnt;i++)
				{
					outFile<<"\t\t"<<current->mean[i];
				}
				
				outFile<<endl;
		     }
				
		
	}//o for
	outFile.close();
	cout<<endl<<"Assassin's Dictionary is being created"<<endl;
}//displayDictionary


void dictionary :: deletedictionary()
{
	node *current;
	if(headnd!=NULL)
	{
		while(headnd!=NULL)
		{
			current=headnd;
			headnd=headnd->next;
			delete current;
		}
		cout<<"\nThe Dictionary is deleted";
	}
	else
	cout<<"\nDictionary is Empty";
}
