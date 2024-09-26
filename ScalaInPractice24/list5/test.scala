object Test extends App {
  def double(text : String) = {
        def rec(text : String, pos : Int) : String = {
            if(text.length() == 0) ""
            else if(pos % 2 == 0)
                text.head + (text.head + rec(text.tail, pos + 1))
            else text.head + rec(text.tail, pos + 1)
        }

        rec(text, 1)
    }

  println(double("abcd"))
}
