
class Rele{
  public:
    Rele(int pin){
      this->pin=pin;
    }
  
    void begin(){
      pinMode(pin, OUTPUT);
      this->setState(0);

    }

    bool getState(){
      return state;
    }
    void setState(bool state){
      this->state=state;
      digitalWrite(this->pin,state);
    }

    void toggle(){
      this->setState(!this->getState());
    }

  private:
    int state;
    int pin;


};
  
