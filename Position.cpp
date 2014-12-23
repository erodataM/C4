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
}

std::vector<long long> Position::winningMasks[42];

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
    return color?this->yellow&(constants::one << n):this->red&(constants::one << n);        
}

void Position::setBit(int n, bool color)
{    
    if(color) {                        
        this->yellow |= constants::one << n;
    } else {                
        this->red    |= constants::one << n;
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
            color += 8 * 16;
        } 
                        
        if(this->isBitSet(i,true)) {                        
            color += 12;
            SetConsoleTextAttribute(hConsole, color);
            std::cout << 2;
        } else {
            if(this->isBitSet(i,false)) {                                
                color += 14;
                SetConsoleTextAttribute(hConsole, color);
                std::cout << 1;
            } else {                
                color += 15;
                SetConsoleTextAttribute(hConsole, color);
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
        return s * 1000 * (depth +1);
    }
    
    if(depth != 0) {
        std::vector<Position> vectorPos = this->generate();
        
        int limit = s * 1000000;        
        
        for(int i=0; i < vectorPos.size(); ++i)
        {                                    
            eval = vectorPos[i].eval(depth - 1, eval);                
            
            if(s * eval <= s * limit) {
                limit = eval;
            }                                    
        }        
        
        eval = limit;
    } else {
        eval = s * this->val();
    }
    
    return eval;    
}

int Position::val()
{
    int val = 0;        
                    
    for(int i = 0; i < 42; ++i)
    {        
        if(this->isBit(i+7) && this->isBitSetable(i)) {            
            int red = false;
            bool yellow = false;
            for(int j = 0; j < Position::winningMasks[i].size(); ++j) {                                
                long long evalMask = Position::winningMasks[i][j] & (~(constants::one << i));                                                
                if(!red && ((evalMask & this->red) == evalMask)) {                    
                    val += i/7;                    
                    red = true;
                }
                if(!yellow && ((evalMask & this->yellow) == evalMask)) {
                    val -= i/7; 
                    yellow = true;
                }
            }            
        }
    }
    
    return val;
}

int Position::val2()
{
    int val[7];                
    for(int i = 0; i < 7; ++i)
    {        
        int red[5];
        int yellow[5];
        for(int j = 34 - (6 - i); j >= 0;i = j - 7) {
            red[j] = 0;
            yellow[j] = 0;
            if(this->isBitSetable(j)) { 
                for(int k = 0; k < Position::winningMasks[j].size(); ++k) { 
                    long long evalMask = Position::winningMasks[j][k] & (~(constants::one << j));                                              
                    if((evalMask & this->red) == evalMask) {            
                        red[j] = 1;
                    }                    
                    if((evalMask & this->yellow) == evalMask) {            
                        yellow[j] = 1;
                    }
                }                
            }
        }                      
    }
    
    return val[0];
}

void Position::calcWinningMasks()
{                            
    for(int i = 0; i < 42; ++i)
    {                        
        for(int j = 0; j < 69; ++j)
        {        
            if(constants::winningMasks[j] & (constants::one << i)) 
            {                
                Position::winningMasks[i].push_back(constants::winningMasks[j]);
            }
        }                                             
    }                
}
