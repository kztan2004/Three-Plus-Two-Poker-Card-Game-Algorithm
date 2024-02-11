#include<iostream>
#include<vector>
#include<time.h>
#include<cstdlib>
#include <unistd.h>

using namespace std;

struct Card
{
    char value;
};

void init(Card cardPile[]);
char value(int val);
int intVal(char val);
void chooseCard(Card cardPile[] ,vector<int> &taken, vector<char> &Card);
int match1(vector<char> player);
int match2(vector<char> player);
bool isBase(int base[]);
bool isThreeSix(int val);
void result(int playerPoint, int opponentPoint);
int winCount = 0;
int loseCount = 0;
int drawCount = 0;
int okane = 0;

int main()
{
    int round = 1;
    do{
        system("cls");
        cout << "      Game "<<round<<endl;
        Card cardPile[52];
        vector<int> taken;
        vector<char> playerCard;
        vector<char> opponentCard;
        int playerPoint, opponentPoint;
        init(cardPile);
        cout << "------ Round 1 ------"<<endl;
        for(int i = 0; i < 3; i++)
        {
            chooseCard(cardPile, taken, playerCard);
            chooseCard(cardPile, taken, opponentCard);
        }
        cout << "Opponent:" <<endl;
        opponentPoint = match1(opponentCard);
        cout <<endl;
        cout << "Player  :" <<endl;
        playerPoint = match1(playerCard);
        cout <<endl;
        result(playerPoint, opponentPoint);
        cout << "Money: "<<okane<<endl;
        cout << endl;
        cout << "------ Round 2 ------"<<endl;
        for(int i = 0; i < 2; i++)
        {
            chooseCard(cardPile, taken, playerCard);
            chooseCard(cardPile, taken, opponentCard);
        }
        cout << "Opponent:" <<endl;
        opponentPoint = match2(opponentCard);
        cout <<endl;
        cout << "Player  :" <<endl;
        playerPoint = match2(playerCard);
        cout << endl;
        result(playerPoint, opponentPoint);
        cout << "Money: "<<okane<<endl;
        round++;
        sleep(1);
    }while(round <= 30);
    cout << endl << endl << endl;
    cout << "------Report------"<<endl;
    cout << "WIN : "<<winCount<<endl;
    cout << "LOSE: "<<loseCount<<endl;  
    cout << "DRAW: "<<drawCount<<endl;
    return 0;
}

void init(Card cardPile[])
{
    int count = 0;
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cardPile[count].value = value(i);
            count++;
        }
    }
}

char value(int val)
{
    char c;
    val++;
    switch(val)
    {
        case 1:
            c = 'A';
            break;
        case 2:
            c = '2';
            break;
        case 3:
            c = '3';
            break;
        case 4:
            c = '4';
            break;
        case 5:
            c = '5';
            break;
        case 6:
            c = '6';
            break;
        case 7:
            c = '7';
            break;
        case 8:
            c = '8';
            break;
        case 9:
            c = '9';
            break;
        case 10:
            c = '0';
            break;
        case 11:
            c = 'J';
            break;
        case 12:
            c = 'Q';
            break;
        case 13:
            c = 'K';
            break;
    }
    return c;
}

int intVal(char val)
{
    int c;
    switch(val)
    {
        case 'A':
            c = 1;
            break;
        case '2':
            c = 2;
            break;
        case '3':
            c = 3;
            break;
        case '4':
            c = 4;
            break;
        case '5':
            c = 5;
            break;
        case '6':
            c = 6;
            break;
        case '7':
            c = 7;
            break;
        case '8':
            c = 8;
            break;
        case '9':
            c = 9;
            break;
        case '0':
            c = 10;
            break;
        case 'J':
            c = 10;
            break;
        case 'Q':
            c = 10;
            break;
        case 'K':
            c = 10;
            break;
    }
    return c;
}

void chooseCard(Card cardPile[] ,vector<int> &taken, vector<char> &Card)
{
    srand(time(NULL));
    bool isChoose = true;
    do{
        int randChoose = rand() % 52;
        if(taken.size() > 0)
        {
            isChoose = true;
            for(int i = 0; i < taken.size(); i++)
            {
                if(randChoose == taken[i])
                {
                    isChoose = false;
                }
            }
        }
        if(isChoose)
        {
            Card.push_back(cardPile[randChoose].value);
            taken.push_back(randChoose);
        }
    }while(!isChoose);
}

int match1(vector<char> player)
{
    int threeSix = 0;
    int maxPoint = 0;
    int playerPoint = 0;
    int testPoint;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    for(int i = 0; i < 3; i++)
    {
        if(isThreeSix(intVal(player[i])))
        {
            threeSix++;
        }else{
            playerPoint += intVal(player[i]);
        }
    }
    for(int i = 0; i < 2 ;i++)
    {
        threeSix >= 1 ? n1 = i == 0 ? 3 : 6 : 0;
        for(int j = 0; j < 2 ;j++)
        {
            threeSix >= 2 ? n2 = j == 0 ? 3 : 6 : 0;
            for(int k = 0; k < 2 ;k++)
            {
                threeSix >= 3 ? n3 = k == 0 ? 3 : 6 : 0;
                testPoint = (playerPoint + n1 + n2 + n3) % 10;
                testPoint == 0 ? testPoint = 10: 0;
                testPoint > maxPoint ?  maxPoint = testPoint : 0;
            } 
        } 
    }
    for(int i = 0; i < 3; i++)
    {
        cout << player[i] << " ";
    }
    cout << endl;
    //cout << maxPoint << endl;
    return maxPoint;
}

int match2(vector<char> player)
{
    int playerPoint = 0;
    int pos1, pos2, pos3;
    int pop1, pop2, Fp1, Fp2;
    int maxPlayer = 0;
    bool haveBase = false;
    for(int i = 0; i < player.size() - 2; i++)
    {
        int base[3];
        base[0] = intVal(player[i]);
        for(int j = i + 1; j < player.size(); j++)
        {
            base[1] = intVal(player[j]);
            for(int k = j + 1; k < player.size(); k++)
            {
                base[2] = intVal(player[k]);
                if(isBase(base))
                {
                    playerPoint = 0;
                    int testPoint = 0;
                    int maxPoint = 0;
                    haveBase = true;
                    int n1 = 0;
                    int n2 = 0;
                    int count = 0;
                    for(int m = 0; m < player.size(); m++)
                    {
                        if(!(m == i || m == j || m == k))
                        {
                            if(count == 0)
                            {
                                pop1 = m;
                            }else{
                                pop2 = m;
                            }
                            if(!isThreeSix(intVal(player[m])))
                            {
                                playerPoint += intVal(player[m]);
                            }
                            count++;
                        }
                    }

                    for(int i = 0; i < 2 ;i++)
                    {
                        isThreeSix(intVal(player[pop1])) ? n1 = i == 0 ? 3 : 6 : 0;
                        for(int j = 0; j < 2 ;j++)
                        {
                            isThreeSix(intVal(player[pop2])) ? n2 = j == 0 ? 3 : 6 : 0;
                            testPoint = playerPoint + n1 + n2;
                            testPoint > maxPoint ? maxPoint = testPoint : 0;
                        } 
                    }
                    playerPoint = maxPoint % 10;
                    playerPoint = playerPoint == 0 ? 10: playerPoint;
                    if(player[pop1] == player[pop2])
                    {
                        playerPoint = 10 + intVal(player[pop1]);
                    }
                    if(playerPoint > maxPlayer)
                    {
                        maxPlayer = playerPoint;
                        pos1 = i;
                        pos2 = j;
                        pos3 = k;
                        Fp1 = pop1;
                        Fp2 = pop2;
                    }
                }
            }
        }
    }
    if(haveBase)
    {
        cout <<" "<< player[Fp1] <<" "<< player[Fp2] <<endl;
        cout << player[pos1]<<" "<<player[pos2]<<" "<<player[pos3]<<endl;
    } 
    else
    {
        for(int i = 0; i < 5; i++)
        {
            cout <<player[i]<<" ";
        }
        cout << endl;
    }
    //cout << maxPlayer << endl;
    return maxPlayer;
}

void result(int playerPoint, int opponentPoint)
{
    if(playerPoint > opponentPoint){
        
        int prize = playerPoint >= 10 ? 2 : 1;
        okane += prize;
        cout << "WIN " <<prize<< endl;
        winCount++;
    }
    else if(playerPoint < opponentPoint){
        int prize = opponentPoint >= 10 ? 2 : 1;
        okane -= prize;
        cout << "LOSE -" <<prize<< endl;
        loseCount++;
    }
    else{
        cout << "DRAW" << endl;
        drawCount++;
    }
}


bool isBase(int base[])
{
    int threeSix = 0;
    int basePoint = 0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    bool isBase = false;

    for(int i = 0; i < 3; i++)
    {
        if(isThreeSix(base[i]))
        {
            threeSix++;
        }else{
            basePoint += base[i];
        }
    }
    for(int i = 0; i < 2 ;i++)
    {
        threeSix >= 1 ? n1 = i == 0 ? 3 : 6 : 0;
        for(int j = 0; j < 2 ;j++)
        {
            threeSix >= 2 ? n2 = j == 0 ? 3 : 6 : 0;
            for(int k = 0; k < 2 ;k++)
            {
                threeSix >= 3 ? n3 = k == 0 ? 3 : 6 : 0;
                if ((basePoint + n1 + n2 + n3) % 10 == 0)
                {
                    isBase = true;
                }
            } 
        } 
    }
    return isBase;
}

bool isThreeSix(int val)
{
    return val == 3 || val == 6;
}