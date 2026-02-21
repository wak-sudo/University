module type Monad = sig
  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t
end

let singleton (x : 'a) : 'a Seq.t =
  fun () -> Seq.Cons (x, fun () -> Seq.Nil)

module BT : sig
  include Monad

  val fail : 'a t
  val flip : bool t

  val run : 'a t -> 'a Seq.t
end = struct
  type 'a t = 'a Seq.t

  let return x = singleton x
  let rec bind m f = Seq.concat_map f m

  let fail = Seq.empty
  let flip = List.to_seq [ true; false ]

  let run m = m
end

type 'a regexp =
    | Eps
    | Lit of ('a -> bool)
    | Or of 'a regexp * 'a regexp
    | Cat of 'a regexp * 'a regexp
    | Star of 'a regexp

let ( +% ) r1 r2 = Or(r1, r2)
let ( *% ) r1 r2 = Cat(r1, r2)

let rec match_regexp (exp : 'a regexp) (lst : 'a list) : 'a list option BT.t =
  match exp with
  | Eps -> BT.return None
  | Lit p ->
      (match lst with
       | [] -> BT.fail
       | x :: xs -> if p x then BT.return (Some xs) else BT.fail)
  | Or (r1, r2) ->
      BT.bind (match_regexp r1 lst) (function
        | None -> BT.bind (match_regexp r2 lst) (function
            | None -> BT.fail
            | Some rest -> BT.return (Some rest))
        | Some rest -> BT.return (Some rest))
  | Cat (r1, r2) ->
      BT.bind (match_regexp r1 lst) (function
        | None -> BT.fail
        | Some rest -> match_regexp r2 rest)
  | Star r ->
      let rec helper inp =
        BT.bind (match_regexp r inp) (function
          | None -> BT.return None
          | Some rest -> BT.bind (helper rest) 
                (function
                    | None -> BT.fail
                    | Some restTwo -> if restTwo = rest then BT.fail else BT.return (Some [])))
       in helper lst


jeżeli mam star, to biorę każdy podział i sprawdzam, czy czy podsłowa też można skonstryować

+% to musi być or

*% musi dokonać n podziałów i zobaczyć czy jedno pasuje

jeżeli jest samo lit to musi zachodzić dla każdego elementu


