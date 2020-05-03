// Brian Pereira Alegria
// brpereir
// Sparse.java

import java.util.Scanner;
import java.io.*;

public class Sparse {

    public static void main(String[] args) throws IOException {
        Scanner in = null;
        PrintWriter out = null;
        int size, a, b, n, m;

        // check that command line arguments are at least 2
        if (args.length != 2) {
            System.out.println("Usage: in out");
            System.exit(1);
        }
        // open files
        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));

        size = in.nextInt();
        a = in.nextInt();
        b = in.nextInt();

        Matrix matrixA = new Matrix(size);
        Matrix matrixB = new Matrix(size);
        int R, C;
        double V;

        n = 0;

        // read content
        while (n < a) {
            R = in.nextInt();
            C = in.nextInt();
            V = in.nextDouble();
            matrixA.changeEntry(R, C, V);
            n++;
        }

        m = 0;
        while (m < b) {
            R = in.nextInt();
            C = in.nextInt();
            V = in.nextDouble();
            matrixB.changeEntry(R, C, V);
            m++;
        }

        // requested printing format
        out.println("A has " + a + " non-zero entries:\n" + matrixA + "B has " + b + " non-zero entries:\n" + matrixB);
        out.println("(1.5)*A = \n" + matrixA.scalarMult(1.5));
        out.println("A+B = \n" + matrixA.add(matrixB) + "A+A = \n" + matrixA.add(matrixA));
        out.println("B-A = \n" + matrixB.sub(matrixA) + "A-A = \n" + matrixA.sub(matrixA));
        out.println("Transpose(A) = \n" + matrixA.transpose());
        out.println("A*B = \n" + matrixA.mult(matrixB) + "B*B = \n" + matrixB.mult(matrixB));

        // close in out files
        in.close();
        out.close();

    }

}
