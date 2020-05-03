// Brian Pereira Alegria
// brpereir
// Matrix.java

@SuppressWarnings("overrides")
public class Matrix {
    private class Entry {
        private int column;
        private double value;

        Entry(int column, double value) {
            this.column = column;
            this.value = value;
        }

        public boolean equals(Object x) {
            boolean eq = false;
            Entry that;
            if (x instanceof Entry) {
                that = (Entry) x;
                eq = (this.column == that.column && this.value == that.value);
            }
            return eq;
        }

        public String toString() {
            return ("(" + column + ", " + value + ")");
        }
    }

    private int numItems;
    private int nonZero;
    private List[] R;

    // Constuctor
    // Makes a new n x n zero Matrix. pre: n>=1
    Matrix(int n) {
        if (n < 1) {
            throw new RuntimeException("Error: Matrix() called on invalid size of Matrix");
        }
        R = new List[n + 1];
        nonZero = 0;
        int m = 0;
        while (m < (n + 1)) {
            R[m] = new List();
            m++;
        }
        numItems = n;
    }

    // Returns n, the number of rows and columns of this Matrix
    int getSize() {
        return numItems;
    }

    // Returns the number of non-zero entries in this Matrix
    int getNNZ() {
        return nonZero;
    }

    // Adds an extra row to Matrix
    int format() {
        return numItems + 1;
    }

    // Sets this Matrix to the zero state
    void makeZero() {
        int n = 0;
        while (n < format()) {
            R[n].clear();
            n++;
        }
        nonZero = 0;
    }

    // overrides Object's equals() method
    public boolean equals(Object x) {
        int i = 0;
        if (x instanceof Matrix) {
            Matrix A = (Matrix) x;
            if (!(A.format() == this.format()) || (A.getNNZ() != this.getNNZ())) {
                return false;
            }
            while (i < format()) {
                if (R[i].equals(A.R[i]) == false) {
                    return false;
                }
                i++;
            }
            return true;
        }
        return false;
    }

    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x) {
        if (1 > i || i > getSize()) {
            throw new RuntimeException("Error: changeEntry() called on invalid R");
        }
        if (1 > j || j > getSize()) {
            throw new RuntimeException(" Error: changeEntry() called on invalid column");
        }
        Entry A = new Entry(j, x);
        Entry entry;
        boolean track = false;
        int z = R[i].length();
        if (x == 0) {
            if (z > 0) {
                for (R[i].moveFront(); 0 <= R[i].index(); R[i].moveNext()) {
                    entry = (Entry) R[i].get();
                    if (entry.column == j)
                        if (!(0 == (int) entry.value)) {
                            R[i].delete();
                            nonZero--;
                            break;
                        }
                }
            }
        }

        if (x != 0) {
            if (z > 0) {
                for (R[i].moveFront(); 0 <= R[i].index(); R[i].moveNext()) {
                    entry = (Entry) R[i].get();
                    if (entry.column == j) {
                        R[i].delete();
                        nonZero--;
                        break;
                    }
                }
                for (R[i].moveFront(); 0 <= R[i].index(); R[i].moveNext()) {
                    entry = (Entry) R[i].get();
                    if (j < entry.column) {
                        R[i].insertBefore(A);
                        nonZero++;
                        track = true;
                        break;
                    }
                }
                if (track == false) {
                    R[i].append(A);
                    nonZero++;
                }
            } else {
                R[i].append(A);
                nonZero++;
            }
        }
    }

    // returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x) {
        Entry E;
        Matrix matrix = new Matrix(getSize());
        int n = 0;
        while (n < format()) {
            for (R[n].moveFront(); R[n].index() >= 0; R[n].moveNext()) {
                E = (Entry) R[n].get();
                matrix.changeEntry(n, E.column, (E.value) * x);
            }
            n++;
        }
        return matrix;
    }

    // returns a new Matrix that is the scalar product of this Matrix with M
    // pre: getSize() == M.getSize()
    Matrix add(Matrix M) {
        if (M.getSize() != getSize()) {
            throw new RuntimeException("Matrix Error: cannot call add() on Matrices with different sizes");
        }
        Matrix matrix = new Matrix(getSize());// Addition matrix to be returned
        if (equals(M)) {
            return scalarMult(2);// If the matrices are equal, return 2M
        }

        for (int n = 1; n < format(); n++) {
            Entry A, B, C, C1, D, E;
            if (0 < M.R[n].length())
                if (0 == R[n].length()) {
                    M.R[n].moveFront();
                    while (M.R[n].index() >= 0) {
                        A = (Entry) M.R[n].get();
                        matrix.changeEntry(n, A.column, A.value);
                        M.R[n].moveNext();
                    }
                }
            if (0 == M.R[n].length())
                if (0 < R[n].length()) {
                    R[n].moveFront();
                    while (!(R[n].index() < 0)) {
                        B = (Entry) R[n].get();
                        matrix.changeEntry(n, B.column, B.value);
                        R[n].moveNext();
                    }
                }
            if (0 < R[n].length()) {
                if (0 < M.R[n].length()) {
                    R[n].moveFront();
                    M.R[n].moveFront();
                    while (R[n].index() >= 0 && M.R[n].index() >= 0) {
                        C = (Entry) R[n].get();
                        C1 = (Entry) M.R[n].get();

                        if (C.column > C1.column) {
                            matrix.changeEntry(n, C1.column, C1.value);
                            M.R[n].moveNext();
                        }

                        if (C.column < C1.column) {
                            matrix.changeEntry(n, C.column, C.value);
                            R[n].moveNext();
                        }

                        if (C.column == C1.column) {
                            matrix.changeEntry(n, C.column, (C.value + C1.value));
                            R[n].moveNext();
                            M.R[n].moveNext();
                        }
                    }
                    if (0 > R[n].index())
                        if (0 <= M.R[n].index()) {
                            while (0 <= M.R[n].index()) {
                                E = (Entry) M.R[n].get();
                                matrix.changeEntry(n, E.column, E.value);
                                M.R[n].moveNext();
                            }
                        }

                    if (0 > M.R[n].index())
                        if (0 <= R[n].index()) {
                            while (0 <= R[n].index()) {
                                D = (Entry) R[n].get();
                                matrix.changeEntry(n, D.column, D.value);
                                R[n].moveNext();
                            }
                        }
                }
            }
        }
        return matrix;
    }

    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M) {
        if (getSize() != M.getSize()) {
            throw new RuntimeException("Matrix Error: cannot call add() on Matrices with different sizes");
        }
        Matrix matrix = M.scalarMult(-1);
        Matrix sub = add(matrix);
        return sub;
    }

    // returns a new Matrix that is the transpose of this Matrix
    Matrix transpose() {
        int n = 0;
        Entry E;
        Matrix matrix = new Matrix(getSize());
        while (n < format()) {
            for (R[n].moveFront(); R[n].index() >= 0; R[n].moveNext()) {
                E = (Entry) R[n].get();
                matrix.changeEntry(E.column, n, E.value);
            }
            n++;
        }
        return matrix;
    }

    // returns a new Matrix having the same entries as this Matrix
    Matrix copy() {
        Matrix copiedMatrix = new Matrix(getSize());
        int n = 0;
        while (n < format()) {
            copiedMatrix.R[n] = R[n].copy();
            n++;
        }
        copiedMatrix.nonZero = this.nonZero;
        return copiedMatrix;
    }

    // computes the vector dot prodcut of two matrix rows represented by Lists P and
    // Q.
    private static double dot(List P, List Q) {
        Entry A, B;

        double product = 0;
        for (P.moveFront(); 0 <= P.index(); P.moveNext()) {
            A = (Entry) P.get();
            for (Q.moveFront(); 0 <= Q.index(); Q.moveNext()) {
                B = (Entry) Q.get();

                if (A.column == B.column) {
                    double C = A.value * B.value;
                    product += C;
                    break;
                }
            }
        }
        return product;
    }

    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix mult(Matrix M) {
        if (getSize() != M.getSize()) {
            throw new RuntimeException("Matrix Error: cannot call mult() on Matrices with a different sizes");
        }
        int n, m, k;
        Matrix matrix, transMatrix;
        matrix = new Matrix(getSize());
        transMatrix = M.transpose();
        n = format();
        m = 1;

        while (m < n) {
            for (k = 1; k < transMatrix.format(); k++) {
                matrix.changeEntry(m, k, dot(R[m], transMatrix.R[k]));
            }
            m++;
        }
        return matrix;
    }

    // overrides Object's toString() method
    public String toString() {
        int n = 0;
        String str = "";
        while (n < (numItems + 1)) {
            if (R[n].length() > 0) {
                str += n + ": " + R[n].toString() + "\n";
            }
            n++;
        }
        return str;
    }
}