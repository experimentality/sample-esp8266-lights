#include <Homie.h>

const int PIN_RELAY = D6;

HomieNode lightNode("boton", "boton");

bool botonHandler(String value) {
  if (value == "true") {
    digitalWrite(PIN_RELAY, HIGH);
    Homie.setNodeProperty(lightNode, "on", "true"); // Update the state of the light
    Serial.println("Light is on");
  } else if (value == "false") {
    digitalWrite(PIN_RELAY, LOW);
    Homie.setNodeProperty(lightNode, "on", "false");
    Serial.println("Light is off");
  } else {
    return false;
  }

  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  delay(2000);

  Homie.setFirmware("boton-relay", "1.0.0");
  lightNode.subscribe("on", botonHandler);
  Homie.registerNode(lightNode);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
