module type Monad = sig
    type 'a t
    val return : 'a -> 'a t
    val bind: 'a t -> ('a -> 'b t) -> 'b t
end

module Id : sig
  include Monad
end = struct
  type 'a t = 'a

  let return x = x
  let bind m f = f m
end

module LazyM : sig
  include Monad
end = struct
  type 'a t = unit -> 'a

  let return x = fun () -> x
  let bind m f = f (m ())
end
