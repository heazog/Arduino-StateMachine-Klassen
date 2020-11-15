class Button{
  private:
    int mOldButtonVal = HIGH;
    int mPin = 0;
  public:
    typedef enum{no, falling, rising} tEdge;
  
    Button(int pin){
      mPin = pin;
      pinMode(mPin, INPUT_PULLUP);
    }

    tEdge edge(){
      int newButtonVal = digitalRead(mPin);

      if(newButtonVal != mOldButtonVal){
        mOldButtonVal = newButtonVal;
        if(newButtonVal == LOW){
          return falling;
        }else{
          return rising;
        }
      }  
      return no;
    }

    bool edge(int trigger){
      int newButtonVal = digitalRead(mPin);

      if(newButtonVal != mOldButtonVal){
        mOldButtonVal = newButtonVal;
        if(newButtonVal == LOW && trigger == FALLING 
        || newButtonVal == HIGH && trigger == RISING){
          return true;
        }
      }  
      return false;
    }

    int read(){
      return digitalRead(mPin);
    }

    bool operator== (int val){
      return read() == val;
    }

    bool operator() (int trigger){
      return edge(trigger);
    }
};



void setup() {
  Serial.begin(9600);
}

void loop() {
  // jede Sekunde soll ein A ausgeben werden
  // bei Tastendruck:
  // jede halbe Sekunde soll ein B ausgegeben werden
  // bei erneutem Tastendruck:
  // alle zwei Sekunden soll ein C ausgegeben werden
  // bei erneutem Tastendruck wieder A
  // Gleichzeitig soll die Anzahl der loop-Durchläufe angezeigt werden.

  static int counter = 0;
  //Serial.println(counter++);

  printABC();
  
}

void printABC(){
  static Button MyButton1(3);
  static Button startButton(4);
  static enum {A,B,C} state = A;
  static int lastTimePrinted = 0;
  int timePassed = millis() - lastTimePrinted;

  if(startButton(RISING)){
    
  }

  if(MyButton1 == HIGH){}

  switch(state){
    case A:
      if(timePassed > 1000){
        lastTimePrinted = millis();
        Serial.println("A");
      }
      if(MyButton1(FALLING)){
        state = B;
      }
      break;
    case B: 
      if(timePassed > 500){
        lastTimePrinted = millis();
        Serial.println("B");
      }
      if(MyButton1(FALLING)){
        state = C;
      }
      break;
    case C: 
      if(timePassed > 2000){
        lastTimePrinted = millis();
        Serial.println("C");
      }
      if(MyButton1(FALLING)){
        state = A;
      }
      break;
  }
}
