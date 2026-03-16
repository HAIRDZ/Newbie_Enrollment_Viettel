# Morse Code Encoder / Decoder (Version 1)

## Giới thiệu

Chương trình C dùng để **mã hóa (encode)** và **giải mã (decode)** mã Morse từ file.
Kết quả được **in ra màn hình tối đa 20 ký tự đầu tiên** và **lưu toàn bộ vào `output.txt`**.

## Biên dịch

```bash
make
```

Sau khi build sẽ tạo ra:

```
my_morse
testRunner
```

## Cách sử dụng

Encode text sang Morse:

```bash
./my_morse -e input.txt
```

Decode Morse sang text:

```bash
./my_morse -d input.txt
```

## Kiểm thử

```bash
./testRunner
```

## Yêu cầu môi trường

* GCC
* Linux / Unix

