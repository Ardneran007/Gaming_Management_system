#include<stdio.h>
#include<string.h>
//introduction (you need to enter some data before accessing function to see the database working so keep the number of records less)
#define MAX_LEN 100
#define NAME_LEN 100
#define PLAYERS 20
#define GAMES 100
#define DB_SIZE 200//database size

struct Game_progress
{
    int games_played;
    int games_won;
    int score;
    int prizes;//to be checked(trophies on scale of 10)
};
struct Player_info
{
    int player_id;
    char name[NAME_LEN];
    int date;//ddmmyyyy(registration date)
    struct Game_progress progress;
    char game_prefrences[MAX_LEN];
};

struct Game_master_details
{
    int game_id;
    char game_name[NAME_LEN];
    char type;
    int players_required;
};

struct Game_played_details
{
    int game_id;
    int player_id[PLAYERS];
    int score[PLAYERS];
    int awards[PLAYERS];
    int active_days[PLAYERS];
    int start_date;
    int end_date;
};

struct Guest_User_details
{
    int id;
    char guest_name[NAME_LEN];
    int date;
    int active_days;//to see how many days heust plays the games without registration
};

struct Player_info Player_DB[DB_SIZE];
struct Game_played_details Game_played[DB_SIZE];
struct Game_master_details game_master_DB[DB_SIZE];
struct Guest_User_details guest_DB[DB_SIZE];


//searching a
void display_games(struct Player_info Player_DB[],struct Game_played_details Game_played[],int P,int G,int num_records,int no_players[])
{
    printf("Displaying the Games which are played by other Players\n");
    printf("-------------------------------------------------------------\n");
    for(int i=0;i<num_records;i++)
    {
        for(int j=0;j<no_players[i];j++){
            if(Game_played[i].player_id[j]!=P)
            {
                if(Game_played[i].player_id[j]==Player_DB[i].player_id)
                {
                    printf("%d:\n",Game_played[i].player_id[j]);
                    puts(Player_DB[i].game_prefrences);
                }
            }
        }
                            
    }
    printf("----------------Successfully done----------------\n");
}

//sorting b
void sort_maxdays(struct Game_played_details Game_played[],int size,int no_players[])
{
    struct Game_played_details temp;
    int temp1,k=0;
    for(int i=0;i<size;i++){
        for(int j=0;j<(size-i-1);j++){
            if(Game_played[j].active_days<Game_played[j+1].active_days){
                temp=Game_played[j];
                Game_played[j]=Game_played[j+1];
                Game_played[j+1]=temp;
                //swapping no of players
                temp1=no_players[j];
                no_players[j]=no_players[j+1];
                no_players[j+1]=temp1;
            }
        }
    }
    printf("**************Printing top 5 game details******************");
    //printing the top 5 game details
    for(int i=0;i<5;i++)
    {
        printf("Game id:%d\n",Game_played[i].game_id);
        for(k=0;k<no_players[i];k++){
            printf("Player id no %d:%d  ",k+1,Game_played[i].player_id[k]);
        }
        printf("\nScore:%d\n",Game_played[i].score);
        printf("Awards:%d\n",Game_played[i].awards);
        printf("Active Days:%d\n",Game_played[i].active_days);
        printf("Start Date:%d\n",Game_played[i].start_date);
        printf("End Date:%d\n",Game_played[i].end_date);
        printf("------------------------------\n");
    }
    printf("Successfully printed\n");
}

//initializing the Player Database with default values
void Initialize_DB(struct Player_info Player_DB[],int size)
{
    for(int i=0;i<size;i++){
        Player_DB[i].player_id=0;
        Player_DB[i].name[0]='\0';
        Player_DB[i].date=0;//assigning initial date as 0 which means no registration
        Player_DB[i].progress.games_played=0;//games played
        Player_DB[i].progress.games_won=0;//games won
        Player_DB[i].progress.prizes=0;//score(5*gameswom)
        Player_DB[i].progress.score=0;//prizes won
    }
}

void add(struct Player_info Player_DB[],int size,char name[],int player_id,int date)
{   
    int index,j=0;
    int length=0;//length of maximum game prefrences
    //to find number of filled records
    while(Player_DB[j].player_id!=0 && j<size){
        j++;
    }
    //To find the game prefrences of the player who has played highest games
    for(int i=0;i<size;i++)
    {
        if(Player_DB[i].progress.games_played>length){
            index=i;
       }
   }
   Player_DB[j].player_id=player_id;
   strcpy(Player_DB[j].name,name);
   Player_DB[j].date=date;
   Player_DB[j].progress.games_played=0;
   Player_DB[j].progress.games_won=0;
   Player_DB[j].progress.prizes=0;
   Player_DB[j].progress.score=0;
   printf("***********New User Added Successfully!!*************\n");

}
void update(struct Game_played_details Game_played[],struct Guest_User_details guest_DB[],int num_players[],int size)
{
    for(int i=0;i<size;i++)
    {
        if(Game_played[i].game_id==guest_DB[i].id)
        {
            for(int j=0;j<num_players[i];j++)
            {
                if(Game_played[i].player_id[j]==0)
                {
                    Game_played[i].player_id[j]==guest_DB[i].id;

                }
            }
            Game_played[i].start_date=guest_DB[i].date;
        }
       
    }
    printf("-------------------------------------------------------------\n");
    printf("Successfully updated\n");
} 
void inactive_users(struct Game_played_details Game_played[],int no_players[],int size)
{
    printf("-------------------------------------------------------------\n");
    printf("Displaying list of inactive users\n");
    for(int i=0;i<size;i++)
    {
        printf("Game id:%d\n",Game_played[i].game_id);
        for(int j=0;j<no_players[i];j++)
        {
            if(Game_played[i].active_days[j]==0)
            {
                printf("Player id(player who has not played this game) :%d\n",Game_played[i].player_id[j]);
            }
        }
    }
    printf("Successfully done\n");
}
void active_users(int K,struct Player_info Player_DB[],int size)
{
    printf("****************ACTIVE USERS*****************\n");
    for(int i=0;i<size;i++)
    {
        if((Player_DB[i].progress.games_played)>K)
        {
            printf("Details of Active User %d:\n",i+1);
            printf("Player id:  %d\n",Player_DB[i].player_id);
            printf("Player Name:  %s\n",Player_DB[i].name);
            printf("Registration Date:  %d\n",Player_DB[i].date);
            printf("Games Played:  %d\n",Player_DB[i].progress.games_played);
            printf("Games Won:  %d\n",Player_DB[i].progress.games_won);
            printf("Prizes Won:  %d\n",Player_DB[i].progress.prizes);
            printf("Score:  %d\n",Player_DB[i].progress.score);
            printf("Game prefrences: \n");
            puts(Player_DB[i].game_prefrences);
            
        }
    }
}
void max_prizes(struct Player_info Player_DB[],int size,struct Game_master_details game_master_DB[],int game_size)
{
    int max=0,index=0;
    for(int i=0;i<size;i++)
    {
        if(Player_DB[i].progress.prizes>max)
        {
            max=Player_DB[i].progress.prizes;
            index=i;
        }
    }
    for(int j=0;j<game_size;j++)
    {   //using substring concept
        char *p=strstr((Player_DB[index].game_prefrences),game_master_DB[j].game_name);//for checking if the game is present in game prefrances
        if(p)
        {
            printf("-------------------------------------------------------------\n");
            printf("Game id->%d\n",game_master_DB[j].game_id);
            puts(game_master_DB[j].game_name);
            printf("Type->%c\n",game_master_DB[j].type);
            printf("Players required->%d\n",game_master_DB[j].players_required);
        }
    }
    printf("Successfully done\n");
    printf("-------------------------------------------------------------\n");

}
void sort_playerdetails(struct Player_info Player_DB[],int size,char G[])
{
    struct Player_info temp;
    char *p;
    for(int i=0;i<size;i++){
        for(int j=0;j<(size-i-1);j++){
            if(Player_DB[j].player_id<Player_DB[j+1].player_id){
                temp=Player_DB[j];
                Player_DB[j]=Player_DB[j+1];
                Player_DB[j+1]=temp;
            }
        }
    }
    printf("Displaying player details who are playing the game G\n");
    printf("-------------------------------------------------------------\n");
    for(int i=0;i<size;i++)
    {   //using substring concept
        p=strstr((Player_DB[i].game_prefrences),G);
        if(p)
        {
            printf("Player id:  %d\n",Player_DB[i].player_id);
            printf("Player Name:  %s\n",Player_DB[i].name);
            printf("Registration Date:  %d\n",Player_DB[i].date);
            printf("Games Played:  %d\n",Player_DB[i].progress.games_played);
            printf("Games Won:  %d\n",Player_DB[i].progress.games_won);
            printf("Prizes Won:  %d\n",Player_DB[i].progress.prizes);
            printf("Score:  %d\n",Player_DB[i].progress.score);
            printf("Game prefrences: \n");
            puts(Player_DB[i].game_prefrences);
            printf("-------------------------------------------------------------\n");
        }
    }
    printf("Successfully done\n");
}
void remove_guest(int id,struct Game_played_details Game_played[],int num_players[],int size)
{
    int is_found=0;
    //transvering through the Gameplayeddatabase to search the player
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<num_players[i];j++)
        {
            if(Game_played[i].player_id[j]==id)
            {
                is_found=1;
                if(Game_played[i].active_days[j]>=20)
                {
                    Game_played[i].player_id[i]=0;
                    Game_played[i].score[j]=0;
                    Game_played[i].awards[j]=0;
                    Game_played[i].active_days[j]=0;
                    Game_played[i].start_date=0;
                    Game_played[i].end_date=0;
                    printf("Successfully deleted account\n");
                }
            }
        }
    }
    if(is_found==0)
    {
        printf("Guest has not played the games for more than 20 days\n");
    }
}
int main()
{
    int choice;
    do
    {
        puts("-------------------------------------------------------------");
        puts("                      GAMING DATABASE");
        puts("-------------------------------------------------------------");
        printf("1.Add new user\n2.Update game_playedrecords\n");
        printf("3.Add Guest details\n");
        printf("4.Display the list of games played by other players\n");
        printf("5.Display Inactive users\n");
        printf("6.Display Active users\n");
        printf("7.Display game details for which players win prizes mostly\n");
        printf("8.List of top 5 game details played for highest no of days\n");
        printf("9.Display Player details who are playong game G\n");
        printf("10.Delete the account of guest who has not registered and played for more than 20 days\n");
        printf("0.Exit\n");
        printf("Enter choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:{
                        char name[NAME_LEN];
                        int player_id,date,size;
                        printf("Enter the size of records\n");
                        scanf("%d",&size);
                        printf("Enter Player id\n");
                        scanf("%d",&player_id);
                        printf("Enter name\n");
                        fflush(stdin);
                        gets(name);
                        printf("Enter Date(ddmmyyyy):\n");
                        scanf("%d",&date);
                        add(Player_DB,size,name,player_id,date);
                        break;
            }
            case 2:{
                        int num_records;
                        printf("Enternumbers of records\n");
                        scanf("%d",&num_records);
                        int no_players[num_records];
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter guest id\n");
                            scanf("%d",&guest_DB[i].id);
                            printf("enter date\n");
                            scanf("%d",&guest_DB[i].date);
                            printf("Enter guest name\n");
                            fflush(stdin);
                            gets(guest_DB[i].guest_name);
                        }
                        update(Game_played,guest_DB,no_players,num_records);
                        break;
            }
            case 3:{
                        int num_records;
                        int ans;
                        printf("Enter number of records\n");
                        scanf("%d",&num_records);
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter guest id\n");
                            scanf("%d",&guest_DB[i].id);
                            printf("Enter Guest Name\n");
                            fflush(stdin);
                            gets(guest_DB[i].guest_name);
                            printf("Enter date\n");
                            scanf("%d",&guest_DB[i].date);
                            printf("Enter the number of active days(if active days are more than 15 then u need to register)\n");
                            scanf("%d",&guest_DB[i].active_days);
                        }
                        for(int i=0;i<num_records;i++)
                        {
                            if(guest_DB[i].active_days>=15){
                                printf("Kindly do the registration to enjoy the gaming\nDo you want to register\n");
                                printf("Enter 1 to register\n");
                                scanf("%d",&ans);
                                if(ans)
                                {
                                    add(Player_DB,num_records,guest_DB[i].guest_name,guest_DB[i].id,guest_DB[i].date);
                                    printf("Successfully added\n");
                                }
                                
                            }
                        }
                        break;
            }
            case 4:{
                        int G,P,status=0;
                        int num_records;
                        printf("Enter the number of records as Database is empty\n:");
                        scanf("%d",&num_records);
                        int no_players[num_records];
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter Game id:\n");
                            scanf("%d",&Game_played[i].game_id);
                            printf("Enter number of players who are playing this game:\n");
                            scanf("%d",&no_players[i]);
                            for(int j=0;j<no_players[i];j++)
                            {
                                printf("Enter id of player no %d:\n",j+1);
                                scanf("%d",&Game_played[i].player_id[j]);
                            }
                            printf("--------------------------\nEnter PLayer id\n");
                            scanf("%d",&Player_DB[i].player_id);
                            printf("Enter game prefrences(Insert list of games with spaces)\n");
                            fflush(stdin);
                            printf("Enter game prefrences\n");
                            gets(Player_DB[i].game_prefrences);
                        }
                        printf("Enter the value of G(game_id) and P(Player id)\n");
                        scanf("%d %d",&G,&P);
                        display_games(Player_DB,Game_played,P,G,num_records,no_players);
                        break;
                        

            }
            case 5:{
                        int num_records;
                        printf("Enter the number of records\n:");
                        scanf("%d",&num_records);
                        int no_players[num_records];
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter Game id:\n");
                            scanf("%d",&Game_played[i].game_id);
                            printf("Enter number of players who are playing this game:\n");
                            scanf("%d",&no_players[i]);
                            for(int j=0;j<no_players[i];j++)
                            {
                                printf("*******Enter for Player%d*******\n",i+1);
                                printf("Enter id of player no %d:\n",j+1);
                                scanf("%d",&Game_played[i].player_id[j]);
                                printf("Enter no of active days\n");
                                scanf("%d",&Game_played[i].active_days[j]);
                            }
                            
                        }
                        inactive_users(Game_played,no_players,num_records);
                        break;
            }
            case 6:{
                        int num_rec,k;
                        printf("Enter the Number of Records as the database is empty\n");
                        scanf("%d",&num_rec);
                        for(int i=0;i<num_rec;i++)
                            {
                                printf("Enter for gamer %d\n",i+1);
                                printf("id\n");
                                scanf("%d",&Player_DB[i].player_id);
                                printf("Name\n");
                                scanf("%s",Player_DB[i].name);
                                printf("Date\n");
                                scanf("%d",&Player_DB[i].date);
                                printf("Games played\n");
                                scanf("%d",&Player_DB[i].progress.games_played);
                                printf("Games won\n");
                                scanf("%d",&Player_DB[i].progress.games_won);
                                printf("prizes\n");
                                scanf("%d",&Player_DB[i].progress.prizes);
                                printf("score\n");
                                scanf("%d",&Player_DB[i].progress.score);
                                // printf("prefrence size\n");
                                // scanf("%d",&Player_DB[i].prefrence_size);
                                fflush(stdin);
                                printf("enter game prefrences\n");
                                gets(Player_DB[i].game_prefrences);
                            }
                        printf("Enter the value of k\n");
                        scanf("%d",&k);
                        active_users(k,Player_DB,num_rec);
                        break;
            }
            case 7:{
                        int num_rec,num_games,k;
                        printf("Enter the Number of Records as the database is empty\n");
                        scanf("%d",&num_rec);
                        for(int i=0;i<num_rec;i++)
                        {
                                printf("Enter for gamer %d\n",i+1);
                                printf("id\n");
                                scanf("%d",&Player_DB[i].player_id);
                                printf("Name\n");
                                scanf("%s",Player_DB[i].name);
                                printf("Date\n");
                                scanf("%d",&Player_DB[i].date);
                                printf("Games played\n");
                                scanf("%d",&Player_DB[i].progress.games_played);           
                                printf("prizes\n");
                                scanf("%d",&Player_DB[i].progress.prizes);
                                printf("Enter game prefrences(List of games seperated by spaces)\n");
                                fflush(stdin);
                                gets(Player_DB[i].game_prefrences);
                        }
                        printf("----------------------------------------\n");
                        printf("Now enter Game Details\n");
                        printf("Enter the number of games in Game master DB\n");
                        scanf("%d",&num_games);
                        for(int i=0;i<num_games;i++)
                        {
                            printf("Enter game id for game %d\n",i+1);
                            scanf("%d",&game_master_DB[i].game_id);
                            printf("Enter game name\n");
                            fflush(stdin);
                            gets(game_master_DB[i].game_name);
                            printf("Enter the type of game(S/M)(S=singleplayer,M=Multiplaye)\n");
                            scanf("%c",&game_master_DB[i].type);
                            printf("Enter no of players required to play game\n");
                            scanf("%d",&game_master_DB[i].players_required);
                        }
                        max_prizes(Player_DB,num_rec,game_master_DB,num_games);
                        break;
            }
            case 8:{
                        int num_records;
                        printf("Enter the number of records(records must be more than 5)\n:");
                        scanf("%d",&num_records);
                        int no_players[num_records];
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter Game id:\n");
                            scanf("%d",&Game_played[i].game_id);
                            printf("Enter number of players who are playing this game:\n");
                            scanf("%d",&no_players[i]);
                            for(int j=0;j<no_players[i];j++)
                            {
                                printf("*******Enter for Player%d*******",i+1);
                                printf("Enter id of player no %d:\n",j+1);
                                scanf("%d",&Game_played[i].player_id[j]);
                                printf("Enter score:\n");
                                scanf("%d",&Game_played[i].score[j]);
                                printf("Enter no of awards\n");
                                scanf("%d",&Game_played[i].awards[j]);
                                printf("Enter no of active dayzs\n");
                                scanf("%d",&Game_played[i].active_days[j]);
                            }
                            printf("Enter start date\n");
                            scanf("%d",&Game_played[i].start_date);
                            printf("Enter end date:\n");
                            scanf("%d",&Game_played[i].end_date);
                        }
                        sort_maxdays(Game_played,num_records,no_players);
                        break;
            
            }
            case 9:{
                        int num_rec,k;
                        char G[NAME_LEN];
                        printf("Enter the Number of Records as the database is empty\n");
                        scanf("%d",&num_rec);
                        for(int i=0;i<num_rec;i++)
                            {
                                printf("Enter for gamer %d\n",i+1);
                                printf("id\n");
                                scanf("%d",&Player_DB[i].player_id);
                                printf("Name\n");
                                scanf("%s",Player_DB[i].name);
                                printf("Date\n");
                                scanf("%d",&Player_DB[i].date);
                                printf("Games played\n");
                                scanf("%d",&Player_DB[i].progress.games_played);
                                printf("Games won\n");
                                scanf("%d",&Player_DB[i].progress.games_won);
                                printf("prizes\n");
                                scanf("%d",&Player_DB[i].progress.prizes);
                                printf("score\n");
                                scanf("%d",&Player_DB[i].progress.score);
                                fflush(stdin);
                                printf("Enter game prefrences\n");
                                gets(Player_DB[i].game_prefrences);
                            }
                        fflush(stdin);
                        printf("Enter Game Name(First letter capital)\n");
                        gets(G);
                        sort_playerdetails(Player_DB,num_rec,G);
                        break;

            }
            case 10:{
                        int num_records,id;
                        printf("Enter the number of records as records are empty\n:");
                        scanf("%d",&num_records);
                        int no_players[num_records];
                        for(int i=0;i<num_records;i++)
                        {
                            printf("Enter Game id:\n");
                            scanf("%d",&Game_played[i].game_id);
                            printf("Enter number of players who are playing this game:\n");
                            scanf("%d",&no_players[i]);
                            for(int j=0;j<no_players[i];j++)
                            {
                                printf("*******Enter for Player%d*******",i+1);
                                printf("Enter id of player no %d:\n",j+1);
                                scanf("%d",&Game_played[i].player_id[j]);
                                printf("Enter score:\n");
                                scanf("%d",&Game_played[i].score[j]);
                                printf("Enter no of awards\n");
                                scanf("%d",&Game_played[i].awards[j]);
                                printf("Enter no of active dayzs(if this is more than 20 then account is deleted)\n");
                                scanf("%d",&Game_played[i].active_days[j]);
                            }
                            printf("Enter start date\n");
                            scanf("%d",&Game_played[i].start_date);
                            printf("Enter end date:\n");
                            scanf("%d",&Game_played[i].end_date);
                        }
                        printf("---------------------------------\nEnter the guest id\n");
                        scanf("%d",&id);
                        remove_guest(id,Game_played,no_players,num_records);
                        break;
            }
        default:
            break;
        }
    }
    while(choice!=0);
    return 0;

}
