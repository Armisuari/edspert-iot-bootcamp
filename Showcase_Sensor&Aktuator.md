# SHOWCASE_Sensor & Aktuator Pertemuan 4
Kode ini dapat digunakan sebagai payload data untuk pengiriman data menggunakan protokol MQTT dan HTTP

Kode yang Anda berikan bertujuan untuk membaca sensor suhu, kelembaban, intensitas cahaya, dan mendeteksi gerakan menggunakan DHT22, LDR, dan sensor PIR, serta menampilkan hasilnya di layar OLED.

### Kebutuhan Library:
- Adafruit GFX Library by Adafruit (1.11.19)
- Adafruit SSD1306 by Adafruit (2.5.9)
- DHT sensor library [DHT sensor library by Adafruit]

### Skema Rangkaian
![Gambar Rangkaian](https://github.com/Armisuari/edspert-iot-bootcamp/blob/main/gambar/asasads.jpg)
### Code
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//========= LDR Sensor ================//
const byte LDRSensor = 33;
float intensitasCahaya;

//========= DHT22 Sensor ================//
#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);     // Membuat Object
float temperature;
float humidity;

//========= PIR Motion Sensor ================//
const byte PIRSENSOR = 2;
bool motion;
String Smotion; 

//========= OLED LCD Declaration ================//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void setup() {
  Serial.begin(115200);
  splashScreenOled();
  pinMode(PIRSENSOR, INPUT);
  
}

void loop() {
  // Read sensor
  int nilaiADC = analogRead(LDRSensor);
  intensitasCahaya = intensitas(nilaiADC); // Conversi ADC ke Lux

  temperature = dht.readTemperature();       // Membaca nilai suhu
  humidity = dht.readHumidity();    // Membaca nilai kelembapan

  motion = digitalRead(PIRSENSOR);
  if(motion == 1){Smotion = "Detected";}
  else{Smotion = "Undetected";}

  displayMeassuring(temperature, humidity, intensitasCahaya, Smotion);
  delay(1000);
  display.clearDisplay();
}

//================  LDR Sensor ==========//
// Fungsi untuk mengconversi nilai ADC menjadi Intensitas
float intensitas(int adcValue){
  // These constants should match the photoresistor's "gamma" and "rl10" attributes
  const float GAMMA = 0.7;
  const float RL10 = 33;;
  // Convert the analog value into lux value:
  float voltage = adcValue / 4096. * 3.3;
  float resistance = 2000 * voltage / (1 - voltage / 3.3);
  float luxValue = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  return luxValue;
}

//================  OLED LCD ==========//
void splashScreenOled(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  // Display static text
  display.println("EDSPERT");
  display.setCursor(20, 35);
  display.println("BOOTCAMP");

  display.display();
  delay(5000); 

  display.clearDisplay();
}

void displayMeassuring(float a, float b, float c, String d){
  display.setTextSize(1.2);
  display.setTextColor(WHITE);
  display.setCursor(15, 5);
  // Display static text
  display.println("Nilai Parameter");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 15);
  display.print("Temp: ");
  display.print(a);
  display.println(" C");

  display.setCursor(10, 25);
  display.print("Hum : ");
  display.print(b);
  display.println(" %");

  display.setCursor(10, 35);
  display.print("Inte: ");
  display.print(c);
  display.println(" Lux");

  display.setCursor(10, 45);
  display.print("Obj : ");
  display.println(d);

  display.display();
}





```

