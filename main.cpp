#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<time.h>



using namespace std;

int p_count = 1;

int t_count = 1;
//..............................................................

struct player
{
    char name[20];
    double price;
    int speed;
    int finishing;
    int defence;
    int team = 0;
    int p_id = 0;
    char post[10];
}player[100];

struct playertemp
{
    int speed;
    int finishing;
    int defence;
    int team = 0;
}tempplayer[100];

struct team
{
    char name[20];
    double money;
    int capacity = 11;
    int t_id = 0;
}team[100];

struct teamtemp
{
    int capacity = 11;
};

//.............................................................

void newplayer();
void newteam();
void buyplayer();
void sellplayer();
int computepower(int i);
int computepower2(playertemp);
void friendlymatch();
void playerpost(int playerID);
int weather();
void realmatch();
void drawgoal(int a , int b);
void goalcount(int a , int b);
void printteam(int teamid);


//..............................................................
int main()
{
    char order1[10];
    char order2 [10];
    cout<<"**********enter your orders**********"<<endl;
    while (true)
    {
        cin>>order1;
        if(strcmp(order1,"new")==0)
        {
            cin>>order2;
            if(strcmp(order2,"player")==0)
                newplayer();
            else if (strcmp(order2,"team")==0)
                newteam();
        }
        else if(strcmp(order1,"buy")==0)
            buyplayer();
        else if (strcmp(order1,"sell")==0)
            sellplayer();
        else if (strcmp(order1,"friendlyMatch")== 0)
            friendlymatch();
        else if (strcmp(order1,"realMatch")== 0)
            realmatch();
        else if (strcmp(order1,"end")==0)
            return 0;

    }


}

void newplayer()
{

        cin>>player[p_count].name;
        cin>>player[p_count].price;
        cin>>player[p_count].speed;
        cin>>player[p_count].finishing;
        cin>>player[p_count].defence;
        player[p_count].p_id = p_count;
        playerpost(player[p_count].p_id);
        p_count++;

}

void newteam()
{

        cin>>team[t_count].name;
        cin>>team[t_count].money;
        team[t_count].t_id = t_count;
        t_count++;

}

void buyplayer()
{
    int playerID,teamID;
    cin>>playerID;
    cin>>teamID;
    //....................................................................................
    if(player[playerID].p_id == 0)
        cout<<"player with the id "<<playerID<<" doesnt exist"<<endl;
    else if (team[teamID].t_id == 0)
        cout<<"team with the id "<<teamID<<" doesnt exist"<<endl;
    else if (player[playerID].price > team[teamID].money)
        cout<<"the team cant afford to buy this player"<<endl;
    else if (player[playerID].team != 0)
        cout<<"player already has a team"<<endl;
    else if (team[teamID].capacity <= 0)
        cout<<"team is full"<<endl;
    else
    {
        cout<<"player "<<playerID<<" added to the team "<<teamID<<" successfully"<<endl;
        team[teamID].money-=player[playerID].price;
        team[teamID].capacity=team[teamID].capacity-1;
        player[playerID].team = teamID;
    }

}

void sellplayer()
{
    int playerID,teamID;
    cin>>playerID;
    cin>>teamID;
    //..........................................................
    if (team[teamID].t_id == 0)
        cout<<"team doesnt exist"<<endl;
    else if(player[playerID].team != teamID)
        cout<<"team doesnt have this player"<<endl;
    else
    {
        team[teamID].money+=player[playerID].price;
        team[teamID].capacity=team[teamID].capacity+1;
        player[playerID].team = 0;
        cout<<"player "<<playerID<<" removed from the team "<<teamID<<" successfully"<<endl;

    }


}

void friendlymatch()
{
    int teamID1,teamID2;
    cin>>teamID1;
    cin>>teamID2;
    if(team[teamID1].t_id == 0 || team[teamID2].t_id ==0)
        cout<<"team doesnt exist"<<endl;
    else if (team[teamID1].capacity>0 || team[teamID2].capacity>0)
        cout<<"the game can not be held due to loss of the players"<<endl;
    else
    {
        if(computepower(teamID1) == computepower(teamID2))
            cout<<"the match is draw"<<endl;
        else if (computepower(teamID1) > computepower(teamID2))
            cout<<"team "<<teamID1<<" win"<<endl;
        else if (computepower(teamID1) < computepower(teamID2))
            cout<<"team "<<teamID2<<" win"<<endl;

    }
}

int computepower(int i)
{
    int power = 0;
    for(int j = 1 ; j<=100 ; j++)
        if(player[j].team == i)
        {
            power = power + player[j].defence + player[j].finishing + player[j].speed;

        }
        return power;
}

int computepower2(int i)
{
    long long power2 = 0;
    for(int j = 1 ; j<=100 ; j++)
        if(tempplayer[j].team == i)
        {
            power2 = power2 + tempplayer[j].defence + tempplayer[j].finishing + tempplayer[j].speed;
            cout<<power2<<endl;
        }
            return power2;
}

void playerpost(int playerID)
{

    if(player[playerID].defence > player[playerID].finishing && player[playerID].defence > player[playerID].speed)
        strcpy(player[playerID].post , "defender");



    else if(player[playerID].finishing > player[playerID].defence && player[playerID].finishing > player[playerID].speed)
        strcpy(player[playerID].post , "forward");


    else if(player[playerID].speed > player[playerID].finishing && player[playerID].speed > player[playerID].defence)
        strcpy(player[playerID].post , "midfielder");

    else if (player[playerID].speed == player[playerID].finishing && player[playerID].finishing == player[playerID].defence)
        strcpy(player[playerID].post , "normal");


}

int weather()
{
    srand(time(0));
    int num = (rand() % (4 - 1 + 1)) + 1;
    if(num == 1)
        return 1;
    else if(num == 2)
        return 2;
    else if(num == 3)
        return 3;
    else if(num == 4)
        return 4;
}

void realmatch()
{

    int teamID1,teamID2;
    cin>>teamID1;
    cin>>teamID2;
    int w_result =weather();
    //....................................................

    if(team[teamID1].t_id == 0 || team[teamID2].t_id ==0)
        cout<<"team doesnt exist"<<endl;
    else if (team[teamID1].capacity>0 || team[teamID2].capacity>0)
        cout<<"the game can not be held due to loss of the players"<<endl;

    else
    {
        printteam(teamID1);
        printteam(teamID2);

        if(w_result == 1)
        {
            char news[20];
            strcpy(news,"today is cloudy!");
            cout<<"\t"<<news<<endl;
            if(computepower(teamID1) == computepower(teamID2))
            {
                cout<<"the match is draw"<<endl;
                drawgoal(teamID1,teamID2);
            }
            else if (computepower(teamID1) > computepower(teamID2))
            {
                cout<<"team "<<teamID1<<" win"<<endl;
                goalcount(teamID1,teamID2);
            }

            else if (computepower(teamID1) < computepower(teamID2))
            {
                cout<<"team "<<teamID2<<" win"<<endl;
                goalcount(teamID2,teamID1);
            }


        }

        else if (w_result == 2)
        {
            char news[20];
            strcpy(news,"today is snowy!");
            cout<<"\t"<<news<<endl;
            for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"defender")==0)
                     player[i].defence = player[i].defence * -1;
            }

            if(computepower(teamID1) == computepower(teamID2))
            {
                cout<<"the match is draw"<<endl;
                drawgoal(teamID1,teamID2);
            }
            else if (computepower(teamID1) > computepower(teamID2))
            {
                cout<<"team "<<teamID1<<" win"<<endl;
                goalcount(teamID1,teamID2);
            }
            else if (computepower(teamID1) < computepower(teamID2))
                {
                    cout<<"team "<<teamID2<<" win"<<endl;
                    goalcount(teamID2,teamID1);
                }

             for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"defender")==0)
                     player[i].defence = player[i].defence * -1;
            }
        }

        else if (w_result == 3)
        {
            char news[20];
            strcpy(news,"today is sunny!");
            cout<<"\t"<<news<<endl;
           for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"forward")==0)
                     player[i].finishing = player[i].finishing - 10;
            }
            if(computepower(teamID1) == computepower(teamID2))
                {
                    cout<<"the match is draw"<<endl;
                    drawgoal(teamID1,teamID2);
                }
            else if (computepower(teamID1) > computepower(teamID2))
                {
                    cout<<"team "<<teamID1<<" win"<<endl;
                    goalcount(teamID1,teamID2);
                }

            else if (computepower(teamID1) < computepower(teamID2))
                {
                     cout<<"team "<<teamID2<<" win"<<endl;
                     goalcount(teamID2,teamID1);
                }

            for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"forward")==0)
                     player[i].finishing = player[i].finishing + 10;
            }
        }

        else if (w_result == 4)
        {
            char news[20];
            strcpy(news,"today is rainy!");
            cout<<"\t"<<news<<endl;
            for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"midfielder")==0)
                     player[i].speed = player[i].speed / 2;
            }

            if(computepower(teamID1) == computepower(teamID2))
                {
                    cout<<"the match is draw"<<endl;
                    drawgoal(teamID1,teamID2);
                }
            else if (computepower(teamID1) > computepower(teamID2))
                {
                    cout<<"team "<<teamID1<<" win"<<endl;
                    goalcount(teamID1,teamID2);
                }

            else if (computepower(teamID1) < computepower(teamID2))
                {
                    cout<<"team "<<teamID2<<" win"<<endl;
                    goalcount(teamID2,teamID1);
                }

            for(int i=0;player[i].name[0]!='\0';i++)
            {
                 if(strcmp(player[i].post,"midfielder")==0)
                     player[i].speed = player[i].speed * 2;

            }
        }

    }
}

void drawgoal(int a , int b)
{
    srand(time(0));
    int num = (rand() % (10 - 0 + 1)) + 0;
    int goalt1 = num;
    int goalt2 = num;
    cout<<"goal team "<<a<<" is: "<<num<<endl;
    cout<<"goal team "<<b<<" is: "<<num<<endl;

}

void goalcount(int a , int b)
{
    srand(time(0));
    int winnergoal,losergoal;
    int num = (rand() % (100 - 1 + 1)) + 1;
    if(num>=1 && num<=50)
    {
        winnergoal = 1;
        losergoal = 0;
        cout<<"goal team "<<a<<" is: "<<winnergoal<<endl;
        cout<<"goal team "<<b<<" is: "<<losergoal<<endl;
    }
    else if(num>=51 && num<=80)
    {
        winnergoal = 2;
        losergoal =(rand() % (1 - 0 + 1)) + 0;
        cout<<"goal team "<<a<<" is: "<<winnergoal<<endl;
        cout<<"goal team "<<b<<" is: "<<losergoal<<endl;

    }
    else if(num>=91 && num<=95)
    {
        winnergoal = 3;
        losergoal =(rand() % (2 - 0 + 1)) + 0;
        cout<<"goal team "<<a<<" is: "<<winnergoal<<endl;
        cout<<"goal team "<<b<<" is: "<<losergoal<<endl;

    }
    if(num>=96 && num<=100)
    {
        winnergoal =(rand() % (10 - 4 + 1)) + 4;
        losergoal =(rand() % ((winnergoal-1) - 0 + 1)) + 0;
        cout<<"goal team "<<a<<" is: "<<winnergoal<<endl;
        cout<<"goal team "<<b<<" is: "<<losergoal<<endl;

    }

}

void printteam(int teamid)
{
    cout<<endl<<"team: "<<teamid<<"\t****LIST****"<<endl;
    for(int i=1;i<=100;i++)
        if(player[i].team == teamid)
    {
        cout<<"name: "<<player[i].name<<"\t"<<"post: "<<player[i].post<<endl;
    }
}
