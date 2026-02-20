import scala.io.Source._

object Basic extends App
{
    //val filesHere = new java.io.File(".").listFiles

    def fileLinesUgly(file: java.io.File): List[String] = {
        var listOfLines = List[String]()
        val lineStream = fromFile(file).getLines()
        if(lineStream.hasNext)
        {
            do
                listOfLines = lineStream.next() :: listOfLines 
            while(lineStream.hasNext)
            
        }
        listOfLines.reverse
    }

    def fileLines(file: java.io.File): List[String] = {
        fromFile(file).getLines.toList
    }

    val file = new java.io.File("testFile")

    println(fileLines(file))
    println(fileLinesUgly(file))
}