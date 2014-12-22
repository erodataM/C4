#include <iostream>
#include <chrono>
#include <vector>

#include "Position.h"

using namespace std;

int main(int argc, char** argv) {
                                                  
    Position position = Position(
        0b000000000000000000000000000000000000000000,
        0b000100000000000000000000000000000000000000,
        true,
        0
    );    
          
    position.display();
    
    int colonne;
    while(1) {
        cin >> colonne;        
                
        for(int i = 41-(6 - colonne); i >=0;i = i-7) {
            if(position.isBitSetable(i)) {
                position.setBit(i, position.getTurn());
                position.setTurn(!position.getTurn());
                break;
            }
        }
                                
        position.display();                
        
        vector<Position> vectorPos = position.generate();   
        
        chrono::time_point<chrono::system_clock> start, end;    
        
        start = chrono::system_clock::now();    
                
        int eval = -10000;
        
        int pos = -1;
        
        int evals[vectorPos.size()];
        
        cout << "eval : ";
        for(int i = 0;i < vectorPos.size(); i++) {
            evals[i] = vectorPos[i].eval(8, 0);            
            cout << evals[i] << " ";
            if(evals[i] > eval) {
                eval = evals[i];                      
                pos = i;
            }
        }   
        cout << endl;
                        
                               
        int count = 0;
        vector<Position> vectorGoodPos;
        for(int i = 0;i < vectorPos.size(); i++) {
            if(evals[i] == eval) {
                vectorGoodPos.push_back(vectorPos[i]);
                count++;                
            }
        }
                                       
        if(count > 1) {
            pos = 0;
            int pref = 0;
            
            for(int i = 0;i < vectorGoodPos.size(); i++) {    
                long long diff = position.getRed() ^ vectorPos[i].getRed();
                                
                for(int j = 0;j < 42;j++) {                    
                    long long one = 1;
                    if(diff & (one << j)) {
                        if(vectorGoodPos[i].pref(j) >= pref) {
                            pos = i;
                            pref = vectorGoodPos[i].pref(j);
                            break;
                        } 
                    }
                }
            }
        }              
        
        end = chrono::system_clock::now();        
        
        int elapsed_seconds = chrono::duration_cast<std::chrono::seconds> (end-start).count();
        cout << "elapsed time: " << elapsed_seconds << "s\n";
        
        position = vectorPos[pos];
        position.display();                   
    }
    
    return 0;
}

