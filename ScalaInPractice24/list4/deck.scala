import cards._
import cards.Global.faceToId
import scala.util.Random

package deck {
  class Deck(val cards: List[Card]) {
    def pull(): Deck = {
      if (cards.length == 0) Deck(Nil)
      else Deck(cards.tail)
    }

    def size = cards.length

    def push(c: Card) = Deck(cards :+ c)

    def push(color: Color, value: CardId) = Deck(cards :+ Card(color, value))

    val isStandard: Boolean = {
      if (cards.length != 52) false
      else {
        cards.forall(x => Deck.standardDeck.contains(x))
      }
    }

    def duplicatesOfCard(card: Card): Int = {
      val numberOfSameCards = cards.foldLeft(0)((x, y) => x + (if (card.equals(y)) 1 else 0))
      if(numberOfSameCards > 0) numberOfSameCards - 1 else 0
    }

    def amountOfColor(color: Color): Int = {
      cards.foldLeft(0)((x, y) => x + (if (color.equals(y.fColor)) 1 else 0))
    }

    def amountOfNumerical(numerical: Int): Int = {
      assert(numerical >= 2 && numerical <= 10)
      cards.foldLeft(0)((x, y) => x + (if (numerical == y.fId.toInt) 1 else 0))
    }

    val amountWithNumerical: Int = cards.foldLeft(0)((x, y) =>
      x + (if (y.fId.toInt >= 2 && y.fId.toInt <= 10) 1 else 0)
    )

    def amountOfFace(face: Face) = {
      val faceInt = faceToId(face)
      cards.foldLeft(0)((x, y) => x + (if (faceInt == y.fId.toInt) 1 else 0))
    }

    val amountWithFace: Int = cards.foldLeft(0)((x, y) =>
      x + (if (y.fId.toInt >= 11 && y.fId.toInt <= 13) 1 else 0)
    )

    override def toString(): String = {
      cards.foldRight("")((x, y) => x.toString() + (", " + y))
    }

    def ++(other: Deck): Deck = Deck(this.cards ++ other.cards)

  }

  object Deck {
    def apply(cards: List[Card]) = new Deck(cards: List[Card])
    def apply() = new Deck(List())

    def random(noOfCards: Int = 52) = {
      assert(noOfCards >= 0)
      if (noOfCards == 0) new Deck(List())
      else {
        val begList: List[Card] = List()
        val randList = {
          for (x <- (1 to noOfCards)) yield Card.random()
        }.toList
        new Deck(randList)
      }

    }

    val standardDeck = {
      for (id <- (1 to Global.MaxCardValue).toSeq; color <- Global.ColorsList)
        yield Card(color, CardId(id))
    }.toList

    def standard(): Deck = {
      new Deck(Random.shuffle(standardDeck))
    }
  }

}
