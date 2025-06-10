#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Để sử dụng tolower cho tìm kiếm

struct SanPham {
    char maSP[20];
    char tenSP[50];
    float giaNhap;
    float giaBan;
    int soLuong;
};

struct SanPham khoHang[100];
int soLuongSanPhamHienCo = 0;
float tongDoanhThu = 0;

void themSanPhamMoi() {
    if (soLuongSanPhamHienCo >= 100) {
        printf("Kho da day, khong the them san pham moi!\n");
        return;
    }

    printf("\n--- Them San Pham Moi ---\n");
    printf("Nhap ma san pham (vd: SP001): ");
    scanf("%s", khoHang[soLuongSanPhamHienCo].maSP);

    printf("Nhap ten san pham (vd: Keo mut): ");
    getchar();
    fgets(khoHang[soLuongSanPhamHienCo].tenSP, sizeof(khoHang[soLuongSanPhamHienCo].tenSP), stdin);
    khoHang[soLuongSanPhamHienCo].tenSP[strcspn(khoHang[soLuongSanPhamHienCo].tenSP, "\n")] = 0;

    printf("Nhap gia nhap: ");
    scanf("%f", &khoHang[soLuongSanPhamHienCo].giaNhap);

    printf("Nhap gia ban: ");
    scanf("%f", &khoHang[soLuongSanPhamHienCo].giaBan);

    printf("Nhap so luong: ");
    scanf("%d", &khoHang[soLuongSanPhamHienCo].soLuong);

    tongDoanhThu -= (khoHang[soLuongSanPhamHienCo].soLuong * khoHang[soLuongSanPhamHienCo].giaNhap);

    printf("Da them san pham '%s' vao kho!\n", khoHang[soLuongSanPhamHienCo].tenSP);
    soLuongSanPhamHienCo++;
}

void hienThiTatCaSanPham() {
    if (soLuongSanPhamHienCo == 0) {
        printf("\nKho chua co san pham nao.\n");
        return;
    }

    printf("\n--- Danh Sach San Pham Hien Co ---\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n", "Ma SP", "Ten SP", "Gia Nhap", "Gia Ban", "So Luong");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < soLuongSanPhamHienCo; i++) {
        printf("%-10s %-20s %-10.0f %-10.0f %-10d\n",
               khoHang[i].maSP,
               khoHang[i].tenSP,
               khoHang[i].giaNhap,
               khoHang[i].giaBan,
               khoHang[i].soLuong);
    }
    printf("--------------------------------------------------------------------\n");
}

void nhapThemSanPham() {
    char maCanTim[20];
    int soLuongThem;
    int daTimThay = 0;

    printf("\n--- Nhap Them San Pham ---\n");
    printf("Nhap ma san pham muon nhap them (hoac ma moi de them moi): ");
    scanf("%s", maCanTim);
    printf("Nhap so luong muon nhap them: ");
    scanf("%d", &soLuongThem);

    for (int i = 0; i < soLuongSanPhamHienCo; i++) {
        if (strcmp(khoHang[i].maSP, maCanTim) == 0) {
            khoHang[i].soLuong += soLuongThem;
            tongDoanhThu -= (soLuongThem * khoHang[i].giaNhap);
            printf("Da tang so luong cho san pham '%s' len %d.\n", khoHang[i].tenSP, khoHang[i].soLuong);
            daTimThay = 1;
            break;
        }
    }

    if (!daTimThay) {
        if (soLuongSanPhamHienCo >= 100) {
            printf("Kho da day, khong the them san pham moi!\n");
            return;
        }
        printf("San pham '%s' chua co trong kho. Them moi!\n", maCanTim);
        strcpy(khoHang[soLuongSanPhamHienCo].maSP, maCanTim);

        printf("Nhap ten san pham moi: ");
        getchar();
        fgets(khoHang[soLuongSanPhamHienCo].tenSP, sizeof(khoHang[soLuongSanPhamHienCo].tenSP), stdin);
        khoHang[soLuongSanPhamHienCo].tenSP[strcspn(khoHang[soLuongSanPhamHienCo].tenSP, "\n")] = 0;

        printf("Nhap gia nhap: ");
        scanf("%f", &khoHang[soLuongSanPhamHienCo].giaNhap);

        printf("Nhap gia ban: ");
        scanf("%f", &khoHang[soLuongSanPhamHienCo].giaBan);

        khoHang[soLuongSanPhamHienCo].soLuong = soLuongThem;

        tongDoanhThu -= (soLuongThem * khoHang[soLuongSanPhamHienCo].giaNhap);
        printf("Da them san pham moi '%s' vao kho!\n", khoHang[soLuongSanPhamHienCo].tenSP);
        soLuongSanPhamHienCo++;
    }
}

void banSanPham() {
    char maCanBan[20];
    int soLuongMuonBan;
    int daTimThay = 0;

    printf("\n--- Ban San Pham ---\n");
    printf("Nhap ma san pham muon ban: ");
    scanf("%s", maCanBan);
    printf("Nhap so luong muon ban: ");
    scanf("%d", &soLuongMuonBan);

    for (int i = 0; i < soLuongSanPhamHienCo; i++) {
        if (strcmp(khoHang[i].maSP, maCanBan) == 0) {
            daTimThay = 1;
            if (khoHang[i].soLuong == 0) {
                printf("San pham '%s' da HET HANG!\n", khoHang[i].tenSP);
            } else if (soLuongMuonBan > khoHang[i].soLuong) {
                printf("Khong du hang! San pham '%s' chi con %d san pham.\n", khoHang[i].tenSP, khoHang[i].soLuong);
            } else {
                khoHang[i].soLuong -= soLuongMuonBan;
                tongDoanhThu += (soLuongMuonBan * khoHang[i].giaBan);
                printf("Da ban %d san pham '%s'. Con lai %d san pham.\n",
                       soLuongMuonBan, khoHang[i].tenSP, khoHang[i].soLuong);
            }
            break;
        }
    }

    if (!daTimThay) {
        printf("Khong tim thay san pham voi ma '%s'.\n", maCanBan);
    }
}

void hienThiDoanhThu() {
    printf("\n--- Doanh Thu Hien Tai ---\n");
    printf("Tong doanh thu cua cua hang: %.0f VND\n", tongDoanhThu);
}

void update_product_info() {
    char product_id[20];
    int found = 0;

    printf("Nhap ma san pham can cap nhat: ");
    scanf("%s", product_id);

    for (int i = 0; i < soLuongSanPhamHienCo; i++) {
        if (strcmp(khoHang[i].maSP, product_id) == 0) {
            found = 1;
            printf("Ban dang cap nhat san pham: %s\n", khoHang[i].tenSP);

            printf("Nhap ten moi (hien tai: %s, bo qua neu khong doi): ", khoHang[i].tenSP);
            getchar();
            char temp_name[50];
            fgets(temp_name, sizeof(temp_name), stdin);
            temp_name[strcspn(temp_name, "\n")] = 0;
            if (strlen(temp_name) > 0) {
                strcpy(khoHang[i].tenSP, temp_name);
            }

            printf("Nhap gia nhap moi (hien tai: %.0f, nhap 0 neu khong doi): ", khoHang[i].giaNhap);
            float temp_import_price;
            scanf("%f", &temp_import_price);
            if (temp_import_price > 0) {
                khoHang[i].giaNhap = temp_import_price;
            }

            printf("Nhap gia ban moi (hien tai: %.0f, nhap 0 neu khong doi): ", khoHang[i].giaBan);
            float temp_sell_price;
            scanf("%f", &temp_sell_price);
            if (temp_sell_price > 0) {
                khoHang[i].giaBan = temp_sell_price;
            }

            printf("Nhap so luong moi (hien tai: %d, nhap 0 neu khong doi): ", khoHang[i].soLuong);
            int temp_quantity;
            scanf("%d", &temp_quantity);
            if (temp_quantity > 0) {
                khoHang[i].soLuong = temp_quantity;
            }

            printf("Cap nhat thong tin san pham thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham voi ma nay.\n");
    }
}

void sort_products_by_price() {
    if (soLuongSanPhamHienCo == 0) {
        printf("Chua co san pham nao de sap xep.\n");
        return;
    }

    int i, j;
    struct SanPham temp;
    char choice, order;

    printf("Sap xep theo gia nhap (n) hay gia ban (b)? ");
    scanf(" %c", &choice);

    printf("Sap xep tang dan (t) hay giam dan (g)? ");
    scanf(" %c", &order);

    for (i = 0; i < soLuongSanPhamHienCo - 1; i++) {
        for (j = i + 1; j < soLuongSanPhamHienCo; j++) {
            int should_swap = 0;
            if (choice == 'n') {
                if (order == 't' && khoHang[i].giaNhap > khoHang[j].giaNhap) {
                    should_swap = 1;
                } else if (order == 'g' && khoHang[i].giaNhap < khoHang[j].giaNhap) {
                    should_swap = 1;
                }
            } else if (choice == 'b') {
                if (order == 't' && khoHang[i].giaBan > khoHang[j].giaBan) {
                    should_swap = 1;
                } else if (order == 'g' && khoHang[i].giaBan < khoHang[j].giaBan) {
                    should_swap = 1;
                }
            } else {
                printf("Lua chon sap xep khong hop le.\n");
                return;
            }

            if (should_swap) {
                temp = khoHang[i];
                khoHang[i] = khoHang[j];
                khoHang[j] = temp;
            }
        }
    }
    printf("San pham da duoc sap xep.\n");
    hienThiTatCaSanPham();
}

void search_product() {
    if (soLuongSanPhamHienCo == 0) {
        printf("Chua co san pham nao de tim kiem.\n");
        return;
    }

    char keyword[50];
    int found_count = 0;

    printf("Nhap ma hoac ten san pham can tim: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for(int i = 0; keyword[i]; i++){
        keyword[i] = tolower(keyword[i]);
    }

    printf("\n--- KET QUA TIM KIEM ---\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n", "Ma SP", "Ten SP", "Gia nhap", "Gia ban", "So luong");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < soLuongSanPhamHienCo; i++) {
        char product_name_lower[50];
        char product_id_lower[20];

        strcpy(product_name_lower, khoHang[i].tenSP);
        for(int j = 0; product_name_lower[j]; j++){
            product_name_lower[j] = tolower(product_name_lower[j]);
        }
        strcpy(product_id_lower, khoHang[i].maSP);
        for(int j = 0; product_id_lower[j]; j++){
            product_id_lower[j] = tolower(product_id_lower[j]);
        }
        
        if (strstr(product_id_lower, keyword) != NULL || strstr(product_name_lower, keyword) != NULL) {
            printf("%-10s %-20s %-10.0f %-10.0f %-10d\n",
                   khoHang[i].maSP,
                   khoHang[i].tenSP,
                   khoHang[i].giaNhap,
                   khoHang[i].giaBan,
                   khoHang[i].soLuong);
            found_count++;
        }
    }
    printf("--------------------------------------------------------------------\n");

    if (found_count == 0) {
        printf("Khong tim thay san pham nao.\n");
    }
}


int main() {
    int luaChon;

    do {
        printf("\n======= MENU QUAN LY SAN PHAM =======\n");
        printf("1. Them san pham moi\n");
        printf("2. Hien thi tat ca san pham\n");
        printf("3. Nhap them san pham (tang so luong hoac them moi)\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Hien thi doanh thu hien tai\n");
        printf("0. Thoat chuong trinh\n");
        printf("=======================================\n");
        printf("Moi ban chon chuc nang: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                themSanPhamMoi();
                break;
            case 2:
                hienThiTatCaSanPham();
                break;
            case 3:
                nhapThemSanPham();
                break;
            case 4:
                update_product_info();
                break;
            case 5:
                sort_products_by_price();
                break;
            case 6:
                search_product();
                break;
            case 7:
                banSanPham();
                break;
            case 8:
                hienThiDoanhThu();
                break;
            case 0:
                printf("Cam on ban da su dung chuong trinh! Tam biet.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}