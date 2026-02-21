import Data.Char (toUpper, toLower)
import System.IO

echoLower :: IO ()
echoLower = do
    eof <- isEOF
    if eof
        then return ()
        else do
            c <- getChar
            putChar (toUpper c)
            echoLower
    
main :: IO ()
main = echoLower
