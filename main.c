/*

*   This program plays BLACKJACK for 1-3 players.
*
*   The game is played against a dealer where each player bets a number of chips on beating the dealer
*
*   There are 3 saved games at any one time which contain each players name and the number of chips that they have.
*
*   The game can be saved after each hand if the user chooses to do so and can be loaded from the top menu
*
*   The only way to exit the code from the inside the terminal is through the top menu
*
*   There is also a hidden cheat-code/Easter-egg
*
*

*/




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define numberCards 52
#define numberSuits 4
#define cardsInSuit 13
#define maxCards 5
#define nameLength 20
#define minPlayers 1
#define maxPlayers 3

//This is a way to reference each type of card within the code later on.
typedef enum {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} Number;
typedef enum {HEARTS, SPADES, DIAMONDS, CLUBS} Suit;

//This structure holds the five properties of each card
typedef struct card {
    Number number;  //The reference to the number of the card number
    int value;      //The value the card holds in the game
    Suit suit;      //The reference to the suit
    char suitName[9];  //The text name of the suit
    char cardName[6];  //The text name of the number of the card
} Card;


//global variables that represent the players name and the chips that they have
int chips[maxPlayers], players, outcome[maxPlayers];
char name[maxPlayers][nameLength];

FILE *Save[3];



void menu();//these functions need to be declared before as they are used in a function that it calls
void Topmenu();

Card* Deckmaker(){


    Card* p;
    p = malloc(numberCards * sizeof *p);  // here is where I allocate the memory for the cards.
    if (p == NULL) {  //sanity checks
        fprintf(stderr, "Out of memory!\n");
        exit(1);
        }

    //temp integers to define the card and suit respectively
    int n;
    int N;


    for (N=0;N<numberSuits;++N){

        for (n=0;n<cardsInSuit;++n){// this double for loop sets up all of the deck

            p[N*cardsInSuit+n].suit = N; //allocates the reference suit


            p[N*cardsInSuit+n].number = n; //allocates the reference number

            switch (N){ //this allocates the text name of the suit
                case 0:
                    p[N*cardsInSuit+n].suitName[0] = 'H';
                    p[N*cardsInSuit+n].suitName[1] = 'E';
                    p[N*cardsInSuit+n].suitName[2] = 'A';
                    p[N*cardsInSuit+n].suitName[3] = 'R';
                    p[N*cardsInSuit+n].suitName[4] = 'T';
                    p[N*cardsInSuit+n].suitName[5] = 'S';
                    p[N*cardsInSuit+n].suitName[6] = '\0';
                    break;

                case 1:
                    p[N*cardsInSuit+n].suitName[0] = 'S';
                    p[N*cardsInSuit+n].suitName[1] = 'P';
                    p[N*cardsInSuit+n].suitName[2] = 'A';
                    p[N*cardsInSuit+n].suitName[3] = 'D';
                    p[N*cardsInSuit+n].suitName[4] = 'E';
                    p[N*cardsInSuit+n].suitName[5] = 'S';
                    p[N*cardsInSuit+n].suitName[6] = '\0';
                    break;

                case 2:
                    p[N*cardsInSuit+n].suitName[0] =  'D';
                    p[N*cardsInSuit+n].suitName[1] =  'I';
                    p[N*cardsInSuit+n].suitName[2] =  'A';
                    p[N*cardsInSuit+n].suitName[3] =  'M';
                    p[N*cardsInSuit+n].suitName[4] =  'O';
                    p[N*cardsInSuit+n].suitName[5] =  'N';
                    p[N*cardsInSuit+n].suitName[6] =  'D';
                    p[N*cardsInSuit+n].suitName[7] =  'S';
                    p[N*cardsInSuit+n].suitName[8] = '\0';
                    break;

                case 3:
                    p[N*cardsInSuit+n].suitName[0] =  'C';
                    p[N*cardsInSuit+n].suitName[1] =  'L';
                    p[N*cardsInSuit+n].suitName[2] =  'U';
                    p[N*cardsInSuit+n].suitName[3] =  'B';
                    p[N*cardsInSuit+n].suitName[4] =  'S';
                    p[N*cardsInSuit+n].suitName[5] = '\0';
                    break;
            }


            switch (n){ //this switch allocates the text names of the cards
                case 0:
                    p[N*cardsInSuit+n].cardName[0] = 'A';
                    p[N*cardsInSuit+n].cardName[1] = 'C';
                    p[N*cardsInSuit+n].cardName[2] = 'E';
                    p[N*cardsInSuit+n].cardName[3] = '\0';
                    break;

                case 1:
                    p[N*cardsInSuit+n].cardName[0] =  'T';
                    p[N*cardsInSuit+n].cardName[1] =  'W';
                    p[N*cardsInSuit+n].cardName[2] =  'O';
                    p[N*cardsInSuit+n].cardName[3] =  '\0';
                    break;

                case 2:
                    p[N*cardsInSuit+n].cardName[0] =  'T';
                    p[N*cardsInSuit+n].cardName[1] =  'H';
                    p[N*cardsInSuit+n].cardName[2] =  'R';
                    p[N*cardsInSuit+n].cardName[3] =  'E';
                    p[N*cardsInSuit+n].cardName[4] =  'E';
                    p[N*cardsInSuit+n].cardName[5] =  '\0';
                    break;

                case 3:
                    p[N*cardsInSuit+n].cardName[0] =  'F';
                    p[N*cardsInSuit+n].cardName[1] =  'O';
                    p[N*cardsInSuit+n].cardName[2] =  'U';
                    p[N*cardsInSuit+n].cardName[3] =  'R';
                    p[N*cardsInSuit+n].cardName[4] =  '\0';
                    break;

                case 4:
                    p[N*cardsInSuit+n].cardName[0] =  'F';
                    p[N*cardsInSuit+n].cardName[1] =  'I';
                    p[N*cardsInSuit+n].cardName[2] =  'V';
                    p[N*cardsInSuit+n].cardName[3] =  'E';
                    p[N*cardsInSuit+n].cardName[4] =  '\0';
                    break;

                case 5:
                    p[N*cardsInSuit+n].cardName[0] =  'S';
                    p[N*cardsInSuit+n].cardName[1] =  'I';
                    p[N*cardsInSuit+n].cardName[2] =  'X';
                    p[N*cardsInSuit+n].cardName[3] =  '\0';
                    break;

                case 6:
                    p[N*cardsInSuit+n].cardName[0] =  'S';
                    p[N*cardsInSuit+n].cardName[1] =  'E';
                    p[N*cardsInSuit+n].cardName[2] =  'V';
                    p[N*cardsInSuit+n].cardName[3] =  'E';
                    p[N*cardsInSuit+n].cardName[4] =  'N';
                    p[N*cardsInSuit+n].cardName[5] =  '\0';
                    break;

                case 7:
                    p[N*cardsInSuit+n].cardName[0] =  'E';
                    p[N*cardsInSuit+n].cardName[1] =  'I';
                    p[N*cardsInSuit+n].cardName[2] =  'G';
                    p[N*cardsInSuit+n].cardName[3] =  'H';
                    p[N*cardsInSuit+n].cardName[4] =  'T';
                    p[N*cardsInSuit+n].cardName[5] =  '\0';
                    break;

                case 8:
                    p[N*cardsInSuit+n].cardName[0] =  'N';
                    p[N*cardsInSuit+n].cardName[1] =  'I';
                    p[N*cardsInSuit+n].cardName[2] =  'N';
                    p[N*cardsInSuit+n].cardName[3] =  'E';
                    p[N*cardsInSuit+n].cardName[4] =  '\0';
                    break;

                case 9:
                    p[N*cardsInSuit+n].cardName[0] =  'T';
                    p[N*cardsInSuit+n].cardName[1] =  'E';
                    p[N*cardsInSuit+n].cardName[2] =  'N';
                    p[N*cardsInSuit+n].cardName[3] =  '\0';
                    break;

                case 10:
                    p[N*cardsInSuit+n].cardName[0] =  'J';
                    p[N*cardsInSuit+n].cardName[1] =  'A';
                    p[N*cardsInSuit+n].cardName[2] =  'C';
                    p[N*cardsInSuit+n].cardName[3] =  'K';
                    p[N*cardsInSuit+n].cardName[4] =  '\0';
                    break;

                case 11:
                    p[N*cardsInSuit+n].cardName[0] =  'Q';
                    p[N*cardsInSuit+n].cardName[1] =  'U';
                    p[N*cardsInSuit+n].cardName[2] =  'E';
                    p[N*cardsInSuit+n].cardName[3] =  'E';
                    p[N*cardsInSuit+n].cardName[4] =  'N';
                    p[N*cardsInSuit+n].cardName[5] =  '\0';
                    break;

                case 12:
                    p[N*cardsInSuit+n].cardName[0] =  'K';
                    p[N*cardsInSuit+n].cardName[1] =  'I';
                    p[N*cardsInSuit+n].cardName[2] =  'N';
                    p[N*cardsInSuit+n].cardName[3] =  'G';
                    p[N*cardsInSuit+n].cardName[4] =  '\0';
                    break;
            }


            if (n==10 || n==11 || n==12)  //these if functions assign the value of each card also setting the picture cards to 10 the ace 's to 11
                p[N*cardsInSuit+n].value = 10;
            else if (n==0)
                p[N*cardsInSuit+n].value = 11;
            else
                p[N*cardsInSuit+n].value = n+1;

        }
    }

    return p; //the function returns the pointer to the Card structure
}


int Random(){ //this function produces a random number between 0 and 52 depending on the computers clock.
   int r;

        srand(time(NULL));
        r = rand() % numberCards;


return r;
}


void hand(){ //this function plays a single hand of blackjack
    Card *p = NULL;

    p=Deckmaker();//this produces a fresh deck of cards which has a pointer p

    printf("Loading please wait...\n \n");  //This is a loading screen as the next steps take a long time


    int i, flag;                                                                          //
    int randoms[(players+1)*maxCards], arands[players][maxCards], Drands[maxCards];       //
        for (i=0;i<((players+1)*maxCards);++i) {                                          //This section produces 2 sets of five random numbers

            if (i==3)
                {printf("Shuffling cards... \n \n ");}
                                                                                          //
            do {randoms[i] = Random();                                                    //  here it loops over and checks to see if the number
            flag=0;                                                                       //  selected has already been picked
                                                                                          //
                for(int j=0;j<i;++j)                                                      //If it has already been selected then it flags
                {                                                                         //
                    if(randoms[j]==randoms[i])                                            //
                        flag=1;                                                           //
                }                                                                         //
            }while (flag==1);                                                             //
        }


        for (int m=0; m<players; ++m){                              //The numbers are then set into arrays for each player
            for (i=0;i<maxCards;++i){                               //
                arands[m][i]=randoms[m*maxCards+i];                 //
                }                                                   //The dealer has a separate array
            }                                                       //
        for (i=0;i<maxCards;++i){                                   //
            Drands[i]=randoms[i+players*maxCards];                  //
            }
    int option, h;
    int value[maxPlayers];

    for (int n=0;n<players;++n){  //looped for each player


        printf("%s 's cards are: \n",name[n]);

        printf("%s of %s \n",p[arands[n][0]].cardName, p[arands[n][0]].suitName);
        printf("%s of %s \n \n",p[arands[n][1]].cardName, p[arands[n][1]].suitName);  //the first two cards are drawn for each player
        value[n] = p[arands[n][0]].value+p[arands[n][1]].value;
        if (p[arands[n][0]].number== ACE && value[n]>21){
            p[arands[n][0]].value=1;}
        if (p[arands[n][1]].number==ACE && value[n]>21){                  //this here is a check to make sure the ace is showing the appropriate value
            p[arands[n][1]].value=1;}
        printf("%s 's total is %i \n \n \n", name[n], value[n]);

        printf("Dealer has a %s of %s \n\n",p[Drands[0]].cardName, p[Drands[0]].suitName); //In blackjack one of the dealers cards are revealed


        h=2;  //this loops for every new card but breaks if the payer chooses to hold or busts
        do{
            printf("Would you like to: \n   1. HIT\n   2. HOLD\n");

                do {scanf("%i",&option);}while (option!=1 && option!=2 && option!=42);  //sanity check


                switch (option){
                    case 1:
                        printf("%s of %s \n \n",p[arands[n][h]].cardName, p[arands[n][h]].suitName);  //a new card is drawn
                        value[n]=value[n]+p[arands[n][h]].value;

                        for (int a=0; a<=h; ++a){
                            if (p[arands[n][a]].number==ACE && value[n]>21){  //this section checks to see if an ace has appeared and they have busted
                                p[arands[n][a]].value=1;
                                value[n]=0;
                                for (int b=0; b<=h; ++b){
                                    value[n]=value[n]+p[arands[n][b]].value;}
                            }
                        }
                        printf("%s 's total is %i \n \n", name[n], value[n]); //prints the new total and moves to the next card.
                        h=1+h;
                        break;

                    case 2:
                        h=maxCards;  //this jumps to make the program think that the player has drawn the max number of cards
                        break;

                    case 42:   //This is a hidden cheat-code/Easter-egg referencing Hitchhikers guide to the galaxy
                        printf("You truly know the meaning of life and have far more intelligence than anyone on this planet...\nYou are far to superior to this puny game. \nHere take 100 chips...\n\n\n");
                        chips[n]=100+chips[n];
                        strcpy(name[n],"far superior being");
                        break;
                }
        }while(h<maxCards && value[n]<21);

        if (value[n]>21){
            printf("BUST! \n \n \n");} // bust condition

    }


    int Dvalue;
    printf("Dealer's cards are: \n");

    printf("%s of %s \n",p[Drands[0]].cardName, p[Drands[0]].suitName); //selects dealers first too cards
    printf("%s of %s \n \n",p[Drands[1]].cardName, p[Drands[1]].suitName);
    Dvalue = p[Drands[0]].value+p[Drands[1]].value;
    if (p[Drands[0]].number== ACE && Dvalue>21){
        p[Drands[0]].value=1;}                    //checking if aces need to be 1 or 11
    if (p[Drands[1]].number==ACE && Dvalue>21){
        p[Drands[1]].value=1;}
    printf("Dealer's total is %i \n \n \n", Dvalue);

    h=2;
    do {
            if (Dvalue<17){  //dealer will always hit if he has less than 17
                printf("Dealer HITs \n");
                printf("%s of %s \n \n",p[Drands[h]].cardName, p[Drands[h]].suitName);
                Dvalue=Dvalue+p[Drands[h]].value;

                for (int a=0; a<=h; ++a){
                    if (p[Drands[a]].number==ACE && Dvalue>21){  //checking if any aces drawn should be changed from 11 to 1
                        p[Drands[a]].value=1;
                        Dvalue=0;
                        for (int b=0; b<=h; ++b){
                            Dvalue=Dvalue+p[Drands[b]].value;}
                    }
                }
                printf("Dealer's total is %i \n \n \n", Dvalue);
                h=1+h;
                }

            else
            {
                h=maxCards;
                printf("Dealer HOLDs \n \n \n"); //if they choose to hold it makes the code think they have drawn all five cards.

            }


    }while(h<maxCards && Dvalue<21);

    if (Dvalue>21){
        printf("BUST! \n \n \n");}

    for (int q=0; q<players; ++q){

        if (value[q]==21){                              //blackjack
            printf("Blackjack for %s\n \n \n",name[q]);
            outcome[q] = 2;}

        else if ((value[q]>21) || (Dvalue<=21 && value[q]<Dvalue)){
            printf("Dealer beats %s\n\n\n",name[q]);         //loss conditions
            outcome[q] = -1;}

        else if (Dvalue==value[q] && value[q]<=21){
            printf("PUSH for %s\n\n\n",name[q]);           //draw conditions
            outcome[q] = 0;}

        else {
            printf("%s wins!\n\n\n",name[q]);         //win conditions
            outcome[q] = 1;}                                             //each conditions returns a multiplier on the bet they made
    }
}


void Chipcheker(){      //this function checks to see if any of the players have 0 chips left, and if they do remove them from the game and reorganise the playing order.

    for (int n=0; n<players; ++n){
        if (chips[n]==0){
            printf("%s is out of money so has left the table with his head bowed in shame...\n\n", name[n]);
            for (int m=n+1; m<players; ++m){   //this loops over each player after the kicked player and assigns all of their data to the player before.
                chips[m-1]=chips[m];
                for (int a=0;a<nameLength;++a){     //this loops over the name
                    name[m-1][a]=name[m][a];
                }

            }
            players=players-1;  // The Number of players is then reduced.
            if (players==0){
                printf("Everyone is out of money...\n\n\n            GAME OVER\n\n\n\n");       // exit condition if all players have no chips
                Topmenu();
            }
        }
    }


}


void Bets(){ //This function lets the players bet

    int bet[maxPlayers];
    int n;
    for(n=0;n<players;++n){
        printf("%s currently has %i Chips\nHow many would you like to bet?\n\n",name[n],chips[n]);

        do{scanf("%i",&bet[n]);
            if(bet[n]>chips[n]){   //taking in each players bet
                printf("You are not that rich...\n\nHow many would you like to bet?\n\n");
                }
            else if (bet[n]<=0){
                printf("you can not bet %i\n", bet[n]);
                }
            }while(bet[n]<=0 || bet[n]>chips[n]);  //sanity checks
    }
    hand();  //the hand function decides the outcome before bets can be checked

    for(n=0; n<players; ++n){
        chips[n]=chips[n]+bet[n]*outcome[n];        //chips are adjusted for each player depending on their bet and outcome

        printf("%s, you now have %i Chips\n\n\n",name[n], chips[n]);
    }

    Chipcheker();  //a check for if they now have no chips

}


void Savemenu(){                    //This is the menu displaying he saved games it was easier having this as a function than being repeated twice



    Save[0]=fopen("Save1.txt","r"); // all three save files are opened for reading and given the reference 'save[]'
    Save[1]=fopen("Save2.txt","r");
    Save[2]=fopen("Save3.txt","r");

    int tempplayers;
    char tempname[3][nameLength];  //a set of temp values are created so the real values are not changed by showing the saved values
           for(int i=0;i<3;++i){
                fscanf(Save[i],"%d",&tempplayers); //this reads how many players are in each save file
                printf("\n     %i . ",i+1);         //this prints the number of the save file and creates the structure or the menu


                fgets(tempname[0],nameLength,Save[i]);
                 //this then moves the reading cursor to before each of the player names



               for(int j=0;j<tempplayers;++j){
                    fgets(tempname[j],nameLength,Save[i]);

                    tempname[j][strlen(tempname[j])-1]='\0';            //this reads the appropriate amount of players names and prints them in the menu.

                    printf("%s ",tempname[j]);

               }

           }
           printf("\n\n\n\n");      //formatting

            fclose(Save[0]);
            fclose(Save[1]);    //closes all of the files
            fclose(Save[2]);



}


void Topmenu(){  //this is the opening menu as soon as the program stars and is the first thing clled from main. it also includes the only exit point from the code

printf("Top Menu\n\n    1. New game\n    2. Load game\n    3. Quit\n\n\n");
    int option;
    do{scanf("%i",&option);}while(option!=1 && option!=2 && option!=3);  //sanity checks


    switch(option){
        case 1:  //NEW GAME

//            Chips[0]=0;
//            Chips[1]=0;
//            Chips[2]=0;

            printf("How many players? 1-3\n");
            do{scanf("%i",&players);}while(players!=1 && players!=2 && players!=3);

            for(int n=0;n<players;++n){

                printf("Please enter P %i 's name\n",n+1);
                scanf("%s", name[n]);
                printf("Hello \"%s\"\n\n", name[n]);

                chips[n]=25;
            }

            menu();

            break;

        case 2:

            printf("Which save game would you like to load?\n");

            Savemenu();

            int soption;
            do{scanf("%i",&soption);}while(soption!=1 && soption!=2 && soption!=3);


            switch(soption)
            {
                case 1:
                Save[0]=fopen("Save1.txt","r");
                break;

                case 2:
                Save[1]=fopen("Save2.txt","r");
                break;

                case 3:
                Save[2]=fopen("Save3.txt","r");
                break;


            }


                fscanf(Save[soption-1],"%d %d %d %d",&players,&chips[0],&chips[1],&chips[2]);


                fgets(name[0],nameLength,Save[soption-1]);


                for(int j=0;j<players;++j)
                       {
                           fgets(name[j],nameLength,Save[soption-1]);

                           name[j][strlen(name[j])-1]='\0';
                       }
                fclose(Save[soption-1]);


            menu();

            break;

        case 3:

            printf("Thanks for playing \n\n\n");
            exit(1);
            break;
    }

}


void menu(){

    printf("Menu\n\n    1. New Hand\n    2. Save game\n    3. Quit to Top Menu\n\n\n");
    int option;
    do{scanf("%i",&option);}while(option!=1 && option!=2 && option!=3);

    switch(option){
        case 1:

            Bets();

            menu();

            break;

        case 2:


            printf("Which save game would you like to overwrite?");

            Savemenu();


            int soption;
            do{scanf("%i",&soption);}while(soption!=1 && soption!=2 && soption!=3);


            switch(soption)
            {
                case 1:
                Save[0]=fopen("Save1.txt","w");
                break;

                case 2:
                Save[1]=fopen("Save2.txt","w");
                break;

                case 3:
                Save[2]=fopen("Save3.txt","w");
                break;
            }


            fprintf(Save[soption-1],"%d %d %d %d\n",players,chips[0],chips[1],chips[2]);


            for(int i=0;i<players;++i)
            {
                fprintf(Save[soption-1],"%s \n",name[i]);
            }
            fclose(Save[soption-1]);

            printf("Done mate!\n\n");

            Topmenu();



            break;

        case 3:

            Topmenu();

            break;
    }

}



int main()
{   printf("BLACKJACK\n\n\n\nA Nutt productions game\n\n\n\n\n");


    Topmenu();

    return 0;
}

