let rec merge s1 s2 =
    let rec helper s1 s2 acc =
      match s1, s2 with
      | [], l | l, [] -> List.rev_append acc l
      | x :: xs, y :: ys ->
          if x <= y then (helper xs s2 (x :: acc))
          else (helper s1 ys (y :: acc))
    in helper s1 s2 []
