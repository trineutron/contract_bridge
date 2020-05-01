import Bridge
import Data.Char

main :: IO ()
main = print . length . filter game . map hcptrick . lines =<< readFile "Library.asc"

game :: (Int, Int) -> Bool
game (hcp, trick)
  | hcp >= 25 && trick >= 9 = True
  | otherwise = False

hcptrick :: String -> (Int, Int)
hcptrick xs = (calchcps xs, tricks xs)

tricks :: String -> Int
tricks xs = digitToInt $ xs !! 69

calchcps :: String -> Int
calchcps xs = totalhcp (cards !! 1) + totalhcp (cards !! 3)
  where
    cards = words $ take 67 xs

totalhcp :: String -> Int
totalhcp = sum . map atohcp
