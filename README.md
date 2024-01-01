# image_format_converter

## Description

- 画像ファイルを他の画像形式に変換するツールです。

## Build

- Makefileからビルドを実行してください。

## How to use

- 変換元画像ファイルを指定して実行してください。
- オプションで変換したい画像ファイルフォーマットを指定できます。（指定しない場合PNGに変換します。）
- 変換元画像ファイルと同じ場所、同じ名前で変換後のファイルを出力します。

```shell
$ image_format_converter [-f format] [変換元画像ファイル] 
```

### Example

- A.bmpをA.pngに変換
```shell
$ image_format_converter A.bmp
```

- B.pngをB.bmpに変換
```shell
$ image_format_converter B.png -f bmp
```

## Convertible image formats

- -fオプションで指定できるファイルフォーマットです。
  - bmp
  - png
