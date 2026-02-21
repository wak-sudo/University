let fib_f fib n =
  if n <= 1 then n
  else fib (n-1) + fib (n-2)

let rec fix_with_limit limit f x =
  if limit = 0 then failwith "Depth limit exceeded" else
    f (fix_with_limit (limit-1) f) x

let fibLimit limit = fix_with_limit limit fib_f

let rec fix_memo f =
  let lookup = Hashtbl.create 128 in
  let rec g x =
    match Hashtbl.find_opt lookup x with
    | Some x -> x
    | None -> let result = f g x in Hashtbl.add lookup x result; result
  in g

let fibMemo = fix_memo fib_f