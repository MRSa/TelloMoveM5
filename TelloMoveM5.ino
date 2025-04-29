//
//  TelloMoveM5 : Tello control app with Unit ASR.
//
#include <M5Unified.h>  // Arduino / ESP-IDF Library for M5Stack Series
#include <M5GFX.h>
#include <unit_asr.hpp> // for Unit ASR
#include <AsyncUDP.h>
#include <WiFi.h>

//
//
ASRUnit asr;
AsyncUDP udp;
AsyncUDP udpStatus1;
AsyncUDP udpStatus2;

// ==========================================================
//  Enter your Tello's Wi-Fi credentials  in 'wifi_creds.h'.
// ==========================================================
#include "wifi_creds.h"
//const char* wifi_ssid = "**********";  // defined in 'wifi_creds.h'
//const char* wifi_key = "**********";   // defined in 'wifi_creds.h'

void receivedStatus1(AsyncUDPPacket& packet)
{
    Serial.write("RX(1): ");
    Serial.write(packet.data(), packet.length());
    Serial.write("\n");
}

void receivedStatus2(AsyncUDPPacket& packet)
{
    Serial.write("RX(2): ");
    Serial.write(packet.data(), packet.length());
    Serial.write("\n");
}

void sendCommandToTello(char *command)
{
    IPAddress destIp(192,168,10,1);
    int dstPort = 8889;
    AsyncUDPMessage msg = AsyncUDPMessage(1024);
    msg.printf("%s", command);
    udp.sendTo(msg, destIp, dstPort);
}

void prepareScreen()
{
    M5.Lcd.setRotation(1); // 0: portrait, 1: Landscape
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);

    M5.Lcd.setTextSize(1);
	M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    // M5.Lcd.setTextFont(2);  // 8 x 16px
    //M5.Lcd.setFont(&fonts::lgfxJapanGothic_16); // JP (8/12/16/20/24/28/32/36/40)
    //M5.Lcd.setFont(&fonts::efontJA_16_b);       // jp BOLD (10/12/14/16/24)
    //M5.Lcd.setFont(&fonts::efontJA_16);         // jp (10/12/14/16/24)

    M5.Lcd.setFont(&fonts::efontJA_24_b);
    M5.Lcd.print("TelloMoveM5\n\n");
    M5.Lcd.setFont(&fonts::efontJA_24);
}

void displayMessage(char *message, int fontColor = TFT_WHITE)
{
    M5.Lcd.fillScreen(TFT_BLACK);
	M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setFont(&fonts::efontJA_24_b);
    M5.Lcd.print("TelloMoveM5\n\n");

    M5.Lcd.setFont(&fonts::lgfxJapanGothic_24);
	M5.Lcd.setTextColor(fontColor, TFT_BLACK);
    M5.Lcd.setCursor(0, 30);
    M5.Display.println(message);
}

void takeoffHandler()
{
    displayMessage("離陸!", TFT_ORANGE);
}

void landHandler()
{
    displayMessage("着陸!", TFT_ORANGE);
}

void up70Handler()
{
    displayMessage("上昇 70", TFT_LIGHTGRAY);
}

void down70Handler()
{
    displayMessage("下降 70", TFT_LIGHTGRAY);
}

void right70Handler()
{
    displayMessage("右移動 70", TFT_LIGHTGRAY);
}

void left70Handler()
{
    displayMessage("左移動 70", TFT_LIGHTGRAY);
}

void forward70Handler()
{
    displayMessage("前進 70", TFT_LIGHTGRAY);
}

void back70Handler()
{
    displayMessage("後退 70", TFT_LIGHTGRAY);
}
void cw45Handler()
{
    displayMessage("右回り 45度", TFT_LIGHTGRAY);
}

void ccw45Handler()
{
    displayMessage("左回り 45度", TFT_LIGHTGRAY);
}

void up150Handler()
{
    displayMessage("上昇 150", TFT_WHITE);
}

void down150Handler()
{
    displayMessage("下降 150", TFT_WHITE);
}

void right150Handler()
{
    displayMessage("右移動 150", TFT_WHITE);
}

void left150Handler()
{
    displayMessage("左移動 150", TFT_WHITE);
}

void forward150Handler()
{
    displayMessage("前進 150", TFT_WHITE);
}

void back150Handler()
{
    displayMessage("後退 150", TFT_WHITE);
}
void cw90Handler()
{
    displayMessage("右回り 90度", TFT_WHITE);
}

void ccw90Handler()
{
    displayMessage("左回り 90度", TFT_WHITE);
}

void emergencyHandler()
{
    displayMessage("緊急!", TFT_ORANGE);
}

void connectedHandler()
{
    displayMessage("接続!", TFT_ORANGE);
}

void receiveHandler()
{
    Serial.println("A command received!");
    M5.Display.setCursor(0, 0);
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Display.println("(命令受信)");
}

void prepareUnitASR()
{
    int8_t port_a_pin1 = -1, port_a_pin2 = -1;
    port_a_pin1 = M5.getPin(m5::pin_name_t::port_a_pin1);
    port_a_pin2 = M5.getPin(m5::pin_name_t::port_a_pin2);
    Serial.printf("getPin: RX:%d TX:%d\n", port_a_pin1, port_a_pin2);
    asr.begin(&Serial1, 115200, port_a_pin1, port_a_pin2);
    asr.addCommandWord(0x1A, "previous",receiveHandler);
    asr.addCommandWord(0x1B, "next",receiveHandler);
    asr.addCommandWord(0x20, "zero",receiveHandler);
    asr.addCommandWord(0x21, "one",receiveHandler);
    asr.addCommandWord(0x22, "two",receiveHandler);
    asr.addCommandWord(0x23, "three",receiveHandler);
    asr.addCommandWord(0x24, "four",receiveHandler);
    asr.addCommandWord(0x25, "five",receiveHandler);
    asr.addCommandWord(0x26, "six",receiveHandler);
    asr.addCommandWord(0x27, "seven",receiveHandler);
    asr.addCommandWord(0x28, "eight",receiveHandler);
    asr.addCommandWord(0x29, "nine",receiveHandler);
    asr.addCommandWord(0x30, "ok",receiveHandler);
    asr.addCommandWord(0x31, "hi_ASR",receiveHandler);
    asr.addCommandWord(0x32, "hello",receiveHandler);
    asr.addCommandWord(0x40, "increase_speed",receiveHandler);
    asr.addCommandWord(0x41, "decrease_speed",receiveHandler);
    asr.addCommandWord(0x42, "maximum_speed",receiveHandler);
    asr.addCommandWord(0x43, "medium_speed",receiveHandler);
    asr.addCommandWord(0x44, "minimum_speed",receiveHandler);
    asr.addCommandWord(0x45, "fw_version",receiveHandler);
    asr.addCommandWord(0x4f, "out_connected",connectedHandler);
    asr.addCommandWord(0x50, "out_zero",receiveHandler);
    asr.addCommandWord(0x51, "out_one",receiveHandler);
    asr.addCommandWord(0x52, "out_two",receiveHandler);
    asr.addCommandWord(0x53, "out_three",receiveHandler);
    asr.addCommandWord(0x54, "out_four",receiveHandler);
    asr.addCommandWord(0x55, "out_five",receiveHandler);
    asr.addCommandWord(0x56, "out_six",receiveHandler);
    asr.addCommandWord(0x57, "out_seven",receiveHandler);
    asr.addCommandWord(0x58, "out_eight",receiveHandler);
    asr.addCommandWord(0x59, "out_nine",receiveHandler);
    asr.addCommandWord(0x5a, "out_ten",receiveHandler);
    asr.addCommandWord(0x5b, "out_error",receiveHandler);
    asr.addCommandWord(0x5c, "out_timeout",receiveHandler);
    asr.addCommandWord(0x5d, "out_disconnect",receiveHandler);
    asr.addCommandWord(0x5e, "out_success",receiveHandler);
    asr.addCommandWord(0x5f, "out_failure",receiveHandler);
    asr.addCommandWord(0x61, "command",receiveHandler);
    asr.addCommandWord(0x62, "takeoff",takeoffHandler);
    asr.addCommandWord(0x63, "land",landHandler);
    asr.addCommandWord(0x71, "up 70",up70Handler);
    asr.addCommandWord(0x72, "down 70",down70Handler);
    asr.addCommandWord(0x73, "right 70",right70Handler);
    asr.addCommandWord(0x74, "left 70",left70Handler);
    asr.addCommandWord(0x75, "forward 70",forward70Handler);
    asr.addCommandWord(0x76, "back 70",back70Handler);
    asr.addCommandWord(0x77, "ccw 45",ccw45Handler);
    asr.addCommandWord(0x78, "cw 45",cw45Handler);
    asr.addCommandWord(0x81, "up 150",up150Handler);
    asr.addCommandWord(0x82, "down 150",down150Handler);
    asr.addCommandWord(0x83, "right 150",right150Handler);
    asr.addCommandWord(0x84, "left 150",left150Handler);
    asr.addCommandWord(0x85, "forward 150",forward150Handler);
    asr.addCommandWord(0x86, "back 150",back150Handler);
    asr.addCommandWord(0x87, "ccw 90",ccw90Handler);
    asr.addCommandWord(0x88, "cw 90",cw90Handler);
    asr.addCommandWord(0x99, "emergency",emergencyHandler);
    asr.addCommandWord(0xfe, "announce",receiveHandler);
    asr.addCommandWord(0xff, "hi_m_five",receiveHandler);
}

void connectToTelloWiFi()
{

    WiFi.begin(wifi_ssid, wifi_key);
    WiFi.setSleep(false);

    char messageBuffer [256];
    sprintf(messageBuffer, "接続中: %s", wifi_ssid);
    displayMessage(messageBuffer, TFT_GREEN);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(550);
      Serial.print(".");
    }
    Serial.println("");
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi connected.");
      displayMessage("Connected.");
    }

    // ------
    if (udpStatus1.listen(IP_ANY_TYPE, 8890))
    {
        udpStatus1.onPacket(receivedStatus1);
    }

    // ------
    if (udpStatus2.listen(IP_ANY_TYPE, 8899))
    {
        udpStatus2.onPacket(receivedStatus2);
    }

}

//
//
//
void setup()
{
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    cfg.output_power = true;
    cfg.clear_display = true;
    cfg.led_brightness = 96;

    M5.begin(cfg);

    // ----- LED(RED) OFF : for M5StickC Plus
    pinMode(GPIO_NUM_10, OUTPUT);
    digitalWrite(GPIO_NUM_10, HIGH);

    prepareScreen();

    prepareUnitASR();
    asr.sendComandNum(0xfe);  // 起動アナウンス
    delay(500);

    connectToTelloWiFi();
    delay(500);

    displayMessage("CONNECTED.", TFT_GREEN);
    asr.sendComandNum(0x4f);  // 接続アナウンス

    if (WiFi.status() == WL_CONNECTED)
    {
        // ----- Enter SDK mode.
        sendCommandToTello("command");
    }
    else
    {
      Serial.println("ERROR>Wi-Fi connection.");
      displayMessage("ERROR>Wi-Fi connection.", TFT_RED);
    }

}

//
//
//
void loop()
{
    M5.update();
    if (asr.update()) {
        Serial.println("----------");
        Serial.println(asr.getCurrentCommandWord());
        Serial.println(asr.getCurrentCommandNum());
        Serial.println(asr.getCurrentRawMessage());
        Serial.println((asr.checkCurrentCommandHandler()));
    }

    if (M5.BtnA.wasPressed()) {
        // ----- Main Button
        asr.printCommandList();
        displayMessage("Pushed Btn A");
    } else if (M5.BtnB.wasPressed()) {
        // ----- Side Button (SEND "Emergency OFF" Command)
        displayMessage("EMERGENCY (Btn B)");
        asr.sendComandNum(0x99);
        emergencyHandler();
    }
}
