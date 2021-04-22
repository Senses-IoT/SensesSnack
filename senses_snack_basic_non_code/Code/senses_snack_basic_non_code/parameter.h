#include "WiFiManager.h"
#include "ESP32Ping.h"

unsigned long previousMillis_ping = 0;
const long interval_ping = 180;

unsigned long previousMillis = 0;
const long interval = 1000;
int cnt_step = 0;

const IPAddress remote_ip(8, 8, 4, 4);
byte cnt_ping  = 0;


//1.ใช้จดจำค่าจากหน้าเว็บ Config แล้วส่งต่อไปบันทึกยัง EEPROM
char senses_id[6];
char senses_key[20];

char ssid[20];
char passw[20];
char userid[20];
char key[20];



//2.จดจำค่าที่อ่านมาได้จาก EEPROM  แล้วทำการแปลงกลับไปเป็น char เพื่อให้ตัวแปรข้อที่ 1 นำไปใช้งาน
String e_senses_id;
String e_senses_key;


//flag for saving data
bool shouldSaveConfig = false;
