#include <stdio.h>
#include <string.h>

#define MAX 100

struct Sach {
    char maSach[20];
    char tenSach[50];
    char tacGia[50];
    float giaTien;
    char theLoai[30];
};

void nhapSach(struct Sach ds[], int *n) {
    int i;
    printf("Nhap so luong sach: ");
    scanf("%d", n);
    getchar(); 

    for (i = 0; i < *n; i++) {
        printf("\nNhap sach thu %d:\n", i + 1);
        printf("Ma sach: "); gets(ds[i].maSach);
        printf("Ten sach: "); gets(ds[i].tenSach);
        printf("Tac gia: "); gets(ds[i].tacGia);
        printf("Gia tien: "); scanf("%f", &ds[i].giaTien);
        getchar();
        printf("The loai: "); gets(ds[i].theLoai);
    }
}

void hienThi(struct Sach ds[], int n) {
    int i;
    printf("\n===== DANH SACH SACH =====\n");
    for (i = 0; i < n; i++) {
        printf("\nSach %d:\n", i + 1);
        printf("Ma sach: %s\n", ds[i].maSach);
        printf("Ten sach: %s\n", ds[i].tenSach);
        printf("Tac gia: %s\n", ds[i].tacGia);
        printf("Gia tien: %.2f\n", ds[i].giaTien);
        printf("The loai: %s\n", ds[i].theLoai);
    }
}

void themSach(struct Sach ds[], int *n) {
    int vitri, i;
    if (*n >= MAX) {
        printf("Danh sach day!\n");
        return;
    }

    printf("Nhap vi tri muon them (0 den %d): ", *n);
    scanf("%d", &vitri);
    getchar();

    if (vitri < 0 || vitri > *n) {
        printf("Vi tri khong hop le.\n");
        return;
    }

    for (i = *n; i > vitri; i--) {
        ds[i] = ds[i - 1];
    }

    printf("Nhap thong tin sach moi:\n");
    printf("Ma sach: "); gets(ds[vitri].maSach);
    printf("Ten sach: "); gets(ds[vitri].tenSach);
    printf("Tac gia: "); gets(ds[vitri].tacGia);
    printf("Gia tien: "); scanf("%f", &ds[vitri].giaTien);
    getchar();
    printf("The loai: "); gets(ds[vitri].theLoai);

    (*n)++;
}

void xoaSach(struct Sach ds[], int *n) {
    char ma[20];
    int i, j, found = 0;
    printf("Nhap ma sach muon xoa: ");
    getchar(); gets(ma);

    for (i = 0; i < *n; i++) {
        if (strcmp(ds[i].maSach, ma) == 0) {
            for (j = i; j < *n - 1; j++) {
                ds[j] = ds[j + 1];
            }
            (*n)--;
            found = 1;
            break;
        }
    }

    if (found)
        printf("Da xoa sach co ma %s.\n", ma);
    else
        printf("Khong tim thay sach.\n");
}

void capNhatSach(struct Sach ds[], int n) {
    char ma[20];
    int i, found = 0;
    printf("Nhap ma sach muon cap nhat: ");
    getchar(); gets(ma);

    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maSach, ma) == 0) {
            printf("Nhap thong tin moi:\n");
            printf("Ten sach: "); gets(ds[i].tenSach);
            printf("Tac gia: "); gets(ds[i].tacGia);
            printf("Gia tien: "); scanf("%f", &ds[i].giaTien);
            getchar();
            printf("The loai: "); gets(ds[i].theLoai);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Khong tim thay sach co ma do.\n");
}

void sapXep(struct Sach ds[], int n, int tang) {
    int i, j;
    struct Sach temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if ((tang && ds[i].giaTien > ds[j].giaTien) ||
                (!tang && ds[i].giaTien < ds[j].giaTien)) {
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    if (tang)
        printf("Da sap xep theo gia tang dan.\n");
    else
        printf("Da sap xep theo gia giam dan.\n");
}

void timSach(struct Sach ds[], int n) {
    char ten[50];
    int i, found = 0;
    printf("Nhap ten sach can tim: ");
    getchar(); gets(ten);

    for (i = 0; i < n; i++) {
        if (strstr(ds[i].tenSach, ten) != NULL) {
            printf("\nTim thay sach:\n");
            printf("Ma sach: %s\n", ds[i].maSach);
            printf("Ten sach: %s\n", ds[i].tenSach);
            printf("Tac gia: %s\n", ds[i].tacGia);
            printf("Gia tien: %.2f\n", ds[i].giaTien);
            printf("The loai: %s\n", ds[i].theLoai);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay sach.\n");
}

int main() {
    struct Sach ds[MAX];
    int n = 0, chon, kieu;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (tang/giam)\n");
        printf("7. Tim kiem sach theo ten sach\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1: nhapSach(ds, &n); break;
            case 2: hienThi(ds, n); break;
            case 3: themSach(ds, &n); break;
            case 4: xoaSach(ds, &n); break;
            case 5: capNhatSach(ds, n); break;
            case 6:
                printf("Nhap 1 (tang dan) hoac 0 (giam dan): ");
                scanf("%d", &kieu);
                sapXep(ds, n, kieu);
                break;
            case 7: timSach(ds, n); break;
            case 8: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (chon != 8);

    return 0;
}
