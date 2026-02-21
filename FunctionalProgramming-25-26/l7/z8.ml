type symbol = string

type ’v term =
    | Var of ’v
    | Sym of symbol * ’v term list

module type Monad = sig
    type 'a t

    val return : 'a -> 'a t
    val bind   : 'a t -> ('a -> 'b t) -> 'b t

end = struct

    type 'a t = 'a
    
    (*/ wprowadzenie zmiennej /*)
    let return (x : 'a) : 'a term = Var x

    (*/ podstawienie pod zmienne /*)
    let rec bind (m : 'a term) (f : 'a -> 'b term) : 'b term =
        match m with
        | Var x -> f x
        | Sym (sym, terms) -> Sym (sym, List.map (fun t -> bind t f) terms)

end
