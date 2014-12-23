#ifndef POSITION_H
#define POSITION_H
 
class Position
{
public:  
  Position(long long yellow, long long red, bool turn, char last);  
  Position(Position* position);
  
  std::vector<Position> generate(void);
  
  bool getTurn();
  
  void setTurn(bool turn);
  
  
  char getLast();
  
  void setLast(char last);
  
  
  long long getYellow();
  
  void setYellow(long long yellow);
  
  
  long long getRed();
  
  void setRed(long long red);
  
  
  bool isBitSet(int n, bool color);
  
  bool isBitSetable(int n);
  
  bool isBit(int n);
  
  void setBit(int n, bool color);   
      
  
  bool isWon();
        
  void display();
    
  int eval(int depth, int eval);
           
  static std::vector<long long> winningMasks[42];
  static std::vector<long long> evalMasks[42];
    
private:    
  bool turn;    
  char last;
  long long yellow;
  long long red;
    
  static void calcWinningMasks();
  static void calcEvalMasks();
};
 
#endif
