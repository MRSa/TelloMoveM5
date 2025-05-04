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

int batteryRemainM5;
int batteryRemainTello;
int currentSpeed;
char commandMessageBuffer[256];

// ==========================================================
//  Enter your Tello's Wi-Fi credentials  in 'wifi_creds.h'.
// ==========================================================
#include "wifi_creds.h"
//const char* wifi_ssid = "**********";  // defined in 'wifi_creds.h'
//const char* wifi_key = "**********";   // defined in 'wifi_creds.h'

void displayMessage(char *message, int fontColor = TFT_WHITE)
{
    if (strlen(message) > 0)
    {
        strncpy(commandMessageBuffer, message, 255);
    }
    M5.Lcd.fillScreen(TFT_BLACK);
	M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setFont(&fonts::efontJA_24_b);
    M5.Lcd.print("TelloMoveM5\n\n");

    M5.Lcd.setFont(&fonts::lgfxJapanGothic_24);
	M5.Lcd.setTextColor(fontColor, TFT_BLACK);
    M5.Lcd.setCursor(0, 30);
    M5.Display.println(commandMessageBuffer);

    M5.Lcd.setCursor(0, 85);
    char batteryM5[64];
    sprintf(batteryM5, "    電池残量(M5) : %d %%", batteryRemainM5);
    M5.Lcd.setFont(&fonts::lgfxJapanGothic_16);
    M5.Lcd.setTextColor(getFontColor(batteryRemainM5), TFT_BLACK);
    M5.Display.println(batteryM5);

    if (batteryRemainTello > 0)
    {
        M5.Lcd.setCursor(0, 105);
        sprintf(batteryM5, "    電池残量(Tello): %d %%", batteryRemainTello);
        M5.Lcd.setFont(&fonts::lgfxJapanGothic_16);
        M5.Lcd.setTextColor(getFontColor(batteryRemainTello), TFT_BLACK);
        M5.Display.println(batteryM5);
    }
}

void receivedStatus1(AsyncUDPPacket& packet)
{
    try
    {
        // ----- Tello からのステータス情報からバッテリ残量のみ抜き出す
        String receivedString = String((char *) packet.data());
        int startIndex = receivedString.indexOf("bat:");
        int endIndex = receivedString.indexOf(";", startIndex);
        String batteryRemainString = receivedString.substring(startIndex + 4, endIndex);

        int battery_remain = atoi(batteryRemainString.c_str());
        if (batteryRemainTello != battery_remain)
        {
            batteryRemainTello = battery_remain;
            displayMessage("");
        }
        //Serial.write("RX(status): ");
        //Serial.write(packet.data(), packet.length());
        //Serial.write("\n");
    }
    catch (...)
    {
        batteryRemainTello = -1;
        Serial.write("\n");
    }
}

void receivedStatus2(AsyncUDPPacket& packet)
{
    //
    //Serial.write("RX(2): ");
    //Serial.write(packet.data(), packet.length());
    //Serial.write("\n");
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

int getFontColor(int value)
{
    int color = TFT_WHITE;
    if (batteryRemainM5 < 50) {
        color = TFT_YELLOW;
    } else if (batteryRemainM5 < 20) {
        color = TFT_RED;
    } else if (batteryRemainM5 < 20) {
        color = TFT_DARKGREY;
    }
    return (color);
}

void takeoffHandler()
{
    displayMessage("離陸!", TFT_ORANGE);
    sendCommandToTello("takeoff");
}

void landHandler()
{
    displayMessage("着陸!", TFT_ORANGE);
    sendCommandToTello("land");
}

void up40Handler()
{
    displayMessage("上昇 40", TFT_LIGHTGRAY);
    sendCommandToTello("up 40");
}

void down40Handler()
{
    displayMessage("下降 40", TFT_LIGHTGRAY);
    sendCommandToTello("down 40");
}

void right40Handler()
{
    displayMessage("右移動 40", TFT_LIGHTGRAY);
    sendCommandToTello("right 40");
}

void left40Handler()
{
    displayMessage("左移動 40", TFT_LIGHTGRAY);
    sendCommandToTello("left 40");
}

void forward40Handler()
{
    displayMessage("前進 40", TFT_LIGHTGRAY);
    sendCommandToTello("forward 40");
}

void back40Handler()
{
    displayMessage("後退 40", TFT_LIGHTGRAY);
    sendCommandToTello("back 40");
}

void cw45Handler()
{
    displayMessage("右回り 45度", TFT_LIGHTGRAY);
    sendCommandToTello("cw 45");
}

void ccw45Handler()
{
    displayMessage("左回り 45度", TFT_LIGHTGRAY);
    sendCommandToTello("ccw 45");
}

void up100Handler()
{
    displayMessage("上昇 100", TFT_WHITE);
    sendCommandToTello("up 100");
}

void down100Handler()
{
    displayMessage("下降 100", TFT_WHITE);
    sendCommandToTello("down 100");
}

void right100Handler()
{
    displayMessage("右移動 100", TFT_WHITE);
    sendCommandToTello("right 100");
}

void left100Handler()
{
    displayMessage("左移動 100", TFT_WHITE);
    sendCommandToTello("left 100");
}

void forward100Handler()
{
    displayMessage("前進 100", TFT_WHITE);
    sendCommandToTello("forward 100");
}

void back100Handler()
{
    displayMessage("後退 100", TFT_WHITE);
    sendCommandToTello("back 100");
}
void cw90Handler()
{
    displayMessage("右回り 90度", TFT_WHITE);
    sendCommandToTello("cw 90");
}

void ccw90Handler()
{
    displayMessage("左回り 90度", TFT_WHITE);
    sendCommandToTello("ccw 90");
}

void sendSpeedCommand()
{
    char cmd[16];
    char disp[24];
    sprintf(disp, "速度 %d", currentSpeed);
    sprintf(cmd, "speed %d", currentSpeed);
    displayMessage(disp, TFT_WHITE);
    sendCommandToTello(cmd);
}


void incSpeedHandler()
{
    currentSpeed = currentSpeed + 20;
    if (currentSpeed > 100)
    {
        currentSpeed = 100;
    }
    sendSpeedCommand();
}

void decSpeedHandler()
{
    currentSpeed = currentSpeed - 20;
    if (currentSpeed < 10)
    {
        currentSpeed = 10;
    }
    sendSpeedCommand();
}

void maxSpeedHandler()
{
    currentSpeed = 100;
    sendSpeedCommand();
}

void midSpeedHandler()
{
    currentSpeed = 55;
    sendSpeedCommand();
}

void minSpeedHandler()
{
    currentSpeed = 10;
    sendSpeedCommand();
}

void emergencyHandler()
{
    displayMessage("緊急停止!", TFT_ORANGE);
    sendCommandToTello("emergency");
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
    asr.addCommandWord(0x40, "increase_speed",incSpeedHandler);
    asr.addCommandWord(0x41, "decrease_speed",decSpeedHandler);
    asr.addCommandWord(0x42, "maximum_speed",maxSpeedHandler);
    asr.addCommandWord(0x43, "medium_speed",midSpeedHandler);
    asr.addCommandWord(0x44, "minimum_speed",minSpeedHandler);
    asr.addCommandWord(0x45, "fw_version",receiveHandler);
    asr.addCommandWord(0x46, "out_finished",receiveHandler);
    asr.addCommandWord(0x47, "out_started",receiveHandler);
    asr.addCommandWord(0x48, "out_desu",receiveHandler);
    asr.addCommandWord(0x49, "out_NG2",receiveHandler);
    asr.addCommandWord(0x4a, "out_NG",receiveHandler);
    asr.addCommandWord(0x4b, "out_fail",receiveHandler);
    asr.addCommandWord(0x4c, "out_ok",receiveHandler);
    asr.addCommandWord(0x4d, "out_yes",receiveHandler);
    asr.addCommandWord(0x4e, "out_accepted",receiveHandler);
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
    asr.addCommandWord(0x64, "landing",landHandler);
    asr.addCommandWord(0x65, "capture",receiveHandler);
    asr.addCommandWord(0x66, "movie_start",receiveHandler);
    asr.addCommandWord(0x67, "movie_end",receiveHandler);
    asr.addCommandWord(0x68, "status",receiveHandler);
    asr.addCommandWord(0x69, "time",receiveHandler);
    asr.addCommandWord(0x6a, "remain",receiveHandler);
    asr.addCommandWord(0x71, "up 70",up40Handler);
    asr.addCommandWord(0x72, "down 70",down40Handler);
    asr.addCommandWord(0x73, "right 70",right40Handler);
    asr.addCommandWord(0x74, "left 70",left40Handler);
    asr.addCommandWord(0x75, "forward 70",forward40Handler);
    asr.addCommandWord(0x76, "back 70",back40Handler);
    asr.addCommandWord(0x77, "ccw 45",ccw45Handler);
    asr.addCommandWord(0x78, "cw 45",cw45Handler);
    asr.addCommandWord(0x81, "up 150",up100Handler);
    asr.addCommandWord(0x82, "down 150",down100Handler);
    asr.addCommandWord(0x83, "right 150",right100Handler);
    asr.addCommandWord(0x84, "left 150",left100Handler);
    asr.addCommandWord(0x85, "forward 150",forward100Handler);
    asr.addCommandWord(0x86, "back 150",back100Handler);
    asr.addCommandWord(0x87, "ccw 90",ccw90Handler);
    asr.addCommandWord(0x88, "cw 90",cw90Handler);
    asr.addCommandWord(0x91, "out_100",receiveHandler);
    asr.addCommandWord(0x92, "out_1000",receiveHandler);
    asr.addCommandWord(0x93, "out_degree",receiveHandler);
    asr.addCommandWord(0x94, "out_percent",receiveHandler);
    asr.addCommandWord(0x95, "out_hour",receiveHandler);
    asr.addCommandWord(0x96, "out_second",receiveHandler);
    asr.addCommandWord(0x97, "out_minute",receiveHandler);
    asr.addCommandWord(0x98, "out_remain",receiveHandler);
    asr.addCommandWord(0x99, "emergency",emergencyHandler);
    asr.addCommandWord(0x9a, "out_time",receiveHandler);
    asr.addCommandWord(0x9b, "out_speed",receiveHandler);
    asr.addCommandWord(0x9c, "out_height",receiveHandler);
    asr.addCommandWord(0x9d, "out_temp",receiveHandler);
    asr.addCommandWord(0xfe, "announce",receiveHandler);
    asr.addCommandWord(0xff, "hi_m_five",receiveHandler);
}

void connectToTelloWiFi()
{
    // ------ Tello へ Wi-Fi接続
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

    // ------  状態受信１
    if (udpStatus1.listen(IP_ANY_TYPE, 8890))
    {
        udpStatus1.onPacket(receivedStatus1);
    }

    // ------  状態受信２
    if (udpStatus2.listen(IP_ANY_TYPE, 8899))
    {
        udpStatus2.onPacket(receivedStatus2);
    }
}

void setup()
{
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    cfg.output_power = true;
    cfg.clear_display = true;
    cfg.led_brightness = 96;

    M5.begin(cfg);

    M5.Power.begin(); 

    batteryRemainM5 = M5.Power.getBatteryLevel();
    batteryRemainTello = -1;

    currentSpeed = 100;

    // ----- LED(RED) OFF : for M5StickC Plus
    pinMode(GPIO_NUM_10, OUTPUT);
    digitalWrite(GPIO_NUM_10, HIGH);

    // ----- 画面表示の初期化
    prepareScreen();

    // ----- Unit ASRの初期化
    prepareUnitASR();
    asr.sendComandNum(0xfe);  // 起動アナウンス
    delay(500);

    // ----- TelloとのWi-Fi接続
    connectToTelloWiFi();
    delay(500);

    // ----- 接続完了通知
    displayMessage("CONNECTED.", TFT_GREEN);
    asr.sendComandNum(0x4f);  // 接続アナウンス

    if (WiFi.status() == WL_CONNECTED)
    {
        // ----- 接続していたら、TelloをSDKモードにする
        sendCommandToTello("command");
    }
    else
    {
        // ----- ここには入り込まないはずだが...一応エラー表示
        Serial.println("ERROR>Wi-Fi connection.");
        displayMessage("ERROR>Wi-Fi connection.", TFT_RED);
    }
}

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

    int batteryRemain = M5.Power.getBatteryLevel();
    if (batteryRemain != batteryRemainM5)
    {
        batteryRemainM5 = batteryRemain;
        displayMessage("");
    }
}
