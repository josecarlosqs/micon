const int teclaPresionada = 144, teclaSuelta = 128;
//Notas:            {C,C#,D,D#,E,F,F#,G,G#,A,A#,B}
const int notas[] = {0,1,2,3,4,5,6,7,8,9,10,11};
const int cantidadNotas = 12;
boolean estadoActual[] = {false,false,false,false,false,false,false};

const double factorConversionVelocidad = 0.1241446725317693, factorConversionCanal = 0.0146627565982405;
/*
Los potenciometros dan valores entre 0 y 1023
La velocidad solo va desde 0 a 127
Solo existen 16 canales MIDI para usar
Los factores de conversion los usamos para, que al multiplicarlos por
los valores leidos por los potenciometros, resulten en los rangos que nesecitemos.

Ejemplo: los valores del potenciometro conectado al A0 son los valores de la
velocidad, esta solo puede ir de 0 a 127 y los potenciometrosdan valores hasta 1023
entonces multiplicamos los valores de A0 con factorConversionVelocidad y resulta
en valores hasta 127.
*/
int pitchActual[] = {0,0,0,0,0,0,0};

void setup(){
  Serial.begin(115200);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(2,INPUT);
}

void loop(){
  int vPitch = analogRead(A1);
  vPitch = (int)(vPitch/100);
  
  int velocidad = analogRead(A0);
  velocidad *= factorConversionVelocidad;
  
  int canal = analogRead(A2);
  canal *= factorConversionCanal;
  
  for(int i = 0; i < cantidadNotas; i++){
    if(digitalRead(13-i) == 0 && estadoActual[i] == false){
      pitchActual[i] = notas[i]+cantidadNotas*vPitch;
      enviarDatosSerial(teclaPresionada, canal, pitchActual[i], velocidad);
      estadoActual[i] = !estadoActual[i];
    }
    if(digitalRead(13-i) == 1 && estadoActual[i] == true){
      enviarDatosSerial(teclaSuelta, canal, pitchActual[i], velocidad);
      estadoActual[i] = !estadoActual[i];
    }
  }
  delay(1);
}

/*Este metodo envia los 3 parametros de MIDI, los cuales seran
interpretados por el programa de Spikenzie Labs*/
void enviarDatosSerial(int msj, int canal, int p2, int p3){
  Serial.write(msj+canal);
  Serial.write(p2);
  Serial.write(p3);
}
