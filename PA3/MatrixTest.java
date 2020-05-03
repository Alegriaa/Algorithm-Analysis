//-----------------------------------------------------------------------------
//  MatrixTest.java
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------

public class MatrixTest {
    public static void main(String[] args) {
        int i, j, n = 100000;
        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);
        Matrix C = new Matrix(n);

        A.changeEntry(1, 1, 1);
        A.changeEntry(2, 1, 1);
        A.changeEntry(3, 2, 8);
        A.changeEntry(4, 2, 0);
        System.out.println(A.getNNZ());
        System.out.println(A);
        Matrix S = A.sub(A);
        System.out.println(S.getNNZ());
        System.out.println(S);
        Matrix D = A.add(A);
        System.out.println(D.getNNZ());
        System.out.println(D);
        B.changeEntry(5, 3, 32);
        B.changeEntry(1, 3, 1);
        B.changeEntry(10, 10, 10);
        B.changeEntry(2, 1, 0);
        // A.changeEntry(22,2,5);
        // .changeEntry(2,2,1);
        B.changeEntry(5, 3, 6);
        // changeEntry(2,3,0);
        Matrix F = B.transpose();
        System.out.println(F.getNNZ());
        System.out.println(F);

        C.changeEntry(23, 1, 7);
        C.changeEntry(23, 21, 11);
        C.changeEntry(3, 223, 8);
        C.changeEntry(3, 2, 1);
        C.changeEntry(3, 3, 9);
        C.changeEntry(333, 333, 333);

        C = A.scalarMult(1.5);
        System.out.println(C.getNNZ());
        System.out.println(C);
        System.out.println(A.equals(B));
        System.out.println(C.equals(B));
        Matrix M = A.copy();
        System.out.println(M);
        System.out.println(M.equals(A));
        A.makeZero();
        // System.out.println(A);
        System.out.println(M.equals(A));
        Matrix T = B.transpose();
        System.out.println(T.getNNZ());
        System.out.println(T);
        Matrix G = B.mult(B);
        System.out.println(G.getNNZ());
        System.out.println(G);
        A.changeEntry(23, 1, 7);
        B.changeEntry(23, 21, 11);
        A.changeEntry(3, 223, 8);
        B.changeEntry(3, 2, 1);
        A.changeEntry(3, 3, 9);
        B.changeEntry(333, 333, 333);
        A.changeEntry(3, 1, 7);
        B.changeEntry(5, 0, 1);
        A.changeEntry(3, 2, 8);
        B.changeEntry(3, 2, 5);
        A.changeEntry(3, 3, 9);
        B.changeEntry(3, 3, 1);
        System.out.println(G);

    }
}