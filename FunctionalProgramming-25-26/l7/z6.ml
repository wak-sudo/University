
let singleton (x : 'a) : 'a Seq.t =
  let rec s () = Seq.Cons (x, fun () -> Seq.Nil) in s

module SBT(State : sig type t end) : sig
    type 'a t
    val return : 'a -> 'a t
    val bind : 'a t -> ('a -> 'b t) -> 'b t
    val fail : 'a t
    val flip : bool t
    val get : State.t t
    val put : State.t -> unit t
    val run : State.t -> 'a t -> 'a Seq.t
end = struct
    type 'a t = State.t -> ('a * State.t) Seq.t
     
    let return (x: 'a) = fun (y : State.t) -> singleton (x, y)

    let bind (m : 'a t) (f : 'a -> 'b t) =
        fun (s : State.t) ->
            let results_m = m s in
            Seq.flat_map (fun (someRes, someState) ->
            (f someRes) someState) results_m

    let fail = fun (s: State.t) -> Seq.empty

    let flip = fun (s : State.t) -> List.to_seq [(true, s); (false, s)]

    (*/ State.t t = State.t -> (State.t * State.t) Seq.t /*)
    let get (s : State.t) = singleton (s, s) 

    (*/ unit t =  State.t -> (unit * State.t) Seq.t /*)
    let put (s : State.t) =  fun (sTwo : State.t) -> singleton ((), s)

    let run (s : State.t) (v : 'a t) : 'a Seq.t = 
      Seq.map (fun (result, _state) -> result) (v s)
end

    


