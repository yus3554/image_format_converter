# image_format_converter

## Description

- 画像ファイルを他の画像形式に変換するツールです。

> [!WARNING]
> 警告
> 2024/04/15時点では、読み込みも返還もBMPにしか対応していません。

## Build

- image_format_converte.slnからビルドしてください。

## How to use

- 変換元画像ファイルを指定して実行してください。
- オプションで変換したい画像ファイルフォーマットを指定できます。（指定しない場合BMPに変換します。）
- 変換元画像ファイルと同じ場所、同じファイル名に変換後のファイルを出力します。
  - ファイル名の最後に拡張子を付与します。（例：A.bmp　→　A.bmp.bmp）

```shell
image_format_converter.exe [-f format] [変換元画像ファイル] 
```

### Example

- A.bmpをA.bmp.bmpに変換
```shell
image_format_converter.exe A.bmp
```

- B.bmpをB.bmp.bmpに変換
```shell
image_format_converter.exe B.bmp -f bmp
```

## Convertible image formats

- -fオプションで指定できるファイルフォーマットです。
  - bmp
