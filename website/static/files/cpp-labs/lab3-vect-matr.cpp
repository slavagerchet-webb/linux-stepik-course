#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

using namespace std;

class vect {
private:
    void checkSameDim(const vect& r, const string& operation) const {
        if (dim != r.dim) {
            throw invalid_argument("Ошибка размерности в операции " + operation);
        }
    }

public:
    int dim;              // размерность вектора
    double* v;            // компоненты вектора
    int num;              // номер объекта
    static int count;     // количество объектов, созданных программой

    vect() : dim(0), v(nullptr), num(++count) {
        cout << "Конструктор по умолчанию: создан vect №" << num
             << ", dim = " << dim << endl;
    }

    explicit vect(int d) : dim(d), v(nullptr), num(++count) {
        if (dim < 0) {
            throw invalid_argument("Размерность вектора не может быть отрицательной");
        }
        v = (dim > 0) ? new double[dim]{} : nullptr;
        cout << "Конструктор с размерностью: создан vect №" << num
             << ", dim = " << dim << endl;
    }

    vect(int d, const double* values) : dim(d), v(nullptr), num(++count) {
        if (dim < 0) {
            throw invalid_argument("Размерность вектора не может быть отрицательной");
        }
        v = (dim > 0) ? new double[dim] : nullptr;
        for (int i = 0; i < dim; ++i) {
            v[i] = values[i];
        }
        cout << "Конструктор с массивом: создан vect №" << num
             << ", dim = " << dim << endl;
    }

    vect(const vect& w) : dim(w.dim), v(nullptr), num(++count) {
        v = (dim > 0) ? new double[dim] : nullptr;
        for (int i = 0; i < dim; ++i) {
            v[i] = w.v[i];
        }
        cout << "Конструктор копирования: создан vect №" << num
             << " как копия vect №" << w.num << endl;
    }

    ~vect() {
        cout << "Деструктор: уничтожается vect №" << num << endl;
        delete[] v;
        v = nullptr;
        dim = 0;
    }

    vect& operator=(const vect& r) {
        cout << "Оператор =: vect №" << num << " = vect №" << r.num << endl;
        if (this == &r) {
            cout << "Самоприсваивание vect №" << num << endl;
            return *this;
        }

        double* newV = (r.dim > 0) ? new double[r.dim] : nullptr;
        for (int i = 0; i < r.dim; ++i) {
            newV[i] = r.v[i];
        }

        delete[] v;
        dim = r.dim;
        v = newV;
        return *this;
    }

    vect operator+(const vect& r) const {
        checkSameDim(r, "v + v");
        cout << "Оператор +: vect №" << num << " + vect №" << r.num << endl;
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.v[i] = v[i] + r.v[i];
        }
        return res;
    }

    vect operator-(const vect& r) const {
        checkSameDim(r, "v - v");
        cout << "Оператор -: vect №" << num << " - vect №" << r.num << endl;
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.v[i] = v[i] - r.v[i];
        }
        return res;
    }

    vect operator-() const {
        cout << "Унарный оператор -: -vect №" << num << endl;
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.v[i] = -v[i];
        }
        return res;
    }

    double operator*(const vect& r) const {
        checkSameDim(r, "v * v");
        cout << "Оператор *: скалярное произведение vect №" << num
             << " и vect №" << r.num << endl;
        double res = 0.0;
        for (int i = 0; i < dim; ++i) {
            res += v[i] * r.v[i];
        }
        return res;
    }

    void print(const string& name = "vect") const {
        cout << name << " (№" << num << ") = (";
        for (int i = 0; i < dim; ++i) {
            cout << setw(8) << v[i];
            if (i + 1 < dim) {
                cout << ";";
            }
        }
        cout << " )" << endl;
    }

    friend vect operator*(double k, const vect& r);
};

int vect::count = 0;

vect operator*(double k, const vect& r) {
    cout << "Внешний оператор *: " << k << " * vect №" << r.num << endl;
    vect res(r.dim);
    for (int i = 0; i < r.dim; ++i) {
        res.v[i] = k * r.v[i];
    }
    return res;
}

class matr {
private:
    void allocate(int d) {
        dim = d;
        if (dim < 0) {
            throw invalid_argument("Размерность матрицы не может быть отрицательной");
        }
        a = (dim > 0) ? new double*[dim] : nullptr;
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim]{};
        }
    }

    void clear() {
        if (a != nullptr) {
            for (int i = 0; i < dim; ++i) {
                delete[] a[i];
            }
            delete[] a;
        }
        a = nullptr;
        dim = 0;
    }

    void checkSameDim(const matr& r, const string& operation) const {
        if (dim != r.dim) {
            throw invalid_argument("Ошибка размерности в операции " + operation);
        }
    }

public:
    int dim;       // размерность квадратной матрицы
    double** a;    // элементы матрицы

    matr() : dim(0), a(nullptr) {}

    explicit matr(int d) : dim(0), a(nullptr) {
        allocate(d);
    }

    matr(int d, const double* values) : dim(0), a(nullptr) {
        allocate(d);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                a[i][j] = values[i * dim + j];
            }
        }
    }

    matr(const matr& r) : dim(0), a(nullptr) {
        allocate(r.dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                a[i][j] = r.a[i][j];
            }
        }
    }

    ~matr() {
        clear();
    }

    matr& operator=(const matr& r) {
        if (this == &r) {
            return *this;
        }

        matr tmp(r);
        clear();
        allocate(tmp.dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                a[i][j] = tmp.a[i][j];
            }
        }
        return *this;
    }

    matr operator+(const matr& r) const {
        checkSameDim(r, "m + m");
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = a[i][j] + r.a[i][j];
            }
        }
        return res;
    }

    matr operator-(const matr& r) const {
        checkSameDim(r, "m - m");
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = a[i][j] - r.a[i][j];
            }
        }
        return res;
    }

    matr operator-() const {
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = -a[i][j];
            }
        }
        return res;
    }

    matr operator*(const matr& r) const {
        checkSameDim(r, "m * m");
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = 0.0;
                for (int k = 0; k < dim; ++k) {
                    res.a[i][j] += a[i][k] * r.a[k][j];
                }
            }
        }
        return res;
    }

    void print(const string& name = "matr") const {
        cout << name << " =" << endl;
        for (int i = 0; i < dim; ++i) {
            cout << "|";
            for (int j = 0; j < dim; ++j) {
                cout << setw(8) << a[i][j];
            }
            cout << " |" << endl;
        }
    }

    friend matr operator*(double k, const matr& r);
    friend vect operator*(const matr& m, const vect& x);
};

matr operator*(double k, const matr& r) {
    matr res(r.dim);
    for (int i = 0; i < r.dim; ++i) {
        for (int j = 0; j < r.dim; ++j) {
            res.a[i][j] = k * r.a[i][j];
        }
    }
    return res;
}

vect operator*(const matr& m, const vect& x) {
    if (m.dim != x.dim) {
        throw invalid_argument("Ошибка размерности в операции m * v");
    }

    vect res(x.dim);
    cout << "Внешний оператор *: matr * vect №" << x.num
         << ", результат vect №" << res.num << endl;

    for (int i = 0; i < m.dim; ++i) {
        res.v[i] = 0.0;
        for (int j = 0; j < m.dim; ++j) {
            res.v[i] += m.a[i][j] * x.v[j];
        }
    }
    return res;
}

int main() {
    try {
        cout << fixed << setprecision(2);

        cout << "=== Работа с векторами ===" << endl;
        double xValues[] = {1.0, 2.0, 3.0};
        double yValues[] = {4.0, 5.0, 6.0};

        vect x(3, xValues);
        vect y(3, yValues);
        x.print("x");
        y.print("y");

        vect sum = x + y;
        sum.print("x + y");

        vect dif = x - y;
        dif.print("x - y");

        vect neg = -x;
        neg.print("-x");

        double dot = x * y;
        cout << "x * y = " << dot << endl;

        vect scaled = 2.0 * x;
        scaled.print("2 * x");

        vect assigned;
        assigned = y;
        assigned.print("assigned = y");

        cout << "Создано объектов vect после векторных операций: " << vect::count << endl;

        cout << "\n=== Работа с матрицами ===" << endl;
        double aValues[] = {
            1.0, 2.0, 0.0,
            0.0, 1.0, 0.0,
            2.0, 0.0, 1.0
        };
        double bValues[] = {
            2.0, 0.0, 1.0,
            1.0, 3.0, 0.0,
            0.0, 1.0, 2.0
        };

        matr A(3, aValues);
        matr B(3, bValues);
        A.print("A");
        B.print("B");

        matr Msum = A + B;
        Msum.print("A + B");

        matr Mdif = A - B;
        Mdif.print("A - B");

        matr Mneg = -A;
        Mneg.print("-A");

        matr Mmul = A * B;
        Mmul.print("A * B");

        matr Mscaled = 3.0 * A;
        Mscaled.print("3 * A");

        matr Massigned;
        Massigned = B;
        Massigned.print("Massigned = B");

        vect Ax = A * x;
        Ax.print("A * x");

        cout << "Всего создано объектов vect за время работы программы: "
             << vect::count << endl;
    }
    catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
        return 1;
    }

    return 0;
}
