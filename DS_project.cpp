#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
using namespace std;


class movie{
    public:
    int     movie_id;
    float   movie_rating;
    string  genre;
    string  movie_name;
    int     runtime;
    
    friend class movieDATABASE;
    public:
    void displayDATA()
    {
        cout<<"Movie ID:    "<<movie_id<<endl;
        cout<<"Name:        "<<movie_name<<endl;
        cout<<"Rating:      "<<movie_rating<<endl;
        cout<<"Genre:       "<<genre<<endl;
        cout<<"Runtime:     "<<runtime<<endl<<endl;
    }
};

class movieDATABASE{

    vector<movie>   MOVIES;
    vector<movie>   MOVIESsortedbyRating;
    vector<movie>   MOVIESsortedbyRuntime;

    public:
    friend class USER;
    friend class userDATABASE;
    movieDATABASE()
    {
        movie   temp;
        float   number;
        char    character;
        string str1;

        ifstream in("MOVIE DATASET.txt");
        while(1)
        {
            in>>number;
            if( number == -1){break;}
            temp.movie_id=number;

            in>>character;  // ',' in character //
            in>>number;
            temp.movie_rating=number;

            in>>character;  // ',' in character //
            getline(in,str1,',');
            temp.movie_name=str1;

            in>>number;
            if( number==1){   temp.genre="funny"; }
            if( number==2){   temp.genre="action";}
            if( number==3){   temp.genre="horror";}
            if( number==4){   temp.genre="thriller";}
            
            in>>character;  // ',' in character //
            in>>number;
            temp.runtime=number;
            MOVIES.push_back(temp);
        }
        buble_sort();
        RuntimeSort();
    }

    movie searchID(int x)
    {
        return MOVIES[x-1];
    }

    //////////////////////////////////////////
    //////////////////////////////////////////
    ////////////// sorting here //////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    
    void RuntimeSort()
	{
        for(int i=0; i<MOVIES.size(); i++)
        {
            MOVIESsortedbyRuntime.push_back( MOVIES[i]);
    	}
    	int i=0,j=0,temp=0;
    	for(i=0;i<MOVIESsortedbyRuntime.size();i++)
    	{
    		temp=i;
    		for(j=i+1;j<MOVIESsortedbyRuntime.size();j++)
    		{
    			if(MOVIESsortedbyRuntime[j].runtime > MOVIESsortedbyRuntime[temp].runtime)
    			{
    				temp=j;
				}
			}
			if(temp!=i)
			{
				movie tmp;
				tmp=MOVIESsortedbyRuntime[i];
				MOVIESsortedbyRuntime[i]=MOVIESsortedbyRuntime[temp];
				MOVIESsortedbyRuntime[temp]=tmp;
			}
		}
	}
	
    void buble_sort()
	{
        for(int i=0; i<MOVIES.size(); i++)
        {
            MOVIESsortedbyRating.push_back( MOVIES[i]);
    	}
    
        movie temp;

        for(int i=0;i<MOVIESsortedbyRating.size()-1;i++)
        {
            for(int j=i+1;j<MOVIESsortedbyRating.size();j++)
            {
                if( MOVIESsortedbyRating[i].movie_rating < MOVIESsortedbyRating[j].movie_rating)
                {
                    temp=MOVIESsortedbyRating[i];
                    MOVIESsortedbyRating[i]=MOVIESsortedbyRating[j];
                    MOVIESsortedbyRating[j]=temp;
                }
            }
        }
	}
    
    void display()
    {
        // output all data of movies //
        for(int i=0; i<MOVIES.size(); i++)
        {
            MOVIES[i].displayDATA();
        }
    }
    
    void displayratingsort()
    {
        // output all data of movies //
        for(int i=0; i<100; i++)
        {
            MOVIESsortedbyRating[i].displayDATA();
        }
    }
    
    void displayruntimesort()
    {
        for(int i=0; i<100; i++)
        {
            MOVIESsortedbyRuntime[i].displayDATA();
        }
    }

};

class Queue{

    vector<movie>   myMOVIES;
    friend class USER;
    public:
    void EnQ(movie item)
    {
        myMOVIES.push_back(item);
    }
    void DeQ()
    {
        myMOVIES.erase(myMOVIES.begin());
    }
    void deleteitem(int x)
    {
        //myMOVIES.erase(myMOVIES.begin()+--x);
    }
    void deleteall()
    {
        myMOVIES.clear();
    }
    void display()
    {
        for(int i=0; i<myMOVIES.size(); i++)
        {
            myMOVIES[i].displayDATA();
        }
    }

};

class USER {
    int             user_id;
    int             number_of_movies_watched;
    vector<float>   watched_movie_id;
    vector<float>   ratings;
    string          preffered_genre;
    Queue           wishlist;
    USER            *next=NULL;

    friend class userDATABASE;
    
    public:
    USER(){}

    void findgenre(movieDATABASE* ptr)
    {
        
        int max=0;
        int maxidx=0;
        int favmovieid;
    
        for(int i=0; i<number_of_movies_watched; i++)
        {
            
            if(     max<ratings[i]   )
            {    
                maxidx=i; 
                max=ratings[i];
            }
        }
        
        favmovieid = watched_movie_id[maxidx];

        for(int i=0; i<ptr->MOVIES.size(); i++)
        {
    
            if(     favmovieid == ptr->MOVIES[i].movie_id      )
            {
                preffered_genre=ptr->MOVIES[i].genre;   
                //cout<<preffered_genre<<" ";
                break;
            }
        }
        
    }

    void addtowishlist(int x, movieDATABASE* ptr)
    {
        wishlist.EnQ( ptr->searchID(x) );
    }
    void removefromwishlist()
    {
        wishlist.DeQ();
    }
    void clearwishlist()
    {
        wishlist.deleteall();
    }
    void showwishlist()
    {
        wishlist.display();
    }

    void RECOMMEND(movieDATABASE* ptr)
    {
        
        int count=0;
        int i=0;
        while(count<5)
        {
            if( preffered_genre == ptr->MOVIESsortedbyRating[i].genre)
            {
                ptr->MOVIESsortedbyRating[i].displayDATA();
                count++;
            }
            i++;
        }
    }

    void display()
    {
        cout<<"User ID: "<<user_id<<endl;
        cout<<"No. of movies watched: "<<number_of_movies_watched<<endl;
        cout<<"Watched movie(s) ID with ratings:"<<endl;
        for(int i=0; i<number_of_movies_watched; i++)
        {
            cout<<watched_movie_id[i]<<":";
            cout<<ratings[i]<<" ";
        }
        cout<<endl;
        cout<<"Preffered Genre: "<<preffered_genre<<endl;
        cout<<endl;
    }

};

class userDATABASE{

    USER *head;
    USER *tail;
    movieDATABASE *MDobj;
    public:

    userDATABASE()
    {
        head=NULL;
    }

    void makedatabase(movieDATABASE* ptr)
    {

        MDobj=ptr;

        int number,number2,size;
        char character,character2;
        ifstream in("USER DATASET 1.txt");   // user data set 1
        ifstream in2("USER DATASET 2.txt");  // user data set 2
        int flag=0;
        int comma=0;    

        while(flag==0)
        {   
            
            USER *newuser = new USER;
            newuser->next=NULL;
            
            in>>number; in2>>number2;       // user id //
            
            if(number == -1)
            {
                delete newuser;
                flag = -1;
                break;
            }
            
            newuser->user_id=number;
            in>>character;  
			in2>>character2;    
			comma++; // ',' //
        
            in>>number; 
			in2>>number2;    
			size=number;        // no. of movies watced //
            newuser->number_of_movies_watched=size;
            in>>character;  in2>>character2;  comma++; // ',' //
        
            for(int i=0; i<size; i++)
            {
                in>>number; in2>>number2;
                newuser->watched_movie_id.push_back(number);
                newuser->ratings.push_back(number2);
                    if(i != size-1){ in>>character; in2>>character2;    comma++; }// ',' //}
            }

            while(comma<=5)
            {
                in>>character;
                in2>>character2;
                comma++;
            }
            comma=0;
            
            newuser->findgenre(MDobj);

            if( head == NULL)
            {
                head=newuser;
                tail=newuser;
                //newuser->display();
                continue;
            }
            tail->next=newuser;
            tail=newuser;
        }
        // open file and save user profiles to linked lists 
    }

    bool isuser(int x)
    {
        USER *tmp=head;
        while( tmp!=NULL )
        {
            if( x == tmp->user_id)
            {
                return true;
            }
            tmp=tmp->next;
        }
        return false;
    }

    USER* getpointer(int x)
    {
        USER *tmp=head;
        while( tmp!=NULL )
        {
            if( x == tmp->user_id)
            {
                return tmp;
            }
            tmp=tmp->next;
        }
    }
    void showusers()
    {
        USER *tmp=head;
        while(tmp!=NULL)
        {
            tmp->display();
            tmp=tmp->next;
        }
    }
};

class bigclass{

    movieDATABASE   MDB1;
    userDATABASE    UDB1;

    public:
    bigclass()
    {
        UDB1.makedatabase(&MDB1);
        userormovie();
    }

    void userormovie()
    {
        int choice;

        while(1)
        {				
			system("cls");
			system("color 06");
		    cout<<"\t\t\xB2\xB2\xB2Welcome our Movie Recomendation System\xB2\xB2\xB2"<<endl;
            Sleep(1500);
            system("cls");
            
            system("color 0A");

            cout<<endl;
            int day,month,year,hour,mint,sec;
            time_t ttime = time(0);
            tm *local_time = localtime(&ttime);
            day=local_time->tm_mday;
            month=1+local_time->tm_mon;
            year=1900+local_time->tm_year;
            hour=0+local_time->tm_hour;
            mint=0+local_time->tm_min;
            sec=0+local_time->tm_sec;
            cout<<"Date: "<<day<<"/"<<month<<"/"<<year<<endl;
            cout<<"Time: "<<hour<<":"<<mint<<":"<<sec<<endl;

            cout<<"\n\n\n1. Users\n2. Movies\n\n3. Exit\n\nEnter choice: ";
            cin>>choice;
            system("CLS");
            if(choice == 1)
            {
                userichooseyou();
            }

            else if(choice == 2)
            {
                moviesichooseyou();
            }
            
            else if(choice == 3)
            {
                system("cls");
                cout<<"Exiting...!!"<<endl;
				Sleep(1000);
				system("cls");
				system("color 06");
				cout<<"\t\t\xB2\xB2\xB2Thanks for choosing our Movie Recomendation System\xB2\xB2\xB2"<<endl;
				cout<<"\t\t\t\xB2\xB2\xB2\xB2\xB2 Hope to see you Again..!\xB2\xB2\xB2\xB2\xB2\n\n"<<endl;
                break;
            }

            else
            {
                cout<<"Wrong option\n";
            }
        }
    }

    void userichooseyou()
    {
        int iid;
        int choice;
        while(1)
        {
            cout<<"Enter user id or -1 to go back: ";
            cin>>iid;
            system("CLS");
            if( iid == -1)
            {
                break;
            }

            if( UDB1.isuser(iid) == true )
            {
                USER *tmp=UDB1.getpointer(iid);
                while(1)
                {
                    cout<<"1. View User Details\n2. Get Movie Recommendations\n3. View Wishlist\n4. Add to wishlist\n5. Remove from wishlist\n6. Delete wishlist\n\n7. Go back\n\nEnter choice: ";
                    cin>>choice;
                    system("CLS");
                    cout<<endl;
                    if( choice == 1)
                    {
                        tmp->display();
                        getch();
                    }

                    if(choice == 2)
                    {
                        tmp->RECOMMEND(&MDB1);
                    }
                    
                    if(choice == 3)
                    {
                        tmp->showwishlist();
                    }

                    if(choice == 4)
                    {
                        int id;
                        while(1)
                        {
                            cout<<"Enter movie id: ";
                            cin>>id;
                            if(id<1 || id > 3939)
                            {
                                cout<<"\nWrong id\n";
                                continue;
                            }
                            break;
                        }
                        tmp->addtowishlist(id, &MDB1);
                    }

                    if(choice == 5)
                    {
                        tmp->removefromwishlist();
                    }

                    if(choice == 6)
                    {
                        tmp->clearwishlist();
                    }

                    if( choice == 7)
                    {
                        cout<<endl;
                        break;
                    }

                    cout<<endl;
                }

            }

            if( UDB1.isuser(iid) == false )
            {
                cout<<"Wrong Id\n\n";
            }
        }

    }

    void moviesichooseyou()
    {
        
        while(1)
        {
            cout<<"1. Movie details\n2. Show sorted by runtime\n3. Show sorted by rating\n\n4. Go back\n\nEnter choice: ";
            int choice;
            cin>>choice;
            system("CLS");
            if(choice == 1)
            {
                while(1)
                {
                    
                    cout<<"\nEnter movie id or -1 to go back:  ";
                    int idd;
                    cin>>idd;
                    system("CLS");
                    if(idd == -1)
                    {
                        break;
                    }

                    if( idd > 3939)
                    {
                        continue;
                    }
                    movie m;
                    m=MDB1.searchID(idd);
                    m.displayDATA();
                    
                }
            }

            else if(choice == 2)
            {
                MDB1.displayruntimesort();
            }

            else if(choice == 3)
            {
                MDB1.displayratingsort();
            }
            
            else if(choice == 4)
            {
                break;
            }
            else
            {
                cout<<"\nWrong choice\n\n";
            }
        }   

    }

};



int main()
{

    bigclass b1;
     
}
