import scala.io.Source._

object Basic extends App
{
    val filesHere = new java.io.File(".").listFiles

    def printNonEmpty(pattern: String): Unit = 
    {
        val files = filesHere.filter(file => file.isFile && file.getName.endsWith(pattern) && file.length > 0)
        files.foreach(file => println(file.getName))
    }

    def printNonEmptyUgly(pattern: String): Unit = 
    {
        val files = List()
        var i = 0
        if(i < filesHere.size)
        {
            do
            {
                val el = filesHere(i)
                if(el.isFile && el.getName.endsWith(pattern) && el.length > 0)
                    println(el.getName)
                i += 1
            }
            while(i < filesHere.size)
        }
    }

    printNonEmpty(".scala")
    println()
    printNonEmptyUgly(".scala")
}