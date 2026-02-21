let rec merge s1 s2 =
  match s1, s2 with
  | [], l | l, [] -> l
  | x :: xs, y :: ys ->
      if x <= y then x :: merge xs (y :: ys)
      else y :: merge (x :: xs) ys
