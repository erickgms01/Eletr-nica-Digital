// Pinos leds
const int pinLed1 = 7;
const int pinLed2 = 9;

// Pinos jogadores
const int pinPedra1 = 12; 
const int pinPapel1 = 11; 
const int pinTesoura1 = 10; 

const int pinPedra2 = 6;
const int pinPapel2 = 5; 
const int pinTesoura2 = 4; 

// Pino para começar o jogo
const int startPin = 8;

// Variáveis de controle e escolhas dos jogadores
bool startButton;
bool player1Chosen = false;
bool player2Chosen = false;
int choiceP1 = 0;
int choiceP2 = 0;

const int timeLimit = 10000; // Tempo limite para escolha

void ledInicialSequen(){ 
      digitalWrite(pinLed1, HIGH);
      digitalWrite(pinLed2, HIGH);
      delay(800);
      digitalWrite(pinLed1, LOW);
      digitalWrite(pinLed2, LOW);
      delay(800);

    } 
void setup() { 
    pinMode(startPin, INPUT_PULLUP); 
    pinMode(pinPedra1, INPUT_PULLUP);
    pinMode(pinPedra2, INPUT_PULLUP);
    pinMode(pinPapel1, INPUT_PULLUP);
    pinMode(pinPapel2, INPUT_PULLUP);  
    pinMode(pinTesoura1, INPUT_PULLUP);
    pinMode(pinTesoura2, INPUT_PULLUP);
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);

    Serial.begin(9600);
}

void loop() {
     
    startButton = digitalRead(startPin);

    if (startButton == LOW) {
        Serial.println("Iniciando jogo...");
        unsigned long initialTime = millis();
        bool roundCompleted = false;
        for (int x = 0; x < 3; x++) {
          ledInicialSequen();
        }
        while ((millis() - initialTime) < timeLimit && !roundCompleted) {
            // Verificando escolhas do Jogador 1
            if (!player1Chosen) {
                if (digitalRead(pinPedra1) == LOW) {
                    choiceP1 = 1; // Pedra escolhida pelo Jogador 1
                    player1Chosen = true;
                } else if (digitalRead(pinPapel1) == LOW) {
                    choiceP1 = 2; // Papel escolhido pelo Jogador 1
                    player1Chosen = true;
                } else if (digitalRead(pinTesoura1) == LOW) {
                    choiceP1 = 3; // Tesoura escolhida pelo Jogador 1
                    player1Chosen = true;
                }
            }

            // Verificando escolhas do Jogador 2
            if (!player2Chosen) {
                if (digitalRead(pinPedra2) == LOW) {
                    choiceP2 = 1; // Pedra escolhida pelo Jogador 2
                    player2Chosen = true;
                    Serial.println("");
                } else if (digitalRead(pinPapel2) == LOW) {
                    choiceP2 = 2; // Papel escolhido pelo Jogador 2
                    player2Chosen = true;
                } else if (digitalRead(pinTesoura2) == LOW) {
                    choiceP2 = 3; // Tesoura escolhida pelo Jogador 2
                    player2Chosen = true;
                }
            }

            //Se os dois tiverem feito suas escolhas
            if (player1Chosen && player2Chosen) {
                Serial.println("Jogador 1 escolheu: " + String(choiceP1));
                Serial.println("Jogador 2 escolheu: " + String(choiceP2));
                
                // Determinando o vencedor
                if ((choiceP1 == 1 && choiceP2 == 3) || 
                    (choiceP1 == 2 && choiceP2 == 1) || 
                    (choiceP1 == 3 && choiceP2 == 2)) {
                    // Jogador 1 venceu
                    digitalWrite(pinLed1, HIGH);
                    digitalWrite(pinLed2, LOW); 
                    delay(3000);
                    digitalWrite(pinLed1, LOW);
                    delay(1000);
                    Serial.println("Jogador 1 venceu!");
                } else if ((choiceP2 == 1 && choiceP1 == 3) || 
                           (choiceP2 == 2 && choiceP1 == 1) || 
                           (choiceP2 == 3 && choiceP1 == 2)) {
                    // Jogador 2 venceu
                    digitalWrite(pinLed2, HIGH);
                    digitalWrite(pinLed1, LOW); 
                    delay(3000);
                    digitalWrite(pinLed2, LOW);
                    delay(1000);
                    Serial.println("Jogador 2 venceu!");
                } else {
                    // Empate
                    digitalWrite(pinLed1, HIGH);
                    digitalWrite(pinLed2, HIGH);
                    delay(2000);
                    digitalWrite(pinLed1, LOW);
                    digitalWrite(pinLed2, LOW);
                    Serial.println("Empate!");
                }
                
                //Rodada Concluida
                roundCompleted = true;
            }
        }
       
        // Resetando variaveis
        player1Chosen = false;
        player2Chosen = false;
        choiceP1 = 0;
        choiceP2 = 0;
    }
}
