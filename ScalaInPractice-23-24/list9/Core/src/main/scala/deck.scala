import cards._

import scala.util.Random

package deck {
  class Deck(val cardsField: List[Card]) {
    def ==(other: Deck) = (this.cardsField == other.cardsField)

    def pull(): Deck = {
      if (cardsField.length == 0) Deck(Nil)
      else Deck(cardsField.tail)
    }

    def size = cardsField.length

    def push(c: Card) = Deck(cardsField :+ c)

    val isStandard: Boolean = {
      if (cardsField.length != 52) false
      else {
        cardsField.forall(x => Deck.standardDeck.contains(x))
      }
    }

    def duplicatesOfCard(card: Card): Int = {
      val numberOfSameCards =
        cardsField.foldLeft(0)((x, y) => x + (if (card == y) 1 else 0))
      if (numberOfSameCards > 0) numberOfSameCards - 1 else 0
    }

    def amountOfColor(color: Color): Int = {
      cardsField.foldLeft(0)((x, y) => x + (if (color == y.fColor) 1 else 0))
    }

    def amountOfNumerical(numerical: Int): Int = {
      assert(numerical >= 2 && numerical <= 10)
      cardsField.foldLeft(0)((x, y) =>
        x + (if (numerical == y.fId.toInt) 1 else 0)
      )
    }

    val amountWithNumerical: Int = cardsField.foldLeft(0)((x, y) =>
      x + (if (y.fId.toInt >= 2 && y.fId.toInt <= 10) 1 else 0)
    )

    def amountOfFace(face: Face) = {
      val faceInt = cards.Global.faceToId(face)
      cardsField.foldLeft(0)((x, y) =>
        x + (if (faceInt == y.fId.toInt) 1 else 0)
      )
    }

    val amountWithFace: Int = cardsField.foldLeft(0)((x, y) =>
      x + (if (y.fId.toInt >= 11 && y.fId.toInt <= 13) 1 else 0)
    )

    override def toString(): String = {
      cardsField.foldRight("")((x, y) => x.toString() + (", " + y))
    }

    def ++(other: Deck): Deck = Deck(this.cardsField ++ other.cardsField)

  }

  object Deck {
    def apply(cards: List[Card]) = new Deck(cards: List[Card])
    def apply() = new Deck(List())

    def random(noOfCards: Int = 52) = {
      assert(noOfCards >= 0)
      if (noOfCards == 0) new Deck(List())
      else {
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
