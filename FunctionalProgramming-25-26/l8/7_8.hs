{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use lambda-case" #-}
{-# HLINT ignore "Use second" #-}

import Data.Char (chr, ord)
import System.IO

data BF
    = MoveR -- >
    | MoveL -- <
    | Inc -- +
    | Dec -- -
    | Output -- .
    | Input -- ,
    | While [BF] -- [ ]

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

charToBf :: Char -> Maybe BF
charToBf c = case c of
    '>' -> Just MoveR
    '<' -> Just MoveL
    '+' -> Just Inc
    '-' -> Just Dec
    '.' -> Just Output
    ',' -> Just Input
    _ -> Nothing

brainfuckParser :: StreamTrans Char BF ()
brainfuckParser = ReadS $ \mi -> 
    case mi of
        Nothing -> Return ()
        Just c -> case c of
            '[' -> case parseLoop [] of
                Return x -> WriteS (While x) brainfuckParser
                ReadS f -> ReadS $ \m -> WriteS (While (f m)) brainfuckParser
            ']' -> error "Unexpected closing bracket"
            _ -> case charToBf c of
                Just bf -> WriteS bf brainfuckParser
                Nothing -> brainfuckParser
    
    where
    
    parseLoop :: [BF] -> StreamTrans Char BF [BF]
    parseLoop acc = ReadS $ \mc ->
        case mc of
            Nothing -> error "No closing bracket"
            Just c -> case c of
                '[' -> parseLoop acc 
                ']' -> Return (reverse acc)
                _ -> case charToBf c of
                        Just bf -> parseLoop (bf : acc)
                        Nothing -> parseLoop acc


type Tape = ([Integer], [Integer])

-- TAPE OPERATIONS

moveLeft :: Tape -> Tape
moveLeft tape =
    case snd tape of
    [] -> (0 : fst tape, [])
    x : xs -> (x : fst tape, xs)

moveRight :: Tape -> Tape
moveRight tape =
    case fst tape of
    [] -> ([], 0 : snd tape)
    x : xs -> (xs, x : snd tape)

inc :: Tape -> Tape
inc tape =
    case snd tape of
    [] -> error "inc error"
    x : xs -> (fst tape, (x+1) : snd tape)

dec :: Tape -> Tape
dec tape =
    case snd tape of
    [] -> error "dec error"
    x : xs -> (fst tape, (x-1) : snd tape)

writeTape :: Tape -> Char -> Tape
writeTape tape c =
    case snd tape of
    [] -> error "writeTape error"
    x : xs -> (fst tape, toInteger (ord c) : snd tape)

readTape :: Tape -> Integer
readTape tape =
    case snd tape of
    [] -> error "readTape error"
    x : xs -> x

-- EVAL

evalBF :: Tape -> BF -> StreamTrans Char Char Tape
evalBF tape token =
    case token of
    MoveR -> Return $ moveRight tape
    MoveL -> Return $ moveLeft tape
    Inc -> Return $ inc tape
    Dec -> Return $ dec tape
    Output -> WriteS (chr $ fromInteger $ readTape tape) (Return tape)
    Input -> ReadS $ \k ->
        case k of
            Nothing -> error "read error" -- ?
            Just x -> Return (writeTape tape x) 
    While bfLst -> if readTape tape /= 0 then
        evalBFBlock tape bfLst
        else Return tape

evalBFBlock :: Tape -> [BF] -> StreamTrans Char Char Tape
evalBFBlock tape block =
    case block of
        [] -> Return tape
        x : xs ->
            case evalBF tape x of
                Return newTape -> evalBFBlock newTape xs
                WriteS c _ -> WriteS c (evalBFBlock tape xs)
                ReadS f -> ReadS $ \mi -> 
                    case f mi of
                    Return newTape -> evalBFBlock newTape xs
                    _ -> error "should not happen"
main = return ()