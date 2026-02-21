{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}

import Data.Char (toLower)

import Distribution.Simple.Program.HcPkg (list)
data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

listTrans :: StreamTrans i o a -> [i] -> ([o], a)
listTrans trans input =
    case trans of
        Return a -> ([], a)
        ReadS f ->
            case input of
                [] -> listTrans (f Nothing) []
                (x : xs) -> listTrans (f (Just x)) xs
        WriteS o nextTrans ->
            let (outputTail, result) = listTrans nextTrans input
            in (o : outputTail, result)

toLowerTrans :: StreamTrans Char Char ()
toLowerTrans =
    ReadS $ \mchar ->
        case mchar of
            Nothing -> Return ()
            Just c -> WriteS (toLower c) toLowerTrans

main = putStr $ take 3 $ fst $ listTrans toLowerTrans ['A', 'A'..]       