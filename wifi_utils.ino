void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      rele.setState(1);
    } else if (messageTemp == "off") {
      Serial.println("off");
      rele.setState(0);
    }
  }
}

//"mqtt-communication","Kk'6.KAX{9?x~@U"

void reconnect() {
  // Loop until we're reconnected
  unsigned int start = millis();
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESPmostato", "termostato", "0000")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {

      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      while (start - millis() < 5000) {
        ArduinoOTA.handle();
        yield();
      }
      // Wait 5 seconds before retrying
    }
  }
}