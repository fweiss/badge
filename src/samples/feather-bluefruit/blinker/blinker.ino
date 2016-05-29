static const int PIN = 13;
static const uint32_t DELAY = 50;

static int counter = 0;

void setup() {
  pinMode(PIN, OUTPUT);
}

void loop() {
  counter++;
  digitalWrite(PIN, (counter % 2) ? HIGH : LOW);
  delay(DELAY);
}
