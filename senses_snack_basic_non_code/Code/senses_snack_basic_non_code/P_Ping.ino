void fn_ping() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis_ping >= 1000*interval_ping) {
    // save the last time you blinked the LED
    previousMillis_ping = currentMillis;
    cnt_ping ++;
    if (cnt_ping > 1)
    {
      Serial.print("Pinging ip ");
      Serial.println(remote_ip);

      if (Ping.ping(remote_ip)) {
        Serial.println("Success!!");
      } else {
        Serial.println("Error :(");
        ESP.restart();
      }
    } 
  }
}
