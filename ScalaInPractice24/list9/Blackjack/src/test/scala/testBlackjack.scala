import cards._
import deck._
import games._
import org.scalatest.funsuite.AnyFunSuite

class GamesFunSuite extends AnyFunSuite {

  test("play") {
    val fstCard = Card(Clubs, CardId(2))
    val sndCard = Card(Diamonds, CardId(10))
    val cardsLst = List(fstCard, sndCard)
    val game = Blackjack.specificDeck(Deck(cardsLst))
    assert(game.play(cardsLst.length) == 12)
  }

  test("fst21") {
    val fstCard = Card(Clubs, Ace)
    val sndCard = Card(Diamonds, CardId(10))
    val cardList = List(fstCard, sndCard)
    val game = Blackjack.specificDeck(Deck(cardList))
    assert(game.first21() == 21)
  }

  test("Blackjack apply") {
    assert(Blackjack(2).deckSize == 2 * 52)
    assertThrows[AssertionError] {
      val _ = Blackjack(0).deckSize
    }
  }
}
