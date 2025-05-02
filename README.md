# TelloMoveM5

TelloMoveM5は、Telloを [M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)と[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)を使って、音声で操作するアプリケーションです。
[M5Unifiedライブラリ](https://docs.m5stack.com/ja/arduino/m5unified/helloworld) を使用して作成していますので、[M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)でなくても動作するはずです。

![TelloMoveM5イメージ](https://github.com/MRSa/TelloMoveM5/blob/main/images/TelloMoveM5.jpg?raw=true)

## システム構成

![システム構成](https://github.com/MRSa/TelloMoveM5/blob/main/images/TelloMoveM5_system?raw=true)

* [Telloドローン](https://www.ryzerobotics.com/jp/tello)
* [M5StickC Plus](https://docs.m5stack.com/ja/core/m5stickc_plus)
* [Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)

## 前提条件

[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)は、[Unit ASRのカスタムファームウェア](https://github.com/MRSa/GokigenOSDN_documents/blob/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v104.bin)の使用が前提です。



## 動作説明

M5を起動すると、Telloに接続しようとします。接続されるまでしばらくお待ちください。
Telloと接続すると、「接続しました」とUnit ASRから発声しますので、所望の操作を
Unit ASRに呼びかけてください。

基本、受け付けたコマンドを画面表示と音声で応答し、Telloを制御します。
M5とTelloの電池残量をパーセント表示します。

なお、Bボタン（M5StickC Plusの場合は右サイドボタン）を押すと、緊急停止のコマンドを
Telloに対して発行します。

![表示説明](https://github.com/MRSa/TelloMoveM5/blob/main/images/M5StickCPlus.png?raw=true)

## 音声コマンド一覧

音声入力を受け付ける用語は、以下となります。

![コマンド一覧](https://github.com/MRSa/TelloMoveM5/blob/main/images/commands.png?raw=true)

## Unit ASR（カスタムファームウェアおよびフラッシング）

詳細は、[Unit ASRのリポジトリ](https://github.com/MRSa/GokigenOSDN_documents/tree/main/miscellaneous/M5/UnitASR)を参照してください。

ファームウェアのフラッシングには、[Stamp ISP](https://docs.m5stack.com/ja/module/StampISP)を使用しました。（Groveケーブルは、 RXD, TXD, 5VIN, GND に接続します。）

フラッシング時の注意点は、[Unit ASR ファームウェアフラッシングツール](https://docs.m5stack.com/ja/guide/offline_voice/unit_asr/firmware)の記載、「フラッシングツールが対応するポートを検出したら、ポートを選択してダウンロードを有効にします。 **その後、Unit ASRを接続し、** プログラムのダウンロードを開始します。」とあるように、ダウンロードを有効にしてから Unit ASRを接続することでした。

* [V1.04(Apr.29, 2025)](https://github.com/MRSa/GokigenOSDN_documents/blob/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v104.bin)

## 参考リンク

* [Tello SDK](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20%E7%BC%96%E7%A8%8B%E7%9B%B8%E5%85%B3/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf)
* [Unit ASR カスタムファームウェアの生成とフラッシング](https://docs.m5stack.com/ja/guide/offline_voice/unit_asr/firmware)
* [smartpi.cn](https://www.smartpi.cn/)
* [Unit ASR ファームウェアフラッシングツール](https://m5stack-doc.oss-cn-shenzhen.aliyuncs.com/635/CI-03T_Serial_burning_software_V3.7.3.zip)
* [Stamp ISP](https://docs.m5stack.com/ja/module/StampISP)

-----

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
