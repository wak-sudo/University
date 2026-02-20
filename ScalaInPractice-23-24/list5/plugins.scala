package plugins {

  class Pluginable {
    def apply(text: String): String = text
  }

  trait Reverting extends Pluginable {
    def reverting(text: String) = {
      text.foldRight("")((x, y) => y + x)
    }

    override def apply(text : String) = {super.apply(reverting(text))}
  }

  trait LowerCasing extends Pluginable {
    def lowerCasing(text: String) = {
      text.map(_.toLower)
    }

    override def apply(text : String) = {super.apply(lowerCasing(text))}
  }

  trait SingleSpacing extends Pluginable {
    def singleSpacing(text: String) = {
      text.foldRight("")((x, y) => if (x == ' ' && y.head == ' ') y else x + y)
    }

    override def apply(text : String) = {super.apply(singleSpacing(text))}
  }

  trait NoSpacing extends Pluginable {
    def noSpacing(text: String) = {
      text.foldRight("")((x, y) => if (x == ' ') y else x + y)
    }

    override def apply(text : String) = {super.apply(noSpacing(text))}
  }

  trait DuplicateRemoval extends Pluginable {
    def duplicateRemoval(text: String) = {
      def createMap(
          text: String,
          alphMapArg: Map[Char, Int]
      ): Map[Char, Int] = {
        if (text.length() == 0) alphMapArg
        else {
          val hd = text.head
          val res = alphMapArg get hd
          res match {
            case Some(x) => createMap(text.tail, alphMapArg.updated(hd, x + 1))
            case None    => createMap(text.tail, alphMapArg + (hd -> 1))
          }
        }
      }

      val alphMap = createMap(text, Map())

      def createString(text: String): String = {
        if (text.length() == 0) ""
        else if (text.head == ' ') "".concat(createString(text.tail))
        else {
          val hd = text.head
          val res = alphMap get hd
          res match {
            case None => hd.toString().concat(createString(text.tail))
            case Some(value) =>
              if (value <= 1) hd.toString().concat(createString(text.tail))
              else "".concat(createString(text.tail))
          }
        }
      }

      createString(text)
    }

    override def apply(text : String) = {super.apply(duplicateRemoval(text))}
  }

  trait Rotating extends Pluginable {
    def rotating(text: String) = {
      val len = text.length()
      if (len == 0 || len == 1) text
      else text.charAt(len-1) + text.substring(0, len-1)
    }

    override def apply(text : String) = {super.apply(rotating(text))}
  }

  trait Doubling extends Pluginable {
    def doubling(text: String) = {
      def rec(text: String, pos: Int): String = {
        if (text.length() == 0) ""
        else if (pos % 2 == 0)
          text.head + (text.head + rec(text.tail, pos + 1))
        else text.head + rec(text.tail, pos + 1)
      }

      rec(text, 1)
    }

    override def apply(text : String) = {super.apply(doubling(text))}
  }

  trait Shortening extends Pluginable {
    def shortening(text: String) = {
      def rec(text: String, pos: Int): String = {
        if (text.length() == 0) ""
        else if (pos % 2 == 0)
          "" + rec(text.tail, pos + 1)
        else text.head + rec(text.tail, pos + 1)
      }

      rec(text, 1)
    }

    override def apply(text : String) = {super.apply(shortening(text))}
  }

}
