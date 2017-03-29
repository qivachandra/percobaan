/*
"MAGIC FAN"

target kerja alat :
- kipas akan diam ketika berada suhu di bawah ambang batas yang ditentukan
- kipas akan berputar ketika suhu sudah melewati batas dengan kecepatan
bergantung perbedaan suhu lingkungan dengan batas yang ditentukan
- lapu LED akan menyala ketika suhu terlalu panas

bahan :
- ESPectro board
- sensor BMP180
- Kipas 12V DC
- Baterai 9 V
- transistor NPN
- kabel jumper

tahap tahap :
- hubungkan
1. NPN base => pin output PWM aduino
2. NPN emitor => GND Espectro dan kutub (-) baterai
3. NPN collector => seri dengan Kipas
4. Vcc => kutub (+) baterai
- sensor BMP merupakan sensor tekanan dan suhu
- digunakan output PWM untuk mengatur besar tegangan bergantung pada suhu
- rangkaian transistor merupakan rangkaian common emitor
- pin PWM pada ESPectro tidak dapat menyalakan langsung pada kipas karena output maksimal dari pin ESPectro sebesar 3.3 V dan ~0.1 mA.

SOURCE CODE :
*/
#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 sensorBMP;// mmbuat onject untuk sensor
#define ALTITUDE 1051;//ketinggian bandung

void setup() {
  Serial.begin(115200);
  //untuk mengecek snsor siap atau tidak
  if (sensorBMP.begin())
  Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  //untuk fan
  pinMode(12,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}

//ulangi terus gan
void loop() {
  //untuk BMP terlebih dahulu supaya bisa ada variabel yang disave
  char status;
  double T,P,p0,a;
  int Tmin=37;
  int Tmax=60;
  int fanSpeed;
  int led=LED_BUILTIN;
  int fan=12;

  status = sensorBMP.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = sensorBMP.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T);
      Serial.println(" deg C, ");
    }else Serial.println("error retrieving temperature measurement\n");
  }else Serial.println("error starting temperature measurement\n");


  if(T< Tmin)     // if temp is lower than minimum temp
   {
       fanSpeed = 0;      // fan is not spinning
       analogWrite(fan, 0);
       digitalWrite(fan, LOW);
       Serial.print("fanspeed :");
       Serial.println(fanSpeed,2);
   }
   //kecepatan kipas akan bergantung dengan suhu
   if((T>= Tmin) && (T <= Tmax)) // if temperature is higher than minimum temp
   {
       fanSpeed = map(T, Tmin, Tmax, 450, 1023);// kesebandingan besar suhu dengan kecepatan secara linear
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed
       Serial.print("fanspeed :");
       Serial.println(fanSpeed,2);
   }
   if(T > Tmax) // if temp is higher than tempMax
     {
     digitalWrite(led, HIGH);  // turn on led
     }
   else               // else turn of led
     {
     digitalWrite(led, LOW);
     }
delay(2);
}
