#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "header.h"
#include "define.h"


// konstanty-piny
const int WAKEUP_PIN1 = 5;
const int WAKEUP_PIN2 = 13;
// buzzer 14
const int BUZZER_PIN = 14;
const int LED_PIN = 12;
const int ENPin = 2;

// globalni promnene
bool BUTTONSTATE1 = false;
bool BUTTONSTATE2 = false;


WiFiClient wificlient;
HTTPClient http;

void feedback_timer(int duration, int quantity) {
    // feedback platformy
    for (int i = 0; i < quantity; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(duration);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
    }
}

bool pin_pressed() {
    // kontrola jake tlacitko bylo zmacknuto
    if (BUTTONSTATE1 == false) {
        return true;
    } else {
        return false;
    }
}

void http_post(String HTTP_CONNECTION) {
    // posle http request zasuvce
    if (http.begin(wificlient, HTTP_CONNECTION)) {
        int httpCode = http.POST(
                (pin_pressed()) ? readEEPROM(HTTP_POS1, HTTP_LEN) : readEEPROM(HTTP_POS2,
                                                                               HTTP_LEN));
        String payload = http.getString();

        if (payload.indexOf("errors") > 0 || payload == "") {
            feedback_timer(200, 3);
        }
        Serial.println(payload);
        http.end();
    } else {
        feedback_timer(200, 3);
    }

}

void parsingIP() {
    // najde prislusnou ip adresu
    int offset = (pin_pressed()) ? IP_POSA : IP_POSB;
    int count = countIP(offset);
    if(count == 0){
        feedback_timer(200, 3);
        ESPSleep();
    } else {
        for (int i = 0; i < count; i++) {
            String HTTP_CONNECTION = "http://";
            HTTP_CONNECTION += readIP(i, offset);
            HTTP_CONNECTION += "/netio.json";
            http_post(HTTP_CONNECTION);
        }
    }
}

void wifi_setup() {
    // precte z pameti ssid a password a pripoji se k wifi
    String ssid = readEEPROM(SSID_POS, SSID_LEN);
    String password = readEEPROM(PASSWORD_POS, PASSWORD_LEN);
    char *s = const_cast<char *>(ssid.c_str()); // prevede string na char*
    char *p = const_cast<char *>(password.c_str());
    //delay(300);
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(s, p);
        for (int i = 0; i < 50; i++) { // kontroluje zda bylo pripojeno k wifi, po 5s se vypne esp
            if (WiFi.status() == WL_CONNECTED)
                break;
            delay(100);
            Serial.print(".");
        }
        if (WiFi.status() != WL_CONNECTED) {// pokud neni pripojen ohlasi chybu
            feedback_timer(200, 2);
            WiFi.disconnect();
            ESPSleep();
        }
    }
}

bool check_conf_mode() {
    // overi zda jsou oba piny zmackle pro konfiguracni mod
    if (!BUTTONSTATE1 && !BUTTONSTATE2) {
        feedback_timer(400, 1);
        Serial.println("Konf");
        setWiFiServer2();
        return true;
    } else if (BUTTONSTATE1 && BUTTONSTATE2) {
        feedback_timer(200, 4);
        ESPSleep();
        return false;
    } else
        return false;
}


void send_message() {
    wifi_setup();
    parsingIP();
}

void setup_boot() {
    // nastaveni po startu
    pinMode(ENPin, OUTPUT);
    digitalWrite(ENPin, HIGH);
    pinMode(WAKEUP_PIN1, INPUT_PULLUP);
    pinMode(WAKEUP_PIN2, INPUT_PULLUP);
    BUTTONSTATE1 = digitalRead(WAKEUP_PIN1);
    BUTTONSTATE2 = digitalRead(WAKEUP_PIN2);
    //Serial.begin(115200);
    EEPROM.begin(1024);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Načtení pinu");
}
void ESPSleep() {
    // digitalWrite(ENPin, LOW);
    ESP.deepSleep(0);

}
// void debug() { 
//     // debug zpravy z pameti
//     Serial.println(readEEPROM(SSID_POS, 64));
//     Serial.println(readEEPROM(PASSWORD_POS, 64));
//     Serial.println(readEEPROM(HTTP_POS1, 100));
//     Serial.println(readEEPROM(HTTP_POS2, 100));
//     Serial.println(BUTTONSTATE1);
//     Serial.println(BUTTONSTATE2);
// }

void setup() {
    setup_boot();
    // debug();
    if (!check_conf_mode()) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("nekonf");
        send_message();
        ESPSleep();

    }
}

void loop() {
    delay(1);
    handleServer();
    if (!digitalRead(WAKEUP_PIN1) && !digitalRead(WAKEUP_PIN2)) {
        feedback_timer(400, 1);
        ESPSleep();
    }

}