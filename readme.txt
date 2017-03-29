"MAGIC FAN"

target kerja alat :
- kipas akan diam ketika berada suhu di bawah ambang batas yang ditentukan
- kipas akan berputar ketika suhu sudah melewati batas dengan kecepatan bergantung perbedaan suhu lingkungan dengan batas yang ditentukan
- lapu LED akan menyala ketika suhu terlalu panas

alat dan bahan :
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
