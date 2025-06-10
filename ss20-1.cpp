#include <stdio.h>
#include <string.h>

#define MAX 100

struct Book {
    char maSach[20];
    char tenSach[50];
    char tacGia[50];
    float gia;
    char theLoai[30];
};

void nhapThongTinSach(struct Book books[], int *n) {
    printf("Nhap so luong sach: ");
    scanf("%d", n);
    getchar(); 

    for (int i = 0; i < *n; i++) {
        printf("\nNhap thong tin sach thu %d:\n", i + 1);
        printf("Ma sach: ");
        gets(books[i].maSach);
        printf("Ten sach: ");
        gets(books[i].tenSach);
        printf("Tac gia: ");
        gets(books[i].tacGia);
        printf("Gia: ");
        scanf("%f", &books[i].gia);
        getchar(); 
        printf("The loai: ");
        gets(books[i].theLoai);
    }
}

void hienThiSach(struct Book books[], int n) {
    printf("\nDanh sach cac sach:\n");
    for (int i = 0; i < n; i++) {
        printf("\nSach %d:\n", i + 1);
        printf("Ma sach: %s\n", books[i].maSach);
        printf("Ten sach: %s\n", books[i].tenSach);
        printf("Tac gia: %s\n", books[i].tacGia);
        printf("Gia: %.2f\n", books[i].gia);
        printf("The loai: %s\n", books[i].theLoai);
    }
}

void themSachViTri(struct Book books[], int *n) {
    int pos;
    if (*n >= MAX) {
        printf("Danh sach da day!\n");
        return;
    }

    printf("Nhap vi tri can them (0-%d): ", *n);
    scanf("%d", &pos);
    getchar();
    if (pos < 0 || pos > *n) {
        printf("Vi tri khong hop le!\n");
        return;
    }

    for (int i = *n; i > pos; i--) {
        books[i] = books[i - 1];
    }

    printf("Nhap thong tin sach moi:\n");
    printf("Ma sach: "); gets(books[pos].maSach);
    printf("Ten sach: "); gets(books[pos].tenSach);
    printf("Tac gia: "); gets(books[pos].tacGia);
    printf("Gia: "); scanf("%f", &books[pos].gia); getchar();
    printf("The loai: "); gets(books[pos].theLoai);
    
    (*n)++;
}

void xoaSachTheoMa(struct Book books[], int *n) {
    char ma[20];
    printf("Nhap ma sach can xoa: ");
    getchar(); gets(ma);

    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(books[i].maSach, ma) == 0) {
            for (int j = i; j < *n - 1; j++) {
                books[j] = books[j + 1];
            }
            (*n)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Da xoa sach co ma %s.\n", ma);
    } else {
        printf("Khong tim thay sach co ma %s.\n", ma);
    }
}

void capNhatSach(struct Book books[], int n) {
    char ma[20];
    printf("Nhap ma sach can cap nhat: ");
    getchar(); gets(ma);

    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].maSach, ma) == 0) {
            printf("Cap nhat thong tin cho sach co ma %s:\n", ma);
            printf("Ten sach moi: "); gets(books[i].tenSach);
            printf("Tac gia moi: "); gets(books[i].tacGia);
            printf("Gia moi: "); scanf("%f", &books[i].gia); getchar();
            printf("The loai moi: "); gets(books[i].theLoai);
            return;
        }
    }

    printf("Khong tim thay sach co ma %s.\n", ma);
}

void sapXepGia(struct Book books[], int n, int tang) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tang && books[i].gia > books[j].gia) || (!tang && books[i].gia < books[j].gia)) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Da sap xep theo gia %s.\n", tang ? "tang dan" : "giam dan");
}

void timSachTheoTen(struct Book books[], int n) {
    char ten[50];
    printf("Nhap ten sach can tim: ");
    getchar(); gets(ten);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(books[i].tenSach, ten) != NULL) {
            printf("\nTim thay sach:\n");
            printf("Ma sach: %s\n", books[i].maSach);
            printf("Ten sach: %s\n", books[i].tenSach);
            printf("Tac gia: %s\n", books[i].tacGia);
            printf("Gia: %.2f\n", books[i].gia);
            printf("The loai: %s\n", books[i].theLoai);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay sach nao co ten chua \"%s\".\n", ten);
    }
}

int main() {
    struct Book books[MAX];
    int n = 0;
    int chon;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (1: tang / 0: giam)\n");
        printf("7. Tim kiem sach theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1: nhapThongTinSach(books, &n); break;
            case 2: hienThiSach(books, n); break;
            case 3: themSachViTri(books, &n); break;
            case 4: xoaSachTheoMa(books, &n); break;
            case 5: capNhatSach(books, n); break;
            case 6: {
                int kieu;
                printf("Nhap 1 (tang dan) hoac 0 (giam dan): ");
                scanf("%d", &kieu);
                sapXepGia(books, n, kieu);
                break;
            }
            case 7: timSachTheoTen(books, n); break;
            case 8: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (chon != 8);

    return 0;
}
