// proyecto bomba de agua 
// Control con transistor C2344
// Etapa de potecia por relevador controlado por transistor 

int baseAgua=45;

int entCisterna = A7; //
int tinAlto =A6; //
int tinBajo =A5; //
int tinOut=12;
int b_apagada=11;
int a_cisterna= 3;
int tran=2;
int estado; //1-lleno, 2-Vacio, 3-Sin agua
int cisSinAgua=10;

int lecturaAlto;
int lecturaBajo;
int cisterna_val;

void setup() {

  pinMode(cisSinAgua,OUTPUT);
  pinMode(a_cisterna,OUTPUT);
  pinMode(tran,OUTPUT);
  pinMode(tinOut,OUTPUT);
  pinMode(b_apagada,OUTPUT);
  
  Serial.begin(9600);

  digitalWrite(tinOut,HIGH);
  digitalWrite(a_cisterna,HIGH);
  //lee iniciales:
  if(analogRead(entCisterna)<baseAgua){
    estado=3;  // no hay agua
    }else if(analogRead(tinBajo)<baseAgua){
      estado=2; // tanque vacio
    }else{ //if(analogRead(tinBajo)>baseAgua)
      estado=1; // tanque lleno
     }
     
  
}

void prendeBomba(){
    digitalWrite(tran,HIGH);
    digitalWrite(b_apagada,LOW);
  }

void apagaBomba(){
    digitalWrite(tran,LOW);
    digitalWrite(b_apagada,OUTPUT);
  }

int revisaCisterna(){  // solo prende y apaga foquito
  int auxCis;
  auxCis=analogRead(entCisterna);

   if(auxCis<baseAgua){
    digitalWrite(cisSinAgua,HIGH);  // no hay agua
    }else{
      digitalWrite(cisSinAgua,LOW);
      }
     return auxCis;
    }

void loop() {
  if (estado==1){   //////////////////////////////
    apagaBomba();
    lecturaBajo=analogRead(tinBajo);
    cisterna_val=revisaCisterna();
    Serial.println("estado");
    Serial.println(estado);
    Serial.println(lecturaBajo);
    delay(999);
      if(lecturaBajo<baseAgua){ // se vacio
          estado=2;
        }
  }else if(estado ==2){  ///////////////////////
    prendeBomba();

    lecturaAlto=analogRead(tinAlto);
    cisterna_val=revisaCisterna();
    Serial.println("estado");
    Serial.println(estado);
    Serial.println(lecturaAlto);
    delay(999);

    if(cisterna_val<baseAgua){
       estado=3;
       
     }else if(lecturaAlto>baseAgua){
        estado=1;
     }
     
  }else if(estado==3){    ////////////////////////
    apagaBomba();
    digitalWrite(cisSinAgua,HIGH);

    cisterna_val=revisaCisterna();
    Serial.println("estado");
    Serial.println(estado);
  Serial.println(cisterna_val);
    delay(999);
    
     if(analogRead(entCisterna)<baseAgua){
    estado=3;  // no hay agua
    }else if(analogRead(tinBajo)<baseAgua){
      estado=2; // tanque vacio
      digitalWrite(cisSinAgua,LOW);
    }else{ //if(analogRead(tinBajo)>baseAgua)
      estado=1; // tanque lleno
      digitalWrite(cisSinAgua,LOW);
     }
  }

}
