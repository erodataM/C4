#ifndef CONSTANTS_H
#define	CONSTANTS_H

namespace constants
{
    const long long one  = 1;        
    
    const long long h00 = 0b111100000000000000000000000000000000000000;  
    const long long h01 = 0b011110000000000000000000000000000000000000;
    const long long h02 = 0b001111000000000000000000000000000000000000;
    const long long h03 = 0b000111100000000000000000000000000000000000;
    
    const long long h10 = 0b000000011110000000000000000000000000000000;  
    const long long h11 = 0b000000001111000000000000000000000000000000;
    const long long h12 = 0b000000000111100000000000000000000000000000;
    const long long h13 = 0b000000000011110000000000000000000000000000;
    
    const long long h20 = 0b000000000000001111000000000000000000000000;  
    const long long h21 = 0b000000000000000111100000000000000000000000;
    const long long h22 = 0b000000000000000011110000000000000000000000;
    const long long h23 = 0b000000000000000001111000000000000000000000;
    
    const long long h30 = 0b000000000000000000000111100000000000000000;  
    const long long h31 = 0b000000000000000000000011110000000000000000;
    const long long h32 = 0b000000000000000000000001111000000000000000;
    const long long h33 = 0b000000000000000000000000111100000000000000;
    
    const long long h40 = 0b000000000000000000000000000011110000000000;  
    const long long h41 = 0b000000000000000000000000000001111000000000;
    const long long h42 = 0b000000000000000000000000000000111100000000;
    const long long h43 = 0b000000000000000000000000000000011110000000;
    
    const long long h50 = 0b000000000000000000000000000000000001111000;  
    const long long h51 = 0b000000000000000000000000000000000000111100;
    const long long h52 = 0b000000000000000000000000000000000000011110;
    const long long h53 = 0b000000000000000000000000000000000000001111;
    
    
    const long long v00 = 0b100000010000001000000100000000000000000000;  
    const long long v01 = 0b000000010000001000000100000010000000000000;
    const long long v02 = 0b000000000000001000000100000010000001000000;
    
    const long long v10 = 0b010000001000000100000010000000000000000000;  
    const long long v11 = 0b000000001000000100000010000001000000000000;
    const long long v12 = 0b000000000000000100000010000001000000100000;
    
    const long long v20 = 0b001000000100000010000001000000000000000000;  
    const long long v21 = 0b000000000100000010000001000000100000000000;
    const long long v22 = 0b000000000000000010000001000000100000010000;
    
    const long long v30 = 0b000100000010000001000000100000000000000000;  
    const long long v31 = 0b000000000010000001000000100000010000000000;
    const long long v32 = 0b000000000000000001000000100000010000001000;
    
    const long long v40 = 0b000010000001000000100000010000000000000000;  
    const long long v41 = 0b000000000001000000100000010000001000000000;
    const long long v42 = 0b000000000000000000100000010000001000000100;
    
    const long long v50 = 0b000001000000100000010000001000000000000000;  
    const long long v51 = 0b000000000000100000010000001000000100000000;
    const long long v52 = 0b000000000000000000010000001000000100000010;
    
    const long long v60 = 0b000000100000010000001000000100000000000000;  
    const long long v61 = 0b000000000000010000001000000100000010000000;
    const long long v62 = 0b000000000000000000001000000100000010000001;
    
    
    
    const long long d000 = 0b100000001000000010000000100000000000000000;  
    const long long d001 = 0b010000000100000001000000010000000000000000;  
    const long long d002 = 0b001000000010000000100000001000000000000000;  
    const long long d003 = 0b000100000001000000010000000100000000000000;  
    
    const long long d010 = 0b000000010000000100000001000000010000000000;  
    const long long d011 = 0b000000001000000010000000100000001000000000;  
    const long long d012 = 0b000000000100000001000000010000000100000000;
    const long long d013 = 0b000000000010000000100000001000000010000000;
    
    const long long d020 = 0b000000000000001000000010000000100000001000;
    const long long d021 = 0b000000000000000100000001000000010000000100;  
    const long long d022 = 0b000000000000000010000000100000001000000010;
    const long long d023 = 0b000000000000000001000000010000000100000001;
    
    
    const long long d100 = 0b000000100000100000100000100000000000000000;
    const long long d101 = 0b000001000001000001000001000000000000000000;  
    const long long d102 = 0b000010000010000010000010000000000000000000;
    const long long d103 = 0b000100000100000100000100000000000000000000;
    
    const long long d110 = 0b000000000000010000010000010000010000000000;
    const long long d111 = 0b000000000000100000100000100000100000000000;  
    const long long d112 = 0b000000000001000001000001000001000000000000;
    const long long d113 = 0b000000000010000010000010000010000000000000;
    
    const long long d120 = 0b000000000000000000001000001000001000001000;
    const long long d121 = 0b000000000000000000010000010000010000010000;  
    const long long d122 = 0b000000000000000000100000100000100000100000;
    const long long d123 = 0b000000000000000001000001000001000001000000;
    
    long long winningMasks[69] = {
        h00, h01, h02, h03,
        h10, h11, h12, h13,
        h20, h21, h22, h23,
        h30, h31, h32, h33,
        h40, h41, h42, h43,
        h50, h51, h52, h53,
        v00, v01, v02,
        v10, v11, v12,
        v20, v21, v22,
        v30, v31, v32,
        v40, v41, v42,
        v50, v51, v52,
        v60, v61, v62,
        d000, d001, d002, d003,
        d010, d011, d012, d013,
        d020, d021, d022, d023,
        d100, d101, d102, d103,
        d110, d111, d112, d113,
        d120, d121, d122, d123
    };        
} 

#endif	/* CONSTANTS_H */

