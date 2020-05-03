// Brian Pereira Alegria
// brpereir
// List.java

@SuppressWarnings("overrides")
public class List {
    // fields
    private class Node {
        Object data;
        Node prev;
        Node next;

        // constructor
        public Node(Object data) {
            this.data = data;
            prev = null;
            next = null;
        }

        // toString (): overrides Object's toString() method
        public String toString() {
            return String.valueOf(data);
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

    // Returns the number of elements in this List
    public int length() {
        return numItems;
    }

    // If cursor is defined, returns the index of the cursor element,
    // otherwise returns -1.
    public int index() {
        Node N = head;
        int i = 0;
        if (cursor == null) {
            return -1;
        } else {
            while (N != null) {
                if (N.data.equals(cursor.data)) {
                    return i;
                }
                N = N.next;
                i++;
            }
            return -1;
        }
    }

    // Returns front element. Pre: length()>0
    public Object front() {
        if (length() <= 0) {
            throw new RuntimeException("cannot call front()  on empty List");
        }
        return head.data;
    }

    // Returns back element. Pre: length()>0
    public Object back() {
        if (length() <= 0) {
            throw new RuntimeException("cannot call back() on empty List");
        }
        return tail.data;
    }

    // Returns cursor element. Pre: length()>0, index()>=0
    public Object get() {
        if (length() <= 0) {
            throw new RuntimeException("List Error: get() called on empty List");
        }
        if (index() < 0) {
            throw new RuntimeException("List Error: get() called on undefined cursor");
        }
        return cursor.data;
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
    public void prepend(Object data) {
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
    public void append(Object data) {
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
    // Pre: length()>0, index()>=0
    public void insertBefore(Object data) {
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
    public void insertAfter(Object data) {
        if (length() <= 0) {
            throw new RuntimeException("cannot call insertAfter() on empty List");
        } else if (index() < 0) {
            throw new RuntimeException("cannot call insertAfter() with undefined cursor");
        }
        Node N = new Node(data);
        Node P;
        if (cursor.equals(tail)) {
            cursor.next = N;
            N.prev = cursor;
            tail = N;
        } else {
            P = new Node(data);
            N.prev = cursor;
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

    // Returns true if and only if this List and L are the same
    // integer sequence. The states of the cursors in the two Lists
    // are not used in determining equality.
    public boolean equals(Object x) {
        boolean eq = true;
        List L;
        Node N, M;

        if (x instanceof List) {
            L = (List) x;
            N = this.head;
            M = L.head;
            if (this.numItems == L.numItems) {
                while (eq && N != null) {
                    eq = N.data.equals(M.data);
                    N = N.next;
                    M = M.next;
                }
                return eq;
            }
        }
        return false;
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
}