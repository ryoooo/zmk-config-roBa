# zmk-config-roBa

<img src="keymap-drawer/roBa.svg" >

## DYA Studio（実験的対応）

[フォーク元のPR #114](https://github.com/kumamuk-git/zmk-config-roBa/pull/114)を参考に、
ZMK・PMW3610ドライバー・DYAモジュールをPR最終更新時点（2026-02-18）のコミットへ固定しています。
`config/west.yml` のDYA関連依存は、互換性を確認せず個別に `main` へ変更しないでください。

左右のファームウェアをビルドして書き込み、右側をUSB接続して
[DYA Studio](https://studio.dya.cormoran.works/)から接続します。
BLE管理・設定RPC・マウス／スクロール感度調整を有効にしています。バッテリー履歴は無効です。

- キー配置、レイヤー7のHJKL矢印、既存のポインター加速・自動マウスレイヤー設定を維持しています。
- DYAの `mouse` 感度調整は既存の加速処理の後に適用されます。
  自動マウスレイヤーは既存モジュールが担当するため、DYA側のTemp-Layerは無効のまま使ってください。
- レイヤー5のスクロールはDYAの `scroll` 処理へ移行しています。
  初期倍率は1/16ですが、旧ドライバーとは端数処理・斜めスクロールの挙動が異なります。
- ドライバー変更後のポインター方向・速度、スクロール、設定保存は実機確認が必要です。
