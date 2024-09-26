package cards {

  import cards.Global.MaxCardValue

  sealed abstract class Color

  case object Clubs extends Color
  case object Diamonds extends Color
  case object Hearts extends Color
  case object Spades extends Color

  class CardId(val value: Int) {
    require(value >= 1 && value <= 13)
    def toInt = value
    def ==(other: CardId) = (this.value == other.value)
  }

  object CardId {
    def apply(n: Int) = new CardId(n)
    def random() = {
      val id = 1 + StaticElem.rand.nextInt(MaxCardValue)
      new CardId(id)
    }
  }

  object Global {
    val MaxCardValue = 13
    val ColorsList = Array(Clubs, Diamonds, Hearts, Spades)
    val FacesList = List(Jack, Queen, King)
    val PicturesList = List(Ace) ++ FacesList

    def faceToId(face: Face): Int = {
      face match {
        case Jack  => 11
        case Queen => 12
        case King  => 13
      }
    }
  }

  sealed abstract class StaticElem
  object StaticElem {
    val rand = new scala.util.Random
  }

  sealed trait Face {}

  case object Jack extends CardId(11) with Face
  case object Queen extends CardId(12) with Face
  case object King extends CardId(13) with Face
  case object Ace extends CardId(1)

  class Card(val fColor: Color, val fId: CardId) {
    override def toString(): String =
      valueToSymbol() + " (" + colorToString() + ")"

    def ==(other: Card) = (this.fColor == other.fColor && this.fId == other.fId)

    private def colorToString(): String = {
      fColor match {
        case Clubs    => "Clubs"
        case Diamonds => "Diamonds"
        case Hearts   => "Hearts"
        case Spades   => "Spades"
      }
    }

    private def valueToSymbol(): String = {
      fId.toInt match {
        case a if 2 to 10 contains a => a.toString()
        case 11                      => "Jack"
        case 12                      => "Queen"
        case 13                      => "King"
        case 1                       => "Ace"
        case _                       => "Null"
      }
    }
  }

  object Card {
    def apply(fColor: Color, fId: CardId) = new Card(fColor, fId)
    def random() = {
      val randIdx = StaticElem.rand.nextInt(Global.ColorsList.length - 1)
      new Card(Global.ColorsList(randIdx), CardId.random())
    }
  }

}
