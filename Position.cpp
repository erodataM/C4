#include <iostream>

#include <bitset>
#include <vector>

#include "Constants.h"
#include "Position.h"

Position::Position(long long yellow, long long red, bool turn, char last)
{
    this->yellow = yellow;
    this->red = red;
    this->turn = turn;    
    this->last = last;
}

Position::Position(Position* position) 
{
    this->yellow = position->yellow;
    this->red = position->red;
    this->turn = position->turn;
    this->last = position->last;
}

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

    for(int i = 35;i < 42;i++) 
    {
        for(int j = 0;j < 6;j++)
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
        this->red |= one << n;
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
    long long one = 1;
    long long diagToCheck = this->turn?this->yellow:this->red;
    
    for(int i=0; i<69; i++)
    {                
        if( (constants::winningMasks[i] & (one << this->last)) && ((constants::winningMasks[i] & diagToCheck) == constants::winningMasks[i]) ){
            return true;
        }
    }
                                       
    return false;
}

void Position::display()
{
    for(int i=0;i<42;i++)
    {
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
        
        for(int i=0; i < vectorPos.size(); i++)
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

int Position::pref(int n)
{    
    int res = 0;
    int arrPref[8] = {n-1, n-8, n-7, n-6, n+1, n+8, n+7, n+6};
        
    for(int i=0;i<8;i++) {
        if(this->isBit(arrPref[i])){
            res++;
        }
    }    
    
    return res;
}

