// demo of Starter Kit V2.0 - Grove Sound Sensor
// when sound larger than a certain value, led will on

const int pinSound=A3;               // pin of Sound Sensor
const int pinVbm=2;                    // pin of Vibration Motor
//const int pinLed=2;                // pin of LED
//const int pinBuz=6;
//int thresholdValue = 300;                 // the threshold to turn on or off the LED

int sndVIDX=0;
int sndVA[]={0,0,0,0,0,0,0,0,0,0};

int vbmRunit=0;
int vbmIter=0;//0,1,2,3,...,29    30,......99     100,........      149,........
              // virbration          still          vibration          still     

         

void setup(){
    Serial.begin(115200);
    pinMode(pinVbm,OUTPUT);
    //pinMode(pinLed, OUTPUT);            //set the LED on Digital 12 as an OUTPUT
    //pinMode(pinBuz,OUTPUT);
}

void loop(){

    //-----------------------------------
    //取樣本次的聲音值 (連抓32次然後平均)
    int avg=0;

    if (vbmRunit==0) {//當在震動時不可偵測聲音，因為兩者會互相干擾，必須震動完後再恢復偵測
      long v=0;
      for(int i=0;i<32;i++) {
        v+=analogRead(pinSound);
      }  
      v >>= 5;

      //----------------------------------
      //依序放進 vA 這個 circle array 中
      //每當 vidx 前進時，去計算這個 array 的平均值 => 這就等於計算近10次聲音值的平均值
      sndVA[sndVIDX]=v;
      sndVIDX=(sndVIDX+1)%10;
      
      int sum=0;
      for(int t=0;t<10;t++) {
        sum+=sndVA[t];
      }
      avg=sum/10;
  
      /*
      String str="::";
      str+=avg;
      str+=":::::::::vbmRunit=";
      str+=vbmRunit;
      str+="::vbmIter=";
      str+=vbmIter;
      Serial.println(str);
      */
      Serial.println(avg);
      
      //----------------------------------
      if (avg>280)
        vbmRunit=1;//vbmRunit++;
    }

    /*String str="::";
    str+=avg;
    str+=":::::::::vbmRunit=";
    str+=vbmRunit;
    str+="::vbmIter=";
    str+=vbmIter;
    Serial.println(str);*/
    
    
    
    //----------------------------------    
    if (vbmRunit>0) {
      if (vbmIter==0)
        digitalWrite(pinVbm,HIGH);
      else if (vbmIter==20)
        digitalWrite(pinVbm,LOW);
      vbmIter=(vbmIter+1)%200;

      if (vbmIter==199) {
        vbmRunit=0;
        for(int t=0;t<10;t++) {//must clear all to make a fresh start
          sndVA[t]=0;
        }
        
        //Serial.println("vbmRunit=0 !!!!");
      }
      
    }
    
    

    
    
    //if (vidx==0) {
      //String str="avg=";
      //str+=avg;
      //Serial.println(str);
      //Serial.println(avg);
    //}
    
    //Serial.println(v);
    delay(10);

    
    
    //int v = analogRead(pinSound);   //read the sensorValue on Analog 0
    //float dBm=16+20*log10(v);
    //Serial.println(dBm);
    //delay(200);
    
    //1.5^13(=200)-1.5^16(=700)

    //float lb=63;//dB
    //float ub=76;//dB

    /*
    x-200       y-63 
    --------- = ----------
    700-200     76-63
    */
    
    //float y=(76-63)*(x-200)/500+63;

    //String bar="";
    //for(int t=0;t<y;t++) {
    //  bar+="▅";
    //}
    
    //Serial.println(x);
    //delay(500);
    
    //if(sensorValue>thresholdValue)
    //  digitalWrite(pinLed,HIGH);
    //delay(1000);
    //digitalWrite(pinLed,LOW);
    //delay(1000);

    //digitalWrite(pinBuz, HIGH);
    //delay(1000);
    //digitalWrite(pinBuz, LOW);
    //delay(1000);

    //digitalWrite(pinVbm,HIGH);
    //delay(5000);
    //digitalWrite(pinVbm,LOW);
    //delay(10000);
    
}
