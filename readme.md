Mô tả Version 1

Chương trình thực hiện mã hóa và giải mã Morse bằng phương pháp tra bảng. Một bảng ánh xạ được xây dựng để liên kết mỗi ký tự chữ cái và chữ số với chuỗi Morse tương ứng. Khi encode, chương trình đọc từng ký tự từ chuỗi đầu vào, chuyển về chữ hoa, sau đó tìm chuỗi Morse tương ứng trong bảng và ghi kết quả vào file output. Khi decode, chuỗi Morse được tách thành từng token, sau đó so sánh với bảng ánh xạ để tìm ký tự tương ứng. Nếu token không tồn tại trong bảng, chương trình xác định đó là chuỗi Morse không hợp lệ.

Mô tả Version 2

Phiên bản này sử dụng cấu trúc dữ liệu cây nhị phân Morse. Trong cây, nhánh trái tương ứng với ký hiệu cộng biểu diễn dot và nhánh phải tương ứng với ký hiệu bằng biểu diễn dash. Khi giải mã, chương trình bắt đầu từ nút gốc của cây và di chuyển theo từng ký hiệu trong chuỗi Morse. Khi gặp ký tự phân cách giữa các ký tự, ký tự tại nút hiện tại được ghi vào kết quả. Phương pháp này giúp quá trình giải mã trở nên rõ ràng và có cấu trúc hơn so với việc tìm kiếm tuyến tính trong bảng ánh xạ.

Phương pháp kiểm thử

Chương trình được kiểm thử bằng một test runner tự động. Test runner tạo các trường hợp kiểm thử bao gồm các chuỗi ký tự cố định và các chuỗi được sinh ngẫu nhiên. Mỗi test được thực hiện bằng cách encode chuỗi đầu vào sang Morse, sau đó decode kết quả trở lại văn bản. Nếu chuỗi sau khi decode giống với chuỗi ban đầu thì test được xem là thành công, ngược lại sẽ được đánh dấu là thất bại. Phương pháp kiểm thử này giúp đảm bảo cả hai chức năng mã hóa và giải mã hoạt động chính xác.
