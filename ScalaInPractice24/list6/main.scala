
import pizzera._
import orders._

package pizzera {

  sealed abstract class Type(val name: String, val price: Double)
  sealed abstract class Toppings(val name: String, val price: Double)
  sealed abstract class Meat(val name: String, val price: Double)
  sealed abstract class Drink(val name: String, val price: Double)

  sealed abstract class Size(val name: String)
  sealed abstract class Crust(val name: String)
  sealed abstract class Discounts(val name: String)

  case object Margarita extends Type("Margarita", 5)
  case object Pepperoni extends Type("Pepperoni", 6.5)
  case object Funghi extends Type("Funghi", 7)

  case object small extends Size("small")
  case object regular extends Size("regular")
  case object large extends Size("large")

  case object thin extends Crust("thin")
  case object thick extends Crust("thick")

  case object ketchup extends Toppings("ketchup", 0.5)
  case object garlic extends Toppings("garlic", 0.5)

  case object salami extends Meat("salami", 1)

  case object lemonade extends Drink("lemonade", 2)

  case object student extends Discounts("student")
  case object senior extends Discounts("senior")

  case class Pizza(
      pizzaType: Type,
      size: Size,
      crust: Crust,
      extraMeat: Option[Meat],
      extraTopping: List[Option[Toppings]]
  ) {

    override def toString() = {
      val header = "Pizza:\n"
      val typeStr = "Type: " + pizzaType.name + "\n"
      val sizeStr =  "Size: " + size.name + "\n"
      val curstStr = "Curst: " + crust.name + "\n"
      val meatStr =  "Extra meat: " +
        (extraMeat match {
          case Some(obj) => obj.name
          case None      => ""
        }) + "\n"

      val toppingStrs = "Extra topping: " + (for (optObj <- extraTopping) yield {
        optObj match {
          case None        => ""
          case Some(value) => value.name
        }
      }).mkString(" ")

      header + typeStr + sizeStr + curstStr + meatStr + toppingStrs
    }

    val price: Double = {
      val sizeMulti = size match {
        case `large`   => 1.50
        case `regular` => 1.0
        case `small`   => 0.9
      }

      val extraMeatPrice = extraMeat match {
        case Some(value) => value.price
        case None        => 0
      }

      val toppingsPrice = (for (optObj <- extraTopping) yield {
        optObj match {
          case None        => 0
          case Some(value) => value.price
        }
      }).sum

      val basePrice = pizzaType.price

      val totalPrice = sizeMulti * (basePrice + toppingsPrice + extraMeatPrice)

      totalPrice
    }
  }

}

package orders {
  case class Order(
      name: String,
      address: String,
      phone: String, // mandatory validated phone-number (hint: regex)
      pizzas: List[pizzera.Pizza],
      drinks: List[pizzera.Drink],
      discount: Option[pizzera.Discounts], // optional value
      specialInfo: String
  ) {

    def phoneNumIsValid: Boolean = {
      if (phone.length() != 9) false
      else {
        val isInvalid = (for (charac <- phone)
          yield { charac.toInt >= '0'.toInt && charac.toInt <= '9'.toInt })
          .contains(false)
        return !isInvalid
      }
    }

    require(phoneNumIsValid)

    override def toString() = {
        val header = "Order:\n"
        val nameStr = "Name: " + name + "\n"
        val adrStr = "Address: " + address + "\n"
        val phoneStr = "Phone: " + phone + "\n"
        val pizzasStr = "Pizzas:\n\n" + 
        (for (onePizza <- pizzas)
            yield (onePizza.toString())).mkString("\n\n") + "\n\n"
        

        val drinksStr = "Drinks: " + 
        (for (oneDrink <- drinks)
            yield (oneDrink.name)).mkString(" ") + '\n'

        val discountStr = "Discount: " + 
        (discount match {
            case None        => "None"
            case Some(value) => value.name
        }) + "\n"

        val specialStr = "Special info: " + specialInfo + "\n"

        header + nameStr + adrStr + phoneStr + pizzasStr + drinksStr + discountStr + specialStr
    }

    def extraMeatPrice: Double = {
      (for (onePizza <- pizzas) yield (onePizza.extraMeat match {
        case None        => 0
        case Some(value) => value.price
      })).sum
    }

    def pizzasPrice: Double =
      (for (onePizza <- pizzas) yield (onePizza.price)).sum

    def drinksPrice: Double =
      (for (oneDrink <- drinks) yield (oneDrink.price)).sum

    def priceByType(pizzaType: pizzera.Type): Double =
      (for (onePizza <- pizzas) yield {
        if (pizzaType.name == onePizza.pizzaType.name) onePizza.price else 0.0
      }).sum

    val price: Double = {
      discount match {
        case None => pizzasPrice + drinksPrice
        case Some(value) => {
          value match {
            case pizzera.student => 0.95 * pizzasPrice + drinksPrice
            case pizzera.senior  => 0.93 * (pizzasPrice + drinksPrice)
          }
        }
      }
    }
  }
}

object Main extends App
{
    val fstPizza = Pizza(Margarita, regular, thin, Some(salami),  List(Some(ketchup)))
    val sndPizza = Pizza(Pepperoni, large, thick, None, List(Some(garlic)))

    println("Fst pizza price: "+ fstPizza.price.toString())
    println("Snd pizza price: "+ sndPizza.price.toString())

    val fstOrder = Order("Important order", "Joliot Curie 15", "123654987", List(fstPizza, sndPizza), List(lemonade), Some(senior), "Knock")

    println(fstOrder.toString())

    println("extraMeatPrice: " + fstOrder.extraMeatPrice.toString())
    println("pizzasPrice: " + fstOrder.pizzasPrice.toString())
    println("drinksPrice: " + fstOrder.drinksPrice.toString())
    println("priceByType (Margarita): " + fstOrder.priceByType(Margarita).toString())
    println("Total price: " + fstOrder.price.toString())
}
