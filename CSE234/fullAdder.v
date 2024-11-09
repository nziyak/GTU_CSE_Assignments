module fullAdder4bit (Sum, Cout, A, B);

    input [3:0] A, B;
    output [3:0] Sum;
    output Cout;

    wire [3:0] c; // Taşıma sinyalleri
    
    // Birinci basamak
    fullAdder FA1(Sum[0], c[0], A[0], B[0], 1'b0); // 1. bit, Cin = 0
    
    // İkinci basamak
    fullAdder FA2(Sum[1], c[1], A[1], B[1], c[0]); // 2. bit, Cin = 1. basamaktan gelen taşıma
    
    // Üçüncü basamak
    fullAdder FA3(Sum[2], c[2], A[2], B[2], c[1]); // 3. bit, Cin = 2. basamaktan gelen taşıma
    
    // Dördüncü basamak
    fullAdder FA4(Sum[3], Cout, A[3], B[3], c[2]); // 4. bit, Cin = 3. basamaktan gelen taşıma
    
endmodule

module fullAdder (Sum, Cout, A, B, Cin);

    input A, B, Cin;
    output Cout, Sum;

    wire w1, w2, w3;

    halfAdder(.A(A), .B(B), .SUM(w1), .CARRY(w2));
    halfAdder(.SUM(Sum), .CARRY(w3), .A(w1), .B(Cin));

    or(Cout, w2, w3);

endmodule

module halfAdder (SUM, CARRY, A, B);
    
    input A, B;
    output SUM, CARRY;
    
    assign SUM = A ^ B;
    assign CARRY = A & B;

endmodule