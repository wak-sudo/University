//import java.math.BigDecimal
import scala.language.implicitConversions
import money._

package object money {
  val defaultCurrencyString: Map[Currency, String] = Map(
    PolishCurrency -> "PLN",
    EUcurrency -> "EUR",
    UScurrency -> "USD"
  )

  sealed trait Currency {
    override def toString(): String = {
      val res = defaultCurrencyString get this
      res match {
        case None =>
          throw new RuntimeException(
            "Invalid symbol entry request for currency."
          )
        case Some(value) => value
      }

    }
  }

  case object PolishCurrency extends Currency
  case object UScurrency extends Currency
  case object EUcurrency extends Currency

  sealed trait Symbol

  case object PLN extends Symbol
  case object EUR extends Symbol
  case object USD extends Symbol
  case object $ extends Symbol
  case object zl extends Symbol

  // euro symbol is an invalid character.

  val conversion: Map[(Currency, Currency), BigDecimal] = Map(
    (PolishCurrency, EUcurrency) -> BigDecimal("0.23"),
    (EUcurrency, PolishCurrency) -> BigDecimal("4.25"),
    (PolishCurrency, UScurrency) -> BigDecimal("0.25"),
    (UScurrency, PolishCurrency) -> BigDecimal("3.91"),
    (EUcurrency, UScurrency) -> BigDecimal("1.08"),
    (UScurrency, EUcurrency) -> BigDecimal("0.92")
  )

  val symbolToCurrency: Map[Symbol, Currency] = Map(
    PLN -> PolishCurrency,
    EUR -> EUcurrency,
    USD -> UScurrency,
    $ -> UScurrency,
    zl -> PolishCurrency
  )

  def getCurrency(sym: Symbol): Currency = {
    val res = symbolToCurrency get sym
    res match {
      case None =>
        throw new RuntimeException(
          "Invalid entry request for: " + sym.toString()
        )
      case Some(value) => value
    }
  }

  case class CurrencyConverter(
      conversion: Map[(Currency, Currency), BigDecimal]
  ) {
    def convert(from: Currency, to: Currency): BigDecimal = {
      if (
        from.toString() == to.toString()
      ) // that actually should be types but that complicated.
        1
      else {
        val res = conversion get (from, to)
        res match {
          case None =>
            throw new RuntimeException(
              "Invalid entry request for: " + from.toString() + " to: " + to
                .toString()
            )
          case Some(value) => value
        }
      }
    }
  }

  // Why can't I make it implicit?
  implicit val impCurrenctConv : CurrencyConverter = CurrencyConverter(conversion)

  case class Money(amount: BigDecimal, currency: Currency)(implicit
      currencyConverter: CurrencyConverter
  ) {

    def +(other: Money): Money = Money(
      this.amount + other.amount * currencyConverter
        .convert(other.currency, this.currency),
      this.currency
    )

    def -(other: Money): Money = Money(
      this.amount - other.amount * currencyConverter
        .convert(other.currency, this.currency),
      this.currency
    )

    def *(mult: BigDecimal): Money = Money(this.amount * mult, this.currency)

    def >(other: Money): Boolean =
      this.amount > (other.amount * currencyConverter.convert(
        other.currency,
        this.currency
      ))

    def <(other: Money): Boolean =
      this.amount < (other.amount * currencyConverter.convert(
        other.currency,
        this.currency
      ))

    def as(sym: Symbol): Money = Money(
      this.amount * currencyConverter.convert(this.currency, getCurrency(sym)),
      this.currency
    )

    override def toString(): String =
      amount.toString() + " " + currency.toString()
  }

  //implicit 

  implicit def double2CurFun(num: Double): (Symbol => Money) =
    (sym: Symbol) =>
      Money(BigDecimal(num), getCurrency(sym))(CurrencyConverter(conversion))
}

object Main extends App {

  val sum1: Money = 100.01 (USD) + 200 (EUR) // result in dollars
  val sum2: Money = 100.01 (zl) + 200 ($) // result in złoty (most
  val sum3: Money = 5 (zl) + 3 (PLN) + 20.5 (USD) // result in złoty
  println(sum1.toString())
  println(sum2.toString())
  println(sum3.toString())

  println()

  val sub: Money = 300.01 (USD) - 200 (EUR)
  println(sub.toString())

  println()

  val mult1: Money = 30 (zl) * 20 // result in złoty
  val mult2: Money = 20 ($) * 11 // result in dollars
  println(mult1.toString())
  println(mult2.toString())

  println()

  val conv1: Money = 150.01 (USD) as PLN // converts to złoty
  val conv2: Money = 120.01 (USD) as EUR // converts to euro

  println(conv1.toString())
  println(conv2.toString())

  println()

  val compare1: Boolean = 300.30 (USD) > 200 (EUR)
  val compare2: Boolean = 300.30 ($) < 200 (EUR)

  println(compare1.toString())
  println(compare2.toString())

}
