{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

(|>|) :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
-- pozwalający na przekierowanie wyjścia jednego transformatora na wejście drugiego.

(|>|) (WriteS o tW) (ReadS tR) =
    Return (tR (Just o))
