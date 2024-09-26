/*
* Wojciech Kieloch
* Lista 3 zad. 1
* Microsoft Visual Studio .NET 7.0
*/

namespace ListaDLL
{
    class Node<T>
    {
        public T val;
        public Node<T>? next;
        public Node<T>? prev;

        public Node(T val, Node<T>? next, Node<T>? prev)
        {
            this.val = val;
            this.next = next;
            this.prev = prev;
        }
    }
    public class Lista<T>
    {
        private Node<T>? head = null;
        private Node<T>? tail = null;

        public void push_front(T elem)
        {
            if (head != null)
            {
                Node<T> newHead = new Node<T>(elem, head, null);
                head.prev = newHead;
                head = newHead;
            }
            else head = new Node<T>(elem, tail, null); ;
        }

        public void push_back(T elem)
        {
            if (head == null)
            {
                head = new Node<T>(elem, tail, null);
            }
            else if (tail == null)
            {
                tail = new Node<T>(elem, null, head);
                head.next = tail;
            }
            else
            {
                Node<T> newTail = new Node<T>(elem, null, tail);
                tail.next = newTail;
                tail = newTail;
            }
        }

        public T? pop_front()
        {
            if (head != null)
            {
                Node<T>? newHead = head.next;
                T removedElVal = head.val;
                if (newHead != null) newHead.prev = null;
                head = newHead;
                return removedElVal;
            }
            return default(T);
        }

        public T? pop_back()
        {
            if (tail != null)
            {
                Node<T>? newTail = tail.prev;
                if (newTail != null) newTail.next = null;
                T removedElVal = tail.val;
                tail = newTail;
                return removedElVal;
            }
            return default(T);
        }

        public bool is_empty()
        {
            return head == null;
        }

        public void print() // debug
        {
            Node<T>? cr = head;
            if (cr != null)
            {
                while (cr != null)
                {
                    Console.Write(cr.val + " ");
                    cr = cr.next;
                }
            }
            else Console.WriteLine("Empty.");
            Console.WriteLine();
        }
    }
}