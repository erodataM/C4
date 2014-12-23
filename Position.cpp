#include <iostream>

#include <bitset>
#include <vector>

#include <windows.h>

#include "Constants.h"
#include "Position.h"

Position::Position(long long yellow, long long red, bool turn, char last)
{
    this->yellow = yellow;
    this->red    = red;
    this->turn   = turn;    
    this->last   = last;
    
    if(Position::winningMasks[0].size() == 0) {
        Position::calcWinningMasks();
    }

    if(Position::evalMasks[0].size() == 0) {
        Position::calcEvalMasks();
    }    
}

Position::Position(Position* position) 
{
    this->yellow = position->yellow;
    this->red    = position->red;
    this->turn   = position->turn;
    this->last   = position->last;
    
    if(Position::winningMasks[0].size() == 0) {
        Position::calcWinningMasks();
    }
    
    if(Position::evalMasks[0].size() == 0) {
        Position::calcEvalMasks();
    }
}

std::vector<long long> Position::winningMasks[42];

std::vector<long long> Position::evalMasks[42];

bool Position::getTurn()
{
    return this->turn;
}

void Position::setTurn(bool turn) 
{    
    this->turn = turn;   
}

char Position::getLast()
{
    return this->last;
}

void Position::setLast(char last) 
{    
    this->last = last;   
}

long long Position::getYellow()
{
    return this->yellow;
}

void Position::setYellow(long long yellow) 
{    
    this->yellow = yellow;   
}

long long Position::getRed()
{
    return this->red;
}

void Position::setRed(long long red) 
{    
    this->red = red;   
}

std::vector<Position> Position::generate(void)
{    
    std::vector<Position> vectorPos;

    for(int i = 35;i < 42; ++i) 
    {
        for(int j = 0;j < 6; ++j)
        {            
            int diff = i - (j*7);            
            if(this->isBitSetable(diff))
            {                    
                Position newPos = Position(this);     
                                
                newPos.setBit(diff, this->turn);                 
                newPos.setTurn(!this->turn);                                                          
                newPos.setLast(diff);      
                vectorPos.push_back(newPos);
                
                break;
            }
        }
    }
    
    return vectorPos;
}

bool Position::isBitSet(int n, bool color)
{
    long long one = 1;
    return color?this->yellow&(one << n):this->red&(one << n);        
}

void Position::setBit(int n, bool color)
{
    long long one = 1;
    if(color) {                        
        this->yellow |= one << n;
    } else {                
        this->red    |= one << n;
    } 
}

bool Position::isBitSetable(int n)
{
    return !this->isBitSet(n, true) && !this->isBitSet(n, false);        
}

bool Position::isBit(int n)
{
    return n >= 0 &&  n < 43 && this->isBitSetable(n);
}

bool Position::isWon()
{                        
    long long diagToCheck = this->turn?this->red:this->yellow;
    
    for(int i=0; i < Position::winningMasks[this->last].size(); i++)
    {                                
        if( ((Position::winningMasks[this->last][i] & diagToCheck) == Position::winningMasks[this->last][i]) )
        {            
            return true;
        }
    }
                                       
    return false;
}

void Position::display()
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    
    
    for(int i=0;i<42;i++)
    {
        int color = 0;
        if(this->last == i) {
            color += 12;
        } else {
            color += 15;
        }
        
        SetConsoleTextAttribute(hConsole, color);
        
        if(this->isBitSet(i,true)) {                        
            std::cout << 2;
        } else {
            if(this->isBitSet(i,false)) {                                
                std::cout << 1;
            } else {                
                std::cout << 0;    
            }
        }
        if((i+1)%7 == 0) {
            std::cout << std::endl;       
        }
    }
    std::cout << std::endl;
}

int Position::eval(int depth, int eval)
{                            
    int s = this->turn?-1:1; 
    
    if(this->isWon()) {
        return s * 1000;
    }
    
    if(depth != 0) {
        std::vector<Position> vectorPos = this->generate();
        
        int limit = s * 10000;        
        
        for(int i=0; i < vectorPos.size(); ++i)
        {                                    
            eval = vectorPos[i].eval(depth - 1, eval);                
            
            if(s * eval <= s * limit) {
                limit = eval;
            }                                    
        }        
        
        eval = limit;
    } else {
        eval = 0;
    }
    
    return eval;    
}

void Position::calcWinningMasks()
{        
    long long one = 1;    
                
    for(int i = 0; i < 42; ++i)
    {                        
        for(int j = 0; j < 69; ++j)
        {        
            if(constants::winningMasks[j] & (one << i)) 
            {                
                Position::winningMasks[i].push_back(constants::winningMasks[j]);
            }
        }                                             
    }                
}

void Position::calcEvalMasks()
{        
    long long one = 1;    
                
    for(int i = 0; i < 42; ++i)
    {                        
        for(int j = 0; j < 69; ++j)
        {        
            if(constants::winningMasks[j] & (one << i)) 
            {                
                for(int k = 0; k < 42; ++k) {
                    
                }
            }
        }                                             
    }                
}
