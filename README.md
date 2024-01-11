Khóa cửa RFID sử dụng Servo - Đồ án 1 (đồ án thiết kế phần mềm nhúng)

Thiết bị sử dụng:
- Arduino Uno R3
- Servo
- Buzzer
- LCD1602 kèm I2C
- RFID RC522
- Then cài cửa và bản lề
- Fomex

Hoạt động:
- Cần nạp scan.ino vào arduino trước để nhận diện mã thẻ RFID. Sau khi nhận diện được mã của các loại thẻ thì vào code.ino để thêm mã vào mảng lưu mã.
- Khi quẹt thẻ đúng mã thì servo quay kéo then cài cửa và cửa mở. Quẹt lại thẻ đúng lần nữa thì servo quay kéo then cài cửa và của đóng. Có thể thêm nhiều mã thẻ đúng vào code.ino để đóng và mở cửa cho nhiều thẻ.
- Khi quẹt thẻ sai thì buzzer kêu
- Trên màn hình LCD1602:
Hiển thị cửa đóng và mở mỗi khi đóng và mở
Hiển thị sai thẻ khi quẹt thẻ sai
