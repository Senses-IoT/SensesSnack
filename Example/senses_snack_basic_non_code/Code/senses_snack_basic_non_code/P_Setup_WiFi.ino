void setup_wifi() {

  WiFiManagerParameter custom_senses_id("senses_id"   , "senses id"   , senses_id    , 6);
  WiFiManagerParameter custom_senses_key("senses_key" , "senses key"  , senses_key   , 20);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set static ip
  //wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  //add all your parameters here
  wifiManager.addParameter(&custom_senses_id);
  wifiManager.addParameter(&custom_senses_key);

  //wifiManager.setTimeout(60);

  if (!wifiManager.autoConnect("AP-LogiSenses", "123456780")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep

#if defined(ESP8266)
    //ESP.reset();
#else
    //ESP.restart();
#endif


    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");


  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
  }

#if defined(ESP8266)
  e_senses_id    = wifiManager.read_String(6);
  e_senses_key   = wifiManager.read_String(20);

#else
  e_senses_id    = wifiManager.read_StringESP32(6);
  e_senses_key   = wifiManager.read_StringESP32(20);

#endif



  String _ssid  = wifiManager.getSSID();
  String _passw = wifiManager.getPassword();

   _ssid.toCharArray(ssid, sizeof(ssid));
   _passw.toCharArray(passw, sizeof(passw));
 

  e_senses_id.toCharArray(userid, sizeof(userid));
  e_senses_key.toCharArray(key,  sizeof(key));


  Serial.print("ssid   = ");  Serial.println(ssid );
  Serial.print("passw  = ");  Serial.println(passw ); 
  Serial.print("userid = ");  Serial.println(userid );
  Serial.print("key    = ");  Serial.println(key );
  Serial.println("==========================================");

  Serial.println("local ip");
  Serial.println(WiFi.localIP());
}



//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
