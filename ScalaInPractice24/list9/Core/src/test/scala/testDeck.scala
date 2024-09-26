import cards._
import deck._
import org.scalatest.funsuite.AnyFunSuite

class DeckFunSuite extends AnyFunSuite {

  test("pull") {
    val fstCard = Card(Clubs, CardId(1))
    val sndCard = Card(Diamonds, CardId(10))
    val deckToTest = Deck(List(fstCard, sndCard))
    val expectedDeck = Deck(List(sndCard))
    assert(deckToTest.pull() == expectedDeck)
    assert(Deck(Nil).pull() == Deck(Nil))
  }

  test("size") {
    val fstCard = Card(Clubs, CardId(1))
    val sndCard = Card(Diamonds, CardId(10))
    val cardsList = List(fstCard, sndCard)
    val deckToTest = Deck(cardsList)
    assert(deckToTest.size == cardsList.length)
  }

  test("push") {
    val fstCard = Card(Clubs, CardId(1))
    val sndCard = Card(Diamonds, CardId(10))
    val deckToTest = Deck(List(fstCard))
    val expectedDeck = Deck(List(fstCard, sndCard))
    assert(deckToTest.push(sndCard) == expectedDeck)
  }

  test("isStandard & standardDeck") {
    val fstCard = Card(Clubs, CardId(1))
    val deckToTest = Deck(List(fstCard))
    val stdDeck = Deck(Deck.standardDeck)
    assert(deckToTest.isStandard == false)
    assert(stdDeck.isStandard == true)
  }

  test("duplicatesOfCard") {
    val fstCard = Card(Clubs, CardId(1))
    val sndCard = Card(Clubs, CardId(1))
    val thirdCard = Card(Diamonds, CardId(10))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.duplicatesOfCard(fstCard) == 1)
    assert(testDeck.duplicatesOfCard(thirdCard) == 0)
  }

  test("amountOfColor") {
    val fstCard = Card(Clubs, CardId(1))
    val sndCard = Card(Clubs, CardId(1))
    val thirdCard = Card(Diamonds, CardId(10))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.amountOfColor(Clubs) == 2)
    assert(testDeck.amountOfColor(Hearts) == 0)
  }

  test("amountOfNumerical") {
    val fstCard = Card(Clubs, CardId(4))
    val sndCard = Card(Clubs, CardId(4))
    val thirdCard = Card(Diamonds, CardId(5))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.amountOfNumerical(4) == 2)
    assert(testDeck.amountOfNumerical(10) == 0)
  }

  test("amountWithNumerical") {
    val fstCard = Card(Clubs, CardId(4))
    val sndCard = Card(Clubs, CardId(4))
    val thirdCard = Card(Diamonds, CardId(11))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.amountWithNumerical == 2)
  }

  test("amountOfFace") {
    val fstCard = Card(Diamonds, Jack)
    val sndCard = Card(Hearts, Jack)
    val thirdCard = Card(Diamonds, CardId(5))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.amountOfFace(Jack) == 2)
    assert(testDeck.amountOfFace(King) == 0)
  }

  test("amountWithFace") {
    val fstCard = Card(Diamonds, Jack)
    val sndCard = Card(Hearts, Jack)
    val thirdCard = Card(Diamonds, CardId(5))
    val testDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(testDeck.amountWithFace == 2)
  }

  test("concatenation (++)") {
    val fstCard = Card(Diamonds, Jack)
    val sndCard = Card(Hearts, Jack)
    val thirdCard = Card(Diamonds, CardId(5))
    val testDeckOne = Deck(List(fstCard))
    val testDeckTwo = Deck(List(sndCard, thirdCard))
    val expectedDeck = Deck(List(fstCard, sndCard, thirdCard))
    assert(expectedDeck == testDeckOne ++ testDeckTwo)
  }

}
