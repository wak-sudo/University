type formula =
    | FALSE
    | VAR of string
    | IMPLIES of formula * formula

let rec string_of_formula f =
    match f with
    | FALSE -> "F"
    | VAR s -> s
    | IMPLIES (leftF, rightF) -> 
        begin match leftF with
        | VAR s -> s ^ " -> " ^ (string_of_formula rightF)
        | FALSE -> "F -> " ^ (string_of_formula rightF)
        | _ -> "(" ^ (string_of_formula leftF) ^ ") -> " ^ (string_of_formula rightF)
        end

let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f)

type theorem = formula list * formula

let assumptions ((assum, consq) : theorem) = assum  

let consequence ((assum, consq) : theorem) = consq

let pp_print_theorem fmtr thm =
  let open Format in
  pp_open_hvbox fmtr 2;
  begin match assumptions thm with
  | [] -> ()
  | f :: fs ->
    pp_print_formula fmtr f;
    fs |> List.iter (fun f ->
      pp_print_string fmtr ",";
      pp_print_space fmtr ();
      pp_print_formula fmtr f);
    pp_print_space fmtr ()
  end;
  pp_open_hbox fmtr ();
  pp_print_string fmtr "⊢";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ()

let rec formulaSyntaxEqual f1 = fun f2 ->
    match (f1, f2) with
    | FALSE, FALSE -> true
    | VAR s1, VAR s2 -> s1 = s2
    | IMPLIES (assum1, res1), IMPLIES (assum2, res2) ->
        (formulaSyntaxEqual assum1 assum2) &&
        (formulaSyntaxEqual res1 res2)
    | _ -> false

let by_assumption f : theorem = ([f], f) 

let imp_i f thm : theorem = (List.filter (fun x -> not ((formulaSyntaxEqual f) x)) (assumptions thm),  
                            IMPLIES (f, consequence thm))

let imp_e th1 th2 : theorem = 
    match (th1, th2) with
    | (assum1, IMPLIES (assumImp, resImp)), (assum2, conseq) 
    | (assum1, conseq), (assum2, IMPLIES (assumImp, resImp))
        -> if formulaSyntaxEqual assumImp conseq then (assum1 @ assum2, resImp) else failwith "Wrong deduction"
    | _ -> failwith "Wrong deduction"
        
let bot_e f thm : theorem = 
    match thm with
    | (assum, FALSE) -> (assum, f)
    | _ -> failwith "Wrong deduction"

type goal = ((string * formula) list) * formula

type incomplete = 
    | SoleGoal of goal
    | ImpI of goal * incomplete
    | ImpE of incomplete * goal * incomplete
    | BotE of goal * incomplete
    | Complete of theorem

type 'a context =
    | Root
    | Top of 'a context * goal * incomplete
    | Left of 'a context * goal * incomplete
    | Right of incomplete * goal * 'a context

type 'zipper = 'a context * incomplete


let go_left
let go_right
let go_down
let go_up

