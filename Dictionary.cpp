#include <iostream>
#include <fstream>
#include <cstdlib>//need for exit()
#include <string.h>
#include <iomanip>

using namespace std;

class Dictionary;

////Dictionary menu
int content()
{
    int number;
    cout<<"\n\n\t\t\t\t? DICTIONARY ?\n\n\t\t"
        <<"1:Enter Word.\t\t\t2:Find Word Meaning.\n\n\t\t3:Delete Word.\t\t\t4:Display Dictionary\n\n\t\t5:Delete Dictionary.\t\t6:Exit\n\n"
        <<"Enter Your Choice(1-6):";
    cin>>number;
    return number;
}

//Dictionary mian function
class myDictionary
{
    char word[1000],mean[4][4000];//1000 words with  //4 types of meanings
    myDictionary *prev,*next;//ppointer for provious and next
    int count;
    friend Dictionary;//friend function for mapping
};

////Dictionary class
class Dictionary
{
    myDictionary *root;//pointer for root
public:
    Dictionary()
    {
        root=NULL;
    }
    void introduction();
    void insertword();
    void displayword();
    void deleteword();
    void displaydictionary();
    void deletedictionary();
};

//Dictionary mian function
int main()
{
    Dictionary d;//object of dictionary class
    int number;
	d.introduction();

    while(1)
    {
        number=content();
        switch(number)
        {
        case 1:
            d.insertword();
            break;
        case 2:
            d.displayword();
            break;
        case 3:
            d.deleteword();
            break;
        case 4:
            d.displaydictionary();
            break;
        case 5:
            d.deletedictionary();
            break;
        case 6:
            exit(0);

        default:
            cout<<"\nInvalid Choice!";
        }
    }
    return 0;
}

//Dictionary insert function
void Dictionary :: insertword()
{
    myDictionary *newnd,*current;//pointer for new and current node
    newnd=new myDictionary;//creating new node
    int i;
    cout<<"Enter the word:";
    cin>>newnd->word;//inserting new word to newnd

    cout<<"How many meanings you want to insert (<5):\t";
    cin>>newnd->count;//inserting how many meanings for new word to newnd->count

    if(newnd->count>4)
    {
        cout<<"\nIt cannot store "<<newnd->count<<" meanings.";
        delete newnd;
        return;
    }
    for(i=0; i<newnd->count; i++)
    {
        cout<<"Enter the meaning "<<i+1<<"\t";

        cin>>newnd->mean[i];//inserting meanings which is pointing to nwend->mean
    }
    
    if(root==NULL)	// It is first node
    {
        root=newnd;//direct
        root->next=NULL;//only one
        root->prev=NULL;//previous also null
        return;
    }
    if(strcmp(newnd->word,root->word)<0)
    {
        // place at the beginning
        newnd->next=root;//set new node next pointer to root
        newnd->prev=NULL;//set new node prev pointer to null
        root->prev=newnd;//root orev = newnode

        root=newnd;
        return;
    }
    // now find position where node should be placed such that list is sorted
    for(current=root; current->next!=NULL; current=current->next)
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

//Dictionary display word function
void Dictionary :: displayword()
{
    myDictionary *current;
    int i,flag,c,j;
    char target[1000];//which word users want to look for
    if(root!=NULL)
    {
        cout<<"\nEnter the target you want to know?\t";
        cin>>target;
        for(current=root,flag=0,c=0; current!=NULL; current=current->next)//condition for comparing current with root
        {
            j=strcmp(target,current->word);//comparing target with current word
            c++;	//count the number of comparisons
            if(j==0)	// target found
            {
                cout<<"\nWORD\t";
                //word and meanings showing in ouput
                for(i=1; i<=current->count; i++)
                {
                    cout<<"\tMEANING"<<i;
                }
                cout<<"\n\n"<<current->word<<" :";
                for(i=0; i<current->count; i++)
                {
                    cout<<"\t\t"<<current->mean[i];
                }
                flag=1;
                break;
            }
        }
        if(flag==0)//if flag is not increased
            cout<<"\n\nWord not available in this Dictionary";
        cout<<"\n\nNumber of comparisons are "<<c;//compare the word and meaning
    }
    else
        cout<<"\nDictionary is Empty";
}

//Dictionary delete word function
void Dictionary :: deleteword()
{
    myDictionary *current;
    char target[1000];//setting target as the users want to delete
    int flag=0;

    if(root!=NULL)// if root is not null
    {
        cout<<"\nEnter the word you want to delete\t";
        cin>>target;//enter the target
        current=root;//setting root as null

        // check at beginning
        if(strcmp(target,root->word)==0)// first node contains target
        {
            root=root->next;//setting root to root next
            delete root->prev;//deleting the root previous pointer
            root->prev=NULL;////setting root->prev to NULL
            cout<<"\nThe word is deleted....";
            return;
        }
        //search elsewhere
        for(current=root->next; current!=NULL; current=current->next)
        {
        if(strcmp(target,current->word)==0)//if any word match with target word
            {
                flag=1;
                break;
            }
        }
        if(flag==0)//if flag is not increased
        {
            cout<<"\nThe word not found....";
            return;
        }
        //current points to node to be deleted

        if(current->next==NULL)	// last node
        {
            current->prev->next=NULL;//?????
            delete current;
        }
        else	// in between
        {
            current->prev->next=current->next;//?????
            current->next->prev=current->prev;//?????
            delete current;
        }
        cout<<"\nThe word is deleted....";

    }
    else
        cout<<"\nDictionary is Empty";
}

//Dictionary display dictionary function
void Dictionary :: displaydictionary()
{
    myDictionary *current;
    int i;

    string filename="Dictionary.txt";//file for storage
    ofstream outFile;

    outFile.open(filename.c_str());//opening file
    if(outFile.fail())//checking if its open or not
    {
        cout<<"The file was not opened"<<endl;
        exit(1);
    }


    if(root==NULL)
    {
        cout<<"\nDictionary is Empty";
        return ;
    }
    outFile<<"WORD \t\tMEANING-1\tMEANING-2\tMEANING-3\tMEANING-4\n";
    cout<<"WORD \t\tMEANING-1\tMEANING-2\tMEANING-3\tMEANING-4\n";

    for(current=root; current!=NULL; current=current->next)//setting current to root
    {
   
        cout<<"\n"<<current->word<<":";//pointing current->word and putting word output

        for(i=0; i<current->count; i++)
        {
            cout<<"\t\t"<<current->mean[i];//pointing current->mean and putting meanings output
        }
        {


            outFile<<current->word;//storing words
            for(i=0; i<current->count; i++)
            {
                outFile<<"\t\t"<<current->mean[i];//storing meanings
            }

            outFile<<endl;
        }
        
    }

    outFile.close();//file storage closed
    cout<<endl<<"Assassin's Dictionary is being created"<<endl; //created dictionary
}

//Dictionary delete dictionary function
void Dictionary :: deletedictionary()
{
    myDictionary *current;
    if(root!=NULL)
    {
        while(root!=NULL)
        {
            current=root;//setting current as root
            root=root->next;//pointing root to root next
            delete current;//deleting every current node
        }
        cout<<"\nThe Dictionary is deleted";
    }
    else
        cout<<"\nDictionary is Empty";
}


void Dictionary :: introduction()
{
	cout<<"Group Name       : Assassin" <<endl;
	cout<<"Group Members    : MD. Jamiur Rahaman [1417673]" <<endl;
	cout<<"                 : MD. Azgar Hossain [1413423]" <<endl;
	cout<<"                 : Ali Mohammad Tarif [1418735]" <<endl;
	cout<<"                 : S.M.Raju [1416463]" <<endl<<endl;
	cout<<"Course Name      : Data Structure and Algorithm"<<endl;
	cout<<"Instructor's Name: Dr. Imad Fakri"<<endl;
	cout<<"Course Code      : CSC 2104"<<endl;
	cout<<"Section      	 : 3"<<endl;
	cout<<"Project Name	 : Dictionary  "<<endl<<endl;

	return;
}
