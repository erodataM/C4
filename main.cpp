#include <iostream>
#include <chrono>
#include <vector>
#include <windows.h>

#include "Position.h"

using namespace std;

int main(int argc, char** argv) {             
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    
    
    Position position = Position(
        0b000000000000000000000000000000000000000000,        
        0b000100000000000000000000000000000000000000,
        true,
        38
    );                        
    
    position.display();
    
    int depth = 8;
    
    int colonne;
    while(1) {
        cin >> colonne;        
                
        for(int i = 41 - (6 - colonne); i >= 0;i = i - 7) {
            if(position.isBitSetable(i)) {
                position.setBit(i, position.getTurn());
                position.setTurn(!position.getTurn());
                position.setLast(i);
                break;
            }
        }
                                
        position.display();                
        
        vector<Position> vectorPos = position.generate();   
        vector<Position> vectorGoodPos;
        
        chrono::time_point<chrono::system_clock> start, end;    
        
        start = chrono::system_clock::now();    
                
        int eval = 10000;
        
        int pos = -1;
        
        int evals[vectorPos.size()];
        
        SetConsoleTextAttribute(hConsole, 2);
        cout << "depth : ";
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << depth << endl;
        
        SetConsoleTextAttribute(hConsole, 2);
        cout << "eval : ";
        
        SetConsoleTextAttribute(hConsole, 15);
        for(int i = 0;i < vectorPos.size(); ++i) {
            evals[i] = vectorPos[i].eval(depth, 0);            
            cout << evals[i] << " ";
            if(evals[i] < eval) {
                eval = evals[i];                      
                pos = i;
            }
        }   
        cout << endl;
                                                       
        for(int i = 0;i < vectorPos.size(); ++i) {
            if(evals[i] == eval) {
                vectorGoodPos.push_back(vectorPos[i]);                  
            }
        }
        
        SetConsoleTextAttribute(hConsole, 2);        
        cout << "best eval : " ;
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << eval << " (" << vectorGoodPos.size() << ")" << endl;
                                       
        if(vectorGoodPos.size() > 1) {
            
        }              
        
        end = chrono::system_clock::now();        
        
        int elapsed_seconds = chrono::duration_cast<std::chrono::seconds> (end-start).count();
        SetConsoleTextAttribute(hConsole, 2);
        cout << "took : ";
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << elapsed_seconds << "s" << endl << endl;
        
        if(elapsed_seconds < 2) {
            ++depth;
        }
        
        position = vectorPos[pos];
        position.display();                   
    }
    
    return 0;
}

