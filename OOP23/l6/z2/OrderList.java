/*
* Wojciech Kieloch
* Lista 6 zad. 2
* javac *.java
* java App
*/

import java.util.*;

class OrderList<T extends Comparable<T>> implements Collection<T>
{
   Node head = null;
   int size = 0;

   class Node
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

   public boolean add(T elem)
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
      size++;
      return true;
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

   public int size()
   {
      return size;
   }

   public boolean remove(Object el)
   {
      if (head != null)
      {
         if(el == head.val)
         {
            head = head.next;
            size--;
            return true;
         }
         else
         {
            Node prev = head;
            Node cr = head.next;
            while(cr != null)
               if(cr.val == el)
               {
                  prev.next = cr.next;
                  size--;
                  return true;
               }
         }
      }
      return false;
   }

   public boolean isEmpty()
   {
      return head == null;
   }

   public void clear()
   {
      head = null;
      size  = 0;
   }

   public boolean contains(T el)
   {
      Node cr = head;
      while(cr != null)
         if(cr.val == el)
            return true;
      return false;
   }

   public boolean containsAll(Collection<?> col)
   {
      boolean flag = true;
      for (var el : col)
      {
         flag &= contains(el);
         if(flag == false) return flag;
      } 
      return flag;
   }

   public boolean addAll(Collection<? extends T> col)
   {
      boolean res = false;
      for (var el : col)
         res |= this.add(el);
      return res;
   }

   public boolean removeAll(Collection<?> c)
   {
      boolean res = false;
      for (var el : c)
         res |= this.remove(el);
      return res;
   }

   public boolean contains(Object o)
   {
      Node cr = head;
      while(cr != null)
      {
         if(cr.val == o)
            return true;
         cr = cr.next; 
      }
      return false;
   }

   public boolean retainAll(Collection<?> col)
   {
      boolean hasChanged = false;
      Object[] arr = col.toArray();
      Arrays.sort(arr);
      Node newHead = null;
      Node cr = null;
      Node walker = this.head; // przechodzi po pierwotnej liście
      int newSize = 0;
      for(var el : arr)
      {
         if(this.contains(el))
         {
            if(arr.length == this.size)
            {
               if ((T)el != walker.val) hasChanged = true; // po posortowaniu kolekcje powinny być identyczne
               walker = walker.next;
            } else hasChanged = false; 

            newSize++;
            if(newHead == null)
            {
               newHead = new Node((T)el);
               cr = newHead;
            }
            else
            {
               cr.next = new Node((T)el);
               cr = cr.next;
            }
         }
      }
      this.head = newHead;
      this.size = newSize;
      return hasChanged;
   }

   public Object[] toArray()
   {
      Object[] arr = new Object[this.size];
      int i =0;
      Node cr = head;
      while(cr != null)
      {
         arr[i] = cr.val;
         i++;
         cr = cr.next;
      }
      return arr;
   }

   public Iterator<T> iterator()
   {
      Iterator<T> it = new Iterator<>()
      {
         private Node cr = head;
         public boolean hasNext()
         {
            return cr != null;
         }
         public T next()
         {
            var ret = cr.val;
            cr = cr.next;
            return ret;
         }
      };
      return it;
   }

   public <T> T[] toArray(T[] a)
   {
      Node cr = head;
      for(int i = 0; i<a.length &&  cr != null; i++)
      {
         a[i] = (T)cr.val;
         cr = cr.next;
      }
      return a;
   }
   
}