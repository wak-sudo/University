import deck._
import cards._
import games.Blackjack
import Deck.random

object Main extends App {
  val listOfCards = List(
    Card(Hearts, Queen),
    Card(Spades, CardId(3)),
    Card(Spades, CardId(5)),
    Card(Diamonds, Ace),
    Card(Hearts, King)
  )
  var myDeck = Deck(listOfCards)
  println(myDeck.isStandard)
  println(myDeck.amountWithNumerical)
  println(myDeck.amountWithFace)
  println()

  myDeck = myDeck.pull()
  println(myDeck.amountWithFace)
  println()

  val newCard = Card(Hearts, King)
  myDeck = myDeck.push(newCard)
  println(myDeck.amountWithFace)
  println(myDeck.duplicatesOfCard(newCard))
  println(myDeck.amountOfColor(Spades))
  println(myDeck.amountOfNumerical(5))
  println(myDeck.amountOfFace(King))
  println()

  val standardDeck = Deck.standard()
  println("Standard deck: " + standardDeck.toString())

  val smallDeck = Deck.random(10)
  val mySpecificGame = Blackjack.specificDeck(smallDeck)
  println("My deck: " + smallDeck.toString())

  println()
  mySpecificGame.play(5)
  println()
  
  val combi = mySpecificGame.all21

  val myGame = Blackjack(1)

  //val combi = myGame.all21
  if(combi.size == 0) println("Empty")
  for(x <- combi)
      println(x.toString())
}
