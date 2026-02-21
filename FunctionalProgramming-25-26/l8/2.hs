{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}

import Data.Char (toLower)
import System.IO

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

toLowerTrans :: StreamTrans Char Char ()
toLowerTrans =
    ReadS $ \mchar ->
        case mchar of
            Nothing -> Return ()
            Just c -> WriteS (toLower c) toLowerTrans

runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (Return x) = return x
runIOStreamTrans (WriteS o c) = do
    putChar o
    runIOStreamTrans c
runIOStreamTrans(ReadS k) = do
    eof <- isEOF
    if eof
        then runIOStreamTrans (k Nothing)
        else do
            c <- getChar
            runIOStreamTrans (k (Just c))

main = runIOStreamTrans toLowerTrans