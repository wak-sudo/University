import cards._

object MainTest extends App {
    val cardOne = Card(Spades, Ace)
    val cardTwo = Card(Spades, King)
    println(cardOne == cardTwo)

    println(cardOne.fId.equals(Ace))
}