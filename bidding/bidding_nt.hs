import Bridge
import Data.Char (digitToInt)

type Hand = (HCP, HCP, Tricks)
type HCP = Int
type Tricks = Int
type Level = Int
type BiddingSequence = (HCP, HCP, [Level])
type Loss = Int

main :: IO ()
main = print . evalSystem . getHands =<< readFile "Library.asc"

getHands :: String -> [Hand]
getHands = map getHand . lines

getHand :: String -> Hand
getHand xs = (hcphigher, hcplower, tricks)
  where
    calchcp = sum . map atohcp
    cards = take 68 xs
    hcp1 = calchcp $ words cards !! 1
    hcp2 = calchcp $ words cards !! 3
    hcphigher = if hcp1 >= hcp2 then hcp1 else hcp2
    hcplower = if hcp1 >= hcp2 then hcp2 else hcp1
    tricks = digitToInt (xs !! 69)

evalSystem :: [Hand] -> Loss
evalSystem = sum . map eval

eval :: Hand -> Loss
eval (hcp1, hcp2, tricks) = loss (bidding hcp1 hcp2) tricks

loss :: Level -> Tricks -> Loss
loss level tricks = downs + loses
  where
    downs = if level > 0 then max (level + 6 - tricks) 0 else 0
    loses  = gamelose + partiallose
    gamelose = if (level < 3 && tricks >= 9) then 1 else 0
    partiallose = if (level < 1 && tricks >= 7) then 1 else 0

biddingSystem :: [Level] -> HCP
biddingSystem [3] = 24
biddingSystem (3:xs) = 25 - biddingSystem xs
biddingSystem [2] = 21
biddingSystem (2:xs) = 24 - biddingSystem xs
biddingSystem [1] = 15
biddingSystem _ = undefined

bidding :: HCP -> HCP -> Level
bidding hcp1 hcp2 = takeLevel biddingSequence
  where
    biddingSequence = until isPass bid (hcp1, hcp2, [])
    takeLevel (_, _, xs) = if length xs >= 2 then xs !! 1 else 0
    isPass (_, _, xs) = xs /= [] && head xs == 0

bid :: BiddingSequence -> BiddingSequence
bid (hcp1, hcp2, xs) = if nextxs /= [] then (hcp2, hcp1, head nextxs) else (hcp2, hcp1, 0:xs)
  where
    currentLevel = if xs == [] then 0 else head xs
    nextxs = [i:xs | i <- [3,2..currentLevel+1], hcp1 >= biddingSystem (i:xs)]
