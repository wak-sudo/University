type 'a zlist = 'a list * 'a list

let of_list (lst : 'a list) = 
    match lst with
    | [] -> ([], [])
    | x :: xs -> (lst, [])

let to_list (lst : 'a zlist) =
    (List.rev (snd lst)) @ (fst lst)

let eleme (lst : 'a zlist) = 
    match (snd lst) with
    | [] -> None
    | x :: _ -> Some(x)

let move_left (lst : 'a zlist) = 
    match (snd lst) with
    | [] -> lst
    | x :: xs -> (x :: (fst lst), xs)

let move_right (lst : 'a zlist) = 
    match (fst lst) with
    | [] -> lst
    | x :: xs -> (xs, x :: (snd lst))

let insert (item : 'a) (lst : 'a zlist) =
    (fst lst, item :: (snd lst))

let remove (lst : 'a zlist) =
    match (fst lst) with
    | [] -> lst
    | x :: xs -> (xs, snd lst) 
