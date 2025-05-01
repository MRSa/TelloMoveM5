# TelloMoveM5

TelloMoveM5は、Telloを M5StickC Plus + Unit ASRを使って、音声で操作するアプリケーションです。
なお、TelloMoveM5は、M5Unified を使用して作成していますので、M5StickC Plusでなくても動作するはずです。

![TelloMoveM5イメージ](https://github.com/MRSa/TelloMoveM5/blob/main/images/TelloMoveM5.jpg?raw=true)

## 動作説明

M5を起動すると、Telloに接続しようとします。接続されるまでしばらくお待ちください。
Telloと接続すると、「接続しました」とUnit ASRから発声しますので、所望の操作を
Unit ASRに呼びかけてください。

なお、Bボタン（M5StickC Plusの場合は右彩度ボタン）を押すと、緊急停止のコマンドを
Telloに対して発行します。

![表示説明](https://github.com/MRSa/TelloMoveM5/blob/main/images/M5StickCPlus.png?raw=true)

## 音声コマンド一覧

基本、受け付けたコマンドを画面表示と音声で応答し、Telloを制御します。

音声入力を受け付ける用語は、以下となります。後述の[Unit ASRのファームウェア](https://github.com/MRSa/GokigenOSDN_documents/blob/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v104.bin)を使用して下さい。

![コマンド一覧](https://github.com/MRSa/TelloMoveM5/blob/main/images/commands.png?raw=true)

## Unit ASRのファームウェア

- [V1.04(Apr.29, 2025)](https://github.com/MRSa/GokigenOSDN_documents/blob/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v104.bin)

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
