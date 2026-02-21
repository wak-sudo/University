type rational = int * int

type rationalNode = rational * rational * rational

type rational_tree = Node of rational_tree Lazy.t * rationalNode * rational_tree Lazy.t

let rec gcd a b =
  if b = 0 then a else gcd b (a mod b)  

(*/let rec reduce (r : rational) =
  let a = (fst r) in let b = (snd r) in
  let curGcd = gcd a b in
  (a / curGcd, b/ curGcd)/*)

let getNodeRational (r1 : rational) (r2 : rational) =
    match r1, r2 with
    | (a, b), (c ,d) -> (a+c, b+d)

let rec calculateLeftNode (parent : rationalNode) : rational_tree = 
  match parent with
  | (_, curValue, leftSide) ->
    let newValue = getNodeRational curValue leftSide in
    let r : rationalNode = (leftSide, newValue, curValue) in
  Node (lazy (calculateLeftNode r), r, lazy(calculateRightNode r))

and calculateRightNode (parent : rationalNode) : rational_tree = (*/ and pozwala żeby funkcje siebie widziały/*)
  match parent with
  | (rightSide, curValue, _) ->
    let newValue = getNodeRational curValue rightSide in
    let r : rationalNode = (curValue, newValue, rightSide) in
  Node (lazy (calculateLeftNode r), r, lazy(calculateRightNode r))

let rationalTreeStart : rational_tree = 
  let l = (0, 1) in
  let r = (1, 0) in
  let v = (1, 1) in
  let node = (l, v, r) in
  Node(lazy (calculateLeftNode node), node, lazy(calculateRightNode node))