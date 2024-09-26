import cards._
import deck._

import scala.collection.mutable.Buffer
import scala.util.Random

package games {
  class Blackjack(deck: Deck) {

    private def pointsMap(card: Card): Int = {
      card.fId match {
        case a if 2 to 10 contains a.toInt  => a.toInt
        case a if 11 to 13 contains a.toInt => 10
        case _                              => 0
      }
    }

    private def printCard(card: Card, points: Int): Unit = {
      println(card.toString() + " (P: " + points.toString() + ")")
    }

    def play(n: Int): Int = {
      def printTable(curDeck: Deck, iter: Int, totalPoints: Int): Int = {
        if (curDeck.size > 0 && iter > 0) {
          val curCard = curDeck.cardsField.head
          val pointsToAdd = pointsForCard(curCard, totalPoints)

          printCard(curCard, pointsToAdd)
          printTable(curDeck.pull(), iter - 1, totalPoints + pointsToAdd)
        } else {
          println("Total points: " + totalPoints.toString())
          totalPoints
        }
      }

      printTable(deck, n, 0)
    }

    lazy val all21: List[List[Card]] = {
      val allCombinBuf: Buffer[List[Card]] = Buffer()

      def combFinder(
          selectList: List[Card],
          curList: List[Card],
          curPoints: Int
      ): Unit = {
        if (curPoints == 21) allCombinBuf.append(curList)
        else if (curPoints < 21) {
          for (anotherCard <- selectList) {
            val newPoints = curPoints + pointsForCard(anotherCard, curPoints)
            val deckFilter = (
                (x: Card) =>
                  !x.equals(anotherCard) && pointsMap(x) + newPoints <= 21
            )
            combFinder(
              selectList.filter(deckFilter),
              curList :+ anotherCard,
              newPoints
            )
          }
        }
      }

      combFinder(deck.cardsField, List(), 0)
      val begList: List[List[Card]] = List(List())
      allCombinBuf
        .foldLeft(begList)((x: List[List[Card]], y: List[Card]) => y +: x)
        .init
    }

    private def pointsForCard(card: Card, prevPoints: Int): Int = {
      if (card.fId.toInt == Ace.toInt) {
        if (prevPoints + 11 <= 21) prevPoints + 11
        else prevPoints + 1
      } else pointsMap(card)
    }

    def first21(): Int = {
      val fst = all21.head
      var totalPoints = 0
      for (x <- fst) {
        val forCard = pointsForCard(x, totalPoints)
        printCard(x, forCard)
        totalPoints += forCard
      }
      totalPoints
    }

    def deckSize: Int = deck.size

  }

  object Blackjack {
    def apply(numOfDecks: Int) = {
      assert(numOfDecks > 0)
      if (numOfDecks == 0) new Blackjack(Deck())
      else {
        val randCards = {
          for (x <- 1 to numOfDecks) yield Random.shuffle(Deck.standardDeck)
        }.flatten.toList
        new Blackjack(Deck(randCards))
      }
    }

    def specificDeck(myDeck: Deck) = new Blackjack(myDeck)
  }
}
