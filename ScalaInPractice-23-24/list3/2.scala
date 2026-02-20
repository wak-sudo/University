object Main2 extends App
{
    case class MyException(val msg : String) extends Exception {}
    /*object MyException {
        def apply(msg : String) : MyException = new MyException(msg)
    }*/

    case class MyDifferentException(val msg : String) extends Exception {}
    /*object MyDifferentException {
        def apply(msg : String) : MyDifferentException = new MyDifferentException(msg)
    }*/

    def unSafe[T](ex: Exception)(f : => T) : T = {
        try {
            f
        } catch {
            case e: Throwable => 
                println(e.toString())
                throw ex  // what about loggin?
        }
    }

    unSafe(MyException("Division by zero")) {
        val a = scala.io.StdIn.readLine().toInt
        val b = scala.io.StdIn.readLine().toInt
        println(a/b)
    }

    unSafe(MyException("Res must be bigger than 25!")) {
        val a = scala.io.StdIn.readLine().toInt
        val power = a*a
        if(power <= 25) throw new Exception("Random ex")
        else println(power)
    }

}