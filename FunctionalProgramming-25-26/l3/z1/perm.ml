module Make (Key : OrderedType) : S with type key = Key.t = struct
  module TMap = Map.Make(Key)

    type key = Key.t

    type t = key TMap.t * key TMap.t

    let id : t = (TMap.empty, TMap.empty)

    let apply ((f, _) : t) (x : key) : key =
        match TMap.find_opt x f with
        | None -> x
        | Some y -> y

    let invert ((f, g) : t) : t = (g, f)

    let custom_update (key : key) (new_value : key) (m : key TMap.t) : key TMap.t =
        let m = TMap.remove key m in
        if key <> new_value then
          TMap.add key new_value m
        else m

    let swap (keyOne : key) (keyTwo : key) : t =
        if keyOne = keyTwo then id
        else 
        let f = (TMap.add keyOne keyTwo TMap.empty) in
        let f = (TMap.add keyTwo keyOne f) in
        (f, f)

    let invert_map m =
        TMap.fold (fun k v acc -> TMap.add v k acc) m TMap.empty

    let compose (pOne : t) (pTwo : t) : t =
        let predicate = fun (x : key) (value : key) -> x <> value in
        let composition = TMap.filter predicate (TMap.map (fun x -> apply pOne x) (fst pTwo)) in
        (composition, invert_map composition)

    let compare ((f1, _) : t) ((f2, _) : t) : int =
        TMap.compare Key.compare f1 f2
    
end
