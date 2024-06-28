#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product {
protected:
    string product_code; // atau disebut ID
    string product_name;
    string product_color;
public:
    // Constructor
    Product(string code,  string name, string color)
        : product_code(code), product_name(name), product_color(color) {}

    // Public accessor methods
    string getCode() { return product_code; }
    string getName()  { return product_name; }
    string getColor()  { return product_color; }

    virtual void print()  {
        cout << "Kode Produk: " << product_code << endl;
        cout << "Nama Produk: " << product_name << endl;
        cout << "Warna: " << product_color << endl;
    }

    virtual ~Product() = default; // Virtual destructor for proper cleanup
};

class Botol_Minum : public Product {
protected:
    float volume;
public:
    Botol_Minum( string code,  string name,  string color, float vol)
        : Product(code, name, color), volume(vol) {}

    void print()  override {
        Product::print();
        cout << "Volume: " << volume << " L" << endl;
    }
};

class Mouse : public Product {
protected:
    int battery;
public:
    Mouse( string code,  string name, string color, int bat)
        : Product(code, name, color), battery(bat) {}

    void print()  override {
        Product::print();
        cout << "Baterai: " << battery << " mAh" << endl;
    }
};

void addProduct(vector<Product*> container) {
    int type;
    string code, name, color;

    cout << "Berikut merupakan jenis produk yang tersedia" << endl;
    cout << "1. Botol Minum" << endl;
    cout << "2. Mouse" << endl;
    cout << "Pilih jenis produk: ";
    cin >> type;

    cout << "Masukkan kode produk: ";
    cin >> code;

    // Periksa apakah kode produk sudah ada
    for ( auto& product : container) {
        if (product->getCode() == code) {
            cout << "Kode produk sudah ada! Masukkan kode produk yang berbeda." << endl;
            return;
        }
    }

    cout << "Masukkan nama produk: ";
    cin >> name;
    cout << "Masukkan warna produk: ";
    cin >> color;

    if (type == 1) {
        float volume;
        cout << "Masukkan volume (L): ";
        cin >> volume;
        container.push_back(new Botol_Minum(code, name, color, volume));
    }
    else if (type == 2) {
        int battery;
        cout << "Masukkan kapasitas baterai (mAh): ";
        cin >> battery;
        container.push_back(new Mouse(code, name, color, battery));
    }
    else {
        cout << "Jenis produk tidak valid!" << endl;
    }
}

void editProduct(vector<Product*> container) {
    string code;
    cout << "Masukkan kode produk yang ingin diedit: ";
    cin >> code;
    for (auto& product : container) {
        if (product->getCode() == code) {
            string name, color;
            cout << "Masukkan nama produk baru: ";
            cin >> name;
            cout << "Masukkan warna produk baru: ";
            cin >> color;

            product->print(); // Display current product details
            if (auto botol = dynamic_cast<Botol_Minum*>(product)) {
                float volume;
                cout << "Volume baru (L): ";
                cin >> volume;
                *botol = Botol_Minum(code, name, color, volume);
            }
            else if (auto mouse = dynamic_cast<Mouse*>(product)) {
                int battery;
                cout << "Baterai baru (mAh): ";
                cin >> battery;
                *mouse = Mouse(code, name, color, battery);
            }
            cout << "Produk berhasil diperbarui." << endl;
            return;
        }
    }
    cout << "Produk dengan kode " << code << " tidak ditemukan." << endl;
}

void displayAllProducts( vector<Product*> container) {
    for ( auto& product : container) {
        product->print();
        cout << endl;
    }
}

void displayProductByID( vector<Product*> container,  string& code) {
    for ( auto& product : container) {
        if (product->getCode() == code) {
            product->print();
            return;
        }
    }
    cout << "Produk dengan kode " << code << " tidak ditemukan." << endl;
}

void deleteAllProducts(vector<Product*>& container) {
    for (auto& product : container) {
        delete product;
    }
    container.clear();
    cout << "Semua produk berhasil dihapus." << endl;
}

void deleteProductByID(vector<Product*> container,  string code) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if ((*it)->getCode() == code) {
            delete *it;
            container.erase(it);
            cout << "Produk dengan kode " << code << " berhasil dihapus." << endl;
            return;
        }
    }
    cout << "Produk dengan kode " << code << " tidak ditemukan." << endl;
}

int main() {
    vector<Product*> container;
    bool isRunning = true;
    int choice;

    while (isRunning) {
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Display All Product" << endl;
        cout << "4. Display Product By ID" << endl;
        cout << "5. Delete All Product" << endl;
        cout << "6. Delete Product By ID" << endl;
        cout << "0. Exut Program" << endl;

        cout << "Input Pilihan: "; cin >> choice;

        switch (choice) {
        case 1:
            addProduct(container);
            break;
        case 2:
            editProduct(container);
            break;
        case 3:
            displayAllProducts(container);
            break;
        case 4: {
            string code;
            cout << "Masukkan kode produk: ";
            cin >> code;
            displayProductByID(container, code);
            break;
        }
        case 5:
            deleteAllProducts(container);
            break;
        case 6: {
            string code;
            cout << "Masukkan kode produk: ";
            cin >> code;
            deleteProductByID(container, code);
            break;
        }
        case 0:
            isRunning = false;
            deleteAllProducts(container); // Clean up before exiting
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
