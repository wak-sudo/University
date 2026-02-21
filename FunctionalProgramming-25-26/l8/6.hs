{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}

import System.IO

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

catchOutput :: StreamTrans i o a -> StreamTrans i b (a, [o])
catchOutput st = collect st []
    where
        collect :: StreamTrans i o a -> [o] -> StreamTrans i b (a, [o])
        collect (Return a) acc = Return (a, reverse acc)
        collect (ReadS next) acc = ReadS $ \mi ->
            collect (next mi) acc
        collect (WriteS o next) acc = collect next (o : acc)