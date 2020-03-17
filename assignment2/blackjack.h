
#include<iostream>
#include<vector>
#include <algorithm>    // std::random_shuffle
#include <random>


    enum Rank{ACE=1, TWO=2,THREE=3, FOUR=4,FIVE=5,SIX=6,SEVEN=7,EIGHT=8,NIGHT=9,TEN=10, JACK=11,QUEEN=12,KING=13};
        //Ace has either 1 or 11 points
        //Jack,queen,king count 10 points each

    enum Type{CLUBS='C',DIAMONDS='D',HEARTS='H',SPADES='S'};

#ifndef CARD_H
#define CARD_H

class Card{
    private:
        Rank rank;
        Type type;
    public:
        int getValue();
        void displayCard();
        Card(int i, char c);
};
#endif

#ifndef HAND_H
#define HAND_H
class Hand{
    private:
        std::vector<Card> aHands;
    public:
        void add(const Card* card);
        void clear();
        int getTotal();
        void showHand();
};
#endif

static int types[4] = {'C','D','H','S'};
#ifndef DECK_H
#define DECK_H
class Deck{
    
    private:
        //can decalre the number of card or not
        std::vector<Card> deck;
    public:
    
    void populate();
    /**
     * Resources:https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
     */
    void shuffle();
    
    Card* deal();

    void printDeck();

    void clearDeck();

};
#endif
#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H
class AbstractPlayer{
    protected:
        Hand *hands;
    public:
        AbstractPlayer();
        virtual ~AbstractPlayer();
        //for everyone it's the same function
        virtual bool isBusted();
        //indicates whether a player wants to draw another card.
        virtual bool isDrawing() const = 0;
        
        void draw(const Card * card);
        void showHands();
};

#endif
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

class HumanPlayer: public AbstractPlayer{
    //preconstraints: not busted
    public:

        bool isDrawing() const;
            
        bool announce(int scores,bool finished, bool finished1);
};
#endif

#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
class ComputerPlayer: public AbstractPlayer{
    //preconstraint: not busted 
    public:
        bool isDrawing() const;
        int getValue();
};
#endif

#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H
class BlackJackGame{
    private:
        Deck* m_deck;
        ComputerPlayer* computer;
        HumanPlayer* user;
        void initialize();
        void clear();
    public:
        void play();

};
#endif
