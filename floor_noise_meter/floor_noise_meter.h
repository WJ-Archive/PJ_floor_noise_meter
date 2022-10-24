class NoiseFIFO {
  protected:
  int front;
  int rear;
  int data[60];
  int maxnoise;
  public:
  NoiseFIFO(){ 
    front = rear = maxnoise = 0;
    for(int i=0; i<60;i++){
      data[i] = 30;
    }
  }
  bool isFull(){ return (rear)+1%60 == front;}
  void enqueue(int val){
     data[rear] = val;
     rear = (rear +1) % 60;
  }
  int Leq(){
    int temp;
    for(int i=0;i<60;i++){
      temp = temp + data[i];
    }
    return temp/60; 
  }
  int maxNoise(){
    if(maxnoise<data[rear-1]){
      maxnoise = data[rear-1];
    }
    return maxnoise;
  }
  void resetMax(){
    maxnoise = 0;
  }
  void DisplayQue(){
    for(int i = 0; i< 60; i++){
      Serial.println(data[i]);  
    }
  }
};

