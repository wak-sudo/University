import plugins._

object Main extends App {
  object Actions {

    val actionA: Pluginable = new Pluginable
      with Shortening
      with Doubling
      with SingleSpacing

    val actionB : Pluginable = new Pluginable
        with Doubling
        with Shortening
        with NoSpacing 
    
    val actionC : Pluginable = new Pluginable with Doubling with LowerCasing

    val actionD : Pluginable = new Pluginable with Rotating with DuplicateRemoval

    val actionE : Pluginable = new Pluginable 
        with Reverting
        with Doubling
        with Shortening
        with NoSpacing

    val actionF : Pluginable = new Pluginable
        with Rotating

    //val actionG : Pluginable = ???
  }

  println(Actions.actionA.apply("Ania  ma kota")) // "Ana m koa"
  println(Actions.actionB.apply("Ania  ma kota")) // "Aiimkkt"
  println(Actions.actionC.apply("Ania  ma kota")) // "anniaa   maa kkotta"
  println(Actions.actionD.apply("Ania  ma kota")) // "Aiimkkt" (in reverse)
  println(Actions.actionE.apply("Ania  ma kota")) // ""
  println(Actions.actionF.apply("Ania  ma kota"))
}
