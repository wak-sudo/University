/*
* Wojciech Kieloch
* Lista 6 zad. 1
* javac *.java
* java App
*/

class OrderList<T extends Comparable<T>> implements java.io.Serializable
{
   Node head = null;

   class Node implements java.io.Serializable
   {
      public T val;
      public Node next;

      Node(T val)
      {
         this.val = val;
         this.next = null;
      }
   }

   void push_front(Node n)
   {
      n.next = head;
      head = n;
   }

   public void add_element(T elem)
   {
      Node newNode = new Node(elem);
      if(head != null) 
      {
         if(elem.compareTo(head.val) > 0)
         {
            Node cr = head;
            while(cr.next != null && cr.next.val.compareTo(elem) < 0)
               cr = cr.next;
            newNode.next = cr.next;
            cr.next = newNode;
         }
         else push_front(newNode);
      } else push_front(newNode);
   }

   public T get_first()
   {
      if(head != null)
         return head.val;
      else return null;
   }

   public String toString()
   {
      String res ="";
      Node cr = head;
      while(cr != null)
      {
         res += cr.val.toString() + " | ";
         cr = cr.next;
      }
      return res;
   }

   public void print()
   {
      System.out.println(this.toString());
   }
}