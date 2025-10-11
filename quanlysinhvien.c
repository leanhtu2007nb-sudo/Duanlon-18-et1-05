#include <stdio.h> // Thư viện nhập xuất chuẩn
#include <string.h> // Thư viện xử lý chuỗi
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h> // Thư viện kiểm tra ký tự


// Định nghĩa cấu trúc SinhVien
typedef struct {
	char hoTen[100];      // Họ tên sinh viên
	int namSinh;         // Năm sinh
	char queQuan[100];   // Quê quán
	char tenNganh[100];  // Tên ngành học

} SinhVien;


// Hàm hiển thị danh sách sinh viên
void hienThiDanhSach(SinhVien ds[], int n) {
	// In tiêu đề bảng
	printf("\nDanh sach sinh vien:\n");
	printf("%-4s %-30s %-8s %-20s %-20s\n", "STT", "Ho ten", "Nam", "Que quan", "Ten nganh");
	printf("%-4s %-30s %-8s %-20s %-20s\n", "----", "------------------------------", "----", "--------------------", "--------------------");
	// In từng dòng với giới hạn độ dài cột (để bảng không bị phá vỡ)
	for (int i = 0; i < n; i++) {
		// %-30.30s: căn trái, tối đa 30 ký tự (cắt nếu dài)
		printf("%-4d %-30.30s %-8d %-20.20s %-20.20s\n",
			   i+1,
			   ds[i].hoTen,
			   ds[i].namSinh,
			   ds[i].queQuan,
			   ds[i].tenNganh);
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


// Hàm đọc dữ liệu sinh viên từ file
int docTuFile(const char *tenFile, SinhVien danhSach[], int *soLuong);

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
			printf("7. Doc du lieu tu file\n");
		printf("0. Thoat\n");
		printf("Chon chuc nang: ");
		scanf("%d", &luaChon);
		switch(luaChon) {
			case 1: {
				// Thêm sinh viên liên tiếp cho đến khi người dùng muốn trở về
				char tiep;
				do {
					themSinhVien(danhSach, &soLuong);
					printf("Nhap 't' de them tiep, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
			case 2: {
				// Sửa sinh viên liên tiếp
				char tiep;
				do {
					suaSinhVien(danhSach, soLuong);
					printf("Nhap 't' de sua tiep, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
			case 3: {
				// Xóa sinh viên liên tiếp
				char tiep;
				do {
					xoaSinhVien(danhSach, &soLuong);
					printf("Nhap 't' de xoa tiep, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
			case 4: {
				// Hiển thị liên tiếp (nhấn 'q' để quay lại)
				char tiep;
				do {
					hienThiDanhSach(danhSach, soLuong);
					printf("Nhap 't' de hien thi lai, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
			case 5: {
				// Sắp xếp — cho phép lặp (ví dụ sắp nhiều lần)
				char tiep;
				do {
					sapXepTheoTen(danhSach, soLuong);
					printf("Nhap 't' de sap xep lai, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
			case 6: {
				// Tìm kiếm liên tiếp
				char tiep;
				do {
					timKiemTheoTen(danhSach, soLuong);
					printf("Nhap 't' de tim tiep, 'q' de tro ve menu: ");
					scanf(" %c", &tiep);
				} while (tiep == 't' || tiep == 'T');
				break;
			}
				case 7: {
					// Đọc dữ liệu từ file
					char tenFile[260];
					printf("Nhap duong dan file: ");
					scanf("%s", tenFile);
					int them = docTuFile(tenFile, danhSach, &soLuong);
					if (them < 0) printf("Khong the mo file %s\n", tenFile);
					else printf("Da them %d ban ghi tu file.\n", them);
					break;
				}
			case 0: printf("Ket thuc chuong trinh!\n"); break; // Thoát chương trình
			default: printf("Chuc nang khong hop le!\n"); // Chức năng không hợp lệ
		}
	} while(luaChon != 0);
	return 0;
}


// Hàm đọc dữ liệu sinh viên từ file
// Format mỗi dòng: Ho Ten|Nam|Que Quan|Ten Nganh
// Trả về số bản ghi mới được thêm, -1 nếu lỗi mở file
int docTuFile(const char *tenFile, SinhVien danhSach[], int *soLuong) {
	FILE *f = fopen(tenFile, "r");
	if (!f) return -1;
	char dong[512];
	int them = 0;

	// buffer để hỗ trợ định dạng 4-dòng: hoTen, nam, que, nganh
	char mau[4][512];
	int mau_count = 0;

	while (fgets(dong, sizeof dong, f)) {
		// loại bỏ CR/LF và các khoảng trắng đầu/cuối
		dong[strcspn(dong, "\r\n")] = '\0';
		// trim leading
		char *p = dong;
		while (*p && isspace((unsigned char)*p)) p++;
		// trim trailing by moving end
		char *end = p + strlen(p) - 1;
		while (end >= p && isspace((unsigned char)*end)) { *end = '\0'; end--; }

		if (*p == '\0') continue; // bỏ dòng rỗng

		if (*soLuong >= 100) break; // đã đầy

		// Nếu dòng chứa '|' => xử lý theo dạng pipe-separated
		if (strchr(p, '|') != NULL) {
			char buf[512];
			strncpy(buf, p, sizeof buf);
			buf[sizeof buf - 1] = '\0';
			char *tk = strtok(buf, "|");
			if (!tk) continue;
			strncpy(danhSach[*soLuong].hoTen, tk, sizeof danhSach[*soLuong].hoTen);
			danhSach[*soLuong].hoTen[sizeof danhSach[*soLuong].hoTen - 1] = '\0';

			tk = strtok(NULL, "|");
			danhSach[*soLuong].namSinh = tk ? atoi(tk) : 0;

			tk = strtok(NULL, "|");
			if (tk) strncpy(danhSach[*soLuong].queQuan, tk, sizeof danhSach[*soLuong].queQuan);
			else danhSach[*soLuong].queQuan[0] = '\0';
			danhSach[*soLuong].queQuan[sizeof danhSach[*soLuong].queQuan - 1] = '\0';

			tk = strtok(NULL, "|");
			if (tk) strncpy(danhSach[*soLuong].tenNganh, tk, sizeof danhSach[*soLuong].tenNganh);
			else danhSach[*soLuong].tenNganh[0] = '\0';
			danhSach[*soLuong].tenNganh[sizeof danhSach[*soLuong].tenNganh - 1] = '\0';

			(*soLuong)++;
			them++;
			// tiếp tục
			continue;
		}

		// Nếu không có '|' thì gom 4 dòng liên tiếp thành một bản ghi
		strncpy(mau[mau_count], p, sizeof mau[mau_count]);
		mau[mau_count][sizeof mau[mau_count] - 1] = '\0';
		mau_count++;

		if (mau_count == 4) {
			// gán vào danhSach
			strncpy(danhSach[*soLuong].hoTen, mau[0], sizeof danhSach[*soLuong].hoTen);
			danhSach[*soLuong].hoTen[sizeof danhSach[*soLuong].hoTen - 1] = '\0';
			danhSach[*soLuong].namSinh = atoi(mau[1]);
			strncpy(danhSach[*soLuong].queQuan, mau[2], sizeof danhSach[*soLuong].queQuan);
			danhSach[*soLuong].queQuan[sizeof danhSach[*soLuong].queQuan - 1] = '\0';
			strncpy(danhSach[*soLuong].tenNganh, mau[3], sizeof danhSach[*soLuong].tenNganh);
			danhSach[*soLuong].tenNganh[sizeof danhSach[*soLuong].tenNganh - 1] = '\0';

			(*soLuong)++;
			them++;
			mau_count = 0;
		}
	}

	// Nếu file kết thúc mà mau_count không phải 0, file thiếu dòng
	if (mau_count != 0) {
		// bỏ qua (không thêm), hoặc có thể log lỗi — ở đây chúng ta bỏ qua phần thừa
	}

	fclose(f);
	return them;
}
