
/*
 Circuito:
 Pin usados por el escudo ethernet 10, 11, 12, 13
 Tampoco usar el pin 4 ya que es para la parte del lector sd
 */
//-------LIBRERIAS DE LA PLACA ETHERNET-----------------------
#include <SPI.h>
#include <Ethernet.h>
//------------------------------------------------------------


const int boton = 7;//CREAMOS UNA CONSTANTE EL CUAL ASIGNAMOS EL PING 7


//-----------------------------------------------------------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Dirección MAC de nuestro módulo ethernet
char server[] = "192.168.10.8"; //URL DEL SERVIDOR O IP EN CASO DE SER LOCAL  
IPAddress ip(192,168,10,78);// IP QUE OCUPARA LA PLACA
EthernetClient client; //CREAMOS EL CLIENTE
//-----------------------------------------------------------------------------------

void setup() {

  pinMode(boton,INPUT_PULLUP);//DECLARAMOS NUESTRAM CONSTANTE COMO UN PING
  Serial.begin(9600);//Velocidad del puerto serie
  
  while (!Serial) {
    ; 
  }
   Serial.println("Sistema Listo");//Nos indica que ya estamos en condiciones de enviar un correo

}

void loop() {

 
  if ( digitalRead(boton)==LOW ) {
    Serial.println("Botón ENCENDIO");
  }else if ( digitalRead(boton)==HIGH ) {
    Serial.println("Botón APAGADO");
  }

   
Envio_mail();//Llama a la función Envio_mail     
 
  
}
//////////////////////////////////
void Envio_mail() {
  
 delay(300);
////////////DHCP Activado////////////////////////////////   
  if (Ethernet.begin(mac) == 0) {
    Serial.println("No se pudo configurar Ethernet mediante DHCP");
    
    Ethernet.begin(mac, ip);
  }
  delay(100);
  Serial.println("conectando espere...");
 
  if (client.connect(server, 80)) {
    if ( digitalRead(boton)==LOW ) {
      Serial.println("connectado :-)");//Si se establece la conexión
      // Make a HTTP request:
      client.println("GET /arduino/pulsador.php?t=BTN_P");// Colocar la dirección del archivo que se va a leer en el servidor
      //client.println(valorPulsador);
      client.println("HTTP/1.1");
      client.println("Host: 192.168.10.8");//Dirección del servidor
      client.println();
      delay(2000);
      Serial.println("Mail Enviado");
    delay(5000);
    }else if ( digitalRead(boton)==HIGH ) {
      Serial.println("connectado :-)");//Si se establece la conexión
      // Make a HTTP request:
      client.println("GET /arduino/pulsador.php?t=BTN_A");// Colocar la dirección del archivo que se va a leer en el servidor
      //client.println(valorPulsador);
      client.println("HTTP/1.1");
      client.println("Host: 192.168.10.8");//Dirección del servidor
      client.println();
      delay(2000);
      Serial.println("Mail Enviado");
    delay(5000);
    }
    
  }
}
