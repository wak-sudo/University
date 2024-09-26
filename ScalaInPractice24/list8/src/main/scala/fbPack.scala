import com.restfb._

import java.io.FileWriter
import java.text.SimpleDateFormat
import java.util.Calendar

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.{Try, Success, Failure}
import scala.io.StdIn.readLine

package FBpackage
{
    object FacebookAdapter {
        private val myAppSecret = ??? //any String (or Note1)

        class MyFacebookClient(currentAccessToken: String) 
        extends DefaultFacebookClient(currentAccessToken, myAppSecret, Version.LATEST) {    
        }

        def getUser(accessToken: String, id: String) = {
            val client = new MyFacebookClient(accessToken)
            val user = client.fetchObject(id, classOf[types.User]) // does it return null?
            user
        }

        def compareLikes(logFile: String, user1: String, user2: String): Unit = {
            val user1FutObj = Future { getUser("", user1) }
            val user2FutObj = Future { getUser("", user2) }
            val ign1 = Future { writeLog(logFile, user1, user2) }
            val ign2 = Future { taskPrint(user1FutObj, user2FutObj) }
        }

        private def taskPrint(user1 : Future[types.User], user2 : Future[types.User]) : Unit = {
            println(taskUserStr(user1) + " vs. " + taskUserStr(user2) + "\n")
        }

        private def writeLog(logFile: String, user1: String, user2: String) : Unit = {
            Try { 
                val fw = new FileWriter(logFile,true);
                fw.write(getTime() + " " + user1 + " " + user2 + "\n")
            }.getOrElse{"compareLikes write failed!"}
        }

        private def taskUserStr(userFutObj : Future[types.User]) : String = {
            val user = userFutObj.onComplete {
                case Success(obj) => obj
                case Failure(t) => throw new RuntimeException
            }
           //user.name.toString() + ", likes: " + user.getLikes.getTotalCount.toString()
           ""
        }

        private def getTime() : String = {
            val dataFormat = new SimpleDateFormat("yyyyMMdd_HHmmss")
            val time = Calendar.getInstance().getTime()
            dataFormat.format(time)
        }
    }
}

object Main extends App {
    println("Provide two users id.")
    val id1 = readLine()
    val id2 = readLine()
    println("Provide log file path:")
    val path = readLine()
    FBpackage.FacebookAdapter.compareLikes(path, id1, id2)
}