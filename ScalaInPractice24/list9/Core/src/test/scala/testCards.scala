import cards._
import org.scalatest.funsuite.AnyFunSuite

class CardsFunSuite extends AnyFunSuite {

  test("Faces have right values") {
    assert(Jack.value == 11)
    assert(Queen.value == 12)
    assert(King.value == 13)
    assert(Ace.value == 1)
  }

  test("CardId cons") {
    for (i <- Range.inclusive(1, 13)) {
      val _ = CardId(i)
    }
  }

}
