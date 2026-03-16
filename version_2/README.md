# Morse Code Encoder / Decoder (Version 2)

## Giới thiệu

Chương trình được viết bằng ngôn ngữ C để **mã hóa (encode)** văn bản sang mã Morse và **giải mã (decode)** mã Morse về văn bản.

Phiên bản này sử dụng **cấu trúc dữ liệu cây nhị phân (Morse Tree)** để thực hiện giải mã.
Trong cây này:

* Nhánh **trái** tương ứng với ký hiệu `+` (dot)
* Nhánh **phải** tương ứng với ký hiệu `=` (dash)

Khi decode, chương trình duyệt cây theo chuỗi Morse để tìm ra ký tự tương ứng.
Khi encode, chương trình tra bảng ánh xạ ký tự → chuỗi Morse.

Quy ước trong chương trình:

* `+` : dot
* `=` : dash
* `" "` : phân cách giữa các ký tự
* `|` : phân cách giữa các từ

Kết quả encode/decode được **ghi đầy đủ vào `output.txt`** và **in ra màn hình tối đa 20 ký tự đầu tiên**.

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

Chạy chương trình kiểm thử:

```bash
./testRunner
```

## Yêu cầu môi trường

* GCC
* Linux / Unix

