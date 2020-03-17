#include<iostream>
#include<stdlib.h>
#include <string.h>
#include "function.h"
/*
 * This funciton check who is the winner given the character 
 */

bool winnerDetermine(char* c){
        if(*c=='x'){
                std::cout<<"The player wins"<<std::endl;
            }
        else if(*c=='o'){
                std::cout<<"The computer wins"<<std::endl;
            }
        return true;
    }
/*
 * Qusiton 1
 */

void greetAndInstruct(){
    std::cout<<"Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer."<< std::endl;
    std::cout<<"The board is numbered from 1 to 27 as per the following:"<< std::endl;
    
    int count1 = 1;
    int count2 =10;
    int count3 =19;
    int counts[3] = {count1,count2,count3};
    for(int p=0;p<3;p++){
        //print three row
        for(int i =0;i<3;i++){
            //choose the right table to print
            int &temp = counts[i];
            for(int j=0;j<3;j++){
                //print 1|2|3, three continue number for the board
                std::cout<< (temp++) <<"|" ;
            }
            std::cout<< "\t";
        }
        std::cout<<std::endl << "------\t---------\t---------\t"<<std::endl;
    }
    std::cout<< "Player starts first."<<" Simply input the number of the cell you want to occupy."
    << " Player\'s move is marked with X." << "Computer\'s move is marked with O. "<< std::endl;
    std::cout<<"Start? (y/n):"<< std::endl;
    char c;
    enter:
        std::cin>>c;
        if(c=='y'){
            std::cout<<"Start!"<< std::endl;
            return;
        }
        else if(c=='n'){
            exit(1);
        }
        else{
            std::cout<<"Please re-enter."<< std::endl;
            goto enter;
        }
}

/*
 * This will take a char[] for all the board and print it.
 * The index of the board consistent with the number of board+1
 * Quesiton 2
 */

void displayBoard(char board[]){
       for(int p=0;p<3;p++){
        //print three row
        for(int i =0;i<3;i++){
            //choose the right table to print
            int temp = p*3+i+8*i;
            for(int j=0;j<3;j++){
                std::cout<< (board[temp++]) <<"|" ;
            }
            std::cout<< "\t";
        }
        std::cout<<std::endl << "------\t------\t------\t"<<std::endl;
    }
}

bool checkIfLegal(int cellNbre, char board[]){
    bool result = false;
    if(cellNbre<0 || cellNbre>26){
        std::cout<<"OUT OF RANGE,PLEASE RE-ENTER."<<std::endl;
    }
    else if(board[cellNbre]!=' '){
        std::cout<<"ALREADY INPUTED, PLEASE RE-ENTER."<<std::endl;
    }
    else{
        std::cout<<"SUCCESSFUL"<<std::endl;
        result = true;
    } 
    return result;
}

bool checkWinner(char board[]){
    bool result = false;
    //horizontal in table
    for(int i1= 0; i1<strlen(board);i1+=3){
        //winning condition 1: 123, 456,789...
        
        if(board[i1]==board[i1+1]&&board[i1+1]==board[i1+2]&&(board[i1+2]=='x'||board[i1+2]=='o')){
            //std::cout<<"1"<<std::endl;
            return winnerDetermine(&board[i1]);
        }
    }
    //vertical in table
    for(int i2=0;i2<3;i2++){
        //winning condition 2:147,258,369,101316,...,212427
        for(int i22=0;i22<3;i22++){
            int temp2 = i2*9+i22;
            //std::cout<<temp2<<std::endl;
            if(board[temp2]==board[temp2+3]&&board[temp2+3]==board[temp2+6]&&(board[temp2+6]=='x'||board[temp2+6]=='o')){
                //std::cout<<"2"<<std::endl;
                return winnerDetermine(&board[temp2]);
            }
        }
    }
    //diagonal in table
    for(int i3=4;i3<strlen(board);i3+=9){
     //winning condition 3:159, 357,101418,121416,192327,212325
        for(int i33=4;i33>=2;i33-=2){
            if(board[i3-i33]==board[i3]&&board[i3]==board[i3+i33]&&(board[i3]=='x'||board[i3]=='o')){
                //std::cout<<"3"<<std::endl;
                return winnerDetermine(&board[i3]);
            }
        }
    }
    //horizontal across table
    for(int i4=0;i4<8;i4+=3){
     //winning condition 4: 1/11/21, 4/14/24,7/17/27
        if(board[i4]==board[i4+10]&&board[i4+10]==board[i4+20]&&(board[i4]=='x'||board[i4]=='o')){
            //std::cout<<"4"<<std::endl;
            return winnerDetermine(&board[i4]);
        }
    }
     //winning condition 4.2, consider the reverse case: 3/11/19,6/14/22,9/17/25
    for(int i4=2;i4<10;i4+=3){
        if(board[i4]==board[i4+8]&&board[i4+8]==board[i4+16]&&(board[i4]=='x'||board[i4]=='o')){
            //std::cout<<"4.2"<<std::endl;
            return winnerDetermine(&board[i4]);
        }
    }
    //vertical across table
    for(int i5=0;i5<3;i5++){
    //winning condition 5: 1,13,25, 2/14/26,3/15/27
        if(board[i5]==board[i5+12]&&board[i5+12]==board[i5+24]&&(board[i5]=='x'||board[i5]=='o')){
            //std::cout<<"5"<<std::endl;
            return winnerDetermine(&board[i5]);
        }
    }

    //winning condition 5.2: 7,13,19, 8/14/20,9/15/21
    for(int i5=6;i5<9;i5++){
        if(board[i5]==board[i5+6]&&board[i5+6]==board[i5+12]&&(board[i5]=='x'||board[i5]=='o')){
            //std::cout<<"5.2"<<std::endl;
            return winnerDetermine(&board[i5]);
        }
    }

    //winning condition 6.2:19/14/9, 3/14/25-checking the winning conditon 
    if(((board[0]==board[13]&&board[13]==board[26])||(board[20]==board[13]&&board[13]==board[6])||(board[8]==board[13]&&board[13]==board[18])||(board[2]==board[13]&&board[13]==board[24]))&&(board[13]=='x'||board[13]=='o')){
        //std::cout<<"6+6.2"<<std::endl;
        return winnerDetermine(&board[13]);
    }
    
    //repeated at same position of the table
    for(int i7=0;i7<9;i7++){
    //winning condition 7:1/10/19, 2/11/20
        if(board[i7]==board[i7+9]&&board[i7+9]==board[i7+18]&&(board[i7]=='x'||board[i7]=='o')){
            //std::cout<<"7"<<std::endl;
            return winnerDetermine(&board[i7]);
        }
    }
    return false;
}

// emunurate any possible 
    // if there is a true
    // perform it 
    // emurate any move that possible for opponent
    // if there is a true
    // block it 
void computerMove(char board[]){
    int last_empty_space;
    bool empty = false;
    for(int i=0;i<strlen(board);i++){
        if(board[i]==' '){
            empty = true;
            board[i]='o';
            //displayBoard(board);

            //std::cout<< i <<"TEST"<<std::endl;
            if(checkWinner(board)){
                displayBoard(board);
                std::cout<< "Game Exit"<<std::endl;
                exit(2);
            }
            board[i]=' ';
        }
        
    }

    std::cout<< "NO WINNING STEP FOUND,TYRING FIND BLOCK"<<std::endl;

    for(int i=0;i<strlen(board);i++){
        if(board[i]==' '){
            last_empty_space = i;
            board[i]='x';
            //displayBoard(board);
            if(checkWinner(board)){
                board[i]='o';
                std::cout<< "BLOCK FOUND"<<std::endl;
                displayBoard(board);
                break;
            }
            board[i]=' ';
        }
    }
    if(empty){
        board[last_empty_space]='o';
        displayBoard(board);
        if(checkWinner(board)){
            std::cout<< "Game Exit"<<std::endl;
            exit(2);
        }
    }
    else{
        std::cout<< "Ties, no one wins"<<std::endl;
            exit(3);
    }
}

void initialization (char board[]){
    for(int i=0; i<27;i++){
        (board)[i] = ' ';
    }
}

