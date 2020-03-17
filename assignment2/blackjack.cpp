
#include<iostream>
#include<vector>
#include <algorithm>    // std::random_shuffle
#include <random>
using namespace std;
#include "blackjack.h"

int Card::getValue(){
    int value;
    rank>=10? value=10: value=rank;
    //cout<< value << endl;
    return value;
}
void Card::displayCard(){
    Rank r = rank;
    
    switch(r){
        case JACK: 
            cout<< "[J" << (char) type << "]" << " ";
            break;
        case QUEEN:
            cout<< "[Q" << (char) type << "]" << " ";
            break;
        case KING:
            cout<< "[K" << (char) type << "]" << " ";
            break;
        default:
            cout<< "["<< rank << (char) type<< "]" << " ";
    }
}

Card::Card(int i, char c){
    rank = Rank(i);
    type = Type(c);
}


void Hand:: add(const Card* card){
    aHands.push_back(*card);
}

void Hand::clear(){
    aHands.clear();
}

int Hand::getTotal(){
    int sum = 0;
    int aces = 0;
    for (auto c = aHands.begin(); c != aHands.end(); ++c) {
        int temp = (*c).getValue();
        //cout << temp << endl;
        //if 1 means it is an ace, need to be handled otherwise
        if(temp == 1) aces++;
        sum+=temp;
    }
    //currently, sum is the value when all aces consider as 1,
    //if busting, we return this value
    /*if(sum>21){
        cout<<"burst"<<endl; 
        return sum;
    }*/
    sum-=aces;
    bool op =false;
    //the following function trying to maximize the value that people can get
    while(aces!=0){
        //can be consider as 1 or 11
        //the optimizer is 11, if it is not busting
        if ((sum+11*aces)<=21){
            sum+=11*aces;
            op = true;
            break;
        } 
        sum+=1;
        aces--;
    }
    return sum;
}

void Hand::showHand(){
for (auto it=aHands.begin(); it!=aHands.end(); ++it){
        (*it).displayCard();
}
cout << "Value:"<<this->getTotal()<<endl;
}

void Deck::populate(){
    cout<<"Generate the deck"<<endl;
    for(int j=1;j<=13;j++){
        //TODO: new shall be call
        for(const auto &t: types){
            //Not really sure about this part
                Card* c = new Card(j,(char)t);
                //(*c).displayCard();
                deck.push_back(*c);
        }
    }

}
    /**
     * Resources:https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
     */
void Deck::shuffle(){
    random_device r;
    auto rng = default_random_engine(r());
    std::shuffle(begin(deck), end(deck), rng);
}

Card* Deck::deal(){
    Card *temp;
        if (!deck.empty()){
        temp = &(deck.back());
        deck.pop_back();
        return temp;
        }
        else{
            cout<<"WARNING: NO CARDS IN DECK!"<<endl;
            //shall be null
            return temp;
        }   
}

void Deck::printDeck(){
    cout << "deck contains:"<<endl;
    for (auto it=deck.begin(); it!=deck.end(); ++it){
            (*it).displayCard();
    }
    cout <<endl;
}

void Deck::clearDeck(){
    deck.clear();
}


AbstractPlayer::AbstractPlayer(){
    hands = new Hand;
}

AbstractPlayer::~AbstractPlayer(){
}
//for everyone it's the same function

bool AbstractPlayer::isBusted(){
    bool result;
    hands->getTotal()>21? result= true: result= false;
    return result;
}
//indicates whether a player wants to draw another card.

void AbstractPlayer::draw(const Card * card){
    hands->add(card);
}

void AbstractPlayer::showHands(){
    hands->showHand();
}

bool HumanPlayer::isDrawing() const{
    cout<< "Do you want to draw? (y/n):"<<endl;
    char c;
    read:
        cin>>c;
    if(c=='y'){
        return true;
    }
    else if(c=='n'){
        return false;
    }
    else{
        cout<< "WARNING: INVALID INPUT"<<endl;
        goto read;
    }
    
}
bool HumanPlayer::announce(int scores,bool finished, bool finished1){
    
    int userpoint = hands->getTotal();
    if(scores>21||userpoint>21){
        scores>21 ?  cout<< "Casino busts."<<"Player wins"<<endl: cout<< "Player busts."<<"Casino wins"<<endl;
    }
    else if(userpoint <scores &&!finished &&!finished1){
        cout<< "Casino wins."<<endl;
    } 
    else if(userpoint==scores&&!finished && !finished1){
        cout<<"Push: No one wins."<<endl;
    }
    else if(userpoint>scores&&!finished &&!finished1){
        cout<<"Player wins."<<endl;
    }
    else{
        cout<<"Continue."<<endl;
        return false;
    }
    return true;
    
}

bool ComputerPlayer::isDrawing() const{
    bool result;
    hands->getTotal()<=16? result=true: result=false;
    return result;
}

int ComputerPlayer::getValue(){
    return this->hands->getTotal();
    
}

void BlackJackGame::initialize(){
    m_deck = new Deck();
    computer = new ComputerPlayer();
    user = new HumanPlayer();
    //the computer should draw one card
    //the user should draw two card.
    (*m_deck).populate();
    m_deck->shuffle();
    
    Card * card1 = (*m_deck).deal();
    Card * card2= (*m_deck).deal();
    Card * card3 = (*m_deck).deal();
    (*user).draw(card1);
    (*user).draw(card3);
    (*computer).draw(card2);
}

void BlackJackGame::clear(){
    delete m_deck;
    delete computer;
    delete user;
}

void BlackJackGame::play(){
    this->initialize();
    bool check1 =true;
    bool check2 =true;
        cout<<"Casino:";
        computer->showHands();
        cout<<"Player:";
        user->showHands();
        bool noresult=true;
    while(check1){
        if(user->isBusted()){
            check1=false;
            check2=false;
            break;
        }
        else{
            check1 = user->isDrawing();
        }
        if(check1){
            Card * temp = (*m_deck).deal();
            (*user).draw(temp);
            cout<<"Player:";
            user->showHands();
        }
    }
    while(check2){
        computer->isBusted()? check2=false:check2= computer->isDrawing();
        if(check2){
                Card * temp = (*m_deck).deal();
            (*computer).draw(temp);
            cout<<"Casino:";
            computer->showHands();
        }
    }
    bool result = user->announce(computer->getValue(),check1,check2);
                
    this->clear();
}

