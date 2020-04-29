  // Brian Pereira Alegria
// brpereir
// List.java


public class List {

        private class Node {
                // fields
                int data;
                Node prev;
                Node next;

                // constuctor
                public Node(int data) {
                        this.data = data;
                        prev = null;
                        next = null;
                }
   // toString():  overrides Object's toString() method
                public String toString() {
                        return String.valueOf(data);
                }
                // equals(): overrides Object's equals() method
                public boolean equals(Object x) {
                        boolean eq = false;
                        Node that;
                        if (x instanceof Node) {
                                that = (Node) x;
                                eq = (this.data == that.data);
                        }
                        return eq;
                }
        }
        // private fields
        private Node head;
        private Node tail;
        private Node cursor;
        private int numItems;
        private int indexCursor;

        // constructor
        List() {
                head = null;
                tail = null;
                cursor = null;
                numItems = 0;
                indexCursor = -1;
        }

        // Returns the number of elements in this List.
        public int length() {
                return numItems;
        }
        // If cursor is defined, returns the index of the cursor element,
        // otherwise returns -1.
        public int index() {
                if( cursor != null){
                        return indexCursor;
                } else {
                        return -1;
                }
        }
        // Returns front element. Pre: length()>0
        public int front() {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call front()  on empty List");
                }
                return head.data;
        }
        // Returns back element. Pre: length()>0
        public int back() {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call back() on empty List");
                }
                return tail.data;
        }
 // Returns cursor element. Pre: length()>0, index()>=0
        public int get() {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call get() called on empty List");
                }
                if (index() < 0) {
                        throw new RuntimeException("cannot call get() with undefined cursor");
                }
                return cursor.data;
        }
        // Returns true if and only if this List and L are the same
        // integer sequence. The states of the cursors in the two Lists
        // are not used in determining equality.
        public boolean equals(Object rhs) {
                boolean eq = false;
                List R = null;
                Node N = null;
                Node M = null;

                if (rhs instanceof List) {
                        R = (List) rhs;
                        eq = (this.numItems == R.numItems);

                        N = this.head;
                        M = R.head;
                        while (eq && N != null) {
                                eq = (N.data == M.data);
                                N = N.next;
                                M = M.next;
                        }
                }
                return eq;
        }
        // Resets this List to its original empty state.
        public void clear() {
                head = null;
                tail = null;
                cursor = null;
                numItems = 0;
                indexCursor = -1;
        }
        // If List is non-empty, places the cursor under the front element,
        // otherwise does nothing.
        public void moveFront() {
                if (length() > 0) {
                        cursor = head;
                        indexCursor = 0;
                }
        }
        // If List is non-empty, places the cursor under the back element,
        // otherwise does nothing.
        public void moveBack() {
                if (length() > 0) {
                        cursor = tail;
                        indexCursor = numItems - 1;
                }
        }
  // If cursor is defined and not at front, moves cursor one step toward
        // front of this List, if cursor is defined and at front, cursor becomes
        // undefined, if cursor is undefined does nothing.
        public void movePrev() {
                if (cursor != null) {
                        if (!cursor.equals(head)) {
                                cursor = cursor.prev;
                                indexCursor--;
                        } else if (cursor.equals(head)) {
                                cursor = null;
                                indexCursor = -1;
                        }
                }
        }
        // If cursor is defined and not at back, moves cursor one step toward 
        // back of this List, if cursor is defined and at back, cursor becomes
        // undefined, if cursor is undefined does nothing.
        public void moveNext() {
                if (cursor != null) {
                        if (!cursor.equals(tail)) {
                                cursor = cursor.next;
                                indexCursor++;
                        } else if (cursor.equals(tail)) {
                                cursor = null;
                                indexCursor = -1;
                        }
                }
        }
        // Insert new element into this List. If List is non-empty, 
        // insertion takes place before front element.
        public void prepend(int data) {
                Node N = new Node(data);
                if (length() != 0) {
                        head.prev = N;
                        N.next = head;
                        head = N;
                        indexCursor++;
                } else {
                        head = tail = N;
                }
                numItems++;
        }
        // Insert new element into this List. If List is non-empty, 
        // insertion takes place after back element.
        public void append(int data) {
                Node N = new Node(data);
                if (numItems != 0) {
                        tail.next = N;
                        N.prev = tail;
                        tail = N;
                } else {
                        head = tail = N;
                }
                numItems++;
        }
  // Insert new element before cursor.
        // // Pre: length()>0, index()>=0
        public void insertBefore(int data) {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call insertBefore() on empty List");
                } else if (index() < 0) {
                        throw new RuntimeException("cannot call insertBefore() with undefined cursor");
                } else {
                        Node N = new Node(data);
                        Node C = cursor;
                        if (C.equals(head)) {
                                N.next = C;
                                C.prev = N;
                                head = N;
                        } else {
                                N.next = C;
                                N.prev = C.prev;
                                C.prev.next = N;
                                C.prev = N;
                        }
                        indexCursor++;
                        numItems++;
                }

        }
        // Inserts new element after cursor.
        // Pre: length()>0, index()>=0
        public void insertAfter(int data) {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call insertAfter() on empty List");
                } else if (index() < 0) {
                        throw new RuntimeException("cannot call insertAfter() with undefined cursor");
                }
                Node N = new Node(data);
                Node C = cursor;
                Node P;
                if (C.equals(tail)) {
                        C.next = N;
                        N.prev = C;
                        tail = N;
                } else {
                        P = new Node(data);
                        N.prev = C;
                        N.next = P;
                        P.prev = N;
                }
                numItems++;
        }
        // Deletes the front element. Pre: length()>0
        public void deleteFront() {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call deleteFront() on empty List");
                }
                if (head.equals(tail)) {
                        head = null;
                } else {
                        head = head.next;
                        head.prev = null;
                }
                numItems--;
        }
          
  // Deletes the back element. Pre: length()>0
        public void deleteBack() {
                if (length() <= 0) {
                        throw new RuntimeException("cannot call deleteBack() on empty List");
                }
                if (tail.equals(head)) {
                        tail = null;
                } else {
                        tail = tail.prev;
                        tail.next = null;
                }
                numItems--;
        }
        // Deletes cursor element, making cursor undefined.
        // Pre: length()>0, index()>=0
        public void delete() {

                if (length() <= 0) {
                        throw new RuntimeException("cannot call delete() on empty List");
                } else if (index() < 0) {
                        throw new RuntimeException("cannot call delete() with undefined cursor");
                } else if (cursor.equals(head)) {
                        deleteFront();
                } else if (cursor.equals(tail)) {
                        deleteBack();
                } else {
                        cursor.next.prev = cursor.prev;
                        cursor.prev.next = cursor.next;
                        cursor = null;
                        numItems--;
                }
                indexCursor = -1;
        }
        // Overrides Object's toString method. Returns a String
        // representation of this List consisting of a space
        // separated sequence of integers, with front on left.
        public String toString() {
                StringBuffer sb = new StringBuffer();
                Node N = head;
                while (N != null) {
                        sb.append(N.toString());
                        sb.append(" ");
                        N = N.next;
                }
                return new String(sb);
        }
        // Returns a new List representing the same integer sequence as this
        // List. The cursor in the new list is undefined, regardless of the
        // state of the cursor in this List. This List is unchanged.
        public List copy() {
                List L = new List();
                Node N = head;

                while (N != null) {
                        L.append(N.data);
                        N = N.next;
                }
                return L;
        }
}

