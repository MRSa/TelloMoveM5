# TelloMoveM5

TelloMoveM5は、[Tello](https://www.ryzerobotics.com/jp/tello)を [M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)と[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)を使って、音声で操作するM5のアプリケーションです。
[M5Unifiedライブラリ](https://docs.m5stack.com/ja/arduino/m5unified/helloworld) を使用して作成していますので、[M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)でなくても動作するはずです。

![TelloMoveM5イメージ](https://github.com/MRSa/TelloMoveM5/blob/main/images/TelloMoveM5.jpg?raw=true)

また、[M5StickC用TF(SD) HAT](https://www.switch-science.com/collections/m5stack/products/9551)を接続したとき、動画を録画することもできます。
ただし、カードに記録された動画ファイルは直接参照はできず、ファイルをPCに転送し、ffmpegでMP4ファイルに変換する必要があります。また動画はきちんと撮れるわけではなく、あくまでもコンセプト実証程度の実装であることをご承知おきください。

![TF(SD) HAT装着＆動画撮影](https://github.com/MRSa/TelloMoveM5/blob/main/images/StickC_wTF.jpg?raw=true)

## システム構成

![システム構成](https://github.com/MRSa/TelloMoveM5/blob/main/images/TelloMoveM5_system.png?raw=true)

* [Tello (ドローン)](https://www.ryzerobotics.com/jp/tello)
* [M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)
* [Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)

## 前提条件

* [Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)は、[Unit ASRのカスタムファームウェア](https://github.com/MRSa/GokigenOSDN_documents/tree/main/miscellaneous/M5/UnitASR)のフラッシングが必要です。
* [Tello](https://www.ryzerobotics.com/jp/tello)とWi-Fi経由で接続するために、**wifi_creds.h** に [Tello](https://www.ryzerobotics.com/jp/tello)の SSID および KEY 設定が必要です。(以下の部分です)

```c++:wifi_creds.h
    const char* wifi_ssid = "TELLO-xxxxxx";
    const char* wifi_key = "";
```

----

## 動作説明

M5を起動すると、自動で[Tello](https://www.ryzerobotics.com/jp/tello)のWi-Fiに接続します。接続でできるまでしばらくお待ちください。
[Tello](https://www.ryzerobotics.com/jp/tello)との接続が完了すると、「接続しました」と[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)から発声します。

「音声コマンド一覧」を参考に、所望の操作をUnit ASRに呼びかけてください。

基本、受け付けたコマンドを画面表示と音声で応答し、[Tello](https://www.ryzerobotics.com/jp/tello)を制御します。M5の画面には、受け付けたコマンド および M5と[Tello](https://www.ryzerobotics.com/jp/tello)の電池残量をパーセント表示します。
なお、Bボタン（[M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)の場合は右サイドボタン）を押すと、緊急停止のコマンドを[Tello](https://www.ryzerobotics.com/jp/tello)に対して発行します。

![表示説明](https://github.com/MRSa/TelloMoveM5/blob/main/images/M5StickCPlus.png?raw=true)

## 音声コマンド一覧

以下のコマンドが使用可能です。　ただし、No.20～ のコマンドは、ウェイクワード（「コマンド」）の後で発声する必要があります。

![コマンド一覧](https://github.com/MRSa/TelloMoveM5/blob/main/images/commands.png?raw=true)

----

## [Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)（カスタムファームウェアおよびフラッシング）

詳細は、[Unit ASRのリポジトリ](https://github.com/MRSa/GokigenOSDN_documents/tree/main/miscellaneous/M5/UnitASR)を参照してください。

ファームウェアのフラッシングには、[Stamp ISP](https://docs.m5stack.com/ja/module/StampISP)を使用しました。（Groveケーブルを、 RXD, TXD, 5VIN, GND に接続します。）

![M5 StampISPとの接続](https://github.com/MRSa/GokigenOSDN_documents/raw/main/miscellaneous/M5/UnitASR/StampISP.jpg)

フラッシングの実行は、[Unit ASR カスタムファームウェアの生成とフラッシング](https://docs.m5stack.com/ja/guide/offline_voice/unit_asr/firmware)の「3. ファームウェアのフラッシング」に書かれている、「フラッシングツールが対応するポートを検出したら、ポートを選択してダウンロードを有効にします。 **その後、Unit ASRを接続し、** プログラムのダウンロードを開始します。」の通りで、ダウンロードのチェックを入れてから [Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)を接続する必要があります。この点、ご注意ください。

## 動画の撮影

[M5StickC用TF(SD) HAT](https://www.switch-science.com/collections/m5stack/products/9551)を接続し、動画を録画することができます。
**ろくがかいし**で動画の記録を開始し、**ろくがしゅうりょう**で動画の記録を停止します。
記録する動画ファイル名は VIDEO00.MOV で、追記モードで記録します。

なお、記録した動画ファイルは、そのまま再生はできません。ファイルをPCに転送し、[ffmpeg](https://ffmpeg.org/)を使用して MP4ファイル等に変換してご視聴ください。ffmpegを使用して変換する時のコマンドは、以下をお試しください。

```bash
    ffmpeg -i VIDEO00.MOV  (変換後ファイル名)
```

なお、動画はUDP転送ということもあり、あまり品質が高くないようです。あらかじめご承知おきください。

### カスタムファームウェア

* [V1.06(May.04, 2025)](https://github.com/MRSa/GokigenOSDN_documents/blob/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v106.bin)

----

## 参考リンク

* [Tello SDK](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20%E7%BC%96%E7%A8%8B%E7%9B%B8%E5%85%B3/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf)
* [Unit ASR カスタムファームウェアの生成とフラッシング](https://docs.m5stack.com/ja/guide/offline_voice/unit_asr/firmware)
* [smartpi.cn](https://www.smartpi.cn/)
* [Unit ASR ファームウェアフラッシングツール](https://m5stack-doc.oss-cn-shenzhen.aliyuncs.com/635/CI-03T_Serial_burning_software_V3.7.3.zip)
* [Stamp ISP](https://docs.m5stack.com/ja/module/StampISP)
* [Unit ASR カスタムファームウェア](https://github.com/MRSa/GokigenOSDN_documents/tree/main/miscellaneous/M5/UnitASR)
* [M5StickC用TF(SD) HAT(Switch Science)](https://ssci.to/9551)
* [M5StickC用TF(SD) HAT(サポートページ)](https://github.com/rin-ofumi/m5stickc_sd_hat)
* [M5stick CPlus & CPlus2 SD Backpack](https://github.com/ATOMNFT/M5stick-CPlus-SD-Backpack/tree/main)

----

Copyright 2025- GOKIGEN Project

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
