import scala.io.Source._

object Basic extends App
{
        def fileLinesUgly(file: java.io.File): Unit = {
          //  val pathName = file.getPath()
            var listOfLines = List[String]()
            val lineStream = fromFile(file).getLines()
            lineStream.foreach(println)
    }

    val file = new java.io.File("testFile")

    fileLinesUgly(file)
}

