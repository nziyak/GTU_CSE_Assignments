#define ledPin 13
#define buttonPin 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  
}

void loop() {
  

    char selection;              // operation variable
    int Number=0;
    String data;
        int k=1;
    if( Serial.available()){
        selection=Serial.read();     // reads the code coming from C
    }
  
    switch(selection){
      
      case '1':
           digitalWrite(ledPin, HIGH);
           break;
      
      case '2':
           digitalWrite(ledPin, LOW);
           break;
      
      case '3':
           
           
 
           for(int i = 0; i < 2; i++ ){
              digitalWrite(ledPin,HIGH);
              delay(500);

              digitalWrite(ledPin,LOW);
              delay(500);
              }
            
           break;

      case '4':
 
  
    
          // checks the connection way
                
        delay(100);
        while(data==0) {
          data = Serial.readString();
          }        
           // reads the command from C code           
        
                    
        Number = data.toInt();       //string to integer
        Number=Number*Number;        //takes square of number
      
        Serial.println(Number);      //prints the result
        break;
                
      
    
    
       
}
}
