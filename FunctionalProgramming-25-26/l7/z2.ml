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

module RS : sig include RandomMonad
    val run : int -> 'a t -> 'a
end =
struct
    type 'a t = int -> 'a * int
    
    let return (x : 'a) : 'a t = fun seed -> (x, seed)

    let bind (m : 'a t) (f: 'a -> 'b t) : 'b t =
       fun seed_in ->
        let (a, seed_mid) = m seed_in in
        let newM = f a in
        newM seed_mid
    
    let random : int t = fun seedIn ->
        let tempSeed = (16807 * (seedIn mod 127773)) - (2836 * (seedIn / 127773)) in
        let seedOut = if tempSeed > 0 then tempSeed
        else tempSeed + 2147483647 in
        (seedOut, seedOut)

    let run (seedIn : int) (m : 'a t) : 'a =
        let (result, _) = m seedIn in result   

end


module TestShuffle = Shuffle(RS)

RS.run 42 (TestShuffle.shuffle [1;2;3;4;5]) 
