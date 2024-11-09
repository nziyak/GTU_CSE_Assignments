module halfAdder (SUM, CARRY, A, B);
    
    input A, B;
    output SUM, CARRY;
    
    assign SUM = A ^ B;
    assign CARRY = A & B;

endmodule

