module type RandomMonad = sig
    type 'a t
    val return : 'a -> 'a t
    val bind : 'a t -> ('a -> 'b t) -> 'b t
    val random : int t
end

module Shuffle(R : RandomMonad) : sig
    val shuffle : 'a list -> 'a list R.t
end = struct open R

let select (idx : int) (lst : 'a list) =
    let rec selectHelp (idx : int) (lst : 'a list) (tempLst : 'a list) = 
        if lst = [] then failwith "empty list"
        else if idx = 0 then (List.hd lst, tempLst @ (List.tl lst)) 
        else selectHelp (idx-1) (List.tl lst) ((List.hd lst) :: tempLst)
    in selectHelp idx lst []
        
let pickRandom lst len =
    match lst with
    | [] -> failwith "error"
    | _ ->
        R.bind R.random (fun index ->
        let safe_index = index mod len in
        let result = select safe_index lst in
        R.return result)

let shuffle lst =
    let rec shuffleHelp lst len =
        match lst with
        | [] -> R.return []
        | _ ->
            R.bind (pickRandom lst len) (fun (el, rest) ->
            R.bind (shuffleHelp rest (len-1)) (fun shuffledRest ->
            R.return (el :: shuffledRest)))
    in shuffleHelp lst (List.length lst)

end
