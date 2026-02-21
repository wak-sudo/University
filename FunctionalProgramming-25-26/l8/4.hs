{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

runCycle :: StreamTrans a a b -> b
runCycle st = loop st []
    where
        loop (Return result) _ = result
        loop (ReadS next) (x : xs) =     
            let newTrans = next (Just x)
            in loop newTrans xs
        loop (ReadS next) [] =       
            let newTrans = next Nothing
            in loop newTrans []
        loop (WriteS output nextTrans) lst =
            loop nextTrans (lst ++ [output]) 