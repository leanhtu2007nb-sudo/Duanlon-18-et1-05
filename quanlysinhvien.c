
#include <stdio.h> // Thư viện nhập xuất chuẩn
#include <string.h> // Thư viện xử lý chuỗi


// Định nghĩa cấu trúc SinhVien
typedef struct {
	char hoTen[100];      // Họ tên sinh viên
	int namSinh;         // Năm sinh
	char queQuan[100];   // Quê quán
	char tenNganh[100];  // Tên ngành học

} SinhVien;


// Hàm hiển thị danh sách sinh viên
void hienThiDanhSach(SinhVien ds[], int n) {
	printf("\nDanh sach sinh vien:\n");
	for (int i = 0; i < n; i++) {
		printf("%d. %s | %d | %s | %s\n", i+1, ds[i].hoTen, ds[i].namSinh,  ds[i].queQuan,  ds[i].tenNganh);
	}
}


// Hàm thêm sinh viên mới vào danh sách
void themSinhVien(SinhVien ds[], int *n) {
	if (*n >= 100) {
		printf("Danh sach da day!\n"); // Kiểm tra danh sách đã đầy chưa
		return;
	}
	printf("\nNhap thong tin sinh vien moi:\n");
	printf("Ho ten: ");
	getchar();
	
	fgets(ds[*n].hoTen, sizeof(ds[*n].hoTen), stdin); // Nhập họ tên
	ds[*n].hoTen[strcspn(ds[*n].hoTen, "\n")] = 0;
	printf("Nam sinh: ");
	
	scanf("%d", &ds[*n].namSinh); // Nhập năm sinh
	getchar();


	printf("Que quan: ");
	fgets(ds[*n].queQuan, sizeof(ds[*n].queQuan), stdin); // Nhập quê quán
	ds[*n].queQuan[strcspn(ds[*n].queQuan, "\n")] = 0;
	
	printf("Ten nganh: ");
	fgets(ds[*n].tenNganh, sizeof(ds[*n].tenNganh), stdin); // Nhập tên ngành
	ds[*n].tenNganh[strcspn(ds[*n].tenNganh, "\n")] = 0;
	(*n)++; // Tăng số lượng sinh viên
}


// Hàm sửa thông tin sinh viên theo số thứ tự
void suaSinhVien(SinhVien ds[], int n) {
	int stt;
	printf("Nhap so thu tu sinh vien can sua: ");
	scanf("%d", &stt);
	if (stt < 1 || stt > n) {
		printf("Khong ton tai sinh vien nay!\n"); // Kiểm tra hợp lệ
		return;
	}
	stt--;
	printf("Ho ten moi: ");
	getchar();
	fgets(ds[stt].hoTen, sizeof(ds[stt].hoTen), stdin); // Nhập họ tên mới
	ds[stt].hoTen[strcspn(ds[stt].hoTen, "\n")] = 0;
	printf("Nam sinh moi: ");
	scanf("%d", &ds[stt].namSinh); // Nhập năm sinh mới
	getchar();
	printf("Ten nganh moi: ");
	fgets(ds[stt].tenNganh, sizeof(ds[stt].tenNganh), stdin); // Nhập tên ngành mới
	ds[stt].tenNganh[strcspn(ds[stt].tenNganh, "\n")] = 0;
}


// Hàm xóa sinh viên khỏi danh sách theo số thứ tự
void xoaSinhVien(SinhVien ds[], int *n) {
	int stt;
	printf("Nhap so thu tu sinh vien can xoa: ");
	scanf("%d", &stt);
	if (stt < 1 || stt > *n) {
		printf("Khong ton tai sinh vien nay!\n"); // Kiểm tra hợp lệ
		return;
	}
	stt--;
	// Dồn các phần tử phía sau lên trên để xóa
	for (int i = stt; i < *n - 1; i++) {
		ds[i] = ds[i+1];
	}
	(*n)--;
	printf("Da xoa sinh vien!\n");
}


// Hàm sắp xếp danh sách sinh viên theo tên (tăng dần)
void sapXepTheoTen(SinhVien ds[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			if (strcmp(ds[i].hoTen, ds[j].hoTen) > 0) {
				SinhVien tmp = ds[i];
				ds[i] = ds[j];
				ds[j] = tmp;
			}
		}
	}
	printf("Da sap xep theo ten!\n");
}


// Hàm tìm kiếm sinh viên theo tên
void timKiemTheoTen(SinhVien ds[], int n) {
	char ten[100];
	printf("Nhap ten can tim: ");
	getchar();
	fgets(ten, sizeof(ten), stdin); // Nhập tên cần tìm
	ten[strcspn(ten, "\n")] = 0;
	int found = 0;
	for (int i = 0; i < n; i++) {
		if (strstr(ds[i].hoTen, ten) != NULL) { // Tìm chuỗi tên trong họ tên
			printf("%d. %s | %d | %s\n", i+1, ds[i].hoTen, ds[i].namSinh, ds[i].tenNganh);
			found = 1;
		}
	}
	if (!found) printf("Khong tim thay sinh vien!\n");
}


// Hàm main: Quản lý menu và gọi các chức năng
int main() {
	SinhVien danhSach[100]; // Mảng lưu danh sách sinh viên
	int soLuong = 0;        // Số lượng sinh viên hiện có
	int luaChon;
	do {
		printf("\n===== MENU QUAN LY SINH VIEN =====\n");
		printf("1. Them sinh vien\n");
		printf("2. Sua sinh vien\n");
		printf("3. Xoa sinh vien\n");
		printf("4. Hien thi danh sach\n");
		printf("5. Sap xep theo ten\n");
		printf("6. Tim kiem theo ten\n");
		printf("0. Thoat\n");
		printf("Chon chuc nang: ");
		scanf("%d", &luaChon);
		switch(luaChon) {
			case 1: themSinhVien(danhSach, &soLuong); break; // Thêm sinh viên
			case 2: suaSinhVien(danhSach, soLuong); break;   // Sửa sinh viên
			case 3: xoaSinhVien(danhSach, &soLuong); break;  // Xóa sinh viên
			case 4: hienThiDanhSach(danhSach, soLuong); break; // Hiển thị danh sách
			case 5: sapXepTheoTen(danhSach, soLuong); break; // Sắp xếp theo tên
			case 6: timKiemTheoTen(danhSach, soLuong); break; // Tìm kiếm theo tên
			case 0: printf("Ket thuc chuong trinh!\n"); break; // Thoát chương trình
			default: printf("Chuc nang khong hop le!\n"); // Chức năng không hợp lệ
		}
	} while(luaChon != 0);
	return 0;
}

