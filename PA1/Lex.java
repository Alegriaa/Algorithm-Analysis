               // Brian Pereira Alegria
// brpereir
// Lex.java



import java.io.*;
import java.util.Scanner;

public class Lex {
        public static void main(String[] args) throws IOException {
                Scanner in;
                PrintWriter out;
                String[] content;
                int n, m, k;
                int line;

                // check number of command line arguments is at least 2
                if (args.length != 2) {
                        System.err.println("Usage: input output");
                        System.exit(1);
                }
               // open files
                in = new Scanner(new File(args[0]));
                out = new PrintWriter(new FileWriter(args[1]));

                n = 0;

                // read lines from in
                while (in.hasNextLine()) {
                        in.nextLine();
                        n++;
                }

                content = new String[n];

                in.close();
                in = new Scanner(new File(args[0]));

                line = -1;

                // place content into array
                while (in.hasNextLine()) {
                        line++;
                        content[line] = in.nextLine();
                }

                List L = new List();
                L.append(0);
                k = content.length;

                // sort arreay accoording to value
                for (int i = 1; i < k; i++) {
                        m = i - 1;
                        L.moveFront();
                        while (0 <= m && content[i].compareTo(content[L.get()]) <= 0) {
                                L.moveNext();
                                m--;
                        }
                        if (0 > L.index()) {
                                L.append(i);
                        } else {
                                L.insertBefore(i);
                        }
                }

                // print content
                L.moveBack();
                for(int i = 0; i < k; i++){
                        out.println(content[L.get()]);
                        L.movePrev();
                }

                // close files
                in.close();
                out.close();
        }
}


