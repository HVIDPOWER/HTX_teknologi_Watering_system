int IN1 = 2;
int IN2 = 3; // Vi starter med at definere alle vores pins som kommer til at tænde og slukke for pumperne i vores switch board

int Pin1 = A0;
int Pin2 = A1; //Dette er vores pins som modtager data fra vores fugt måler

float value1 = 0;
float value2 = 0; //Disse variabler er vores værdier fra fugtmåleren

void setup() { //Vores setup funktion
  Serial.begin(9600); //Her fortæller vi vores arduino hvor hurtigt den skal sende data til vores sketch monitor(vores data vindue)
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);// Vi definere bare vores pins IN1 og IN2 til at de skal sende et signal ud istedet for at modtage et

  pinMode(Pin1, INPUT); //Her sætter vi vores Pin1 og Pin2 til at de skal modtage data og signaler
  pinMode(Pin2, INPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH); //Her sætter vi vores pins IN1 og IN2 til at de skal udsende en strøm, som man kan se ved at pumperne starter

  delay(500); // Vi venter bare lige et halvt sekund
}
void loop() { //Her begynder det sjove

  Serial.print("MOISTURE LEVEL1:"); //Vi sætter programmet til at skrive MOISTURE LEVEL1: på vores sketch monitor
  value1 = analogRead(Pin1); // Vi læser dataet fra Pin1 som får data fra vores ene fugtmåler
  float moisPercent1 = map(value1, 570, 253, 0, 100); // Vi sætter dataet fra fra fugtmåleren op så den bliver delt op i procent.
  //Den er delt op i (vores værdi fra fugtmåleren, mindste værdi i data intervallet, maks værdi i data intervallet, mindste nye værdi, højeste nye værdi)
  Serial.print(moisPercent1); //Her skriver vi vores fugt niveau i procent på vores sketch monitor
  Serial.println("%");// Så skriver vi bare % for at vi kan se det er % på vores sketch monitor
  if (moisPercent1 > 80) //Her spørger vi programmet om fugt niveauet er over 80%
  {
    digitalWrite(IN1, LOW); // Hvis ja sætter vi IN1 til LOW så den ikke udsender en strøm, og effektivt slukker for pumpen
  }
  else // Hvis den ikke er over 80%, så gør vi nedenstående
  {
    digitalWrite(IN1, HIGH); // Vi sætter IN1 til HIGH så vi for den til at udsende en strøm, og effektivt tænder pumpen
    delay(10000); //så venter vi i 10 sekunder mens den pumper vand med pumpen
    digitalWrite(IN1, LOW); // nu slukker vi den så igen ved at sætte IN1 til LOW
    delay(30000); // nu venter vi så 30 sekunder så vandet kan nå at fordele sig før vi tager endnu en måling
  }

  Serial.print("MOISTURE LEVEL2:");
  value2 = analogRead(Pin2);
  float moisPercent2 = map(value2, 570, 253, 0, 100);
  Serial.println(moisPercent2);
  Serial.println("%");
  if (moisPercent2 > 80)
  {
    digitalWrite(IN2, LOW);
  }
  else
  {
    digitalWrite(IN2, HIGH);
    delay(10000);
    digitalWrite(IN2, LOW);
    delay(30000);
  }
  // I den her blok gør vi præcist det samme som før men bare for vores anden fugtmåler, pumpe, og de to andre pins

  digitalWrite(IN1, LOW);//Her slukker programmet for den ene pumpe for at kunne bedst at tage den næste måling
  digitalWrite(IN2, LOW); //Her slukker programmet for den anden pumpe for at kunne bedst at tage den næste måling
  delay(30000);//Her venter programmet i 30 sekunder på at tage en ny måling
}
