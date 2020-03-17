#include "function.h"
#include<iostream>
#include<stdlib.h>

int main(){
    // //Step1:
    // //greetAndInstruct();
    // //Step2:
    // int move=0;
    // char board[27]={'x',' ','x',
    //                 ' ',' ',' ',
    //                 'x',' ',' ',

    //                 ' ','x',' ',
    //                 'x',' ',' ',
    //                 ' ',' ',' ',

    //                 ' ',' ',' ',
    //                 ' ',' ',' ',
    //                 'x',' ',' ',
    //                 };
    // displayBoard(board);
    // checkWinner(board);
    //Step1:
    greetAndInstruct();
    //Step2:
    int move=0;
    char board[27];
    initialization(board);
    displayBoard(board);
    int input;
    //Step3:
    player:
        std::cout<< "Enter a number from 1 to 27 to place X"<<std::endl;
        std::cin>>input;
        if(!checkIfLegal(input-1,board)){
            std::cout<< "Invalid, Please RE-ENTER!" <<std::endl;
            goto player;
        }
        board[input-1] ='x';
        move++;
        displayBoard(board);
        if(move>=5&&checkWinner(board)){
            std::cout<< "Exit The GAME" <<std::endl;
            return 1;
        }
    //Step4:
    computer:
        std::cout<< "Computer move...."<<std::endl;
        computerMove(board);
        move++;
        //loop
        if(move>=27){
            std::cout<< "Ties, no one wins"<<std::endl;
            exit(3);
        }
        else{
            goto player;
        }

    std::cout<< strlen(board)<<std::endl ;
}