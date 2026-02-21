module R = Random

let () = R.self_init ()

let rec generate_n_random_numbers (n : int) (max_val : int) : int list =
  if n <= 0 then
    []
  else
    let random_num = R.int (max_val + 1) in
    random_num :: generate_n_random_numbers (n - 1) max_val

let generate_random_monotonic_list (n : int) (max_val : int) : int list =
  let random_list = generate_n_random_numbers n max_val in
  List.sort compare random_list

let rec mergeOne s1 s2 =
  match s1, s2 with
  | [], l | l, [] -> l
  | x :: xs, y :: ys ->
      if x <= y then x :: merge xs (y :: ys)
      else y :: merge (x :: xs) ys

(* tail rec *)

let rec mergeTwo s1 s2 =
    let rec helper s1 s2 acc =
      match s1, s2 with
      | [], l | l, [] -> List.rev_append acc l
      | x :: xs, y :: ys ->
          if x <= y then (helper xs s2 (x :: acc))
          else (helper s1 ys (y :: acc))
    in helper s1 s2 []

let time_function f s1 s2 =
  let start_time = gettimeofday () in
  let _ = (f s1 s2)
  let end_time = gettimeofday () in
  end_time -. start_time

let () =
  let s1 = generate_random_monotonic_list 100 1000
  let s2 = generate_random_monotonic_list 100 1000
  let time_f1 = time_function mergeOne s1 s2 in
  Printf.printf "\nCzas wykonania F1: %.4f sekund.\n\n" time_f1;

  let time_f2 = time_function mergeTwo s1 s2 in
  Printf.printf "\nCzas wykonania F2: %.4f sekund.\n" time_f2;
